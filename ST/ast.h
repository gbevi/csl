
#ifndef AST_H
#define AST_H

typedef enum { TIPO_INT, TIPO_FLOAT, TIPO_STRING, TIPO_DOUBLE, TIPO_CHAR, TIPO_BOOLEAN, TIPO_ERRO } Tipo;

typedef enum {
    OP_SOMA,
    OP_SUB,
    OP_MULT,
    OP_DIV,
    OP_EQ,
    OP_NEQ,
    OP_LT,
    OP_GT,
    OP_LE,
    OP_GE,
    OP_AND,
    OP_OR,
    OP_NOT,
    OP_ASSIGN,
    OP_PRINT,
    OP_PUTS,
    OP_RETURN,
    OP_GETS,
    OP_IF,
    OP_ELSE,
    OP_ELSIF,
    OP_WHILE,
    OP_FOR,
    OP_DEF,
    OP_FUNC_CALL,
    OP_FUNC_CALL_BLOCK,
    OP_SEQ,
    OP_COMMA,
    OP_ERR
} Operador;

typedef struct NoAST {
    Operador operador;
    int valor;
    char nome[32];
    Tipo tipo;
    struct NoAST *esquerda;
    struct NoAST *direita;
} NoAST;

NoAST *criarNoNum(int val);
NoAST *criarNoId(char *nome, Tipo tipo);
NoAST *criarNoOp(Operador op, NoAST *esq, NoAST *dir);
void imprimirAST(NoAST *no);
int tiposCompativeis(Tipo t1, Tipo t2);
char* gerarTAC(NoAST *no);


#endif