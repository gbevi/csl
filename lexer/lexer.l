%{
#include "parser.tab.h"
#include <string.h>
%}

%%

puts            { return PUTS; }
\"[^\"]*\"      { yylval.str = strdup(yytext); return STRING; }
[ \t\n]+        ; // ignora espaços e quebras de linha
.               ; // ignora outros caracteres por enquanto

%%

int yywrap(void) {
    return 1;
}
