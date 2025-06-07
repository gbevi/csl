#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "tabela.h"


NoAST *criarNo(Node_Type type, NoAST *esquerda, NoAST *direita){
    NoAST *v = malloc (sizeof(NoAST));

    v->type = type;
    v->esquerda = esquerda;
    v->direita = direita;

    return v;
}

NoAST *criarNoDecl(int dataType, list_t **names){
    NoAST_Decl *v = malloc(sizeof(NoAST_Decl));

    v->dateType = dataType;
    v->names = names;
    v->type = DECL_NODE;

    return (struct NoAST *) v;
}

NoAST *criarNoConst(int const_type, Value val){
    NoAST_Const *v = malloc(sizeof(NoAST_Const));

    v->type = CONST_NODE;
    v->const_type = const_type;
    v->val = val;

    return (struct NoAST*) v;
}


NoAST *criarNoIf(NoAST *condition, NoAST *if_branch, NoAST **elseif_branchs, int elseif_count, NoAST *elseif_branch) {
    NoAST_if *v = mallox(sizeof(NoAST_if));

    v->type = IF_NODE;
    v->condition = condition;
    v->if_branch = if_branch;
    v->elsif_branchs = elseif_branchs;
    v->elseif_count = elseif_count;
    v->else_branch;

    return (struct NoAST *) v;

}

NoAST *criarNoElsif(NoAST *condition, NoAST *elsif_branch) {
    NoAST_elsif *v = malloc(sizeof(NoAST_elsif));

    v->type = ELSIF_NODE;
    v->condition = condition;
    v->elsif_branch = elsif_branch;

    return (struct NoAST *) v;
}

NoAST *criarNoFor(NoAST *initialize, NoAST *condition, NoAST *increment, NoAST *for_branch) {
    NoAST_for *v = malloc (sizeof(NoAST_for));

    v->type = FOR_NODE;
    v->initialize = initialize;
    v->increment = increment;
    v->for_branch = for_branch;

    return (struct NoAST *) v;
}

NoAST *criarNoWhile(NoAST *condition, NoAST *while_brach) {
    NoAST_while *v = malloc(sizeof(NoAST_while));

    v->type = WHILE_NODE;
    v->condition = condition;
    v->while_branch = while_brach;

    return (struct NoAST *) v;
}

NoAST *criarNoAssign(list_t *entry, NoAST *assign_val) {
    NoAST_assign *v = malloc(sizeof(NoAST_assign));

    v->type = ASSIGN_NODE;
    v->entry = entry;
    v->assign_val = assign_val;

    return (struct NoAST *) v;
}

NoAST *criarNoSimple(int statement_type) {
    NoAST_simple *v = malloc (sizeof(NoAST_simple));

    v->type = SIMPLE_NODE;
    v->statement_type = statement_type;

    return (struct NoAST *) v;
}

NoAST *criarNoIncr(list_t *entry, int incr_type, int pf_type) {
    NoAST_incr *v = malloc (sizeof(NoAST_incr));

    v->type = INCR_NODE;
    v->entry = entry;
    v->incr_type = incr_type;
    v->pf_type = pf_type;

    return (struct NoAST *) v;
}

NoAST *criarNoFuncCall(list_t *entry, NoAST **params, int num_of_pars) {
    NoAST_Func_Call *v = malloc (sizeof(NoAST_Func_Call));

    v->type = FUNC_CALL;
    v->entry = entry;
    v->params = params;
    v->num_of_pars = num_of_pars;

    return (struct NoAST *) v;
}

NoAST *criarNoArithm(enum Arithm_op op, NoAST *esquerda, NoAST *direita){
    NoAST_Arithm *v = malloc (sizeof (NoAST_Arithm));
	
	v->type = ARITHM_NODE;
	v->op = op;
	v->esquerda = esquerda;
	v->direita = direita;
		return (struct AST_Node *) v;
}

NoAST *criarNoBool(enum Bool_op op, NoAST *esquerda, NoAST *direita){
	NoAST_Bool *v = malloc (sizeof (NoAST_Bool));
	
	v->type = BOOL_NODE;
    v->op = op;
	v->esquerda = esquerda;
	v->direita = direita;
	
	return (struct NoAST *) v;
}

NoAST *criarNoRel(enum Rel_op op, NoAST *esquerda, NoAST *direita){
    NoAST_Rel *v = malloc(sizeof(NoAST_Rel));

    v->type = REL_NODE;
    v->op = op;
    v->esquerda = esquerda;
    v->direita = direita;

    return (struct NoAST *) v;
}

NoAST *criarNoEque(enum Equal_op op, NoAST *esquerda, NoAST *direita){
    NoAST_Equ *v = malloc(sizeof(NoAST_Equ));

    v->type = EQU_NODE;
    v->op = op;
    v->esquerda = esquerda;
    v->direita = direita;

    return (struct NoAST *) v;
}

NoAST *criarNoFuncDecl(int ret_type, list_t *entry){
    NoAST_Func_Decl *v = malloc(sizeof(NoAST_Func_Decl));

    v->type = FUNC_DECL;
    v->ret_type = ret_type;
    v->entry = entry;

    return (struct NoAST *) v;
}

NoAST *criarNoReturn(int ret_type, NoAST *ret_val){
    NoAST_Return *v = malloc(sizeof(NoAST_Return));

    v->type = FUNC_DECL;
    v->ret_type = ret_type;
    v->ret_val;

    return (struct NoAST *) v;
}

void imprimirAST(NoAST *no) {

    NoAST_Decl *temp_decl;
    NoAST_Const *temp_const;
    NoAST_if *temp_if;
	NoAST_assign *temp_assign;
	NoAST_simple *temp_simple;
	NoAST_incr *temp_incr;
	NoAST_Func_Call *temp_func_call;
	NoAST_Arithm *temp_arithm;
	NoAST_Bool *temp_bool;
	NoAST_Rel *temp_rel;
	NoAST_Equ *temp_equ;
	NoAST_Func_Decl *temp_func_decl;
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
		case FOR_NODE:
			printf("For Node\n");
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
    else if(no->type == ELSIF_NODE){
		NoAST_elsif *temp_elsif = (struct AST_Node_Elsif *) no;
		gerarTAC(temp_elsif->condition);
		gerarTAC(temp_elsif->elsif_branch);
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
		NoAST_assign *temp_assign = (struct AST_Node_Assign *) no;
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