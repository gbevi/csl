
typedef enum Node_Type {
    BASIC_NODE,
    DECL_NODE,
    CONST_NODE,
    IF_NODE,
    ELSIF_NODE,
    FOR_NODE,
    WHILE_NODE,
    ASSIGN_NODE,
    SIMPLE_NODE,
    INCR_NODE,
    FUNC_CALL,
    ARITHM_NODE,
    BOOL_NODE,
    REL_NODE,
    EQU_NODE,
    FUNC_DECL,
    RETURN_NODE,
}Node_Type;

typedef enum Arithm_op{
    ADD,
    SUB,
    MUL,
    DIV,
    INC,
    DEC,
} Arithm_op;

typedef enum Bool_op{
    OR,
    AND,
    NOT,
}Bool_op;

typedef enum Rel_op{
    GREATER,
    LESS,
    GREATER_EQ,
    LESS_EQ,
}Rel_op;

typedef enum Equal_op{
    EQUAL,
    NOT_EQUAL,
}Equal_op;

typedef union Value{
    int valint;
    double valfloat;
    char valchar;
    char *valstring;
}Value;

typedef struct NoAST {
    enum Node_Type type;
    struct NoAST *esquerda;
    struct NoAST *direita;
} NoAST;

typedef struct NoAST_Decl{
    enum Node_Type type;
    int dateType;
    list_t** names;
}NoAST_Decl;

typedef struct NoAST_Const{
    enum Node_Type type;
    int const_type;
    Value val;
}NoAST_Const;

typedef struct NoAST_if{
    enum Node_Type type;

    struct NoAST *condition;

    struct NoAST *if_branch;

    struct NoAST **elsif_branchs;

    struct NoAST *else_branch;

    int elseif_count;
}NoAST_if;

typedef struct NoAST_elsif{
    enum Node_Type type;

    struct NoAST *condition;

    struct NoAST *elsif_branch;
}NoAST_elsif;

typedef struct NoAST_for{
    enum Node_Type type;

    struct NoAST *initialize;

    struct NoAST *condition;

    struct NoAST *increment;

    struct NoAST *for_branch;
}NoAST_for;

typedef struct NoAST_while{
    enum Node_Type type;

    struct NoAST *condition;

    struct NoAST *while_branch;
}NoAST_while;

typedef struct NoAST_assign{
    enum Node_Type type;

    list_t *entry;

    struct NoAST *assign_val;
}NoAST_assign;

typedef struct NoAST_simple{
    enum Node_Type type;

    int statement_type;
}NoAST_simple;

typedef struct NoAST_incr{
	enum Node_Type type;

	list_t *entry;

	int incr_type; 

	int pf_type; 
}NoAST_incr;

typedef struct NoAST_Func_Call{
	enum Node_Type type; 
	list_t *entry;

	NoAST **params;	
    int num_of_pars;
}NoAST_Func_Call;

typedef struct NoAST_Arithm{
	enum Node_Type type; 

	enum Arithm_op op;

	struct NoAST *esquerda;  
	struct NoAST *direita;
}NoAST_Arithm;

typedef struct NoAST_Bool{
	enum Node_Type type; 
	enum Bool_op op;

	struct NoAST *esquerda;  
	struct NoAST *direita; 
}NoAST_Bool;

typedef struct NoAST_Rel{
	enum Node_Type type;

	enum Rel_op op;

	struct NoAST *esquerda; 
	struct NoAST *direita; 
}NoAST_Rel;

typedef struct NoAST_Equ{
	enum Node_Type type; 

	enum Equal_op op;

	struct NoAST *esquerda; 
	struct NoAST *direita; 
}NoAST_Equ;

typedef struct NoAST_Func_Decl{
	enum Node_Type type; 

	int ret_type;

	list_t *entry;
}NoAST_Func_Decl;

typedef struct NoAST_Return{
	enum Node_Type type; 

	int ret_type;

	struct NoAST *ret_val;
}NoAST_Return;



NoAST *criarNo(Node_Type type, NoAST *esquerda, NoAST *direita);

NoAST *criarNoDecl(int dataType, list_t **names);

NoAST *criarNoConst(int const_type, Value val);

NoAST *criarNoIf(NoAST *condition, NoAST *if_branch, NoAST **elseif_branchs, int elseif_count, NoAST *elseif_branch);

NoAST *criarNoElsif(NoAST *condition, NoAST *elsif_branch);

NoAST *criarNoFor(NoAST *initialize, NoAST *condition, NoAST *increment, NoAST *for_branch);

NoAST *criarNoWhile(NoAST *condition, NoAST *while_brach);

NoAST *criarNoAssign(list_t *entry, NoAST *assign_val);

NoAST *criarNoSimple(int statement_type);

NoAST *criarNoIncr(list_t *entry, int incr_type, int pf_type);

NoAST *criarNoFuncCall(list_t *entry, NoAST **params, int num_of_pars);

NoAST *criarNoArithm(enum Arithm_op op, NoAST *esquerda, NoAST *direita);

NoAST *criarNoBool(enum Bool_op op, NoAST *esquerda, NoAST *direita);

NoAST *criarNoRel(enum Rel_op op, NoAST *esquerda, NoAST *direita);

NoAST *criarNoEque(enum Equal_op op, NoAST *esquerda, NoAST *direita);

NoAST *criarNoFuncDecl(int ret_type, list_t *entry);

NoAST *criarNoReturn(int ret_type, NoAST *ret_val);

void imprimirAST(NoAST *no);
