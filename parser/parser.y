%{
#include <stdio.h>
#include <stdlib.h>

void yyerror(const char *s);
int yylex(void);

%}

%union {
    char *str;
}

%token <str> STRING
%token PUTS
%type <str> expression

%%

program:
    statement
    ;

statement:
    PUTS expression {
        printf("#include <stdio.h>\n\nint main() {\n");
        printf("    printf(%s);\n", $2);
        printf("    return 0;\n}\n");
    }
    ;

expression:
    STRING { $$ = $1; }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Erro: %s\n", s);
}
