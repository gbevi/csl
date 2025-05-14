%{
#include "parser.tab.h"
#include <stdio.h>
#include <string.h>
%}

%%

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

// tipos de dados
int             { return INT_TYPE; }
float           { return FLOAT_TYPE; }
double          { return DOUBLE_TYPE; }
char            { return CHAR_TYPE; }
string          { return STRING_TYPE; }
boolean         { return BOOLEAN_TYPE; }

// strings
\"[^\"]*\"      { yylval.str = strdup(yytext); return STRING; }

// identificadores válidos
[a-zA-Z_][a-zA-Z0-9_]*  { yylval.str = strdup(yytext); return ID; }

// identificadores inválidos
[0-9]+[a-zA-Z_][a-zA-Z0-9_]* {printf("Identificador inválido (%s)\n", yytext);}

// operadores relacionais
"=="            { return EQ; }
"!="            { return NEQ; }
"<="            { return LE; }
">="            { return GE; }
"<"             { return LT; }
">"             { return GT; }

// atribuição
"="             { return ASSIGN; }

// operadores aritméticos
"+"             { return PLUS; }
"-"             { return MINUS; }
"*"             { return MULTIPLY; }
"/"             { return DIVIDE; }

// intervalo (range)
".."            { return RANGE; }

// parênteses chaves e vírgulas
"("             { return LPAREN; }
")"             { return RPAREN; }
"{"             { return LBRACE; }
"}"             { return RBRACE; }
","             { return COMMA; }

// operadores lógicos
"and"           { return AND; }
"or"            { return OR; }
"not"           { return NOT; }

// comentários de linha única
"#" {}

// comentários de bloco
"=begin" {BEGIN_COMMENT = 1;}
"=end" {BEGIN_COMMENT = 0;}

. {if (BEGIN_COMMENT) {return COMMENT;}} // para ignorar caracteres dentro dos comentários

// ignora espaços e quebras de linha
[ \t\n]+        ;

// ignora outros caracteres por enquanto
. { printf("Caractere inválido '%s'\n", yytext);}



%%

int yywrap(void) {
    return 1;
}
