%{
#include "parser.tab.h"
#include <stdio.h>
#define _GNU_SOURCE
#include <string.h>
%}

%option yylineno

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

[ \t]+          ;
[\r]?\n         { yylineno++; return EOL; }

[0-9]+\.[0-9]+  { yylval.double_val_token = atof(yytext); return FLOAT_LITERAL; } 
[0-9]+          { yylval.int_val_token = atoi(yytext); return NUM; }

"true"          { yylval.int_val_token = 1; return BOOL_LITERAL; }
"false"         { yylval.int_val_token = 0; return BOOL_LITERAL; }

'\''[^\']'\''   { yylval.char_val_token = yytext[1]; return CHAR_LITERAL; }

\"[^\"]*\"      {
                    size_t len = strlen(yytext);
                    yylval.str_val_token = strndup(yytext + 1, len - 2);
                    return STRING;
                }

[0-9]+[a-zA-Z_][a-zA-Z0-9_]* {printf("Identificador inválido (%s)\n", yytext);}
[a-zA-Z_][a-zA-Z0-9_]* { yylval.str_val_token = strdup(yytext); return ID; }

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

".."     { return RANGE_INCLUSIVE; }
"..."    { return RANGE_EXCLUSIVE; }

"("             { return LPAREN; }
")"             { return RPAREN; }
"{"             { return LBRACE; }
"}"             { return RBRACE; }
","             { return COMMA; }
";"             { return SEMICOLON; }

. { fprintf(stderr, "Erro lexico na linha %d: Caractere invalido '%c' (codigo %d)\n", yylineno, yytext[0], yytext[0]); }

%%

int yywrap(void) {
    return 1;
}