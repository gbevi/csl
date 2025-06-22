#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tabela.h"
#include "ast.h"

NoAST *criarNo(Node_Type type, NoAST *esquerda, NoAST *direita){
    NoAST *v = malloc (sizeof(NoAST));
    v->type = type;
    v->esquerda = esquerda;
    v->direita = direita;
    v->data = NULL;
    return v;
}

NoAST *criarNoDecl(int dataType, Simbolo **names){
    NoAST_Decl *v = malloc(sizeof(NoAST_Decl));
    v->dateType = dataType;
    v->names = names;
    v->type = DECL_NODE;
    return (struct NoAST *) v;
}

NoAST *criarNoConst(DataType const_type, Value val){
    NoAST_Const *v = malloc(sizeof(NoAST_Const));
    v->type = CONST_NODE;
    v->const_type = const_type;
    v->val = val;
    if (const_type == TIPO_STRING && val.valstring != NULL) {
        v->val.valstring = strdup(val.valstring);
    }
    NoAST *node = criarNo(CONST_NODE, NULL, NULL);
    node->data = v;
    return node;
}

NoAST *criarNoId(char *name, void *entry) {
    NoAST_Id *id_node = malloc(sizeof(NoAST_Id));
    id_node->type = ID_NODE;
    id_node->name = strdup(name); 
    id_node->entry = entry;
    NoAST *node = criarNo(ID_NODE, NULL, NULL);
    node->data = id_node;
    return node;
}


NoAST *criarNoIfElseChain(Node_Type type, NoAST *condition, NoAST *branch_block, NoAST *next_branch) {
    NoAST *base_node = criarNo(type, NULL, NULL); 
    NoAST_if *v = malloc(sizeof(NoAST_if));
    v->type = type;
    v->condition = condition; 
    v->if_branch = branch_block;
    v->next_branch = next_branch;
    base_node->data = v; 
    return base_node;
}

NoAST *criarNoElsifCompleto(NoAST *condition, NoAST *elsif_branch) {
    NoAST *base_node = criarNo(ELSIF_NODE, NULL, NULL);
    NoAST_elsif *v = malloc(sizeof(NoAST_elsif));
    v->type = ELSIF_NODE;
    v->condition = condition;
    v->elsif_branch = elsif_branch;
    base_node->data = v;
    return base_node;
}

NoAST *criarNoFor(NoAST *initialize, NoAST *condition, NoAST *increment, NoAST *for_branch) {
    NoAST_for *v = malloc (sizeof(NoAST_for));
    v->type = FOR_NODE;
    v->initialize = initialize;
    v->condition = condition;
    v->increment = increment;
    v->for_branch = for_branch;
    NoAST *base_node = criarNo(FOR_NODE, NULL, NULL);
    base_node->data = v;
    return base_node;
}

NoAST *criarNoForIn(NoAST *iterator_id, NoAST *collection_expr, NoAST *body) {
    NoAST_ForIn *v = malloc(sizeof(NoAST_ForIn));
    v->type = FOR_IN_NODE;
    v->iterator_id = iterator_id;
    v->collection_expr = collection_expr;
    v->body = body;
    NoAST *base_node = criarNo(FOR_IN_NODE, NULL, NULL);
    base_node->data = v;
    return base_node;
}

NoAST *criarNoRange(NoAST *start_expr, NoAST *end_expr, int exclusive) {
    NoAST_Range *range_data = malloc(sizeof(NoAST_Range));
    range_data->type = RANGE_NODE;
    range_data->start = start_expr;
    range_data->end = end_expr;
    range_data->exclusive = exclusive;
    NoAST *base_node = criarNo(RANGE_NODE, NULL, NULL);
    base_node->data = range_data;
    return base_node;
}


NoAST *criarNoWhile(NoAST *condition, NoAST *while_brach) {
    NoAST_while *v = malloc(sizeof(NoAST_while));
    v->type = WHILE_NODE;
    v->condition = condition;
    v->while_branch = while_brach;
    NoAST *base_node = criarNo(WHILE_NODE, NULL, NULL);
    base_node->data = v;
    return base_node;
}

NoAST *criarNoAssign(void *target_entry, NoAST *value_expr) {
    NoAST_Assign *assign_node = malloc(sizeof(NoAST_Assign));
    assign_node->type = ASSIGN_NODE;
    assign_node->target_entry = target_entry;
    assign_node->value_expr = value_expr;
    NoAST *node = malloc(sizeof(NoAST));
    node->type = ASSIGN_NODE;
    node->esquerda = NULL;
    node->direita = NULL;
    node->data = assign_node;
    return node;
}

const char* op_rel_para_str(Rel_op op) {
    switch(op) {
        case OP_REL_EQ: return "==";
        case OP_REL_NEQ: return "!=";
        case OP_REL_LT: return "<";
        case OP_REL_GT: return ">";
        case OP_REL_LE: return "<=";
        case OP_REL_GE: return ">=";
        default: return "?REL?";
    }
}



NoAST *criarNoFuncCall(Simbolo *entry, NoAST *args_list) {
    NoAST_Func_Call *v = malloc (sizeof(NoAST_Func_Call));
    v->type = FUNC_CALL_NODE;
    v->entry = entry;
    v->args = args_list;
    NoAST *base_node = criarNo(FUNC_CALL_NODE, NULL, NULL);
    base_node->data = v;
    return base_node;
}

NoAST* criarNoExprList(NoAST *expr, NoAST *next_expr_list) {
    No_Expr_List *node = malloc(sizeof(No_Expr_List));
    node->tipo_no = EXPR_LIST_NODE;
    node->expr = expr;
    node->next = next_expr_list;
    NoAST *base_node = criarNo(EXPR_LIST_NODE, NULL, NULL);
    base_node->data = node;
    return base_node;
}

NoAST *criarNoArithm(Arithm_op op, NoAST *esquerda, NoAST *direita){
    NoAST_Arithm *v = malloc (sizeof (NoAST_Arithm));
    v->type = ARITHM_NODE;
    v->op = op;
    v->esquerda = esquerda;
    v->direita = direita;
    NoAST *node = criarNo(ARITHM_NODE, NULL, NULL);
    node->data = v;
    return node;
}

NoAST *criarNoLogic(Bool_op op, NoAST *esquerda, NoAST *direita){
    NoAST_Logic *v = malloc (sizeof (NoAST_Logic));
    v->type = LOGIC_OP_NODE;
    v->op = op;
    v->esquerda = esquerda;
    v->direita = direita;
    NoAST *node = criarNo(LOGIC_OP_NODE, NULL, NULL);
    node->data = v;
    return node;
}


NoAST *criarNoRel(Rel_op op, NoAST *left, NoAST *right) {
    NoAST_Rel *rel_node = malloc(sizeof(NoAST_Rel));
    rel_node->type = REL_OP_NODE; 
    rel_node->op = op;
    rel_node->esquerda = left;
    rel_node->direita = right;
    NoAST *node = criarNo(REL_OP_NODE, NULL, NULL);
    node->data = rel_node;
    return node;
}

NoAST *criarNoFuncDef(Simbolo *symbol_entry, Parametro *parameters, NoAST *body) {
    NoAST_FuncDef *func_def_data = malloc(sizeof(NoAST_FuncDef));
    if (func_def_data == NULL) {
        perror("Erro ao alocar NoAST_FuncDef data");
        exit(EXIT_FAILURE);
    }
    func_def_data->type = FUNC_DEF_NODE;
    func_def_data->func_entry = symbol_entry;
    func_def_data->params_list = parameters;
    func_def_data->body = body;
    NoAST *base_node = criarNo(FUNC_DEF_NODE, NULL, NULL);
    base_node->data = func_def_data;
    return base_node;
}

NoAST *criarNoReturn(NoAST *ret_val){
    NoAST *node = (NoAST *)malloc(sizeof(NoAST));
    NoAST_Return *v = malloc(sizeof(NoAST_Return));
    v->type = RETURN_NODE;
    v->ret_val = ret_val;
    // O nó base deve apontar para os dados específicos do retorno
    node->type = RETURN_NODE;
    node->data = v;
    node->esquerda = NULL;
    node->direita = NULL;
    return node;
}

// Em ast.c
// SUBSTITUA SUA FUNÇÃO ANTIGA POR ESTA

void imprimirAST(NoAST *node, int indent) {
    if (!node) return;

    // Imprime a indentação para mostrar o nível da árvore
    for (int i = 0; i < indent; i++) {
        printf("  "); // 2 espaços por nível de indentação
    }

    // Imprime o tipo do nó atual
    printf("Type: %d ", node->type);

    // Usa o switch para imprimir detalhes específicos de cada tipo de nó
    switch (node->type) {
        case CONST_NODE: {
            NoAST_Const* data = (NoAST_Const*)node->data;
            printf("(CONST: ");
            if (data->const_type == TIPO_INT) printf("%d", data->val.valint);
            else if (data->const_type == TIPO_STRING) printf("\"%s\"", data->val.valstring);
            printf(")\n");
            break;
        }
        case ID_NODE: {
            NoAST_Id* data = (NoAST_Id*)node->data;
            printf("(ID: %s)\n", data->name);
            break;
        }
        case ARITHM_NODE: {
            NoAST_Arithm *data = (NoAST_Arithm*)node->data;
            const char* op_str = "?";
            switch (data->op) {
                case OP_ADICAO: op_str = "+"; break;
                case OP_SUBTRACAO: op_str = "-"; break;
                case OP_MULTIPLICACAO: op_str = "*"; break;
                case OP_DIVISAO: op_str = "/"; break;
            }
            printf("(ARITH_OP: %s)\n", op_str);
            // Recursão para os filhos de nós de expressão
            imprimirAST(data->esquerda, indent + 1);
            imprimirAST(data->direita, indent + 1);
            break;
        }
        case REL_OP_NODE: {
            NoAST_Rel *data = (NoAST_Rel *)node->data;
            printf("(REL_OP)\n");
             // Recursão para os filhos
            imprimirAST(data->esquerda, indent + 1);
            imprimirAST(data->direita, indent + 1);
            break;
        }
        case LOGIC_OP_NODE: {
            NoAST_Logic *data = (NoAST_Logic *)node->data;
            printf("(LOGIC_OP)\n");
             // Recursão para os filhos
            imprimirAST(data->esquerda, indent + 1);
            if(data->direita) imprimirAST(data->direita, indent + 1); // NOT não tem filho direito
            break;
        }
        case ASSIGN_NODE: {
            NoAST_Assign *data = (NoAST_Assign*)node->data;
            Simbolo* target = (Simbolo*)data->target_entry;
            printf("(ASSIGN TO: %s)\n", target->nome);
            // Recursão para o valor da expressão
            imprimirAST(data->value_expr, indent + 1);
            break;
        }
        case IF_NODE: case ELSE_NODE: case ELSIF_NODE: {
            NoAST_if *data = (NoAST_if *)node->data;
            if (node->type == IF_NODE) printf("(IF)\n");
            else if (node->type == ELSE_NODE) printf("(ELSE)\n");
            else printf("(ELSIF)\n");

            if (data->condition) {
                for (int i = 0; i < indent + 1; i++) printf("  ");
                printf("Condition:\n");
                imprimirAST(data->condition, indent + 2);
            }
            if (data->if_branch) {
                for (int i = 0; i < indent + 1; i++) printf("  ");
                printf("Body:\n");
                imprimirAST(data->if_branch, indent + 2);
            }
            if (data->next_branch) {
                imprimirAST(data->next_branch, indent); // Próximo na cadeia if/elsif/else
            }
            break;
        }
        case WHILE_NODE: {
             NoAST_while *data = (NoAST_while*)node->data;
             printf("(WHILE)\n");
             for (int i = 0; i < indent + 1; i++) printf("  ");
             printf("Condition:\n");
             imprimirAST(data->condition, indent + 2);

             for (int i = 0; i < indent + 1; i++) printf("  ");
             printf("Body:\n");
             imprimirAST(data->while_branch, indent + 2);
             break;
        }
        case FUNC_DEF_NODE: {
            NoAST_FuncDef *data = (NoAST_FuncDef*)node->data;
            printf("(FUNC_DEF: %s)\n", ((Simbolo*)data->func_entry)->nome);
            // Imprimir parâmetros se houver
            for (int i = 0; i < indent + 1; i++) printf("  ");
            printf("Body:\n");
            imprimirAST(data->body, indent + 2);
            break;
        }
        case FUNC_CALL_NODE: {
            NoAST_Func_Call* data = (NoAST_Func_Call*)node->data;
            printf("(FUNC_CALL: %s)\n", ((Simbolo*)data->entry)->nome);
            if (data->args) {
                 for (int i = 0; i < indent + 1; i++) printf("  ");
                 printf("Arguments:\n");
                 imprimirAST(data->args, indent + 2);
            }
            break;
        }
        case EXPR_LIST_NODE: {
            No_Expr_List* data = (No_Expr_List*)node->data;
            printf("(ARG)\n");
            imprimirAST(data->expr, indent+1); // Imprime a expressão atual
            if (data->next) {
                imprimirAST(data->next, indent); // Imprime o próximo argumento no mesmo nível
            }
            break;
        }
        case BASIC_NODE: {
             printf("(BLOCK)\n");
             imprimirAST(node->esquerda, indent + 1);
             imprimirAST(node->direita, indent + 1);
             break;
        }

        case RETURN_NODE: {
            NoAST_Return* data = (NoAST_Return*)node->data;
            printf("(RETURN)\n");
            
            for (int i = 0; i < indent + 1; i++) printf("  ");
            printf("Value:\n");
            imprimirAST(data->ret_val, indent + 2);
            break;
        }

        case FOR_NODE: {
            NoAST_for *data = (NoAST_for*)node->data;
            printf("(FOR)\n");

            for (int i = 0; i < indent + 1; i++) printf("  ");
            printf("Initialize:\n");
            imprimirAST(data->initialize, indent + 2);

            for (int i = 0; i < indent + 1; i++) printf("  ");
            printf("Condition:\n");
            imprimirAST(data->condition, indent + 2);
            
            for (int i = 0; i < indent + 1; i++) printf("  ");
            printf("Increment:\n");
            imprimirAST(data->increment, indent + 2);

            for (int i = 0; i < indent + 1; i++) printf("  ");
            printf("Body:\n");
            imprimirAST(data->for_branch, indent + 2);
            break;
        }


        default:
            printf("(Tipo de Nó Desconhecido ou Não Tratado na Impressão)\n");
            break;
    }
}

static int contador_temp = 0;
static int contador_label = 0;

char* gerarTAC_impl(NoAST *no);

char* novo_temp() {
    char buffer[20];
    sprintf(buffer, "_t%d", contador_temp++);
    return strdup(buffer);
}

char* novo_label() {
    char buffer[20];
    sprintf(buffer, "_L%d", contador_label++);
    return strdup(buffer);
}

const char* op_arithm_para_str(Arithm_op op) {
    switch(op) {
        case OP_ADICAO: return "+";
        case OP_SUBTRACAO: return "-";
        case OP_MULTIPLICACAO: return "*";
        case OP_DIVISAO: return "/";
        default: return "?OP?";
    }
}

void percorrerEGerar(NoAST* no, Node_Type tipo_alvo, int gerar_se_alvo);

void gerarCodigoTAC(NoAST *raiz) {
    if (!raiz) return;

    contador_temp = 0; 
    contador_label = 0;
    char* main_label = novo_label();

    printf("goto %s\n\n", main_label);

    printf("--- Function Definitions ---\n");
    percorrerEGerar(raiz, FUNC_DEF_NODE, 1); 
    
    printf("\n--- Main Code ---\n");
    printf("%s:\n", main_label);
    

    percorrerEGerar(raiz, FUNC_DEF_NODE, 0); 

    free(main_label);
}

void percorrerEGerar(NoAST* no, Node_Type tipo_alvo, int gerar_se_alvo) {
    if (!no) return;

    if (no->type == BASIC_NODE) {
        
        percorrerEGerar(no->esquerda, tipo_alvo, gerar_se_alvo);
        percorrerEGerar(no->direita, tipo_alvo, gerar_se_alvo);
    } else {
       
        int tipo_corresponde = (no->type == tipo_alvo);

        if ( (gerar_se_alvo && tipo_corresponde) || (!gerar_se_alvo && !tipo_corresponde) ) {
        
            char* res = gerarTAC_impl(no);
            if (res) free(res);
            if (no->type == FUNC_DEF_NODE) printf("\n");
        }
    }
}

char* gerarTAC_impl(NoAST *no) {
    if (no == NULL) {
        return NULL;
    }

    switch (no->type) {
        case CONST_NODE: {
            NoAST_Const *data = (NoAST_Const*)no->data;
            char buffer[100];
            if (data->const_type == TIPO_INT) {
                sprintf(buffer, "%d", data->val.valint);
            } else if (data->const_type == TIPO_STRING) {
                sprintf(buffer, "\"%s\"", data->val.valstring);
            } // Adicionar outros tipos aqui (float, bool, etc.)
            return strdup(buffer);
        }

        case ID_NODE: {
            NoAST_Id *data = (NoAST_Id*)no->data;
            return strdup(data->name);
        }

        case ARITHM_NODE: {
            NoAST_Arithm *data = (NoAST_Arithm*)no->data;
            
            char *endereco_esq = gerarTAC_impl(data->esquerda);
            char *endereco_dir = gerarTAC_impl(data->direita);
            char *endereco_res = novo_temp();
            
            printf("%s = %s %s %s\n", 
                   endereco_res, 
                   endereco_esq, 
                   op_arithm_para_str(data->op), 
                   endereco_dir);
            
            free(endereco_esq);
            free(endereco_dir);
            
            return endereco_res;
        }

        case ASSIGN_NODE: {
            NoAST_Assign *data = (NoAST_Assign*)no->data;
            Simbolo *simbolo_alvo = (Simbolo*)data->target_entry;
            
            char *endereco_valor = gerarTAC_impl(data->value_expr);
            
            printf("%s = %s\n", simbolo_alvo->nome, endereco_valor);
            
            free(endereco_valor);
            return NULL; // Statements não retornam valor.
        }

        case IF_NODE: {
            NoAST_if *data = (NoAST_if*)no->data;
            
            char* label_else = novo_label();
            char* label_fim = novo_label();

            // 1. Processa a condição
            char* cond_res = gerarTAC_impl(data->condition);
            printf("if_false %s goto %s\n", cond_res, label_else);
            free(cond_res);

            // 2. Processa o bloco 'then'
            gerarTAC_impl(data->if_branch);

            // Se houver um 'else', precisamos pular sobre ele
            if (data->next_branch) {
                printf("goto %s\n", label_fim);
            }

            // 3. Emite o rótulo do 'else'
            printf("%s:\n", label_else);
            
            // 4. Processa o 'else' ou 'elsif'
            if (data->next_branch) {
                gerarTAC_impl(data->next_branch);
                printf("%s:\n", label_fim); // Emite o rótulo de fim
            }

            free(label_else);
            free(label_fim);
            return NULL;
        }
        
        case ELSE_NODE: {
            NoAST_if *data = (NoAST_if*)no->data;
            gerarTAC_impl(data->if_branch); // O corpo do else está no 'if_branch'
            return NULL;
        }
        
        case REL_OP_NODE: {
            NoAST_Rel *data = (NoAST_Rel*)no->data;

            char *endereco_esq = gerarTAC_impl(data->esquerda);
            char *endereco_dir = gerarTAC_impl(data->direita);
            char *endereco_res = novo_temp(); // O resultado de uma comparação vai para um temporário

            // Gera a linha que estava faltando! Ex: "_t0 = i < 3"
            printf("%s = %s %s %s\n", 
                   endereco_res, 
                   endereco_esq, 
                   op_rel_para_str(data->op), 
                   endereco_dir);

            free(endereco_esq);
            free(endereco_dir);

            return endereco_res; // Retorna o nome do temporário com o resultado
        }

        case LOGIC_OP_NODE: {
            NoAST_Logic *data = (NoAST_Logic*)no->data;
            
            if (data->op == OP_AND) {
                char* label_fim_and = novo_label();
                
                // Avalia o lado esquerdo
                char* res_esq = gerarTAC_impl(data->esquerda);
                
                // Prepara um temporário para o resultado final, inicializando com o primeiro resultado
                char* resultado_final = novo_temp();
                printf("%s = %s\n", resultado_final, res_esq);

                // Se o lado esquerdo for falso, pula a avaliação do direito
                printf("if_false %s goto %s\n", res_esq, label_fim_and);
                free(res_esq); // Libera o temporário, pois o valor já foi copiado

                // Se não pulou, avalia o lado direito
                char* res_dir = gerarTAC_impl(data->direita);
                // O resultado final agora é o resultado do lado direito
                printf("%s = %s\n", resultado_final, res_dir);
                free(res_dir);

                // Emite o rótulo de fim
                printf("%s:\n", label_fim_and);
                free(label_fim_and);

                // Retorna o temporário que contém o resultado final da expressão
                return resultado_final;

            } else if (data->op == OP_OR) {
                char* label_verdadeiro = novo_label();
                char* label_fim_or = novo_label();
                
                // Avalia o lado esquerdo
                char* res_esq = gerarTAC_impl(data->esquerda);
                
                char* resultado_final = novo_temp();
                printf("%s = %s\n", resultado_final, res_esq);

                // Se o lado esquerdo for VERDADEIRO, pula a avaliação do direito
                // (Usando if_true que pode ser implementado no backend ou simulado)
                printf("if_true %s goto %s\n", res_esq, label_verdadeiro);
                free(res_esq);

                // Se não pulou, avalia o lado direito
                char* res_dir = gerarTAC_impl(data->direita);
                printf("%s = %s\n", resultado_final, res_dir);
                free(res_dir);
                
                // Salta para o fim
                printf("goto %s\n", label_fim_or);

                // Rótulo para onde saltamos se o resultado já for verdadeiro
                printf("%s:\n", label_verdadeiro);
                // Não precisa fazer nada aqui, pois o resultado em 'resultado_final' já é 1 (true)
                
                printf("%s:\n", label_fim_or);

                free(label_verdadeiro);
                free(label_fim_or);
                
                return resultado_final;
            }
            return NULL;
        }

        // Nós de Bloco/Controle: apenas chamam recursivamente para os filhos
        case BASIC_NODE: {
             // Libera os resultados, pois não são usados neste nível
            char* res_esq = gerarTAC_impl(no->esquerda);
            if(res_esq) free(res_esq);
            char* res_dir = gerarTAC_impl(no->direita);
            if(res_dir) free(res_dir);
            return NULL;
        }


         case WHILE_NODE: {
            NoAST_while *data = (NoAST_while*)no->data;

            // 1. Cria os rótulos necessários para o início e o fim do loop.
            char* label_inicio = novo_label();
            char* label_fim = novo_label();

            // 2. Emite o rótulo de início.
            printf("%s:\n", label_inicio);

            // 3. Processa a condição do loop.
            char* cond_res = gerarTAC_impl(data->condition);
            printf("if_false %s goto %s\n", cond_res, label_fim);
            free(cond_res);

            // 4. Processa o corpo do loop.
            // A chamada recursiva aqui cuidará de todo o código dentro do while.
            gerarTAC_impl(data->while_branch);

            // 5. Emite o salto incondicional de volta para o início para repetir o ciclo.
            printf("goto %s\n", label_inicio);

            // 6. Emite o rótulo de fim, para onde o 'if_false' salta.
            printf("%s:\n", label_fim);
            
            // Libera a memória dos nomes dos rótulos.
            free(label_inicio);
            free(label_fim);
            
            return NULL; // While é um statement, não retorna valor.
        }

        case FOR_NODE: {
            NoAST_for *data = (NoAST_for*)no->data;
            
            // 1. Gera o código para a inicialização (parte A)
            if (data->initialize) {
                gerarTAC_impl(data->initialize);
            }

            // 2. Cria os rótulos para o loop, como no 'while'
            char* label_inicio = novo_label();
            char* label_fim = novo_label();

            // 3. Emite o rótulo de início do loop
            printf("%s:\n", label_inicio);

            // 4. Processa a condição (parte B)
            if (data->condition) {
                char* cond_res = gerarTAC_impl(data->condition);
                printf("if_false %s goto %s\n", cond_res, label_fim);
                free(cond_res);
            }
            
            // 5. Processa o corpo do for (parte D)
            if (data->for_branch) {
                gerarTAC_impl(data->for_branch);
            }
            
            // 6. Processa o incremento (parte C)
            if (data->increment) {
                gerarTAC_impl(data->increment);
            }

            // 7. Salta de volta para o início
            printf("goto %s\n", label_inicio);

            // 8. Emite o rótulo de fim
            printf("%s:\n", label_fim);
            
            free(label_inicio);
            free(label_fim);
            
            return NULL;
        }

         case FUNC_DEF_NODE: {
            NoAST_FuncDef *data = (NoAST_FuncDef*)no->data;
            Simbolo* func_simbolo = data->func_entry;

            // Conta os parâmetros para a instrução begin_func
            int num_params = 0;
            Parametro* p_count = data->params_list;
            while(p_count) {
                num_params++;
                p_count = p_count->prox;
            }
            
            // Emite o marcador de início, agora com o número de parâmetros
            printf("begin_func %s, %d\n", func_simbolo->nome, num_params);

            // ENTRA EM UM NOVO ESCOPO para a função
            enterScope();
            
            // --- Lógica para registrar os parâmetros na Tabela de Símbolos ---
            Parametro* p_current = data->params_list;
            while (p_current) {
                // Para cada parâmetro na definição, insere-o na tabela do escopo atual
                inserirNaTabela(current_scope->symbol_table, p_current->nome, "int"); // Assumindo tipo int por enquanto
                p_current = p_current->prox;
            }
            // --- Fim da lógica dos parâmetros ---

            // Processa o corpo da função (agora ele poderá encontrar os parâmetros na tabela)
            if (data->body) {
                char* res = gerarTAC_impl(data->body);
                if (res) free(res);
            }

            // SAI DO ESCOPO da função
            exitScope();

            // Emite o marcador de fim da função
            printf("end_func\n");
            
            return NULL; 
        }

        case FUNC_CALL_NODE: {
            NoAST_Func_Call *data = (NoAST_Func_Call*)no->data;
            Simbolo* func_simbolo = data->entry;

            // --- Lógica para processar os argumentos ---
            int num_params = 0;
            char* arg_results[20]; // Suporta até 20 argumentos. Aumente se precisar.

            NoAST* arg_list_node = data->args;
            while(arg_list_node != NULL && arg_list_node->type == EXPR_LIST_NODE) {
                No_Expr_List* arg_item = (No_Expr_List*)arg_list_node->data;
                
                // Gera o código para a expressão do argumento e guarda o resultado
                arg_results[num_params] = gerarTAC_impl(arg_item->expr);
                num_params++;

                arg_list_node = arg_item->next;
            }

            // Emite as instruções 'param' na ordem inversa (da direita para a esquerda)
            for (int i = num_params - 1; i >= 0; i--) {
                printf("param %s\n", arg_results[i]);
                free(arg_results[i]); // Libera a memória do resultado do argumento
            }

            // Gera a instrução de chamada com o número correto de parâmetros
            printf("call %s, %d\n", func_simbolo->nome, num_params);
            
            if (num_params > 0) {
                 printf("pop_params %d\n", num_params);
            }

            // Cria um temporário para receber o valor de retorno
            char* temp_ret = novo_temp();
            printf("%s = get_retval\n", temp_ret);

            // Retorna o temporário que contém o valor
            return temp_ret;
        }
        
        case RETURN_NODE: {
            NoAST_Return *data = (NoAST_Return*)no->data;
            
            // Processa a expressão que está sendo retornada
            char* val_retorno = gerarTAC_impl(data->ret_val);
            
            // Emite a instrução de retorno
            printf("return %s\n", val_retorno);
            
            free(val_retorno);
            return NULL; // Return é um statement.
        }

        default:
            // Para qualquer outro nó não tratado, apenas visitamos os filhos genéricos
            // se eles existirem. Isso permite que blocos de código funcionem.
            if (no->esquerda) {
                char* res = gerarTAC_impl(no->esquerda);
                if(res) free(res);
            }
            if (no->direita) {
                char* res = gerarTAC_impl(no->direita);
                if(res) free(res);
            }
            return NULL;
    }
}