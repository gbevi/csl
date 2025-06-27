%{
#include "parser.tab.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *strndup(const char *s, size_t n) {
    size_t len = strnlen(s, n);
    char *new = malloc(len + 1);
    if (!new) {
        perror("Erro ao alocar memória para strndup");    
        return NULL;
    }
    memcpy(new, s, len);
    new[len] = '\0';
    return new;
}
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

"true"               { yylval.int_val = 1; return BOOL_LITERAL; }
"false"              { yylval.int_val = 0; return BOOL_LITERAL; }

[0-9]+\.[0-9]+      { yylval.double_val = atof(yytext); return FLOAT_LITERAL; } 
[0-9]+            { yylval.int_val = atoi(yytext); return NUM; }

\'[^\']\' { yylval.char_val = yytext[1]; return CHAR_LITERAL; }

\"([^"\\]|\\.)*\" {
    int len = strlen(yytext);
    yylval.string_val = strndup(yytext + 1, len - 2);
    return STRING;
}


"=="            { return EQ; }
"!="            { return NEQ; }
"<="            { return LE; }
">="            { return GE; }
"<"             { return LT; }
">"             { return GT; }
"+="                { return PLUS_ASSIGN; }
"-="                { return MINUS_ASSIGN; }
".."                { return RANGE_INCLUSIVE; }
"..."               { return RANGE_EXCLUSIVE; }

"="                 { return ASSIGN; }
"+"                 { return PLUS; }
"-"                 { return MINUS; }
"*"                 { return MULTIPLY; }
"/"                 { return DIVIDE; }
"("             { return LPAREN; }
")"             { return RPAREN; }
"{"             { return LBRACE; }
"}"             { return RBRACE; }
","             { return COMMA; }
";"             { return SEMICOLON; }



[0-9]+[a-zA-Z_][a-zA-Z0-9_]* { fprintf(stderr, "Erro lexico na linha %d: Identificador invalido '%s' (nao pode comecar com numero)\n", yylineno, yytext); /* AQUI VOCE PODE RETORNAR UM TOKEN DE ERRO OU APENAS IMPRIMIR */ }
[a-zA-Z_][a-zA-Z0-9_]* { yylval.string_val = strdup(yytext); return ID; }


[ \t]+              ; // Ignora espaços e tabs
[\r]?\n             { yylineno++; return EOL; } // Nova linha, com \r opcional para compatibilidade CRLF


. { fprintf(stderr, "Erro lexico na linha %d: Caractere invalido '%c' (codigo %d)\n", yylineno, yytext[0], yytext[0]); }

%%

int yywrap(void) {
    return 1;
}