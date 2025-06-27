#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tabela.h"
#include "ast.h"

NoAST *raiz = NULL; 

NoAST *criarNo(Node_Type type, NoAST *esquerda, NoAST *direita){
    NoAST *v = malloc (sizeof(NoAST));

    v->type = type;
    v->esquerda = esquerda;
    v->direita = direita;
	v->data = NULL;
    v->simbolo = NULL;
    return v;
}

NoAST* criarNoConst(DataType const_type, Value val) {
    NoAST_Const *const_node = (NoAST_Const *)malloc(sizeof(NoAST_Const));
    const_node->const_type = const_type;
    const_node->val = val; 

    NoAST *base_node = criarNo(CONST_NODE, NULL, NULL); 
    base_node->data = const_node;
    
    // DEBUG ADICIONADO: Verifique o ponteiro retornado
    fprintf(stderr, "DEBUG-AST: criarNoConst retornando NoAST* %p (const_type: %d)\n", (void*)base_node, const_type);
    
    return base_node;
}

NoAST *criarNoId(char *name, Simbolo *entry) {
    NoAST_Id *id_node = malloc(sizeof(NoAST_Id));

    id_node->type = ID_NODE;
    id_node->name = strdup(name); 
    id_node->entry = entry;

    NoAST *node = criarNo(ID_NODE, NULL, NULL);
    node->data = id_node;
    node->simbolo = entry;
    return node;
}


NoAST *criarNoIfElseChain(Node_Type type, NoAST *condition, NoAST *branch_block, NoAST *next_branch) {
    NoAST_if *v = malloc(sizeof(NoAST_if));

    v->type = type;
    v->condition = condition; 
    v->if_branch = branch_block;
    v->next_branch = next_branch;

    NoAST *base_node = criarNo(type, NULL, NULL); 
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

NoAST *criarNoAssign(Simbolo *target_entry, NoAST *value_expr) {
    NoAST_Assign *assign_node_data = malloc(sizeof(NoAST_Assign));

    assign_node_data->type = ASSIGN_NODE;
    assign_node_data->target_entry = target_entry;
    assign_node_data->value_expr = value_expr;

    NoAST *node = criarNo(ASSIGN_NODE, NULL, NULL);
    node->data = assign_node_data;
    node->simbolo = target_entry;
    return node;
}

/*
NoAST *criarNoIncr(Simbolo *entry, int incr_type, int pf_type) {
    NoAST_incr *v = malloc (sizeof(NoAST_incr));

    v->type = INCR_NODE;
    v->entry = entry;
    v->incr_type = incr_type;
    v->pf_type = pf_type;

    return (struct NoAST *) v;
}*/

NoAST* criarNoFuncCall(Simbolo *entry, NoAST *args_node) { // args_node é o NoAST* EXPR_LIST_NODE
    NoAST_Func_Call *func_call_node = (NoAST_Func_Call *)malloc(sizeof(NoAST_Func_Call));
    if (!func_call_node) {
        perror("malloc NoAST_Func_Call");
        exit(EXIT_FAILURE);
    }
    func_call_node->entry = entry;
    
    // Agora, extraia o No_Expr_List* do campo 'data' do NoAST* args_node
    if (args_node && args_node->type == EXPR_LIST_NODE && args_node->data) {
        func_call_node->args_list_head = (No_Expr_List*)args_node->data; // <<<<<< CORREÇÃO CRÍTICA
    } else {
        func_call_node->args_list_head = NULL;
    }

    NoAST *base_node = criarNo(FUNC_CALL_NODE, NULL, NULL);
    base_node->data = func_call_node;
    return base_node;
}

NoAST* criarNoExprList(NoAST *expr, NoAST *next_expr_list) {
    No_Expr_List *node = malloc(sizeof(No_Expr_List));
    node->tipo_no = EXPR_LIST_NODE;
    node->expr = expr;
    node->next = next_expr_list; 

    NoAST *base_node = criarNo(EXPR_LIST_NODE, NULL, NULL); 
    base_node->data = node;

    fprintf(stderr, "DEBUG-AST: criarNoExprList retornando NoAST* %p\n", (void*)base_node);

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

    return (struct NoAST *) v;
}

const char* node_type_to_string(Node_Type type) {
    switch (type) {
        case BASIC_NODE: return "BASIC_NODE";
        case ID_NODE: return "ID_NODE";
        case CONST_NODE: return "CONST_NODE";
        case ASSIGN_NODE: return "ASSIGN_NODE";
        case ARITHM_NODE: return "ARITHM_NODE";
        case LOGIC_OP_NODE: return "LOGIC_OP_NODE";
        case REL_OP_NODE: return "REL_OP_NODE";
        case IF_NODE: return "IF_NODE";
        case ELSIF_NODE: return "ELSIF_NODE";
        case ELSE_NODE: return "ELSE_NODE";
        case FOR_HEADER_NODE: return "FOR_HEADER_NODE";
        case FOR_IN_NODE: return "FOR_IN_NODE";
        case RANGE_NODE: return "RANGE_NODE";
        case WHILE_NODE: return "WHILE_NODE";
        case FUNC_CALL_NODE: return "FUNC_CALL_NODE";
        case EXPR_LIST_NODE: return "EXPR_LIST_NODE";
        case FUNC_DEF_NODE: return "FUNC_DEF_NODE";
        case RETURN_NODE: return "RETURN_NODE";
        default: return "UNKNOWN_NODE";
    }
}

void imprimirAST(NoAST *node, int indent) {
    if (!node) {
        return;
    }

    for (int i = 0; i < indent; i++) {
        printf("  "); 
    }

    printf("%s", node_type_to_string(node->type));

    switch (node->type) {
        case ID_NODE: {
            NoAST_Id *id_node = (NoAST_Id *)node->data;
            printf(": %s\n", id_node->name);
            break; 
        }
        case CONST_NODE: {
            NoAST_Const *const_node = (NoAST_Const *)node->data;
            printf(" (Tipo: %d) - Valor: ", const_node->const_type);
            switch (const_node->const_type) {
                case TIPO_INT: printf("%d\n", const_node->val.valint); break;
                case TIPO_FLOAT: printf("%f\n", const_node->val.valfloat); break;
                case TIPO_STRING: printf("\"%s\"\n", const_node->val.valstring); break;
                case TIPO_CHAR: printf("'%c'\n", const_node->val.valchar); break;
                case TIPO_BOOLEAN: printf("%s\n", const_node->val.valint ? "true" : "false"); break;
                default: printf("N/A\n"); break;
            }
            break;
        }
        case BASIC_NODE: {
            printf("\n");
            imprimirAST(node->esquerda, indent);  
            imprimirAST(node->direita, indent);  
            break;
        }
        case ARITHM_NODE: {
            NoAST_Arithm *op_node = (NoAST_Arithm *)node->data;
            switch(op_node->op) {
                case OP_ADICAO: printf(": +\n"); break;
                case OP_SUBTRACAO: printf(": -\n"); break;
                case OP_MULTIPLICACAO: printf(": *\n"); break;
                case OP_DIVISAO: printf(": /\n"); break;
            }
            imprimirAST(op_node->esquerda, indent + 1);
            imprimirAST(op_node->direita, indent + 1);
            break;
        }
        case REL_OP_NODE: {
            NoAST_Rel *op_node = (NoAST_Rel *)node->data;
            switch(op_node->op) {
                case OP_REL_EQ: printf(": ==\n"); break;
                case OP_REL_NEQ: printf(": !=\n"); break;
                case OP_REL_LT: printf(": <\n"); break;
                case OP_REL_GT: printf(": >\n"); break;
                case OP_REL_LE: printf(": <=\n"); break;
                case OP_REL_GE: printf(": >=\n"); break;
            }
            imprimirAST(op_node->esquerda, indent + 1);
            imprimirAST(op_node->direita, indent + 1);
            break;
        }
        case LOGIC_OP_NODE: {
            NoAST_Logic *op_node = (NoAST_Logic *)node->data;
             switch(op_node->op) {
                case OP_AND: printf(": AND\n"); break;
                case OP_OR: printf(": OR\n"); break;
                case OP_NOT: printf(": NOT\n"); break;
            }
            imprimirAST(op_node->esquerda, indent + 1);
            imprimirAST(op_node->direita, indent + 1); 
            break;
        }
        case ASSIGN_NODE: {
            NoAST_Assign *assign_node = (NoAST_Assign *)node->data;
            printf(" (Para: %s)\n", assign_node->target_entry->nome);
            imprimirAST(assign_node->value_expr, indent + 1);
            break;
        }
        case IF_NODE:
        case ELSIF_NODE:
        case ELSE_NODE: {
            printf("\n");
            NoAST_if *if_node = (NoAST_if *)node->data;
            
            if (if_node->condition) {
                for (int i = 0; i < indent + 1; i++) printf("  ");
                printf("Condicao:\n");
                imprimirAST(if_node->condition, indent + 2);
            }

            for (int i = 0; i < indent + 1; i++) printf("  ");
            printf("Bloco:\n");
            imprimirAST(if_node->if_branch, indent + 2);

            if (if_node->next_branch) {
                imprimirAST(if_node->next_branch, indent); 
            }
            break;
        }
        case WHILE_NODE: {
            printf("\n");
            NoAST_while *while_node = (NoAST_while *)node->data;
            for (int i = 0; i < indent + 1; i++) printf("  ");
            printf("Condicao:\n");
            imprimirAST(while_node->condition, indent + 2);

            for (int i = 0; i < indent + 1; i++) printf("  ");
            printf("Bloco:\n");
            imprimirAST(while_node->while_branch, indent + 2);
            break;
        }
        case FUNC_CALL_NODE: {
            /*
            NoAST_Func_Call *call_node = (NoAST_Func_Call *)node->data;
            printf(": %s\n", call_node->entry->nome);
            if (call_node->args) {
                for (int i = 0; i < indent + 1; i++) printf("  ");
                printf("Argumentos:\n");
                imprimirAST(call_node->args, indent + 2);
            }
            break;*/
        }
        case EXPR_LIST_NODE: {
            printf("\n");
            NoAST* current_list_node = node;
            while(current_list_node && current_list_node->type == EXPR_LIST_NODE) {
                No_Expr_List *list_data = (No_Expr_List*)current_list_node->data;
                imprimirAST(list_data->expr, indent); 
                current_list_node = list_data->next; 
            }
            break;
        }
        case FOR_IN_NODE: {
            printf("\n");
            NoAST_ForIn *for_node = (NoAST_ForIn *)node->data;
            for (int i = 0; i < indent + 1; i++) printf("  ");
            printf("Iterador:\n");
            imprimirAST(for_node->iterator_id, indent + 2);

            for (int i = 0; i < indent + 1; i++) printf("  ");
            printf("Colecao:\n");
            imprimirAST(for_node->collection_expr, indent + 2);

            for (int i = 0; i < indent + 1; i++) printf("  ");
            printf("Bloco:\n");
            imprimirAST(for_node->body, indent + 2);
            break;
        }
        case RANGE_NODE: {
            NoAST_Range* range_node = (NoAST_Range*)node->data;
            printf(" (Exclusive: %d)\n", range_node->exclusive);
            
            for (int i = 0; i < indent + 1; i++) printf("  ");
            printf("Inicio:\n");
            imprimirAST(range_node->start, indent+2);

            for (int i = 0; i < indent + 1; i++) printf("  ");
            printf("Fim:\n");
            imprimirAST(range_node->end, indent+2);
            break;
        }
        case FUNC_DEF_NODE: {
            NoAST_FuncDef *func_def = (NoAST_FuncDef *)node->data;
            printf(": %s\n", func_def->func_entry->nome);
            
            if (func_def->params_list) {
                 for (int i = 0; i < indent + 1; i++) printf("  ");
                 printf("Parametros:\n");
                 Parametro* param = func_def->params_list;
                 while(param) {
                    for (int i = 0; i < indent + 2; i++) printf("  ");
                    printf("PARAM: %s\n", param->nome);
                    param = param->prox;
                 }
            }

            for (int i = 0; i < indent + 1; i++) printf("  ");
            printf("Corpo:\n");
            imprimirAST(func_def->body, indent + 2);
            break;
        }
        case RETURN_NODE: {
            printf("\n");
            NoAST_Return *return_node = (NoAST_Return *)node->data;
            imprimirAST(return_node->ret_val, indent + 1);
            break;
        }
        default:
            printf(" (Tipo de no nao implementado na impressao)\n");
            break;
    }
}

const char* Node_Type_to_String(Node_Type type) {
    switch(type) {
        case BASIC_NODE: return "BASIC_NODE";
        case ID_NODE: return "ID_NODE";
        case CONST_NODE: return "CONST_NODE";
        case ASSIGN_NODE: return "ASSIGN_NODE";
        case ARITHM_NODE: return "ARITHM_NODE";
        case LOGIC_OP_NODE: return "LOGIC_OP_NODE";
        case REL_OP_NODE: return "REL_OP_NODE";
        case IF_NODE: return "IF_NODE";
        case ELSIF_NODE: return "ELSIF_NODE";
        case ELSE_NODE: return "ELSE_NODE";
        case FOR_IN_NODE: return "FOR_IN_NODE";
        // Adicione outros casos conforme for testando
        default: return "UNKNOWN_NODE";
    }
}
