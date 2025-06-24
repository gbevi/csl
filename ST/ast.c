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
    v->simbolo = NULL;
    return v;
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

NoAST *criarNoFuncCall(Simbolo *entry, NoAST *args_list) {
    NoAST_Func_Call *v = malloc (sizeof(NoAST_Func_Call));

    v->type = FUNC_CALL_NODE;
    v->entry = entry;
    v->args = args_list;

    NoAST *base_node = criarNo(FUNC_CALL_NODE, NULL, NULL);
    base_node->data = v;
    base_node->simbolo = entry;
    return base_node;
}

NoAST* criarNoExprList(NoAST *expr, NoAST *next_expr_list) {
    No_Expr_List *node = malloc(sizeof(No_Expr_List));
    node->tipo_no = EXPR_LIST_NODE;
    node->expr = expr;
    node->next = next_expr_list; // next é o início da lsita

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

void imprimirAST(NoAST *node, int indent) {
    if (!node) return;

    for (int i = 0; i < indent; i++) printf("  ");

    printf("Type: %d (", node->type);

    switch (node->type) {
        case FUNC_CALL_NODE: {
            NoAST_Func_Call *func_node = (NoAST_Func_Call*)node;
            printf("Type: FUNC_CALL (Nome: %s)\n", func_node->entry->nome);
            if (func_node->args) {
                imprimirAST(func_node->args, indent + 1); // Imprime os argumentos
            }
            break;
        }
        case EXPR_LIST_NODE: {
            No_Expr_List *list_node = (No_Expr_List*)node;
            printf("Type: EXPR_LIST\n");
            // Percorre a lista de expressões
            No_Expr_List *current_node = list_node;
            while (current_node) {
                imprimirAST(current_node->expr, indent + 1);
                // IMPORTANTE: A lista é construída de trás para frente no Bison.
                // O 'next' aponta para o que foi adicionado *antes* dele.
                // Para imprimir na ordem correta, você pode precisar de uma lógica diferente,
                // ou simplesmente aceitar a ordem inversa na AST por enquanto.
                // Por simplicidade agora, vou manter a impressão de 'next'.
                current_node = (No_Expr_List*)current_node->next;
            }
            break;
        }
        case ARITHM_NODE: {
            NoAST_Arithm *arithm_node = (NoAST_Arithm *)node->data;
            printf("ARITH_OP - ");
            switch (arithm_node->op) {
                case OP_ADICAO: printf("+"); break;
                case OP_SUBTRACAO: printf("-"); break;
                case OP_MULTIPLICACAO: printf("*"); break;
                case OP_DIVISAO: printf("/"); break;
            }
            break;
        }
        case LOGIC_OP_NODE: {
            NoAST_Logic *logic_node = (NoAST_Logic *)node->data;
            printf("LOGIC_OP - ");
            switch (logic_node->op) {
                case OP_AND: printf("AND"); break;
                case OP_OR: printf("OR"); break;
                case OP_NOT: printf("NOT"); break;
            }
            break;
        }
        case REL_OP_NODE: {
            NoAST_Rel *rel_node = (NoAST_Rel *)node->data;
            printf("REL_OP - ");
            switch (rel_node->op) {
                case OP_REL_EQ: printf("=="); break;
                case OP_REL_NEQ: printf("!="); break;
                case OP_REL_LT: printf("<"); break;
                case OP_REL_GT: printf(">"); break;
                case OP_REL_LE: printf("<="); break;
                case OP_REL_GE: printf(">="); break;
            }
            break;
        }
        case IF_NODE:
        case ELSE_NODE: {
            NoAST_if *if_node_data = (NoAST_if *)node->data;
            if (if_node_data->condition) {
                for (int i = 0; i < indent + 1; i++) printf("  ");
                printf("  Condition:\n");
                imprimirAST(if_node_data->condition, indent + 2);
            }
            if (if_node_data->if_branch) { // Seu campo é if_branch
                for (int i = 0; i < indent + 1; i++) printf("  ");
                printf("  Block:\n");
                imprimirAST(if_node_data->if_branch, indent + 2);
            }
            if (if_node_data->next_branch) {
                for (int i = 0; i < indent + 1; i++) printf("  ");
                printf("  Next Branch:\n");
                imprimirAST(if_node_data->next_branch, indent + 1); // Mesmo nível para o próximo ramo
            }
            break;
        }
    }
    printf(")\n");

    if (node->type == BASIC_NODE) {
        imprimirAST(node->esquerda, indent + 1);
        imprimirAST(node->direita, indent + 1);
    } else if (node->data != NULL) {
        switch (node->type) {
            case ASSIGN_NODE:
                imprimirAST(((NoAST_Assign *)node->data)->value_expr, indent + 1);
                break;
            case ARITHM_NODE:
            case LOGIC_OP_NODE:
            case REL_OP_NODE: 
                imprimirAST(((NoAST_Arithm *)node->data)->esquerda, indent + 1); 
                if (((NoAST_Arithm *)node->data)->direita) {
                    imprimirAST(((NoAST_Arithm *)node->data)->direita, indent + 1);
                }
                break;
            default:
                break;
        }
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

/*
void imprimirAST(NoAST *no) {

    NoAST_Const *temp_const;
    NoAST_if *temp_if;
	NoAST_Assign *temp_assign;
	NoAST_incr *temp_incr;
	NoAST_Func_Call *temp_func_call;
	NoAST_Arithm *temp_arithm;
	NoAST_Logic *temp_bool;
	NoAST_Rel *temp_rel;
	NoAST_Return *temp_return;
    
    switch (no->type){
        case BASIC_NODE:
            printf("Basic Node\n");
            break;
        case DECL_NODE:
            temp_decl = (struct NoAST *) no;
			printf("Declaration Node of data-type %d for %d names\n",
				temp_decl->dateType, temp_decl->names);
			break;
        case CONST_NODE:
			temp_const = (struct AST_Node_Const *) no;
			printf("Constant Node of const-type %d\n", temp_const->const_type);
			break;
		case IF_NODE:
			temp_if = (struct AST_Node_If *) no;
			printf("If Node with %d elseifs\n", temp_if->elseif_count);
			break;
		case ELSIF_NODE:
			printf("Elsif Node\n");
			break;
		case WHILE_NODE:
			printf("While Node\n");
			break;
		case ASSIGN_NODE:
			temp_assign = (struct AST_Node_Assign *) no;
			printf("Assign Node of entry %s\n", temp_assign);
			break;
		case SIMPLE_NODE:
			temp_simple = (struct AST_Node_Simple *) no;
			printf("Simple Node of statement %d\n", temp_simple->statement_type);
			break;
		case INCR_NODE:
			temp_incr = (struct AST_Node_Incr *) no;
			printf("Increment Node of entry %s being %d %d\n", 
				temp_incr->entry->st_name, temp_incr->incr_type, temp_incr->pf_type);
			break;
		case FUNC_CALL:
			temp_func_call = (struct AST_Node_Func_Call *) no;
			printf("Function Call Node with %d parameters\n", temp_func_call->num_of_pars);
			break;
		case ARITHM_NODE:
			temp_arithm = (struct AST_Node_Arithm *) no;
			printf("Arithmetic Node of operator %d\n", temp_arithm->op);
			break;
		case BOOL_NODE:
			temp_bool = (struct AST_Node_Bool *) no;
			printf("Boolean Node of operator %d\n", temp_bool->op);
			break;
		case REL_NODE:
			temp_rel = (struct AST_Node_Rel *) no;
			printf("Relational Node of operator %d\n", temp_rel->op);
			break;
		case EQU_NODE:
			temp_equ = (struct AST_Node_Equ *) no;
			printf("Equality Node of operator %d\n", temp_equ->op);
			break;
		case FUNC_DECL:
			temp_func_decl = (struct AST_Node_Func_Decl *) no;
			printf("Function Declaration Node of %s with ret_type %d\n", temp_func_decl->entry->st_name, temp_func_decl->ret_type);
			break;
		case RETURN_NODE:
			temp_return = (struct AST_Node_Return *) no;
			printf("Return Node of ret_type %d\n", temp_return->ret_type);
			break;
		default:
			fprintf(stderr, "Error in node selection!\n");
			exit(1);
    }
}

char* gerarTAC(NoAST *no) {
    int i;

    if(no == NULL){
        return;
    }

    if(no->type == BASIC_NODE || no->type == ARITHM_NODE || no->type == BOOL_NODE
	|| no->type == REL_NODE || no->type == EQU_NODE){
		gerarTAC(no->esquerda);
		gerarTAC(no->direita);
		ast_print_node(no);
	}
    else if(no->type == IF_NODE){
		NoAST_if *temp_if = (struct AST_Node_If *) no;
		gerarTAC(temp_if->condition);
		gerarTAC(temp_if->if_branch);
		for(i = 0; i < temp_if->elseif_count; i++){
			gerarTAC(temp_if->elsif_branchs[i]);
		}
		gerarTAC(temp_if->else_branch);
		ast_print_node(no);
	}
    else if(no->type == FOR_NODE){
		NoAST_for *temp_for = (struct AST_Node_For *) no;
		gerarTAC(temp_for->condition);
		gerarTAC(temp_for->for_branch);
		ast_print_node(no);
	}
    else if(no->type == WHILE_NODE){
		NoAST_while *temp_while = (struct AST_Node_While *) no;
		gerarTAC(temp_while->condition);
		gerarTAC(temp_while->while_branch);
		ast_print_node(no);
	}
    else if(no->type == ASSIGN_NODE){
		NoAST_Assign *temp_assign = (struct AST_Node_Assign *) no;
		gerarTAC(temp_assign->assign_val);
		ast_print_node(no);
	}
    else if(no->type == FUNC_CALL){
		NoAST_Func_Call *temp_func_call = (struct AST_Node_Func_Call *) no;
		for(i = 0; i < temp_func_call->num_of_pars; i++){
			gerarTAC(temp_func_call->params[i]);
		}
		ast_print_node(no);
	}
    else if(no->type == RETURN_NODE){
		NoAST_Return *temp_return = (struct AST_Node_Return *) no;
		gerarTAC(temp_return->ret_val);
		ast_print_node(no);
	}
    else{
		ast_print_node(no);
	}
}

*/