%{
#include <stdio.h>
#include <stdlib.h>
#include "../ST/tabela.h"
#include "../ST/ast.h"

int tem_erro = 0;

void yyerror(const char *s);
int yylex(void);
NoAST *raiz;
%}

%code requires {
    typedef struct NoAST NoAST;
}

%union {
    char *str;
    int valor;
    NoAST *no;
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


%type <no> program statements expr stmt bloco arg_list param_list func_call_bloco func_call endif

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
    | func_call_bloco EOL       { $$ = $1; }
    | expr EOL                  { $$ = $1; }
    | PRINT expr EOL            { $$ = criarNoOp(OP_PRINT, $2, NULL); }
    | PUTS  expr EOL            { $$ = criarNoOp(OP_PUTS, $2, NULL); }
    | RETURN expr EOL           { $$ = criarNoOp(OP_RETURN, $2, NULL); }
    | GETS  LPAREN RPAREN EOL   { $$ = criarNoOp(OP_GETS, NULL, NULL); }
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
                                      NoAST *nome = criarNoId($2, TIPO_INT);
                                      NoAST *params = $4; 
                                      NoAST *corpo  = $6;
                                      $$ = criarNoOp(OP_DEF, criarNoOp(OP_SEQ, nome, params), corpo);
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

func_call_bloco:
    ID LPAREN arg_list RPAREN DO bloco END    { $$ = criarNoOp(OP_FUNC_CALL_BLOCK, criarNoId($1, TIPO_INT), $6); }
    ;

func_call:
    ID LPAREN arg_list RPAREN        { $$ = criarNoOp(OP_FUNC_CALL, criarNoId($1, TIPO_INT), $3); }
    ;

param_list:
    ID                      { $$ = criarNoId($1, TIPO_INT); }
    | param_list COMMA ID   { $$ = criarNoOp(OP_SEQ, $1, criarNoId($3, TIPO_INT)); }
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
