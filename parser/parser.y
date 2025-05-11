%{
#include <stdio.h>
#include <stdlib.h>
#include "ST/tabela.h"

void yyerror(const char *s);
int yylex(void);

%}

%union {
    char *str;
}

%token <str> STRING ID
%token PUTS PRINT GETS IF ELSE ELSIF WHILE FOR IN DO END DEF RETURN
%token EQ NEQ LE GE LT GT ASSIGN PLUS MINUS MULTIPLY DIVIDE RANGE
%token LPAREN RPAREN LBRACE RBRACE COMMA
%token INT_TYPE FLOAT_TYPE DOUBLE_TYPE CHAR_TYPE STRING_TYPE BOOLEAN_TYPE
%token AND OR NOT

%type <str> expression

%%

program:
    statement
    ;

statement:
    PUTS expression {
        printf("#include <stdio.h>\n\nint main() {\n");
        printf("    printf(%s);", $2);
        printf("\n    return 0;\n}\n");
    }
    | PRINT expression {
        printf("#include <stdio.h>\n\nint main() {\n");
        printf("    printf(%s);", $2); // em Ruby print não adiciona "\n"
        printf("\n    return 0;\n}\n");
    }
    ;

expression:
    STRING { $$ = $1; }
    | ID    { $$ = $1; }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Erro: %s\n", s);
}
