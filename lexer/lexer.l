%{
#include "parser.tab.h"
#include <stdio.h>
#include <string.h>
%}

%x COMMENT_BLOCK

%%

"=begin"[ \t]*[\r]?\n       {BEGIN(COMMENT_BLOCK); }
<COMMENT_BLOCK>"=end"[ \t]*[\r]?\n   {BEGIN(INITIAL); }
<COMMENT_BLOCK>.|\n    ; 

"#".*     {} ; 

puts            { return PUTS; }
print           { return PRINT; }
gets            { return GETS; }

if              { return IF; }
else            { return ELSE; }
elsif           { return ELSIF; }
while           { return WHILE; }
for             { return FOR; }
in              { return IN; }
do              { return DO; }
end             { return END; }
def             { return DEF; }
return          { return RETURN; }

"and"           { return AND; }
"or"            { return OR; }
"not"           { return NOT; }

[0-9]+\.[0-9]+    { yylval.str = strdup(yytext); return FLOAT_LITERAL; }
[0-9]+            { yylval.str = strdup(yytext); return INT_LITERAL; }

"true"   { yylval.str = strdup("true"); return BOOL_LITERAL; }
"false"  { yylval.str = strdup("false"); return BOOL_LITERAL; }

'\''[a-zA-Z0-9]'\''    { yylval.str = strdup(yytext); return CHAR_LITERAL; }

\"[^\"]*\"      { yylval.str = strdup(yytext); return STRING; }

[a-zA-Z_][a-zA-Z0-9_]*  { yylval.str = strdup(yytext); return ID; }

[0-9]+[a-zA-Z_][a-zA-Z0-9_]* {printf("Identificador inválido (%s)\n", yytext);}

"=="            { return EQ; }
"!="            { return NEQ; }
"<="            { return LE; }
">="            { return GE; }
"<"             { return LT; }
">"             { return GT; }

"="             { return ASSIGN; }

"+"             { return PLUS; }
"-"             { return MINUS; }
"*"             { return MULTIPLY; }
"/"             { return DIVIDE; }

".."            { return RANGE; }

"("             { return LPAREN; }
")"             { return RPAREN; }
"{"             { return LBRACE; }
"}"             { return RBRACE; }
","             { return COMMA; }

\n              { return EOL; }

[ \t\n]+        ;

. { printf("Caractere inválido '%s'\n", yytext);}

%%

int yywrap(void) {
    return 1;
}
