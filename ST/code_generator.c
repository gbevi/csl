#include "code_generator.h" // Inclui ast.h e tabela.h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// funcao auxiliar para converter Node_Type para string (para avisos)
extern const char* Node_Type_to_String(Node_Type type);

// Declaracoes de funcoes auxiliares (static para escopo de arquivo)
static void gerarExpressao(NoAST *no, FILE *saida);
static void gerarStatement(NoAST *no, FILE *saida);

// Variaveis auxiliares
static int current_indent_level = 0; // para identacao de código

// Lista para armazenar variáveis já declaradas no escopo C atual, para que cada variável seja declarada apenas uma vez no C
typedef struct DeclaredVar {
    char *name;
    struct DeclaredVar *next;
} DeclaredVar;

static DeclaredVar *current_c_scope_declared_vars_head = NULL; // Cabeça da lista de vars declaradas no escopo C

// adiciona uma variável a lista de variáveis declaradas para o escopo C atual
static void addDeclaredVar(const char *name) {
    DeclaredVar *new_var = (DeclaredVar *)malloc(sizeof(DeclaredVar));
    if (!new_var) { perror("malloc DeclaredVar"); exit(EXIT_FAILURE); }
    new_var->name = strdup(name);
    new_var->next = current_c_scope_declared_vars_head;
    current_c_scope_declared_vars_head = new_var;
}

// limpa a lista de variáveis declaradas para o escopo C atual
static void clearDeclaredVars() {
    DeclaredVar *temp = current_c_scope_declared_vars_head;
    while(temp != NULL) {
        DeclaredVar *next = temp->next;
        free(temp->name);
        free(temp);
        temp = next;
    }
    current_c_scope_declared_vars_head = NULL;
}

// verifica se uma variável já foi declarada no escopo C atual
static int isVarDeclaredInCurrentCScope(const char *name) {
    DeclaredVar *temp = current_c_scope_declared_vars_head;
    while(temp != NULL) {
        if (strcmp(temp->name, name) == 0) {
            return 1; // retorna 1 se foi declarada
        }
        temp = temp->next;
    }
    return 0; // 0, se não
}

// imprime a indentação atual no arquivo de saída
static void print_indent(FILE *saida) {
    for (int i = 0; i < current_indent_level; i++) {
        fprintf(saida, "    "); // a identação vai ter 4 espaços
    }
}


// função auxiliar para determinar o tipo C de uma expressão para formatacao de printf
static const char* get_c_format_specifier(NoAST *expr_node) {
    if (!expr_node) return "%s"; // Default para string ou erro

    if (expr_node->type == CONST_NODE) {
        NoAST_Const *const_node = (NoAST_Const *)expr_node->data;
        if (const_node) {
            switch (const_node->const_type) {
                case TIPO_INT: return "%d";
                case TIPO_FLOAT:
                case TIPO_DOUBLE: return "%lf";
                case TIPO_CHAR: return "%c";
                case TIPO_STRING: return "%s";
                case TIPO_BOOLEAN: return "%d"; 
                default: return "%s"; 
            }
        }
    } else if (expr_node->type == ID_NODE) {
        NoAST_Id *id_node = (NoAST_Id *)expr_node->data;
        if (id_node && id_node->entry && id_node->entry->tipo) {
            if (strcmp(id_node->entry->tipo, "int") == 0) return "%d";
            if (strcmp(id_node->entry->tipo, "float") == 0) return "%lf";
            if (strcmp(id_node->entry->tipo, "double") == 0) return "%lf";
            if (strcmp(id_node->entry->tipo, "char") == 0) return "%c";
            if (strcmp(id_node->entry->tipo, "string") == 0) return "%s";
            if (strcmp(id_node->entry->tipo, "boolean") == 0) return "%d";
        }
    }
    // para expressoes complexas (aritmeticas, logicas, etc.)
    else if (expr_node->type == ARITHM_NODE || expr_node->type == REL_OP_NODE || expr_node->type == LOGIC_OP_NODE) {
        return "%d"; // assume int para resultados de operacoes
    }
    
    return "%s"; // fallback
}


// gera o código C para uma expressão
static void gerarExpressao(NoAST *no, FILE *saida) {
    if (no == NULL) return;

    switch (no->type) {
        case CONST_NODE: {
            NoAST_Const *const_node = (NoAST_Const *)no->data;
            if (!const_node) return; 

            switch (const_node->const_type) {
                case TIPO_INT:
                    fprintf(saida, "%d", const_node->val.valint);
                    break;
                case TIPO_FLOAT: 
                case TIPO_DOUBLE: 
                    fprintf(saida, "%lf", const_node->val.valfloat);
                    break;
                case TIPO_CHAR:
                    fprintf(saida, "'%c'", const_node->val.valchar);
                    break;
                case TIPO_STRING:
                    fprintf(saida, "\"%s\"", const_node->val.valstring);
                    break;
                case TIPO_BOOLEAN:
                    fprintf(saida, "%s", const_node->val.valint ? "1" : "0"); 
                    break;
                default:
                    fprintf(stderr, "Erro na geracao de codigo: Tipo de constante desconhecido (%d)\n", const_node->const_type);
                    break;
            }
            break;
        }
        case ID_NODE: {
            NoAST_Id *id_node = (NoAST_Id *)no->data;
            if (!id_node || !id_node->name) return; 
            fprintf(saida, "%s", id_node->name);
            break;
        }
        case ASSIGN_NODE: {
            NoAST_Assign *assign_node = (NoAST_Assign *)no->data;
            if (!assign_node || !assign_node->target_entry) return; 
            Simbolo *target_symbol = assign_node->target_entry; 

            const char* c_type = "int"; 

            if (target_symbol->tipo != NULL) { 
                if (strcmp(target_symbol->tipo, "int") == 0) c_type = "int";
                else if (strcmp(target_symbol->tipo, "float") == 0) c_type = "float";
                else if (strcmp(target_symbol->tipo, "double") == 0) c_type = "double"; 
                else if (strcmp(target_symbol->tipo, "char") == 0) c_type = "char";
                else if (strcmp(target_symbol->tipo, "string") == 0) c_type = "char*";
                else if (strcmp(target_symbol->tipo, "boolean") == 0) c_type = "int";
            } else {
                if (assign_node->value_expr && assign_node->value_expr->type == CONST_NODE) {
                    NoAST_Const *const_node = (NoAST_Const *)assign_node->value_expr->data;
                    if (const_node) {
                        switch (const_node->const_type) {
                            case TIPO_FLOAT: c_type = "float"; break;
                            case TIPO_DOUBLE: c_type = "double"; break;
                            case TIPO_CHAR: c_type = "char"; break;
                            case TIPO_STRING: c_type = "char*"; break;
                            case TIPO_BOOLEAN: c_type = "int"; break; 
                            case TIPO_INT: c_type = "int"; break; 
                            default: break; 
                        }
                    }
                }
            }
            
            if (!isVarDeclaredInCurrentCScope(target_symbol->nome)) {
                fprintf(saida, "%s ", c_type);
                addDeclaredVar(target_symbol->nome); 
            }
            fprintf(saida, "%s = ", target_symbol->nome);
            gerarExpressao(assign_node->value_expr, saida);
            break;
        }
        case ARITHM_NODE: {
            NoAST_Arithm *arithm_node = (NoAST_Arithm *)no->data;
            if (!arithm_node) return; 

            fprintf(saida, "(");
            gerarExpressao(arithm_node->esquerda, saida);
            switch (arithm_node->op) {
                case OP_ADICAO: fprintf(saida, " + "); break;
                case OP_SUBTRACAO: fprintf(saida, " - "); break;
                case OP_MULTIPLICACAO: fprintf(saida, " * "); break;
                case OP_DIVISAO: fprintf(saida, " / "); break;
                default: fprintf(saida, " /* UNKNOWN_ARITHM_OP */ "); break; 
            }
            gerarExpressao(arithm_node->direita, saida); 
            fprintf(saida, ")");
            break;
        }
        case LOGIC_OP_NODE: {
            NoAST_Logic *logic_node = (NoAST_Logic *)no->data;
            if (!logic_node) return; 

            fprintf(saida, "(");
            if (logic_node->op == OP_NOT) {
                fprintf(saida, "!");
                gerarExpressao(logic_node->esquerda, saida); 
            } else {
                gerarExpressao(logic_node->esquerda, saida);
                switch (logic_node->op) {
                    case OP_AND: fprintf(saida, " && "); break;
                    case OP_OR: fprintf(saida, " || "); break;
                    default: fprintf(saida, " /* UNKNOWN_LOGIC_OP */ "); break; 
                }
                gerarExpressao(logic_node->direita, saida);
            }
            fprintf(saida, ")");
            break;
        }
        case REL_OP_NODE: { 
            NoAST_Rel *rel_node = (NoAST_Rel *)no->data;
            if (!rel_node) return; 

            fprintf(saida, "(");
            gerarExpressao(rel_node->esquerda, saida);
            switch (rel_node->op) {
                case OP_REL_EQ: fprintf(saida, " == "); break;
                case OP_REL_NEQ: fprintf(saida, " != "); break;
                case OP_REL_LT: fprintf(saida, " < "); break;
                case OP_REL_GT: fprintf(saida, " > "); break;
                case OP_REL_LE: fprintf(saida, " <= "); break;
                case OP_REL_GE: fprintf(saida, " >= "); break;
                default: fprintf(saida, " /* UNKNOWN_REL_OP */ "); break; 
            }
            gerarExpressao(rel_node->direita, saida);
            fprintf(saida, ")");
            break;
        }
        case FUNC_CALL_NODE: {
            NoAST_Func_Call* call_node = (NoAST_Func_Call*)no->data;
            if (!call_node || !call_node->entry) return;

            No_Expr_List* arg_list_head = call_node->args_list_head; 

            // tratamento unificado para built-ins puts e print
            if (strcmp(call_node->entry->nome, "puts") == 0 || strcmp(call_node->entry->nome, "print") == 0) {
                fprintf(saida, "printf(");
                
                // primeira passada: gera a string de formato (ex: "%%d %%lf %%s")
                fprintf(saida, "\""); 
                int first_format_specifier_added = 1;
                No_Expr_List* temp_iter_format = arg_list_head; 

                fprintf(stderr, "DEBUG-CG: Gerando formato para %s. arg_list_head: %p\n", call_node->entry->nome, (void*)arg_list_head);
                fflush(stderr);

                while (temp_iter_format) {
                    fprintf(stderr, "DEBUG-CG:   Format Loop: Current temp_iter_format: %p, expr: %p, next: %p\n",
                            (void*)temp_iter_format, (void*)temp_iter_format->expr, (void*)temp_iter_format->next);
                    fflush(stderr);

                    if (temp_iter_format->expr) { // somente adiciona formato se a expressao existe
                        if (!first_format_specifier_added) {
                            fprintf(saida, " "); // adiciona espaço entre os especificadores
                        }
                        const char* spec = get_c_format_specifier(temp_iter_format->expr);
                        fprintf(saida, "%s", spec);
                        fprintf(stderr, "DEBUG-CG:     Added format specifier: %s\n", spec);
                        fflush(stderr);
                        first_format_specifier_added = 0;
                    } else {
                        fprintf(stderr, "DEBUG-CG:     Format Loop: temp_iter_format->expr is NULL, skipping.\n");
                        fflush(stderr);
                    }
                    temp_iter_format = (No_Expr_List*)temp_iter_format->next;
                }

                // adiciona nova linha se for 'puts' ou fecha a string de formato para 'print'
                if (strcmp(call_node->entry->nome, "puts") == 0) {
                    fprintf(saida, "\\n\""); 
                    fprintf(stderr, "DEBUG-CG:   Added newline to format for puts.\n");
                    fflush(stderr);
                } else { // for 'print'
                    fprintf(saida, "\""); 
                    fprintf(stderr, "DEBUG-CG:   Closing format for print.\n");
                    fflush(stderr);
                }
                
                // SEGUNDA PARTE: gerar os valores das expressões (argumentos reais do printf)
                int first_value_added = 1;
                No_Expr_List* temp_iter_value = arg_list_head; 
                fprintf(stderr, "DEBUG-CG: Gerando valores para %s. arg_list_head: %p\n", call_node->entry->nome, (void*)arg_list_head);
                fflush(stderr);

                while (temp_iter_value) {
                    fprintf(stderr, "DEBUG-CG:   Value Loop: Current temp_iter_value: %p, expr: %p, next: %p\n",
                            (void*)temp_iter_value, (void*)temp_iter_value->expr, (void*)temp_iter_value->next);
                    fflush(stderr);

                    if (temp_iter_value->expr) { // somente adiciona valor se a expressao existe
                        if (first_value_added) {
                            fprintf(saida, ", "); 
                            fprintf(stderr, "DEBUG-CG:     Added initial comma for values.\n");
                            fflush(stderr);
                        } else {
                            fprintf(saida, ", "); 
                            fprintf(stderr, "DEBUG-CG:     Added subsequent comma for values.\n");
                            fflush(stderr);
                        }
                        gerarExpressao(temp_iter_value->expr, saida);
                        fprintf(stderr, "DEBUG-CG:     Generated expression for value.\n");
                        fflush(stderr);
                        first_value_added = 0;
                    } else {
                        fprintf(stderr, "DEBUG-CG:     Value Loop: temp_iter_value->expr is NULL, skipping.\n");
                        fflush(stderr);
                    }
                    temp_iter_value = (No_Expr_List*)temp_iter_value->next;
                }
                fprintf(saida, ")"); 
                fprintf(stderr, "DEBUG-CG: Closing printf call.\n");
                fflush(stderr);
            } else if (strcmp(call_node->entry->nome, "scan") == 0 || strcmp(call_node->entry->nome, "gets") == 0) {
                No_Expr_List* current_arg = (No_Expr_List*)call_node->args_list_head; 
                if (current_arg && current_arg->expr && current_arg->expr->type == ID_NODE) {
                    NoAST_Id* target_id = (NoAST_Id*)current_arg->expr->data;
                    Simbolo *target_symbol = target_id->entry;
                    
                    if (!isVarDeclaredInCurrentCScope(target_symbol->nome)) {
                        const char* scan_type = "int"; 
                        if (target_symbol->tipo != NULL) {
                            if (strcmp(target_symbol->tipo, "float") == 0) scan_type = "float";
                            else if (strcmp(target_symbol->tipo, "double") == 0) scan_type = "double";
                            else if (strcmp(target_symbol->tipo, "char") == 0) scan_type = "char";
                            else if (strcmp(target_symbol->tipo, "string") == 0) scan_type = "char*";
                        }

                        fprintf(saida, "%s ", scan_type);
                        addDeclaredVar(target_symbol->nome);
                    }
                    fprintf(saida, "scanf(\"%s\", &%s)", get_c_format_specifier(current_arg->expr), target_symbol->nome);
                } else {
                    fprintf(stderr, "Erro: Chamada de '%s' com argumento invalido ou nao implementado.\n", call_node->entry->nome);
                    fprintf(saida, "/* ERRO_SCAN_INVALIDO */");
                }
            }
            else { // funcoes definidas pelo usuario
                fprintf(saida, "%s(", call_node->entry->nome);
                No_Expr_List* current_arg_list_node = (No_Expr_List*)call_node->args_list_head; 
                int first_arg = 1;
                while (current_arg_list_node) {
                    if (!current_arg_list_node->expr) { 
                        current_arg_list_node = (No_Expr_List*)current_arg_list_node->next;
                        continue; 
                    }
                    if (!first_arg) fprintf(saida, ", ");
                    gerarExpressao(current_arg_list_node->expr, saida);
                    first_arg = 0;
                    current_arg_list_node = (No_Expr_List*)current_arg_list_node->next;
                }
                fprintf(saida, ")");
            }
            break;
        }
        case EXPR_LIST_NODE: { 
            No_Expr_List *expr_list_node = (No_Expr_List*)no->data;
            if (expr_list_node && expr_list_node->expr) {
                fprintf(stderr, "Aviso: EXPR_LIST_NODE passado diretamente para gerarExpressao. Gerando apenas a primeira expressao.\n");
                gerarExpressao(expr_list_node->expr, saida);
            } else {
                fprintf(stderr, "Aviso: EXPR_LIST_NODE nulo ou com expressao nula passado diretamente para gerarExpressao.\n");
            }
            break;
        }
        case RANGE_NODE: {
            NoAST_Range* range_node = (NoAST_Range*)no->data;
            if (!range_node) return;
            fprintf(saida, "/* Range: "); 
            gerarExpressao(range_node->start, saida);
            fprintf(saida, "%s", range_node->exclusive ? "..." : "..");
            gerarExpressao(range_node->end, saida);
            fprintf(saida, " */");
            break;
        }
        case BASIC_NODE:
        case IF_NODE:
        case ELSIF_NODE:
        case ELSE_NODE:
        case FOR_IN_NODE:
        case WHILE_NODE:
        case FUNC_DEF_NODE:
        case RETURN_NODE:
            fprintf(stderr, "Aviso: no de expressao inesperado (%s) passado para gerarExpressao. Tratando como statement.\n", Node_Type_to_String(no->type)); 
            gerarStatement(no, saida); 
            break;
        default:
            fprintf(stderr, "Erro na geracao de codigo: Tipo de expressao desconhecido ou nao implementado (%s)\n", Node_Type_to_String(no->type)); 
            fprintf(saida, "/* ERRO_EXPRESSAO_DESCONHECIDA */");
            break;
    }
}

// gera o código C para um statement
static void gerarStatement(NoAST *no, FILE *saida) {
    if (no == NULL) return;

    switch (no->type) {
        case BASIC_NODE: 
            if (no->esquerda) gerarStatement(no->esquerda, saida); 
            if (no->direita) gerarStatement(no->direita, saida);  
            break;
        case ASSIGN_NODE: 
        case FUNC_CALL_NODE: 
        case ID_NODE:       
        case CONST_NODE:    
        case ARITHM_NODE:   
        case LOGIC_OP_NODE: 
        case REL_OP_NODE:   
            print_indent(saida);
            gerarExpressao(no, saida); 
            fprintf(saida, ";\n");
            break;
        case IF_NODE: {
            NoAST_if *if_node = (NoAST_if *)no->data;
            if (!if_node) return; 

            print_indent(saida);
            fprintf(saida, "if (");
            gerarExpressao(if_node->condition, saida);
            fprintf(saida, ") {\n");
            current_indent_level++;
            clearDeclaredVars(); 
            gerarStatement(if_node->if_branch, saida);
            current_indent_level--;
            print_indent(saida);
            fprintf(saida, "}\n");
            if (if_node->next_branch != NULL) {
                gerarStatement(if_node->next_branch, saida); 
            }
            break;
        }
        case ELSIF_NODE: {
            NoAST_if *elsif_node = (NoAST_if *)no->data;
            if (!elsif_node) return; 

            print_indent(saida);
            fprintf(saida, "else if (");
            gerarExpressao(elsif_node->condition, saida);
            fprintf(saida, ") {\n");
            current_indent_level++;
            clearDeclaredVars(); 
            gerarStatement(elsif_node->if_branch, saida);
            current_indent_level--;
            print_indent(saida);
            fprintf(saida, "}\n");
            if (elsif_node->next_branch != NULL) {
                gerarStatement(elsif_node->next_branch, saida);
            }
            break;
        }
        case ELSE_NODE: {
            NoAST_if *else_node = (NoAST_if *)no->data;
            if (!else_node) return; 

            print_indent(saida);
            fprintf(saida, "else {\n");
            current_indent_level++;
            clearDeclaredVars(); 
            gerarStatement(else_node->if_branch, saida); 
            current_indent_level--;
            print_indent(saida);
            fprintf(saida, "}\n");
            break;
        }
        case FOR_IN_NODE:{
            NoAST_ForIn* for_node = (NoAST_ForIn*)no->data;
            if (!for_node) return; 

            print_indent(saida);
            
            if (for_node->collection_expr->type == RANGE_NODE) {
                NoAST_Range* range_node = (NoAST_Range*)for_node->collection_expr->data;
                NoAST_Id* iter_id_node = (NoAST_Id*)for_node->iterator_id->data; 
                if (!range_node || !iter_id_node || !iter_id_node->name) return; 

                const char* iterator_name = iter_id_node->name;

                fprintf(saida, "for (int %s = ", iterator_name); 
                gerarExpressao(range_node->start, saida);
                fprintf(saida, "; %s %s ", iterator_name, (range_node->exclusive ? "<" : "<="));
                gerarExpressao(range_node->end, saida);
                fprintf(saida, "; %s++) {\n", iterator_name);

                current_indent_level++;
                clearDeclaredVars(); 
                gerarStatement(for_node->body, saida);
                current_indent_level--;

                print_indent(saida);
                fprintf(saida, "}\n");

            } else {
                fprintf(stderr, "Erro na geracao de codigo: FOR_IN_NODE com colecao nao suportada.\n");
                print_indent(saida);
                fprintf(saida, "/* ERRO_FOR_IN_COLECAO_NAO_SUPORTADA */\n");
            }
            break;
        }
        case WHILE_NODE:{
            NoAST_while* while_node = (NoAST_while*)no->data;
            if (!while_node) return; 

            print_indent(saida);
            fprintf(saida, "while (");
            gerarExpressao(while_node->condition, saida);
            fprintf(saida, ") {\n");

            current_indent_level++;
            clearDeclaredVars(); 
            gerarStatement(while_node->while_branch, saida);
            current_indent_level--;

            print_indent(saida);
            fprintf(saida, "}\n");
            break;
        }

        case RETURN_NODE: {
            NoAST_Return* ret_node = (NoAST_Return*)no->data;
            if (!ret_node) return; 

            print_indent(saida);
            fprintf(saida, "return ");
            if (ret_node->ret_val) { 
                gerarExpressao(ret_node->ret_val, saida); 
            }
            fprintf(saida, ";\n");
            break;
        }
        case FUNC_DEF_NODE: {
            NoAST_FuncDef* func_def = (NoAST_FuncDef*)no->data;
            if (!func_def || !func_def->func_entry) return; 

            const char* return_c_type = "int"; 
            if (func_def->func_entry->tipo != NULL) {
                if (strcmp(func_def->func_entry->tipo, "int") == 0) return_c_type = "int";
                else if (strcmp(func_def->func_entry->tipo, "float") == 0) return_c_type = "float";
                else if (strcmp(func_def->func_entry->tipo, "double") == 0) return_c_type = "double";
                else if (strcmp(func_def->func_entry->tipo, "char") == 0) return_c_type = "char";
                else if (strcmp(func_def->func_entry->tipo, "string") == 0) return_c_type = "char*";
                else if (strcmp(func_def->func_entry->tipo, "boolean") == 0) return_c_type = "int";
                else if (strcmp(func_def->func_entry->tipo, "void") == 0) return_c_type = "void"; 
            }

            fprintf(saida, "%s %s(", return_c_type, func_def->func_entry->nome); 

            Parametro* param = func_def->params_list; 
            int first_param = 1;
            while (param) {
                if (!first_param) fprintf(saida, ", ");
                const char* param_c_type = "int";
                if (param->tipo != NULL) {
                    if (strcmp(param->tipo, "int") == 0) param_c_type = "int";
                    else if (strcmp(param->tipo, "float") == 0) param_c_type = "float";
                    else if (strcmp(param->tipo, "double") == 0) param_c_type = "double";
                    else if (strcmp(param->tipo, "char") == 0) param_c_type = "char";
                    else if (strcmp(param->tipo, "string") == 0) param_c_type = "char*";
                    else if (strcmp(param->tipo, "boolean") == 0) param_c_type = "int";
                }
                fprintf(saida, "%s %s", param_c_type, param->nome);
                first_param = 0;
                param = param->prox; 
            }
            fprintf(saida, ") {\n");

            current_indent_level++;
            clearDeclaredVars(); 
            gerarStatement(func_def->body, saida); 
            current_indent_level--;
            print_indent(saida); 
            fprintf(saida, "}\n\n");
            break;
        }
        default:
            fprintf(stderr, "Erro na geracao de codigo: Tipo de statement desconhecido ou nao implementado (%s)\n", Node_Type_to_String(no->type)); 
            print_indent(saida);
            fprintf(saida, "/* ERRO_STATEMENT_DESCONHECIDO */\n");
            break;
    }
}

// Funcao principal para iniciar a geracao de codigo C
void gerarCodigoC(NoAST *raiz, FILE *saida) {
    fprintf(saida, "#include <stdio.h>\n");
    fprintf(saida, "#include <stdlib.h>\n");
    fprintf(saida, "#include <string.h>\n\n");

    fprintf(saida, "int main() {\n");
    current_indent_level = 1; 

    clearDeclaredVars(); 

    if (raiz != NULL) {
        gerarStatement(raiz, saida);
    }

    print_indent(saida);
    fprintf(saida, "return 0;\n");
    fprintf(saida, "}\n"); 

    clearDeclaredVars(); 
}