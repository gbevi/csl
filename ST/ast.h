// ast.h - VERSÃO CORRIGIDA

#ifndef AST_H
#define AST_H

#include <stdio.h> // Mantenha seus includes essenciais

// ========================================================================
// CORREÇÃO 1: DECLARAÇÕES FORWARD
// Isso resolve todos os erros de "unknown type name".
// Diz ao compilador: "Confie em mim, esses tipos existem, 
// as definições completas deles estão em outro lugar (tabela.h)".
// ========================================================================
typedef struct Simbolo Simbolo;
typedef struct Parametro Parametro;


// O resto do seu arquivo continua EXATAMENTE IGUAL
typedef enum {
    TIPO_INT, TIPO_FLOAT, TIPO_DOUBLE, TIPO_CHAR, TIPO_STRING,
    TIPO_BOOLEAN, TIPO_UNKNOWN, TIPO_VOID, TIPO_INVALIDO
} DataType;

typedef enum Node_Type {
    BASIC_NODE, ID_NODE, CONST_NODE, ASSIGN_NODE, ARITHM_NODE, LOGIC_OP_NODE,
    REL_OP_NODE, IF_NODE, ELSIF_NODE, ELSE_NODE, FOR_NODE, FOR_HEADER_NODE,
    FOR_IN_NODE, RANGE_NODE, WHILE_NODE, FUNC_CALL_NODE, EXPR_LIST_NODE,
    FUNC_DEF_NODE, RETURN_NODE, DECL_NODE
} Node_Type;

typedef enum Arithm_op { OP_ADICAO, OP_SUBTRACAO, OP_MULTIPLICACAO, OP_DIVISAO } Arithm_op;
typedef enum Bool_op { OP_OR, OP_AND, OP_NOT } Bool_op;
typedef enum Rel_op { OP_REL_EQ, OP_REL_NEQ, OP_REL_LT, OP_REL_GT, OP_REL_LE, OP_REL_GE } Rel_op;
typedef enum Equal_op { EQUAL, NOT_EQUAL } Equal_op;

typedef union Value {
    int valint;
    double valfloat;
    char valchar;
    char *valstring;
} Value;

typedef struct NoAST {
    Node_Type type;
    struct NoAST *esquerda;
    struct NoAST *direita;
    void *data;
} NoAST;

typedef struct NoAST_Decl {
    Node_Type type;
    int dateType;
    Simbolo** names; // OK agora
} NoAST_Decl;

typedef struct NoAST_Const {
    Node_Type type;
    DataType const_type;
    Value val;
} NoAST_Const;

typedef struct NoAST_Id {
    Node_Type type; 
    char *name;
    void *entry;
} NoAST_Id;

typedef struct NoAST_if {
    Node_Type type;
    struct NoAST *condition;
    struct NoAST *if_branch;
    struct NoAST *next_branch;
} NoAST_if;

typedef struct NoAST_elsif {
    Node_Type type;
    struct NoAST *condition;
    struct NoAST *elsif_branch;
} NoAST_elsif;

typedef struct NoAST_for {
    Node_Type type;
    struct NoAST *initialize;
    struct NoAST *condition;
    struct NoAST *increment;
    struct NoAST *for_branch;
} NoAST_for;

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
    int exclusive;
} NoAST_Range;

typedef struct NoAST_while {
    Node_Type type;
    struct NoAST *condition;
    struct NoAST *while_branch;
} NoAST_while;

typedef struct NoAST_Assign {
    Node_Type type;
    void *target_entry;
    struct NoAST *value_expr;
} NoAST_Assign;

typedef struct NoAST_simple {
    Node_Type type;
    int statement_type;
} NoAST_simple;

typedef struct NoAST_incr {
    Node_Type type;
    Simbolo *entry; // OK agora
    int incr_type; 
    int pf_type; 
} NoAST_incr;

typedef struct NoAST_Func_Call {
    Node_Type type; 
    Simbolo *entry; // OK agora
    struct NoAST *args; 
} NoAST_Func_Call;

typedef struct NoExprList {
    Node_Type tipo_no; 
    struct NoAST *expr; 
    struct NoAST *next; 
} No_Expr_List;

typedef struct NoAST_FuncDef {
    Node_Type type; 
    Simbolo *func_entry; // OK agora
    Parametro *params_list; // OK agora
    NoAST *body;
} NoAST_FuncDef;

typedef struct NoAST_Arithm {
    Node_Type type; 
    Arithm_op op;
    struct NoAST *esquerda; 
    struct NoAST *direita;
} NoAST_Arithm;

typedef struct NoAST_Logic {
    Node_Type type; 
    Bool_op op;
    struct NoAST *esquerda; 
    struct NoAST *direita; 
} NoAST_Logic;

typedef struct NoAST_Rel {
    Node_Type type;
    Rel_op op;
    struct NoAST *esquerda; 
    struct NoAST *direita; 
} NoAST_Rel;

typedef struct NoAST_Equ {
    Node_Type type; 
    Equal_op op;
    struct NoAST *esquerda; 
    struct NoAST *direita; 
} NoAST_Equ;

typedef struct NoAST_Func_Decl {
    Node_Type type; 
    int ret_type;
    Simbolo *entry; // OK agora
} NoAST_Func_Decl;

typedef struct NoAST_Return {
    Node_Type type; 
    struct NoAST *ret_val;
} NoAST_Return;

// --- PROTÓTIPOS DAS SUAS FUNÇÕES (sem alteração) ---
NoAST *criarNo(Node_Type type, NoAST *esquerda, NoAST *direita);
NoAST *criarNoDecl(int dataType, Simbolo **names); // OK
NoAST *criarNoConst(DataType const_type, Value val);
NoAST *criarNoId(char *name, void *entry); 
NoAST *criarNoIfElseChain(Node_Type type, NoAST *condition, NoAST *branch_block, NoAST *next_branch);
NoAST *criarNoFor(NoAST *initialize, NoAST *condition, NoAST *increment, NoAST *for_branch);
NoAST *criarNoForIn(NoAST *iterator_id, NoAST *collection_expr, NoAST *body);
NoAST *criarNoRange(NoAST *start_expr, NoAST *end_expr, int exclusive);
NoAST *criarNoWhile(NoAST *condition, NoAST *while_brach);
NoAST *criarNoAssign(void *target_entry, NoAST *value_expr);
NoAST *criarNoSimple(int statement_type);
NoAST *criarNoIncr(Simbolo *entry, int incr_type, int pf_type); // OK
NoAST *criarNoFuncDef(Simbolo *symbol_entry, Parametro *parameters, NoAST *body); // OK
NoAST* criarNoFuncCall(Simbolo *entry, NoAST *args_list); // OK
NoAST* criarNoExprList(NoAST *expr, NoAST *next_expr_list);
NoAST *criarNoArithm(Arithm_op op, NoAST *esquerda, NoAST *direita);
NoAST *criarNoLogic(Bool_op op, NoAST *esquerda, NoAST *direita);
NoAST *criarNoRel(Rel_op op, NoAST *esquerda, NoAST *direita);
NoAST *criarNoEque(Equal_op op, NoAST *esquerda, NoAST *direita);
NoAST *criarNoFuncDecl(int ret_type, Simbolo *entry); // OK
NoAST *criarNoReturn(NoAST *ret_val);
void imprimirAST(NoAST *node, int indent);
NoAST** convert_sequence_to_array(NoAST *sequence_node, int *count);

// ========================================================================
// CORREÇÃO 2: ADICIONAR PROTÓTIPO PÚBLICO
// Isso resolve o aviso de "implicit declaration" em main.c
// ========================================================================
void gerarCodigoTAC(NoAST *raiz);

#endif