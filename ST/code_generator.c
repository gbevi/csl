#include "code_generator.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void gerarExpressao(NoAST *no, FILE *saida);
static void gerarStatement(NoAST *no, FILE *saida);
static void gerarDeclaracaoFuncao(NoAST *no, FILE *saida);

// funções e variáveis auxiliares

static int current_indent_level = 0; // para identação de código

// lista para armazenar variáveis já declaradas no escopo C atual, para que cada variável seja declarada apenas uma vez no C
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

// gera o código C para uma expressão (focado em constantes, IDs, atribuições, aritmética, lógica, relacional e I/O básico)
static void gerarExpressao(NoAST *no, FILE *saida) {
    if (no == NULL) return;

    switch (no->type) {
        case CONST_NODE: {
            NoAST_Const *const_node = (NoAST_Const *)no->data;
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
                    fprintf(saida, "%s", const_node->val.valint ? "1" : "0"); // true/false para 1/0
                    break;
                default:
                    fprintf(stderr, "Erro na geracao de codigo: Tipo de constante desconhecido (%d)\n", const_node->const_type);
                    break;
            }
            break;
        }
        case ID_NODE: {
            NoAST_Id *id_node = (NoAST_Id *)no->data;
            fprintf(saida, "%s", id_node->name);
            break;
        }
        case ASSIGN_NODE: {
            NoAST_Assign *assign_node = (NoAST_Assign *)no->data;
            Simbolo *target_symbol = (Simbolo *)assign_node->target_entry;
            
            // se a variável não foi declarada em C neste escopo, por enquanto vai ser declarada 'int'
            // dps q os tipos for tratados na análise semântica, tem que mudar aqui
            if (!isVarDeclaredInCurrentCScope(target_symbol->nome)) {
                fprintf(saida, "int ");
                addDeclaredVar(target_symbol->nome); // marca como declarada para o escopo C atual
            }
            fprintf(saida, "%s = ", target_symbol->nome);
            gerarExpressao(assign_node->value_expr, saida);
            break;
        }
        case ARITHM_NODE: {
            NoAST_Arithm *arithm_node = (NoAST_Arithm *)no->data;
            fprintf(saida, "(");
            gerarExpressao(arithm_node->esquerda, saida);
            switch (arithm_node->op) {
                case OP_ADICAO: fprintf(saida, " + "); break;
                case OP_SUBTRACAO: fprintf(saida, " - "); break;
                case OP_MULTIPLICACAO: fprintf(saida, " * "); break;
                case OP_DIVISAO: fprintf(saida, " / "); break;
            }
            fprintf(saida, ")");
            break;
        }
        case LOGIC_OP_NODE: {
            NoAST_Logic *logic_node = (NoAST_Logic *)no->data;
            fprintf(saida, "(");
            if (logic_node->op == OP_NOT) {
                fprintf(saida, "!");
                gerarExpressao(logic_node->esquerda, saida); // NOT usa apenas esquerda
            } else {
                gerarExpressao(logic_node->esquerda, saida);
                switch (logic_node->op) {
                    case OP_AND: fprintf(saida, " && "); break;
                    case OP_OR: fprintf(saida, " || "); break;
                    default: break;
                }
                gerarExpressao(logic_node->direita, saida);
            }
            fprintf(saida, ")");
            break;
        }
        case REL_OP_NODE: { // operações relacionais ==, !=, <, >, <=, >=
            NoAST_Rel *rel_node = (NoAST_Rel *)no->data;
            fprintf(saida, "(");
            gerarExpressao(rel_node->esquerda, saida);
            switch (rel_node->op) {
                case OP_REL_EQ: fprintf(saida, " == "); break;
                case OP_REL_NEQ: fprintf(saida, " != "); break;
                case OP_REL_LT: fprintf(saida, " < "); break;
                case OP_REL_GT: fprintf(saida, " > "); break;
                case OP_REL_LE: fprintf(saida, " <= "); break;
                case OP_REL_GE: fprintf(saida, " >= "); break;
            }
            gerarExpressao(rel_node->direita, saida);
            fprintf(saida, ")");
            break;
        }
        case FUNC_CALL_NODE: {
            break;
        }
        case EXPR_LIST_NODE: {
            break;
        }
        case BASIC_NODE:
        case IF_NODE:
        case ELSIF_NODE:
        case ELSE_NODE:
        case FOR_IN_NODE:
        case FOR_HEADER_NODE:
        case WHILE_NODE:
        case FUNC_DEF_NODE:
        case RETURN_NODE:
        case RANGE_NODE: // geralmente o range só é tratado dentro do for, ent n precisa tratar ele separadamente
            fprintf(stderr, "Aviso: no de expressão inesperado (%s) ignorado na geracao de codigo.\n", Node_Type_to_String(no->type));
            fprintf(saida, "/* ERRO_EXPRESSAO_INESPERADA_OU_NAO_TRATADA */");
            break;
        default:
            fprintf(stderr, "Erro na geracao de codigo: Tipo de expressao desconhecido ou não implementado (%d)\n", no->type);
            fprintf(saida, "/* ERRO_EXPRESSAO_DESCONHECIDA */");
            break;
    }
}

// gera o código C para um statement (focado em atribuições e chamadas de I/O)
static void gerarStatement(NoAST *no, FILE *saida) {
    if (no == NULL) return;

    switch (no->type) {
        case BASIC_NODE: // usado por statements_list para encadear statements
            gerarStatement(no->esquerda, saida); // primeiro statement na sequência
            gerarStatement(no->direita, saida);  // resto dos statements
            break;
        case ASSIGN_NODE: // atribuição de variável
            print_indent(saida);
            gerarExpressao(no, saida);
            fprintf(saida, ";\n");
            break;
        case FUNC_CALL_NODE: // chamada de função ( tbm inclui puts, print, scan ou definidas pelo usuário)
        case ID_NODE:
        case CONST_NODE:
        case ARITHM_NODE:
        case LOGIC_OP_NODE:
        case REL_OP_NODE:
             print_indent(saida);
             gerarExpressao(no, saida);
             fprintf(saida, ";\n");
             break;
        case IF_NODE:
        case ELSIF_NODE:
        case ELSE_NODE:
        case FOR_IN_NODE:
        case FOR_HEADER_NODE:
        case WHILE_NODE:
        case RETURN_NODE:
        case FUNC_DEF_NODE: // definição de função
        default:
            fprintf(stderr, "Erro na geracao de codigo: Tipo de statement desconhecido ou não implementado (%d)\n", no->type);
            print_indent(saida);
            break;
    }
}

void gerarCodigoC(NoAST *raiz, FILE *saida) {
    
    fprintf(saida, "#include <stdio.h>\n");
    fprintf(saida, "#include <stdlib.h>\n");
    fprintf(saida, "#include <string.h>\n\n");

    fprintf(saida, "int main() {\n");
    current_indent_level = 1; // identação pro corpo da main aqui

    clearDeclaredVars(); // inicia a lista de variáveis declaradas para o escopo da main em C

    // percorre a AST principal ('program' -> 'statements')
    if (raiz != NULL) {
        gerarStatement(raiz, saida); // 'raiz' aponta para o nó 'statements' ou 'statements_list'
    }

    print_indent(saida);
    fprintf(saida, "return 0;\n");
    fprintf(saida, "}\n"); // fecha a main

    clearDeclaredVars(); // limpa as variáveis declaradas da main
}