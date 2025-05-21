%{
#include <stdio.h>
#include <stdlib.h>
#include "ST/tabela.h"
#include "ST/ast.h"

void yyerror(const char *s);
int yylex(void);
NoAST *raiz;

%}

%union {
    char *str;
    int valor;
    NoAST *no;
}

%token <str> STRING ID
%token <valor> INT_LITERAL

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
    | statements stmt           { $$ = criarNoOp(';', $1, $2); }
    ;

stmt:
    func_call EOL               { $$ = $1; }
    | func_call_bloco EOL       { $$ = $1; }
    | expr EOL                  { $$ = $1; }
    | PRINT expr EOL            { $$ = criarNoOp('p', $2, NULL); }
    | PUTS  expr EOL            { $$ = criarNoOp('p', $2, NULL); }
    | RETURN expr EOL           { $$ = criarNoOp('r', $2, NULL); }
    | GETS  LPAREN RPAREN EOL   { $$ = criarNoOp('g', NULL, NULL); }
    | IF expr bloco END         { $$ = criarNoOp('i', $2, $3); }
    | WHILE expr bloco END      { $$ = criarNoOp('w', $2, $3); }
    
    | IF expr bloco endif       { $$ = criarNoOp('i', $2, $3); }
    | WHILE expr bloco END EOL  { $$ = criarNoOp('w', $2, $3); }
    | FOR ID IN expr DO bloco END EOL
                                  {
                                      NoAST *iter = criarNoId($2, TIPO_INT);
                                      NoAST *cab  = criarNoOp('f', iter, $4);
                                      $$ = criarNoOp('F', cab, $6);
                                  }
    | DEF ID LPAREN param_list RPAREN bloco END EOL
                                  {
                                      NoAST *nome = criarNoId($2, TIPO_INT);
                                      NoAST *params = $4; 
                                      NoAST *corpo  = $6;
                                      $$ = criarNoOp('d', criarNoOp(',', nome, params), corpo);
                                  }
    ;

endif: 
    END EOL                 { $$ = NULL; }              
    | ELSE bloco END EOL      { $$ = criarNoOp('e', $2, NULL); }
    | ELSIF expr bloco endif  { $$ = criarNoOp('l', $2, criarNoOp('b', $3, $4)); }
    ;

bloco:
    statements { $$ = $1; }
    |          { $$ = NULL; }
    ;

expr:
    INT_LITERAL            { $$ = criarNoNum($1); }
    | STRING        { $$ = criarNoId($1, TIPO_STRING); }
    | ID            { $$ = criarNoId($1, TIPO_INT); }

    | expr PLUS expr { $$ = criarNoOp('+', $1, $3); }
    | expr MINUS expr  { $$ = criarNoOp('-', $1, $3); }
    | expr MULTIPLY expr { $$ = criarNoOp('*', $1, $3); }
    | expr DIVIDE expr  { $$ = criarNoOp('/', $1, $3); }

    | expr EQ expr   { $$ = criarNoOp('==', $1, $3); }
    | expr NEQ expr  { $$ = criarNoOp('n', $1, $3); }
    | expr LT expr   { $$ = criarNoOp('<', $1, $3); }
    | expr GT expr   { $$ = criarNoOp('>', $1, $3); }
    | expr LE expr   { $$ = criarNoOp('l', $1, $3); }
    | expr GE expr   { $$ = criarNoOp('g', $1, $3); }

    | expr AND expr  { $$ = criarNoOp('&', $1, $3); }
    | expr OR  expr  { $$ = criarNoOp('|', $1, $3); }
    | NOT expr  %prec UMINUS  { $$ = criarNoOp('!', $2, NULL); }

    | ID ASSIGN expr          { $$ = criarNoOp('=', criarNoId($1, TIPO_INT), $3); }

    | LPAREN expr RPAREN      { $$ = $2; }
    ;

func_call_bloco:
    ID LPAREN arg_list RPAREN DO bloco END    { $$ = criarNoOp('C', criarNoId($1, TIPO_INT), $6); }
    ;

func_call:
    ID LPAREN arg_list RPAREN        { $$ = criarNoOp('c', criarNoId($1, TIPO_INT), $3); }
    ;

param_list:
    ID                      { $$ = criarNoId($1, TIPO_INT); }
    | param_list COMMA ID   { $$ = criarNoOp(',', $1, criarNoId($3, TIPO_INT)); }
    ;

arg_list:
    expr                    { $$ = $1; }
    | arg_list COMMA expr   { $$ = criarNoOp(',', $1, $3); }
    |                       { $$ = NULL; }
    ;

%%

extern int yylieno;
void yyerror(const char *s) {
    fprintf(stderr, "Erro na linha %d: %s\n", yylieno, s);
}
