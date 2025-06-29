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

#ifndef YY_YY_PARSER_PARSER_H_INCLUDED
# define YY_YY_PARSER_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 32 "parser/parser.y"

    #include "ST/tabela.h"
    #include "ST/ast.h"
    #include "ST/code_generator.h"

#line 55 "parser/parser.h"

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
    BOOL_LITERAL = 261,            /* BOOL_LITERAL  */
    FLOAT_LITERAL = 262,           /* FLOAT_LITERAL  */
    CHAR_LITERAL = 263,            /* CHAR_LITERAL  */
    PUTS = 264,                    /* PUTS  */
    PRINT = 265,                   /* PRINT  */
    GETS = 266,                    /* GETS  */
    IF = 267,                      /* IF  */
    ELSE = 268,                    /* ELSE  */
    ELSIF = 269,                   /* ELSIF  */
    WHILE = 270,                   /* WHILE  */
    FOR = 271,                     /* FOR  */
    IN = 272,                      /* IN  */
    DO = 273,                      /* DO  */
    END = 274,                     /* END  */
    DEF = 275,                     /* DEF  */
    RETURN = 276,                  /* RETURN  */
    EQ = 277,                      /* EQ  */
    NEQ = 278,                     /* NEQ  */
    LE = 279,                      /* LE  */
    GE = 280,                      /* GE  */
    LT = 281,                      /* LT  */
    GT = 282,                      /* GT  */
    ASSIGN = 283,                  /* ASSIGN  */
    PLUS = 284,                    /* PLUS  */
    MINUS = 285,                   /* MINUS  */
    MULTIPLY = 286,                /* MULTIPLY  */
    DIVIDE = 287,                  /* DIVIDE  */
    RANGE_EXCLUSIVE = 288,         /* RANGE_EXCLUSIVE  */
    RANGE_INCLUSIVE = 289,         /* RANGE_INCLUSIVE  */
    PLUS_ASSIGN = 290,             /* PLUS_ASSIGN  */
    MINUS_ASSIGN = 291,            /* MINUS_ASSIGN  */
    LPAREN = 292,                  /* LPAREN  */
    RPAREN = 293,                  /* RPAREN  */
    LBRACE = 294,                  /* LBRACE  */
    RBRACE = 295,                  /* RBRACE  */
    COMMA = 296,                   /* COMMA  */
    SEMICOLON = 297,               /* SEMICOLON  */
    AND = 298,                     /* AND  */
    OR = 299,                      /* OR  */
    NOT = 300,                     /* NOT  */
    INT_TYPE = 301,                /* INT_TYPE  */
    FLOAT_TYPE = 302,              /* FLOAT_TYPE  */
    STRING_TYPE = 303,             /* STRING_TYPE  */
    CHAR_TYPE = 304,               /* CHAR_TYPE  */
    DOUBLE_TYPE = 305,             /* DOUBLE_TYPE  */
    EOL = 306,                     /* EOL  */
    UMINUS = 307,                  /* UMINUS  */
    CALL = 308,                    /* CALL  */
    LPAREN_GROUP = 309             /* LPAREN_GROUP  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 38 "parser/parser.y"

    char char_val;
    int int_val;
    double double_val;
    char* string_val;

    NoAST* ast_node; 
    Simbolo* symtab_item;
    Parametro* param_list_head;

#line 137 "parser/parser.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_PARSER_H_INCLUDED  */
