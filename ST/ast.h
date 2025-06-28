#ifndef  AST_H
#define  AST_H

#include "tabela.h"

typedef enum {
    TIPO_INT,
    TIPO_FLOAT,
    TIPO_DOUBLE,
    TIPO_CHAR,
    TIPO_STRING,
    TIPO_BOOLEAN,
    TIPO_UNKNOWN, // inferencia de tipo
    TIPO_VOID, // pra funções void
    TIPO_INVALIDO // pra erros e valores invalidos
} DataType;

typedef enum Node_Type {
    // nós básicos
    BASIC_NODE,
    ID_NODE,
    CONST_NODE,

    // operações
    ASSIGN_NODE, // =
    ARITHM_NODE, // + - * /
    LOGIC_OP_NODE, // and or not
    REL_OP_NODE, // já inclui == != < > <= >=

    // estruturas de controle
    IF_NODE,
    ELSIF_NODE,
    ELSE_NODE,
    FOR_HEADER_NODE,
    FOR_IN_NODE,
    RANGE_NODE, // pro for com 'do'
    WHILE_NODE,
    FUNC_CALL_NODE, // chamada de função
    EXPR_LIST_NODE, // lista de expressões (para argumentos de funçõs)
    FUNC_DEF_NODE, // definição de função
    SWITCH_NODE,
    RETURN_NODE,
}Node_Type;

typedef enum Arithm_op{
    OP_ADICAO,
    OP_SUBTRACAO,
    OP_MULTIPLICACAO, 
    OP_DIVISAO
} Arithm_op;

typedef enum Bool_op{
    OP_OR,
    OP_AND,
    OP_NOT,
}Bool_op;

typedef enum Rel_op{
    OP_REL_EQ,  // == 
    OP_REL_NEQ, // !=
    OP_REL_LT,  // <
    OP_REL_GT,  // >
    OP_REL_LE,  // <=
    OP_REL_GE   // >=
}Rel_op;

typedef union Value{
    int valint;
    double valfloat; 
    char valchar;
    char *valstring;
}Value;

typedef struct NoAST {
    Node_Type type;
    struct NoAST *esquerda;
    struct NoAST *direita;
    void *data; // ponteiro genérico para a struct específica do nó
    Simbolo *simbolo; // adicionando esse campo para nós mais simples q n
                    // precisam de data
} NoAST;

extern NoAST *raiz; 

typedef struct NoAST_Const{
    Node_Type type;
    DataType const_type;
    Value val;
}NoAST_Const;

typedef struct NoAST_Id {
    Node_Type type; 
    char *name;
    Simbolo *entry;
} NoAST_Id;

typedef struct NoAST_if{
    Node_Type type;
    struct NoAST *condition;
    struct NoAST *if_branch;
    struct NoAST *next_branch;
}NoAST_if;

typedef struct NoAST_ForIn {
    Node_Type type; 
    NoAST *iterator_id; 
    NoAST *collection_expr; 
    NoAST *body; 
} NoAST_ForIn;

typedef struct NoAST_Range {
    Node_Type type;
    struct NoAST *start;
    struct NoAST *end;
    int exclusive; // 0 para .., 1 para ...
} NoAST_Range;

typedef struct NoAST_while{
    Node_Type type;
    struct NoAST *condition;
    struct NoAST *while_branch;
}NoAST_while;

typedef struct NoAST_Assign{
    Node_Type type;
    Simbolo *target_entry; // void pra evitar dependencia circular
    struct NoAST *value_expr;
}NoAST_Assign;

// remover dps (mas talvez seja útil pra implementar +=)
typedef struct NoAST_incr{
	Node_Type type;
	Simbolo *entry;
	int incr_type; 
	int pf_type; 
}NoAST_incr;

typedef struct NoExprList {
    Node_Type tipo_no; 
    struct NoAST *expr; 
    struct NoAST *next; 
}No_Expr_List;

typedef struct NoAST_Func_Call {
    Simbolo *entry;
    No_Expr_List* args_list_head;
} NoAST_Func_Call;



typedef struct NoAST_FuncDef {
    Node_Type type; 
    Simbolo *func_entry;
    Parametro *params_list; 
    NoAST *body;
} NoAST_FuncDef;

typedef struct NoAST_Arithm{
	Node_Type type; 
	Arithm_op op;
	struct NoAST *esquerda;  
	struct NoAST *direita;
}NoAST_Arithm;

typedef struct NoAST_Logic{
	Node_Type type; 
	Bool_op op;
	struct NoAST *esquerda;  
	struct NoAST *direita; 
}NoAST_Logic;

typedef struct NoAST_Rel{
	Node_Type type;
	Rel_op op;
	struct NoAST *esquerda; 
	struct NoAST *direita; 
}NoAST_Rel;

typedef struct NoAST_Return{
	Node_Type type; 
	struct NoAST *ret_val;
}NoAST_Return;

typedef struct NoAST_Case {
    int case_value;
    struct NoAST *stmt;
    struct NoAST_Case *next_case;
} NoAST_Case;

typedef struct NoAST_Switch {
    struct NoAST *expr;            
    NoAST_Case *case_list;         
    struct NoAST *default_case;   
} NoAST_Switch;

NoAST *criarNo(Node_Type type, NoAST *esquerda, NoAST *direita);

NoAST *criarNoConst(DataType const_type, Value val);

NoAST *criarNoId(char *name, Simbolo *entry); 

NoAST *criarNoIfElseChain(Node_Type type, NoAST *condition, NoAST *branch_block, NoAST *next_branch);

NoAST *criarNoForIn(NoAST *iterator_id, NoAST *collection_expr, NoAST *body);

NoAST *criarNoRange(NoAST *start_expr, NoAST *end_expr, int exclusive);

NoAST *criarNoWhile(NoAST *condition, NoAST *while_brach);

NoAST *criarNoAssign(Simbolo *target_entry, NoAST *value_expr);

// remover se não for implementado +=
NoAST *criarNoIncr(Simbolo *entry, int incr_type, int pf_type);

NoAST *criarNoFuncDef(Simbolo *symbol_entry, Parametro *parameters, NoAST *body);

NoAST* criarNoFuncCall(Simbolo *entry, NoAST *args_list);

NoAST* criarNoExprList(NoAST *expr, NoAST *next_expr_list);

NoAST *criarNoArithm(Arithm_op op, NoAST *esquerda, NoAST *direita);

NoAST *criarNoLogic(Bool_op op, NoAST *esquerda, NoAST *direita);

NoAST *criarNoRel(Rel_op op, NoAST *esquerda, NoAST *direita);

NoAST *criarNoReturn(NoAST *ret_val);

void imprimirAST(NoAST *node, int indent);

NoAST** convert_sequence_to_array(NoAST *sequence_node, int *count);

const char* Node_Type_to_String(Node_Type type);

NoAST* criarNoSwitch(NoAST* expr, NoAST_Case* cases, NoAST* default_stmt);
NoAST_Case* criarNoCase(int case_value, NoAST* stmt);
void adicionarCase(NoAST_Case** head, NoAST_Case* new_case);
NoAST* criarNoReturn(NoAST* expr);


#endif