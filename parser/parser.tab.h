/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_PARSER_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 14 "parser/parser.y"

    typedef struct NoAST NoAST;

#line 53 "parser/parser.tab.h"

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    STRING = 258,                  /* STRING  */
    ID = 259,                      /* ID  */
    NUM = 260,                     /* NUM  */
    PUTS = 261,                    /* PUTS  */
    PRINT = 262,                   /* PRINT  */
    GETS = 263,                    /* GETS  */
    IF = 264,                      /* IF  */
    ELSE = 265,                    /* ELSE  */
    ELSIF = 266,                   /* ELSIF  */
    WHILE = 267,                   /* WHILE  */
    FOR = 268,                     /* FOR  */
    IN = 269,                      /* IN  */
    DO = 270,                      /* DO  */
    END = 271,                     /* END  */
    DEF = 272,                     /* DEF  */
    RETURN = 273,                  /* RETURN  */
    EQ = 274,                      /* EQ  */
    NEQ = 275,                     /* NEQ  */
    LE = 276,                      /* LE  */
    GE = 277,                      /* GE  */
    LT = 278,                      /* LT  */
    GT = 279,                      /* GT  */
    ASSIGN = 280,                  /* ASSIGN  */
    PLUS = 281,                    /* PLUS  */
    MINUS = 282,                   /* MINUS  */
    MULTIPLY = 283,                /* MULTIPLY  */
    DIVIDE = 284,                  /* DIVIDE  */
    RANGE = 285,                   /* RANGE  */
    LPAREN = 286,                  /* LPAREN  */
    RPAREN = 287,                  /* RPAREN  */
    LBRACE = 288,                  /* LBRACE  */
    RBRACE = 289,                  /* RBRACE  */
    COMMA = 290,                   /* COMMA  */
    INT_TYPE = 291,                /* INT_TYPE  */
    FLOAT_TYPE = 292,              /* FLOAT_TYPE  */
    DOUBLE_TYPE = 293,             /* DOUBLE_TYPE  */
    CHAR_TYPE = 294,               /* CHAR_TYPE  */
    STRING_TYPE = 295,             /* STRING_TYPE  */
    BOOLEAN_TYPE = 296,            /* BOOLEAN_TYPE  */
    FLOAT_LITERAL = 297,           /* FLOAT_LITERAL  */
    BOOL_LITERAL = 298,            /* BOOL_LITERAL  */
    CHAR_LITERAL = 299,            /* CHAR_LITERAL  */
    AND = 300,                     /* AND  */
    OR = 301,                      /* OR  */
    NOT = 302,                     /* NOT  */
    EOL = 303,                     /* EOL  */
    UMINUS = 304                   /* UMINUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 18 "parser/parser.y"

    char *str;
    int valor;
    NoAST *no;

#line 125 "parser/parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_PARSER_TAB_H_INCLUDED  */
