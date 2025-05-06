%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PUTS 1
#define PRINT 2
#define GETS 3
#define IF 4
#define ELSE 5
#define ELSIF 6
#define WHILE 7
#define FOR 8
#define IN 9
#define DO 10
#define END 11
#define DEF 12
#define RETURN 13
#define INT_TYPE 14
#define FLOAT_TYPE 15
#define DOUBLE_TYPE 16
#define CHAR_TYPE 17
#define STRING_TYPE 18
#define BOOLEAN_TYPE 19
#define STRING 20
#define ID 21
#define EQ 22
#define NEQ 23
#define LE 24
#define GE 25
#define LT 26
#define GT 27
#define ASSIGN 28
#define PLUS 29
#define MINUS 30
#define MULTIPLY 31
#define DIVIDE 32
#define RANGE 33
#define LPAREN 34
#define RPAREN 35
#define LBRACE 36
#define RBRACE 37
#define COMMA 38
#define AND 39
#define OR 40
#define NOT 41

typedef union {
    char *str;
    int num;
} YYSTYPE;

YYSTYPE yylval;

%}

%%

puts        { printf("TOKEN: PUTS\n"); return PUTS; }
print       { printf("TOKEN: PRINT\n"); return PRINT; }
gets        { printf("TOKEN: GETS\n"); return GETS; }
if          { printf("TOKEN: IF\n"); return IF; }
else        { printf("TOKEN: ELSE\n"); return ELSE; }
elsif       { printf("TOKEN: ELSIF\n"); return ELSIF; }
while       { printf("TOKEN: WHILE\n"); return WHILE; }
for         { printf("TOKEN: FOR\n"); return FOR; }
in          { printf("TOKEN: IN\n"); return IN; }
do          { printf("TOKEN: DO\n"); return DO; }
end         { printf("TOKEN: END\n"); return END; }
def         { printf("TOKEN: DEF\n"); return DEF; }
return      { printf("TOKEN: RETURN\n"); return RETURN; }

int         { printf("TOKEN: INT_TYPE\n"); return INT_TYPE; }
float       { printf("TOKEN: FLOAT_TYPE\n"); return FLOAT_TYPE; }
double      { printf("TOKEN: DOUBLE_TYPE\n"); return DOUBLE_TYPE; }
char        { printf("TOKEN: CHAR_TYPE\n"); return CHAR_TYPE; }
string      { printf("TOKEN: STRING_TYPE\n"); return STRING_TYPE; }
boolean     { printf("TOKEN: BOOLEAN_TYPE\n"); return BOOLEAN_TYPE; }

\"[^\"]*\"  { yylval.str = strdup(yytext); printf("TOKEN: STRING (%s)\n", yytext); return STRING; }

[a-zA-Z_][a-zA-Z0-9_]*  { yylval.str = strdup(yytext); printf("TOKEN: ID (%s)\n", yytext); return ID; }

"=="        { printf("TOKEN: EQ\n"); return EQ; }
"!="        { printf("TOKEN: NEQ\n"); return NEQ; }
"<="        { printf("TOKEN: LE\n"); return LE; }
">="        { printf("TOKEN: GE\n"); return GE; }
"<"         { printf("TOKEN: LT\n"); return LT; }
">"         { printf("TOKEN: GT\n"); return GT; }

"="         { printf("TOKEN: ASSIGN\n"); return ASSIGN; }

"+"         { printf("TOKEN: PLUS\n"); return PLUS; }
"-"         { printf("TOKEN: MINUS\n"); return MINUS; }
"*"         { printf("TOKEN: MULTIPLY\n"); return MULTIPLY; }
"/"         { printf("TOKEN: DIVIDE\n"); return DIVIDE; }

".."        { printf("TOKEN: RANGE\n"); return RANGE; }

"("         { printf("TOKEN: LPAREN\n"); return LPAREN; }
")"         { printf("TOKEN: RPAREN\n"); return RPAREN; }
"{"         { printf("TOKEN: LBRACE\n"); return LBRACE; }
"}"         { printf("TOKEN: RBRACE\n"); return RBRACE; }
","         { printf("TOKEN: COMMA\n"); return COMMA; }

"and"       { printf("TOKEN: AND\n"); return AND; }
"or"        { printf("TOKEN: OR\n"); return OR; }
"not"       { printf("TOKEN: NOT\n"); return NOT; }

[ \t\n]+    ;

.           { printf("TOKEN DESCONHECIDO: %s\n", yytext); }

%%

int yywrap(void) {
    return 1;
}
