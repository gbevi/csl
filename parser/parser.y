%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../ST/tabela.h"
#include "../ST/ast.h"

int tem_erro = 0;

void yyerror(const char *s);
int yylex(void);
NoAST *raiz;
%}

%code requires {
#include "../ST/ast.h"
}

%union {
    char char_val;
    int int_val;
    double double_val;
    char* str_val;

    list_t* symtab_item;
    NoAST* node;
}

%token <str> STRING ID
%token <valor> NUM

%token PUTS PRINT GETS IF ELSE ELSIF WHILE FOR IN DO END DEF RETURN
%token EQ NEQ LE GE LT GT ASSIGN PLUS MINUS MULTIPLY DIVIDE RANGE
%token LPAREN RPAREN LBRACE RBRACE COMMA
%token INT_TYPE FLOAT_TYPE DOUBLE_TYPE CHAR_TYPE STRING_TYPE BOOLEAN_TYPE
%token <str> FLOAT_LITERAL BOOL_LITERAL CHAR_LITERAL
%token AND OR NOT

%token EOL 

%left  OR
%left  AND
%left  EQ NEQ LT GT LE GE
%left  PLUS MINUS
%left  MULTIPLY DIVIDE
%right NOT UMINUS
%right ASSIGN

%type <param> param_list param_list_non_empty
%type <no> program statements expr stmt bloco arg_list func_call endif

%%

program:
    statements                  { raiz = $1; }
    |                           { raiz = NULL; }
    ;

statements:
    stmt                        { $$ = $1; }
    | statements stmt           { $$ = criarNoOp(OP_SEQ, $1, $2); }
    ;

stmt:
    func_call EOL               { $$ = $1; }
    | expr EOL                  { $$ = $1; }
    | PRINT expr EOL            { $$ = criarNoPrint($2); }
    | PUTS  expr EOL            { $$ = criarNoPuts($2); }
    | RETURN expr EOL           { $$ = criarNoOp(OP_RETURN, $2, NULL); }
    | GETS ID EOL              { $$ = criarNoGets($2); }
    | IF expr bloco END         { $$ = criarNoOp(OP_IF, $2, $3); }
    | WHILE expr bloco END      { $$ = criarNoOp(OP_WHILE, $2, $3); }
    
    | IF expr bloco endif       { $$ = criarNoOp(OP_IF, $2, $3); }
    | WHILE expr bloco END EOL  { $$ = criarNoOp(OP_WHILE, $2, $3); }
    | FOR ID IN expr DO bloco END EOL
                                  {
                                      NoAST *iter = criarNoId($2, TIPO_INT);
                                      NoAST *cab  = criarNoOp(OP_FOR, iter, $4);
                                      $$ = criarNoOp(OP_SEQ, cab, $6);
                                  }
    | DEF ID LPAREN param_list RPAREN bloco END EOL
                                  {
                                      $$ = criarNoDef($2, $4, $6);
                                  }
    ;

endif: 
    END EOL                 { $$ = NULL; }              
    | ELSE bloco END EOL      { $$ = criarNoOp(OP_ELSE, $2, NULL); }
    | ELSIF expr bloco endif  { $$ = criarNoOp(OP_ELSIF, $2, criarNoOp(OP_SEQ, $3, $4)); }
    ;

bloco:
    statements { $$ = $1; }
    |          { $$ = NULL; }
    ;

expr:
    NUM             { $$ = criarNoNum($1); }
    | STRING        { $$ = criarNoId($1, TIPO_STRING); }
    | ID            { $$ = criarNoId($1, TIPO_INT); }
    | expr PLUS expr { $$ = criarNoOp(OP_SOMA, $1, $3); }
    | expr MINUS expr  { $$ = criarNoOp(OP_SUB, $1, $3); }
    | expr MULTIPLY expr { $$ = criarNoOp(OP_MULT, $1, $3); }
    | expr DIVIDE expr  { $$ = criarNoOp(OP_DIV, $1, $3); }
    | expr EQ expr   { $$ = criarNoOp(OP_EQ, $1, $3); }
    | expr NEQ expr  { $$ = criarNoOp(OP_NEQ, $1, $3); }
    | expr LT expr   { $$ = criarNoOp(OP_LT, $1, $3); }
    | expr GT expr   { $$ = criarNoOp(OP_GT, $1, $3); }
    | expr LE expr   { $$ = criarNoOp(OP_LE, $1, $3); }
    | expr GE expr   { $$ = criarNoOp(OP_GE, $1, $3); }
    | expr AND expr  { $$ = criarNoOp(OP_AND, $1, $3); }
    | expr OR  expr  { $$ = criarNoOp(OP_OR, $1, $3); }
    | NOT expr  %prec UMINUS  { $$ = criarNoOp(OP_NOT, $2, NULL); }
    | ID ASSIGN expr          { $$ = criarNoOp(OP_ASSIGN, criarNoId($1, TIPO_INT), $3); }
    | LPAREN expr RPAREN      { $$ = $2; }
    ;



func_call:
    ID LPAREN arg_list RPAREN        { $$ = criarNoOp(OP_FUNC_CALL, criarNoId($1, TIPO_INT), $3); }
    ;

param_list:
    /* lista vazia */
    { $$ = NULL; }
  | param_list_non_empty
    { $$ = $1; }
;

param_list_non_empty:
    ID
    {
        Parametro *p = malloc(sizeof(Parametro));
        strcpy(p->nome, $1);
        p->prox = NULL;
        $$ = p;
    }
  | param_list_non_empty COMMA ID
    {
        Parametro *p = malloc(sizeof(Parametro));
        strcpy(p->nome, $3);
        p->prox = NULL;

        Parametro *iter = $1;
        while(iter->prox) iter = iter->prox;
        iter->prox = p;

        $$ = $1;
    }
;

arg_list:
    expr                    { $$ = $1; }
    | arg_list COMMA expr   { $$ = criarNoOp(OP_SEQ, $1, $3); }
    |                       { $$ = NULL; }
    ;

%%

extern int yylineno;

void yyerror(const char *s) {
    fprintf(stderr, "Erro na linha %d: %s\n", yylineno, s);
    tem_erro = 1;
}
