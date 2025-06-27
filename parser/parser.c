/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser/parser.y"

#define YYDEBUG 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ST/tabela.h"
#include "ST/ast.h"
#include "ST/code_generator.h"

extern FILE *yyin;
extern int yylineno;

int tem_erro = 0;

void yyerror(const char *s);
int yylex(void);
extern NoAST *raiz;

void inicializarTabelaBuiltins() {
    if (current_scope == NULL || current_scope->symbol_table == NULL) {
        fprintf(stderr, "Erro: Escopo global nao inicializado para adicionar built-ins.\n");
        exit(EXIT_FAILURE);
    }
    inserirNaTabela(current_scope->symbol_table, "print", "builtin_function");
    inserirNaTabela(current_scope->symbol_table, "puts", "builtin_function");
    inserirNaTabela(current_scope->symbol_table, "scan", "builtin_function");
}


#line 102 "parser/parser.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_STRING = 3,                     /* STRING  */
  YYSYMBOL_ID = 4,                         /* ID  */
  YYSYMBOL_NUM = 5,                        /* NUM  */
  YYSYMBOL_BOOL_LITERAL = 6,               /* BOOL_LITERAL  */
  YYSYMBOL_FLOAT_LITERAL = 7,              /* FLOAT_LITERAL  */
  YYSYMBOL_CHAR_LITERAL = 8,               /* CHAR_LITERAL  */
  YYSYMBOL_PUTS = 9,                       /* PUTS  */
  YYSYMBOL_PRINT = 10,                     /* PRINT  */
  YYSYMBOL_GETS = 11,                      /* GETS  */
  YYSYMBOL_IF = 12,                        /* IF  */
  YYSYMBOL_ELSE = 13,                      /* ELSE  */
  YYSYMBOL_ELSIF = 14,                     /* ELSIF  */
  YYSYMBOL_WHILE = 15,                     /* WHILE  */
  YYSYMBOL_FOR = 16,                       /* FOR  */
  YYSYMBOL_IN = 17,                        /* IN  */
  YYSYMBOL_DO = 18,                        /* DO  */
  YYSYMBOL_END = 19,                       /* END  */
  YYSYMBOL_DEF = 20,                       /* DEF  */
  YYSYMBOL_RETURN = 21,                    /* RETURN  */
  YYSYMBOL_EQ = 22,                        /* EQ  */
  YYSYMBOL_NEQ = 23,                       /* NEQ  */
  YYSYMBOL_LE = 24,                        /* LE  */
  YYSYMBOL_GE = 25,                        /* GE  */
  YYSYMBOL_LT = 26,                        /* LT  */
  YYSYMBOL_GT = 27,                        /* GT  */
  YYSYMBOL_ASSIGN = 28,                    /* ASSIGN  */
  YYSYMBOL_PLUS = 29,                      /* PLUS  */
  YYSYMBOL_MINUS = 30,                     /* MINUS  */
  YYSYMBOL_MULTIPLY = 31,                  /* MULTIPLY  */
  YYSYMBOL_DIVIDE = 32,                    /* DIVIDE  */
  YYSYMBOL_RANGE_EXCLUSIVE = 33,           /* RANGE_EXCLUSIVE  */
  YYSYMBOL_RANGE_INCLUSIVE = 34,           /* RANGE_INCLUSIVE  */
  YYSYMBOL_PLUS_ASSIGN = 35,               /* PLUS_ASSIGN  */
  YYSYMBOL_MINUS_ASSIGN = 36,              /* MINUS_ASSIGN  */
  YYSYMBOL_LPAREN = 37,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 38,                    /* RPAREN  */
  YYSYMBOL_LBRACE = 39,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 40,                    /* RBRACE  */
  YYSYMBOL_COMMA = 41,                     /* COMMA  */
  YYSYMBOL_SEMICOLON = 42,                 /* SEMICOLON  */
  YYSYMBOL_AND = 43,                       /* AND  */
  YYSYMBOL_OR = 44,                        /* OR  */
  YYSYMBOL_NOT = 45,                       /* NOT  */
  YYSYMBOL_INT_TYPE = 46,                  /* INT_TYPE  */
  YYSYMBOL_FLOAT_TYPE = 47,                /* FLOAT_TYPE  */
  YYSYMBOL_STRING_TYPE = 48,               /* STRING_TYPE  */
  YYSYMBOL_CHAR_TYPE = 49,                 /* CHAR_TYPE  */
  YYSYMBOL_DOUBLE_TYPE = 50,               /* DOUBLE_TYPE  */
  YYSYMBOL_EOL = 51,                       /* EOL  */
  YYSYMBOL_UMINUS = 52,                    /* UMINUS  */
  YYSYMBOL_CALL = 53,                      /* CALL  */
  YYSYMBOL_LPAREN_GROUP = 54,              /* LPAREN_GROUP  */
  YYSYMBOL_YYACCEPT = 55,                  /* $accept  */
  YYSYMBOL_program = 56,                   /* program  */
  YYSYMBOL_opt_leading_eols = 57,          /* opt_leading_eols  */
  YYSYMBOL_statements = 58,                /* statements  */
  YYSYMBOL_statements_list = 59,           /* statements_list  */
  YYSYMBOL_opt_terminators = 60,           /* opt_terminators  */
  YYSYMBOL_stmt_terminator = 61,           /* stmt_terminator  */
  YYSYMBOL_stmt = 62,                      /* stmt  */
  YYSYMBOL_optional_args = 63,             /* optional_args  */
  YYSYMBOL_optional_args_list = 64,        /* optional_args_list  */
  YYSYMBOL_optional_empty_paren = 65,      /* optional_empty_paren  */
  YYSYMBOL_optional_body_statements = 66,  /* optional_body_statements  */
  YYSYMBOL_for_init_block = 67,            /* for_init_block  */
  YYSYMBOL_func_declaration_and_scope = 68, /* func_declaration_and_scope  */
  YYSYMBOL_param_list = 69,                /* param_list  */
  YYSYMBOL_param = 70,                     /* param  */
  YYSYMBOL_expr = 71,                      /* expr  */
  YYSYMBOL_atom_expr = 72,                 /* atom_expr  */
  YYSYMBOL_call_or_id_expr = 73,           /* call_or_id_expr  */
  YYSYMBOL_func_call = 74,                 /* func_call  */
  YYSYMBOL_expr_list = 75,                 /* expr_list  */
  YYSYMBOL_elsif_else_parts = 76,          /* elsif_else_parts  */
  YYSYMBOL_elsif_clause_list = 77,         /* elsif_clause_list  */
  YYSYMBOL_elsif_clause = 78,              /* elsif_clause  */
  YYSYMBOL_optional_else_part = 79,        /* optional_else_part  */
  YYSYMBOL_else_clause = 80                /* else_clause  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   400

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  55
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  26
/* YYNRULES -- Number of rules.  */
#define YYNRULES  78
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  158

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   309


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    95,    95,   102,   103,   108,   109,   113,   114,   118,
     119,   123,   124,   128,   129,   150,   169,   188,   207,   226,
     234,   242,   250,   253,   264,   267,   276,   279,   286,   291,
     300,   301,   305,   306,   310,   314,   335,   379,   380,   392,
     404,   405,   406,   453,   475,   497,   498,   499,   500,   501,
     502,   503,   504,   505,   506,   507,   508,   509,   510,   511,
     512,   516,   520,   526,   530,   534,   546,   561,   565,   579,
     596,   597,   604,   633,   640,   647,   656,   657,   661
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "STRING", "ID", "NUM",
  "BOOL_LITERAL", "FLOAT_LITERAL", "CHAR_LITERAL", "PUTS", "PRINT", "GETS",
  "IF", "ELSE", "ELSIF", "WHILE", "FOR", "IN", "DO", "END", "DEF",
  "RETURN", "EQ", "NEQ", "LE", "GE", "LT", "GT", "ASSIGN", "PLUS", "MINUS",
  "MULTIPLY", "DIVIDE", "RANGE_EXCLUSIVE", "RANGE_INCLUSIVE",
  "PLUS_ASSIGN", "MINUS_ASSIGN", "LPAREN", "RPAREN", "LBRACE", "RBRACE",
  "COMMA", "SEMICOLON", "AND", "OR", "NOT", "INT_TYPE", "FLOAT_TYPE",
  "STRING_TYPE", "CHAR_TYPE", "DOUBLE_TYPE", "EOL", "UMINUS", "CALL",
  "LPAREN_GROUP", "$accept", "program", "opt_leading_eols", "statements",
  "statements_list", "opt_terminators", "stmt_terminator", "stmt",
  "optional_args", "optional_args_list", "optional_empty_paren",
  "optional_body_statements", "for_init_block",
  "func_declaration_and_scope", "param_list", "param", "expr", "atom_expr",
  "call_or_id_expr", "func_call", "expr_list", "elsif_else_parts",
  "elsif_clause_list", "elsif_clause", "optional_else_part", "else_clause", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-60)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-61)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -60,     6,    86,   -60,   -60,    45,   -60,   -60,   -60,   -60,
      31,   112,   -19,   155,   155,    17,    18,   155,   155,   155,
      27,    29,    42,    47,    63,   -60,    69,   135,   -60,   294,
     -60,   -60,   -60,   155,   155,   155,     7,   155,   -60,   294,
     155,   -60,   294,    36,    34,   -60,   144,   202,    66,   135,
      62,    49,   294,   248,   -60,    75,    76,    77,    80,    81,
     -60,   -60,   -23,   155,   155,   155,   155,   155,   155,   155,
     155,   155,   155,   155,   155,   155,   155,   294,   294,   294,
     -60,    -9,   271,   248,     9,   155,   -60,   135,    61,   155,
      94,   110,   135,   -60,   155,   155,   155,   155,   155,   -23,
     -60,   -60,   -60,   366,   366,   185,   185,   185,   185,    10,
      10,   -60,   -60,    97,    97,   355,   340,   -60,   317,   -60,
     294,   107,   135,   225,   -60,   -60,    33,   -60,   -60,   -60,
     294,   294,   294,   294,   294,   155,   103,   111,   107,   129,
      79,   -60,   110,    -2,   179,   -60,   101,   -60,   -60,   -60,
     -60,   -60,   -60,   -60,   135,   135,   -60,   -60
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       3,     0,     5,     1,    62,    66,    61,    64,    63,    65,
       0,     0,    32,     0,     0,     0,     0,    27,     0,     0,
       0,     0,     0,     0,     0,     4,     0,     6,     9,    13,
      40,    41,    67,     0,     0,     0,     0,     0,    19,    28,
       0,    20,    70,    30,     0,    21,     0,     0,     0,     5,
       0,     0,    26,     0,    51,     0,     0,     0,     0,     0,
       2,     9,     7,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    42,    44,    43,
      68,     0,     0,    70,     0,     0,    33,     5,     0,     0,
       0,     0,     5,    60,     0,     0,     0,     0,     0,     8,
      12,    11,    10,    52,    53,    56,    57,    54,    55,    45,
      46,    47,    48,    59,    58,    49,    50,    69,    29,    31,
      71,    74,     5,     0,    23,    39,     0,    37,    34,     9,
      14,    15,    16,    17,    18,     0,     0,    77,    74,     0,
       0,    36,     0,     0,     0,    22,     0,    72,    76,    73,
      24,    35,    38,    25,     5,     5,    75,    78
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -60,   -60,   -60,   -44,   -60,   -59,   -60,   126,   -60,   -60,
     -60,   -60,   -60,   -60,   -60,    12,   -10,   -60,   -60,   -60,
     -20,   -60,    26,   -60,   -60,   -60
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,     2,    26,    27,    62,   102,    28,    38,    41,
      45,   129,    49,    51,   126,   127,    29,    30,    31,    32,
      43,   136,   137,   138,   147,   148
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      39,    42,    99,    46,    47,    90,     3,    52,    53,    54,
       4,     5,     6,     7,     8,     9,    81,   153,    44,   100,
      84,    48,    50,    77,    78,    79,    42,    82,   101,   117,
      83,    55,    85,    56,     4,     5,     6,     7,     8,     9,
     100,    71,    72,   121,    18,    80,    57,   119,   128,   101,
      85,    58,    19,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,    59,    37,    60,
     143,   141,    86,    33,   142,   120,    19,    85,   139,   123,
      34,    35,    36,    89,   130,   131,   132,   133,   134,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    91,
      92,    14,    15,    94,    95,    96,    16,    17,    97,    98,
     156,   157,   122,   124,   125,     4,     5,     6,     7,     8,
       9,   135,   145,    18,   146,   144,    69,    70,    71,    72,
     151,    19,    20,    21,    22,    23,    24,    25,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,   150,    40,
      14,    15,   155,    61,   152,    16,    17,    19,     4,     5,
       6,     7,     8,     9,   149,     0,    63,    64,    65,    66,
      67,    68,    18,    69,    70,    71,    72,    73,    74,     0,
      19,    20,    21,    22,    23,    24,     0,    75,    76,     0,
       0,     0,    18,     0,     0,    87,     0,     0,     0,     0,
      19,    63,    64,    65,    66,    67,    68,     0,    69,    70,
      71,    72,    73,    74,    69,    70,    71,    72,    73,    74,
      88,     0,    75,    76,    63,    64,    65,    66,    67,    68,
     154,    69,    70,    71,    72,    73,    74,     0,     0,     0,
       0,     0,     0,   140,     0,    75,    76,    63,    64,    65,
      66,    67,    68,     0,    69,    70,    71,    72,    73,    74,
       0,     0,     0,     0,     0,     0,     0,     0,    75,    76,
      63,    64,    65,    66,    67,    68,     0,    69,    70,    71,
      72,    73,    74,     0,     0,     0,    93,     0,     0,     0,
       0,    75,    76,    63,    64,    65,    66,    67,    68,     0,
      69,    70,    71,    72,    73,    74,     0,     0,     0,   118,
       0,     0,     0,     0,    75,    76,    63,    64,    65,    66,
      67,    68,     0,    69,    70,    71,    72,    73,    74,     0,
       0,     0,     0,     0,     0,     0,     0,    75,    76,   -60,
     -60,   -60,   -60,   -60,   -60,     0,   -60,   -60,   -60,   -60,
     -60,   -60,     0,     0,     0,     0,     0,     0,     0,     0,
     -60,   -60,    63,    64,    65,    66,    67,    68,     0,    69,
      70,    71,    72,    73,    74,     0,     0,    63,    64,    65,
      66,    67,    68,    75,    69,    70,    71,    72,    73,    74,
      65,    66,    67,    68,     0,    69,    70,    71,    72,    73,
      74
};

static const yytype_int16 yycheck[] =
{
      10,    11,    61,    13,    14,    49,     0,    17,    18,    19,
       3,     4,     5,     6,     7,     8,    36,    19,    37,    42,
      40,     4,     4,    33,    34,    35,    36,    37,    51,    38,
      40,     4,    41,     4,     3,     4,     5,     6,     7,     8,
      42,    31,    32,    87,    37,    38,     4,    38,    92,    51,
      41,     4,    45,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,     4,    37,     0,
     129,    38,    38,    28,    41,    85,    45,    41,   122,    89,
      35,    36,    37,    17,    94,    95,    96,    97,    98,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    37,
      51,    15,    16,    28,    28,    28,    20,    21,    28,    28,
     154,   155,    51,    19,     4,     3,     4,     5,     6,     7,
       8,    14,    19,    37,    13,   135,    29,    30,    31,    32,
      51,    45,    46,    47,    48,    49,    50,    51,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    19,    37,
      15,    16,    51,    27,   142,    20,    21,    45,     3,     4,
       5,     6,     7,     8,   138,    -1,    22,    23,    24,    25,
      26,    27,    37,    29,    30,    31,    32,    33,    34,    -1,
      45,    46,    47,    48,    49,    50,    -1,    43,    44,    -1,
      -1,    -1,    37,    -1,    -1,    51,    -1,    -1,    -1,    -1,
      45,    22,    23,    24,    25,    26,    27,    -1,    29,    30,
      31,    32,    33,    34,    29,    30,    31,    32,    33,    34,
      18,    -1,    43,    44,    22,    23,    24,    25,    26,    27,
      51,    29,    30,    31,    32,    33,    34,    -1,    -1,    -1,
      -1,    -1,    -1,    18,    -1,    43,    44,    22,    23,    24,
      25,    26,    27,    -1,    29,    30,    31,    32,    33,    34,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,    44,
      22,    23,    24,    25,    26,    27,    -1,    29,    30,    31,
      32,    33,    34,    -1,    -1,    -1,    38,    -1,    -1,    -1,
      -1,    43,    44,    22,    23,    24,    25,    26,    27,    -1,
      29,    30,    31,    32,    33,    34,    -1,    -1,    -1,    38,
      -1,    -1,    -1,    -1,    43,    44,    22,    23,    24,    25,
      26,    27,    -1,    29,    30,    31,    32,    33,    34,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,    44,    22,
      23,    24,    25,    26,    27,    -1,    29,    30,    31,    32,
      33,    34,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      43,    44,    22,    23,    24,    25,    26,    27,    -1,    29,
      30,    31,    32,    33,    34,    -1,    -1,    22,    23,    24,
      25,    26,    27,    43,    29,    30,    31,    32,    33,    34,
      24,    25,    26,    27,    -1,    29,    30,    31,    32,    33,
      34
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    56,    57,     0,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    15,    16,    20,    21,    37,    45,
      46,    47,    48,    49,    50,    51,    58,    59,    62,    71,
      72,    73,    74,    28,    35,    36,    37,    37,    63,    71,
      37,    64,    71,    75,    37,    65,    71,    71,     4,    67,
       4,    68,    71,    71,    71,     4,     4,     4,     4,     4,
       0,    62,    60,    22,    23,    24,    25,    26,    27,    29,
      30,    31,    32,    33,    34,    43,    44,    71,    71,    71,
      38,    75,    71,    71,    75,    41,    38,    51,    18,    17,
      58,    37,    51,    38,    28,    28,    28,    28,    28,    60,
      42,    51,    61,    71,    71,    71,    71,    71,    71,    71,
      71,    71,    71,    71,    71,    71,    71,    38,    38,    38,
      71,    58,    51,    71,    19,     4,    69,    70,    58,    66,
      71,    71,    71,    71,    71,    14,    76,    77,    78,    58,
      18,    38,    41,    60,    71,    19,    13,    79,    80,    77,
      19,    51,    70,    19,    51,    51,    58,    58
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    55,    56,    57,    57,    58,    58,    59,    59,    60,
      60,    61,    61,    62,    62,    62,    62,    62,    62,    62,
      62,    62,    62,    62,    62,    62,    62,    62,    63,    63,
      64,    64,    65,    65,    66,    67,    68,    69,    69,    70,
      71,    71,    71,    71,    71,    71,    71,    71,    71,    71,
      71,    71,    71,    71,    71,    71,    71,    71,    71,    71,
      71,    72,    72,    72,    72,    72,    73,    73,    74,    74,
      75,    75,    76,    77,    77,    78,    79,    79,    80
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     3,     0,     2,     0,     1,     2,     3,     0,
       2,     1,     1,     1,     4,     4,     4,     4,     4,     2,
       2,     2,     6,     4,     6,     6,     2,     1,     1,     3,
       1,     3,     0,     2,     1,     5,     4,     1,     3,     1,
       1,     1,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     2,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     1,     1,     1,     1,     1,     1,     1,     3,     4,
       1,     3,     2,     2,     0,     4,     1,     0,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: opt_leading_eols statements $end  */
#line 95 "parser/parser.y"
                                      {
        raiz = (yyvsp[-1].ast_node); // $2 já é um NoAST* por causa de %type <ast_node> statements
        fprintf(stderr, "DEBUG-PARSER: Raiz da AST final atribuida a 'raiz': %p\n", (void*)raiz);
    }
#line 1326 "parser/parser.c"
    break;

  case 3: /* opt_leading_eols: %empty  */
#line 102 "parser/parser.y"
    { (yyval.ast_node) = NULL; }
#line 1332 "parser/parser.c"
    break;

  case 4: /* opt_leading_eols: opt_leading_eols EOL  */
#line 103 "parser/parser.y"
                           { (yyval.ast_node) = NULL; }
#line 1338 "parser/parser.c"
    break;

  case 5: /* statements: %empty  */
#line 108 "parser/parser.y"
    { (yyval.ast_node) = NULL; }
#line 1344 "parser/parser.c"
    break;

  case 6: /* statements: statements_list  */
#line 109 "parser/parser.y"
                      { (yyval.ast_node) = (yyvsp[0].ast_node); }
#line 1350 "parser/parser.c"
    break;

  case 7: /* statements_list: stmt opt_terminators  */
#line 113 "parser/parser.y"
                         { (yyval.ast_node) = (yyvsp[-1].ast_node); }
#line 1356 "parser/parser.c"
    break;

  case 8: /* statements_list: statements_list stmt opt_terminators  */
#line 114 "parser/parser.y"
                                           { (yyval.ast_node) = criarNo(BASIC_NODE, (yyvsp[-2].ast_node), (yyvsp[-1].ast_node)); }
#line 1362 "parser/parser.c"
    break;

  case 9: /* opt_terminators: %empty  */
#line 118 "parser/parser.y"
    { }
#line 1368 "parser/parser.c"
    break;

  case 10: /* opt_terminators: opt_terminators stmt_terminator  */
#line 119 "parser/parser.y"
                                      { }
#line 1374 "parser/parser.c"
    break;

  case 11: /* stmt_terminator: EOL  */
#line 123 "parser/parser.y"
            { }
#line 1380 "parser/parser.c"
    break;

  case 12: /* stmt_terminator: SEMICOLON  */
#line 124 "parser/parser.y"
                { }
#line 1386 "parser/parser.c"
    break;

  case 13: /* stmt: expr  */
#line 128 "parser/parser.y"
          { (yyval.ast_node) = (yyvsp[0].ast_node); }
#line 1392 "parser/parser.c"
    break;

  case 14: /* stmt: INT_TYPE ID ASSIGN expr  */
#line 129 "parser/parser.y"
                              {
        // Declaração de variável int
        Simbolo *id_entry = buscarSimbolo((yyvsp[-2].string_val));
        if (id_entry) {
            fprintf(stderr, "Erro semântico na linha %d: Variável '%s' já declarada.\n", yylineno, (yyvsp[-2].string_val));
            tem_erro = 1;
            (yyval.ast_node) = NULL;
        } else {
            inserirNaTabela(current_scope->symbol_table, (yyvsp[-2].string_val), "int");
            Simbolo *id_entry = buscarSimbolo((yyvsp[-2].string_val));
            // Checagem de tipo: só aceita TIPO_INT
            if ((yyvsp[0].ast_node) && (yyvsp[0].ast_node)->type == CONST_NODE && (yyvsp[0].ast_node)->data) {
                NoAST_Const *c = (NoAST_Const*)(yyvsp[0].ast_node)->data;
                if (c->const_type != TIPO_INT) {
                    fprintf(stderr, "Erro semântico na linha %d: Atribuição de tipo incompatível para variável int '%s'.\n", yylineno, (yyvsp[-2].string_val));
                    tem_erro = 1;
                }
            }
            (yyval.ast_node) = criarNoAssign(id_entry, (yyvsp[0].ast_node));
        }
    }
#line 1418 "parser/parser.c"
    break;

  case 15: /* stmt: FLOAT_TYPE ID ASSIGN expr  */
#line 150 "parser/parser.y"
                                {
        Simbolo *id_entry = buscarSimbolo((yyvsp[-2].string_val));
        if (id_entry) {
            fprintf(stderr, "Erro semântico na linha %d: Variável '%s' já declarada.\n", yylineno, (yyvsp[-2].string_val));
            tem_erro = 1;
            (yyval.ast_node) = NULL;
        } else {
            inserirNaTabela(current_scope->symbol_table, (yyvsp[-2].string_val), "float");
            id_entry = buscarSimbolo((yyvsp[-2].string_val));
            if ((yyvsp[0].ast_node) && (yyvsp[0].ast_node)->type == CONST_NODE && (yyvsp[0].ast_node)->data) {
                NoAST_Const *c = (NoAST_Const*)(yyvsp[0].ast_node)->data;
                if (c->const_type != TIPO_FLOAT && c->const_type != TIPO_DOUBLE) {
                    fprintf(stderr, "Erro semântico na linha %d: Atribuição de tipo incompatível para variável float '%s'.\n", yylineno, (yyvsp[-2].string_val));
                    tem_erro = 1;
                }
            }
            (yyval.ast_node) = criarNoAssign(id_entry, (yyvsp[0].ast_node));
        }
    }
#line 1442 "parser/parser.c"
    break;

  case 16: /* stmt: STRING_TYPE ID ASSIGN expr  */
#line 169 "parser/parser.y"
                                 {
        Simbolo *id_entry = buscarSimbolo((yyvsp[-2].string_val));
        if (id_entry) {
            fprintf(stderr, "Erro semântico na linha %d: Variável '%s' já declarada.\n", yylineno, (yyvsp[-2].string_val));
            tem_erro = 1;
            (yyval.ast_node) = NULL;
        } else {
            inserirNaTabela(current_scope->symbol_table, (yyvsp[-2].string_val), "string");
            id_entry = buscarSimbolo((yyvsp[-2].string_val));
            if ((yyvsp[0].ast_node) && (yyvsp[0].ast_node)->type == CONST_NODE && (yyvsp[0].ast_node)->data) {
                NoAST_Const *c = (NoAST_Const*)(yyvsp[0].ast_node)->data;
                if (c->const_type != TIPO_STRING) {
                    fprintf(stderr, "Erro semântico na linha %d: Atribuição de tipo incompatível para variável string '%s'.\n", yylineno, (yyvsp[-2].string_val));
                    tem_erro = 1;
                }
            }
            (yyval.ast_node) = criarNoAssign(id_entry, (yyvsp[0].ast_node));
        }
    }
#line 1466 "parser/parser.c"
    break;

  case 17: /* stmt: CHAR_TYPE ID ASSIGN expr  */
#line 188 "parser/parser.y"
                               {
        Simbolo *id_entry = buscarSimbolo((yyvsp[-2].string_val));
        if (id_entry) {
            fprintf(stderr, "Erro semântico na linha %d: Variável '%s' já declarada.\n", yylineno, (yyvsp[-2].string_val));
            tem_erro = 1;
            (yyval.ast_node) = NULL;
        } else {
            inserirNaTabela(current_scope->symbol_table, (yyvsp[-2].string_val), "char");
            id_entry = buscarSimbolo((yyvsp[-2].string_val));
            if ((yyvsp[0].ast_node) && (yyvsp[0].ast_node)->type == CONST_NODE && (yyvsp[0].ast_node)->data) {
                NoAST_Const *c = (NoAST_Const*)(yyvsp[0].ast_node)->data;
                if (c->const_type != TIPO_CHAR) {
                    fprintf(stderr, "Erro semântico na linha %d: Atribuição de tipo incompatível para variável char '%s'.\n", yylineno, (yyvsp[-2].string_val));
                    tem_erro = 1;
                }
            }
            (yyval.ast_node) = criarNoAssign(id_entry, (yyvsp[0].ast_node));
        }
    }
#line 1490 "parser/parser.c"
    break;

  case 18: /* stmt: DOUBLE_TYPE ID ASSIGN expr  */
#line 207 "parser/parser.y"
                                 {
        Simbolo *id_entry = buscarSimbolo((yyvsp[-2].string_val));
        if (id_entry) {
            fprintf(stderr, "Erro semântico na linha %d: Variável '%s' já declarada.\n", yylineno, (yyvsp[-2].string_val));
            tem_erro = 1;
            (yyval.ast_node) = NULL;
        } else {
            inserirNaTabela(current_scope->symbol_table, (yyvsp[-2].string_val), "double");
            id_entry = buscarSimbolo((yyvsp[-2].string_val));
            if ((yyvsp[0].ast_node) && (yyvsp[0].ast_node)->type == CONST_NODE && (yyvsp[0].ast_node)->data) {
                NoAST_Const *c = (NoAST_Const*)(yyvsp[0].ast_node)->data;
                if (c->const_type != TIPO_DOUBLE && c->const_type != TIPO_FLOAT) {
                    fprintf(stderr, "Erro semântico na linha %d: Atribuição de tipo incompatível para variável double '%s'.\n", yylineno, (yyvsp[-2].string_val));
                    tem_erro = 1;
                }
            }
            (yyval.ast_node) = criarNoAssign(id_entry, (yyvsp[0].ast_node));
        }
    }
#line 1514 "parser/parser.c"
    break;

  case 19: /* stmt: PUTS optional_args  */
#line 226 "parser/parser.y"
                                {
        Simbolo *puts_entry = buscarSimbolo("puts");
        if (!puts_entry) {
            inserirNaTabela(current_scope->symbol_table, "puts", "builtin_function");
            puts_entry = buscarSimbolo("puts");
        }
        (yyval.ast_node) = criarNoFuncCall(puts_entry, (yyvsp[0].ast_node));
    }
#line 1527 "parser/parser.c"
    break;

  case 20: /* stmt: PRINT optional_args_list  */
#line 234 "parser/parser.y"
                               {
        Simbolo *print_entry = buscarSimbolo("print");
        if (!print_entry) {
            inserirNaTabela(current_scope->symbol_table, "print", "builtin_function");
            print_entry = buscarSimbolo("print");
        }
        (yyval.ast_node) = criarNoFuncCall(print_entry, (yyvsp[0].ast_node));
    }
#line 1540 "parser/parser.c"
    break;

  case 21: /* stmt: GETS optional_empty_paren  */
#line 242 "parser/parser.y"
                                {
        Simbolo *gets_entry = buscarSimbolo("gets");
        if (!gets_entry) {
            inserirNaTabela(current_scope->symbol_table, "gets", "builtin_function");
            gets_entry = buscarSimbolo("gets");
        }
        (yyval.ast_node) = criarNoFuncCall(gets_entry, NULL);
    }
#line 1553 "parser/parser.c"
    break;

  case 22: /* stmt: IF expr EOL statements elsif_else_parts END  */
#line 250 "parser/parser.y"
                                                  {
        (yyval.ast_node) = criarNoIfElseChain(IF_NODE, (yyvsp[-4].ast_node), (yyvsp[-2].ast_node), (yyvsp[-1].ast_node));
    }
#line 1561 "parser/parser.c"
    break;

  case 23: /* stmt: FOR for_init_block statements END  */
#line 253 "parser/parser.y"
                                        {
        NoAST *header_node = (yyvsp[-2].ast_node);
        NoAST *for_var_node = header_node->esquerda; 
        NoAST *range_expr = header_node->direita;
        NoAST *body_statements = (yyvsp[-1].ast_node);

        (yyval.ast_node) = criarNoForIn(for_var_node, range_expr, body_statements);
        
        exitScope();
        free(header_node); 
    }
#line 1577 "parser/parser.c"
    break;

  case 24: /* stmt: WHILE expr DO EOL statements END  */
#line 264 "parser/parser.y"
                                       {
        (yyval.ast_node) = criarNoWhile((yyvsp[-4].ast_node), (yyvsp[-1].ast_node));
    }
#line 1585 "parser/parser.c"
    break;

  case 25: /* stmt: DEF func_declaration_and_scope EOL optional_body_statements opt_terminators END  */
#line 268 "parser/parser.y"
    {
        Simbolo *func_entry = (yyvsp[-4].symtab_item); 
        Parametro *params = func_entry->parameters;
        NoAST *body = (yyvsp[-2].ast_node);
        
        (yyval.ast_node) = criarNoFuncDef(func_entry, params, body);
        exitScope();
    }
#line 1598 "parser/parser.c"
    break;

  case 26: /* stmt: RETURN expr  */
#line 276 "parser/parser.y"
                  {
        (yyval.ast_node) = criarNoReturn((yyvsp[0].ast_node)); 
    }
#line 1606 "parser/parser.c"
    break;

  case 27: /* stmt: RETURN  */
#line 279 "parser/parser.y"
             { 
        (yyval.ast_node) = criarNoReturn(NULL);
    }
#line 1614 "parser/parser.c"
    break;

  case 28: /* optional_args: expr  */
#line 286 "parser/parser.y"
                       {
        fprintf(stderr, "DEBUG-PARSER: optional_args: $1 (expr) antes de criarNoExprList: %p\n", (void*)(yyvsp[0].ast_node));
        (yyval.ast_node) = criarNoExprList((yyvsp[0].ast_node), NULL); // $1 é ast_node
        fprintf(stderr, "DEBUG-PARSER: optional_args: $$ (EXPR_LIST_NODE) apos criarNoExprList: %p\n", (void*)(yyval.ast_node));
    }
#line 1624 "parser/parser.c"
    break;

  case 29: /* optional_args: LPAREN expr RPAREN  */
#line 291 "parser/parser.y"
                         {
        fprintf(stderr, "DEBUG-PARSER: optional_args: $2 (expr) antes de criarNoExprList (com paren): %p\n", (void*)(yyvsp[-1].ast_node));
        (yyval.ast_node) = criarNoExprList((yyvsp[-1].ast_node), NULL); // $2 é ast_node
        fprintf(stderr, "DEBUG-PARSER: optional_args: $$ (EXPR_LIST_NODE) apos criarNoExprList (com paren): %p\n", (void*)(yyval.ast_node));
    }
#line 1634 "parser/parser.c"
    break;

  case 30: /* optional_args_list: expr_list  */
#line 300 "parser/parser.y"
                            { (yyval.ast_node) = (yyvsp[0].ast_node); }
#line 1640 "parser/parser.c"
    break;

  case 31: /* optional_args_list: LPAREN expr_list RPAREN  */
#line 301 "parser/parser.y"
                              { (yyval.ast_node) = (yyvsp[-1].ast_node); }
#line 1646 "parser/parser.c"
    break;

  case 32: /* optional_empty_paren: %empty  */
#line 305 "parser/parser.y"
    { (yyval.ast_node) = NULL; }
#line 1652 "parser/parser.c"
    break;

  case 33: /* optional_empty_paren: LPAREN RPAREN  */
#line 306 "parser/parser.y"
                       { (yyval.ast_node) = NULL; }
#line 1658 "parser/parser.c"
    break;

  case 34: /* optional_body_statements: statements  */
#line 310 "parser/parser.y"
               { (yyval.ast_node) = (yyvsp[0].ast_node); }
#line 1664 "parser/parser.c"
    break;

  case 35: /* for_init_block: ID IN expr DO EOL  */
#line 315 "parser/parser.y"
    {
        char *for_var_name = strdup((yyvsp[-4].string_val)); 
        if (!for_var_name) { yyerror("Memory allocation error."); YYABORT; }

        enterScope();

        inserirNaTabela(current_scope->symbol_table, for_var_name, "loop_variable"); 

        Simbolo *loop_item_entry = buscarNaTabela(current_scope->symbol_table, for_var_name);
        if (!loop_item_entry) {
            fprintf(stderr, "Erro interno CRITICO: Simbolo '%s' nao encontrado APOS insercao no escopo FOR (linha %d).\n", for_var_name, yylineno);
            tem_erro = 1; (yyval.ast_node) = NULL; free(for_var_name); exitScope(); YYABORT;
        }

        (yyval.ast_node) = criarNo(FOR_HEADER_NODE, criarNoId(strdup(for_var_name), loop_item_entry), (yyvsp[-2].ast_node));
        free(for_var_name); 
    }
#line 1686 "parser/parser.c"
    break;

  case 36: /* func_declaration_and_scope: ID LPAREN param_list RPAREN  */
#line 336 "parser/parser.y"
    {
        char *func_name = strdup((yyvsp[-3].string_val));
        if (!func_name) { yyerror("Memory allocation error."); YYABORT; }
        
        // registra o nome da função no escopo atual
        Simbolo *func_entry = buscarSimbolo(func_name);
        if (func_entry != NULL) {
            // se o símbolo já existe e é ou não é uma função
            if (strcmp(func_entry->tipo, "function") != 0 && strcmp(func_entry->tipo, "builtin_function") != 0) {
                fprintf(stderr, "Erro semântico na linha %d: O nome '%s' já está em uso como '%s'. Redefinição como função não permitida.\n", yylineno, func_name, func_entry->tipo);
                tem_erro = 1; (yyval.symtab_item) = NULL; free(func_name); YYABORT;
            }
            fprintf(stderr, "Erro semântico na linha %d: Função '%s' já declarada. Redefinição não permitida.\n", yylineno, func_name);
            tem_erro = 1; (yyval.symtab_item) = NULL; free(func_name); YYABORT;
        } else {
            // insere o nome da função na tabela de símbolos do escopo global
            inserirNaTabela(current_scope->symbol_table, func_name, "function");
            func_entry = buscarSimbolo(func_name); 
            if (!func_entry) { fprintf(stderr, "Erro interno: Símbolo '%s' da funcao nao encontrado APOS insercao (linha %d).\n", func_name, yylineno); tem_erro = 1; YYABORT; }
            func_entry->parameters = (yyvsp[-1].param_list_head);
            (yyval.symtab_item) = func_entry;
        }

        free(func_name);

        // entra no escopo da função
        enterScope();

        // insere os parametros no novo escopo 
        Parametro *current_param = (yyvsp[-1].param_list_head); 
        while (current_param != NULL) {
            if (buscarNaTabela(current_scope->symbol_table, current_param->nome) != NULL) {
                fprintf(stderr, "Erro semântico na linha %d: Parâmetro '%s' duplicado na função '%s'.\n", yylineno, current_param->nome, func_entry->nome);
                tem_erro = 1;
            } else {
                inserirNaTabela(current_scope->symbol_table, current_param->nome, "parameter");
            }
            current_param = current_param->prox;
        }
    }
#line 1731 "parser/parser.c"
    break;

  case 37: /* param_list: param  */
#line 379 "parser/parser.y"
                                { (yyval.param_list_head) = (yyvsp[0].param_list_head); }
#line 1737 "parser/parser.c"
    break;

  case 38: /* param_list: param_list COMMA param  */
#line 380 "parser/parser.y"
                                {
                                    Parametro *head = (yyvsp[-2].param_list_head);
                                    Parametro *current = head;
                                    while(current->prox != NULL) {
                                        current = current->prox;
                                    }
                                    current->prox = (yyvsp[0].param_list_head);
                                    (yyval.param_list_head) = head;
                                }
#line 1751 "parser/parser.c"
    break;

  case 39: /* param: ID  */
#line 392 "parser/parser.y"
                                {
                                    Parametro *p = malloc(sizeof(Parametro));
                                    if (!p) { yyerror("Erro de alocação de memória para parâmetro."); YYABORT; }
                                    strncpy(p->nome, (yyvsp[0].string_val), sizeof(p->nome) - 1);
                                    p->nome[sizeof(p->nome) - 1] = '\0';
                                    p->prox = NULL;
                                    (yyval.param_list_head) = p; 
                                }
#line 1764 "parser/parser.c"
    break;

  case 42: /* expr: ID ASSIGN expr  */
#line 406 "parser/parser.y"
                     {
                        char *var_name = strdup((yyvsp[-2].string_val));
                        if (!var_name) {
                            yyerror("Erro de alocação de memória para nome da variável.");
                            YYABORT;
                        }

                        Simbolo *id_entry = buscarSimbolo(var_name);

                        if (!id_entry) {
                            // tipo padrão "int"
                            char *inferred_type_str = "int"; 

                            // tenta inferir o tipo a partir da expressão atribuída ($3)
                            if ((yyvsp[0].ast_node) && (yyvsp[0].ast_node)->type == CONST_NODE) {
                                NoAST_Const *const_node = (NoAST_Const *)(yyvsp[0].ast_node)->data;
                                if (const_node) {
                                    switch (const_node->const_type) {
                                        case TIPO_INT: 
                                            inferred_type_str = "int"; 
                                            break;
                                        case TIPO_FLOAT: 
                                            inferred_type_str = "float";
                                            break;
                                        case TIPO_DOUBLE:
                                            inferred_type_str = "double";
                                            break;
                                        case TIPO_CHAR: 
                                            inferred_type_str = "char"; 
                                            break;
                                        case TIPO_STRING: 
                                            inferred_type_str = "string";
                                            break;
                                        case TIPO_BOOLEAN: 
                                            inferred_type_str = "boolean";
                                            break;
                                        default:
                                            break; 
                                    }
                                }
                            } 
                            inserirNaTabela(current_scope->symbol_table, var_name, inferred_type_str);
                            id_entry = buscarSimbolo(var_name);
                        }
                        (yyval.ast_node) = criarNoAssign(id_entry, (yyvsp[0].ast_node));
                        free(var_name); 
                    }
#line 1816 "parser/parser.c"
    break;

  case 43: /* expr: ID MINUS_ASSIGN expr  */
#line 453 "parser/parser.y"
                                {
                                    char *var_name = strdup((yyvsp[-2].string_val));
                                    if (!var_name) { yyerror("Memory allocation error."); YYABORT; }

                                    Simbolo *id_entry = buscarSimbolo(var_name);
                                    if (!id_entry) {
                                        // Erro: não se pode usar -= em uma variável não definida.
                                        fprintf(stderr, "Erro semântico na linha %d: Variável '%s' não definida para a operação '-='.\n", yylineno, var_name);
                                        tem_erro = 1;
                                        (yyval.ast_node) = NULL; // Retorna NULL para evitar falhas na AST
                                        free(var_name);
                                    } else {
                                        // Constrói a árvore para: ID = ID - expr
                                        // 1. Cria um nó ID para o lado esquerdo da subtração
                                        NoAST *var_node_rhs = criarNoId(strdup(var_name), id_entry);
                                        // 2. Cria o nó de subtração (ID - expr)
                                        NoAST *subtraction_node = criarNoArithm(OP_SUBTRACAO, var_node_rhs, (yyvsp[0].ast_node));
                                        // 3. Cria o nó de atribuição (ID = [resultado da subtração])
                                        (yyval.ast_node) = criarNoAssign(id_entry, subtraction_node);
                                        free(var_name);
                                    }
                                }
#line 1843 "parser/parser.c"
    break;

  case 44: /* expr: ID PLUS_ASSIGN expr  */
#line 475 "parser/parser.y"
                                {
                                    char *var_name = strdup((yyvsp[-2].string_val));
                                    if (!var_name) { yyerror("Memory allocation error."); YYABORT; }

                                    Simbolo *id_entry = buscarSimbolo(var_name);
                                    if (!id_entry) {
                                        // Erro: não se pode usar += em uma variável não definida.
                                        fprintf(stderr, "Erro semântico na linha %d: Variável '%s' não definida para a operação '+='.\n", yylineno, var_name);
                                        tem_erro = 1;
                                        (yyval.ast_node) = NULL; // Retorna NULL para evitar falhas na AST
                                        free(var_name);
                                    } else {
                                        // Constrói a árvore para: ID = ID + expr
                                        // 1. Cria um nó ID para o lado esquerdo da adição
                                        NoAST *var_node_rhs = criarNoId(strdup(var_name), id_entry);
                                        // 2. Cria o nó de adição (ID + expr)
                                        NoAST *addition_node = criarNoArithm(OP_ADICAO, var_node_rhs, (yyvsp[0].ast_node));
                                        // 3. Cria o nó de atribuição (ID = [resultado da adição])
                                        (yyval.ast_node) = criarNoAssign(id_entry, addition_node);
                                        free(var_name);
                                    }
                                }
#line 1870 "parser/parser.c"
    break;

  case 45: /* expr: expr PLUS expr  */
#line 497 "parser/parser.y"
                                { (yyval.ast_node) = criarNoArithm(OP_ADICAO, (yyvsp[-2].ast_node), (yyvsp[0].ast_node)); }
#line 1876 "parser/parser.c"
    break;

  case 46: /* expr: expr MINUS expr  */
#line 498 "parser/parser.y"
                                { (yyval.ast_node) = criarNoArithm(OP_SUBTRACAO, (yyvsp[-2].ast_node), (yyvsp[0].ast_node)); }
#line 1882 "parser/parser.c"
    break;

  case 47: /* expr: expr MULTIPLY expr  */
#line 499 "parser/parser.y"
                                { (yyval.ast_node) = criarNoArithm(OP_MULTIPLICACAO, (yyvsp[-2].ast_node), (yyvsp[0].ast_node)); }
#line 1888 "parser/parser.c"
    break;

  case 48: /* expr: expr DIVIDE expr  */
#line 500 "parser/parser.y"
                                { (yyval.ast_node) = criarNoArithm(OP_DIVISAO, (yyvsp[-2].ast_node), (yyvsp[0].ast_node)); }
#line 1894 "parser/parser.c"
    break;

  case 49: /* expr: expr AND expr  */
#line 501 "parser/parser.y"
                                { (yyval.ast_node) = criarNoLogic(OP_AND, (yyvsp[-2].ast_node), (yyvsp[0].ast_node)); }
#line 1900 "parser/parser.c"
    break;

  case 50: /* expr: expr OR expr  */
#line 502 "parser/parser.y"
                                { (yyval.ast_node) = criarNoLogic(OP_OR, (yyvsp[-2].ast_node), (yyvsp[0].ast_node)); }
#line 1906 "parser/parser.c"
    break;

  case 51: /* expr: NOT expr  */
#line 503 "parser/parser.y"
                                  { (yyval.ast_node) = criarNoLogic(OP_NOT, (yyvsp[0].ast_node), NULL); }
#line 1912 "parser/parser.c"
    break;

  case 52: /* expr: expr EQ expr  */
#line 504 "parser/parser.y"
                                { (yyval.ast_node) = criarNoRel(OP_REL_EQ, (yyvsp[-2].ast_node), (yyvsp[0].ast_node)); }
#line 1918 "parser/parser.c"
    break;

  case 53: /* expr: expr NEQ expr  */
#line 505 "parser/parser.y"
                                { (yyval.ast_node) = criarNoRel(OP_REL_NEQ, (yyvsp[-2].ast_node), (yyvsp[0].ast_node)); }
#line 1924 "parser/parser.c"
    break;

  case 54: /* expr: expr LT expr  */
#line 506 "parser/parser.y"
                                { (yyval.ast_node) = criarNoRel(OP_REL_LT, (yyvsp[-2].ast_node), (yyvsp[0].ast_node)); }
#line 1930 "parser/parser.c"
    break;

  case 55: /* expr: expr GT expr  */
#line 507 "parser/parser.y"
                                { (yyval.ast_node) = criarNoRel(OP_REL_GT, (yyvsp[-2].ast_node), (yyvsp[0].ast_node)); }
#line 1936 "parser/parser.c"
    break;

  case 56: /* expr: expr LE expr  */
#line 508 "parser/parser.y"
                                { (yyval.ast_node) = criarNoRel(OP_REL_LE, (yyvsp[-2].ast_node), (yyvsp[0].ast_node)); }
#line 1942 "parser/parser.c"
    break;

  case 57: /* expr: expr GE expr  */
#line 509 "parser/parser.y"
                                { (yyval.ast_node) = criarNoRel(OP_REL_GE, (yyvsp[-2].ast_node), (yyvsp[0].ast_node)); }
#line 1948 "parser/parser.c"
    break;

  case 58: /* expr: expr RANGE_INCLUSIVE expr  */
#line 510 "parser/parser.y"
                                { (yyval.ast_node) = criarNoRange((yyvsp[-2].ast_node), (yyvsp[0].ast_node), 0); }
#line 1954 "parser/parser.c"
    break;

  case 59: /* expr: expr RANGE_EXCLUSIVE expr  */
#line 511 "parser/parser.y"
                                { (yyval.ast_node) = criarNoRange((yyvsp[-2].ast_node), (yyvsp[0].ast_node), 1); }
#line 1960 "parser/parser.c"
    break;

  case 60: /* expr: LPAREN expr RPAREN  */
#line 512 "parser/parser.y"
                                            { (yyval.ast_node) = (yyvsp[-1].ast_node); }
#line 1966 "parser/parser.c"
    break;

  case 61: /* atom_expr: NUM  */
#line 516 "parser/parser.y"
                            {
        (yyval.ast_node) = criarNoConst(TIPO_INT, (Value){.valint = (yyvsp[0].int_val)}); // $1 é int_val
        fprintf(stderr, "DEBUG-PARSER: atom_expr: NUM (%d) -> $$ (NoAST*): %p\n", (yyvsp[0].int_val), (void*)(yyval.ast_node));
    }
#line 1975 "parser/parser.c"
    break;

  case 62: /* atom_expr: STRING  */
#line 520 "parser/parser.y"
                            {
        char *copied_string = strdup((yyvsp[0].string_val)); // $1 é string_val
        if (!copied_string) { yyerror("Erro de alocacao de memoria para string literal."); YYABORT; }
        (yyval.ast_node) = criarNoConst(TIPO_STRING, (Value){.valstring = copied_string});
        fprintf(stderr, "DEBUG-PARSER: atom_expr: STRING ('%s') -> $$ (NoAST*): %p\n", (yyvsp[0].string_val), (void*)(yyval.ast_node));
    }
#line 1986 "parser/parser.c"
    break;

  case 63: /* atom_expr: FLOAT_LITERAL  */
#line 526 "parser/parser.y"
                            {
        (yyval.ast_node) = criarNoConst(TIPO_DOUBLE, (Value){.valfloat = (yyvsp[0].double_val)}); // $1 é double_val
        fprintf(stderr, "DEBUG-PARSER: atom_expr: FLOAT (%f) -> $$ (NoAST*): %p\n", (yyvsp[0].double_val), (void*)(yyval.ast_node));
    }
#line 1995 "parser/parser.c"
    break;

  case 64: /* atom_expr: BOOL_LITERAL  */
#line 530 "parser/parser.y"
                            {
        (yyval.ast_node) = criarNoConst(TIPO_BOOLEAN, (Value){.valint = (yyvsp[0].int_val)}); // $1 é int_val
        fprintf(stderr, "DEBUG-PARSER: atom_expr: BOOL (%d) -> $$ (NoAST*): %p\n", (yyvsp[0].int_val), (void*)(yyval.ast_node));
    }
#line 2004 "parser/parser.c"
    break;

  case 65: /* atom_expr: CHAR_LITERAL  */
#line 534 "parser/parser.y"
                            {
        (yyval.ast_node) = criarNoConst(TIPO_CHAR, (Value){.valchar = (char)(yyvsp[0].char_val)}); // $1 é char_val (cast para char)
        fprintf(stderr, "DEBUG-PARSER: atom_expr: CHAR ('%c') -> $$ (NoAST*): %p\n", (char)(yyvsp[0].char_val), (void*)(yyval.ast_node));
    }
#line 2013 "parser/parser.c"
    break;

  case 66: /* call_or_id_expr: ID  */
#line 546 "parser/parser.y"
                      {
                        char *id_name = strdup((yyvsp[0].string_val));
                        if (!id_name) { yyerror("Memory allocation error."); YYABORT; }

                        Simbolo *id_entry = buscarSimbolo(id_name);
                        if (!id_entry) {
                            fprintf(stderr, "Erro semântico na linha %d: Uso de variável não definida '%s'.\n", yylineno, id_name);
                            tem_erro = 1;
                            (yyval.ast_node) = NULL;
                            free(id_name); 
                        } else {
                            (yyval.ast_node) = criarNoId(strdup(id_name), id_entry);
                            free(id_name);
                        }
                    }
#line 2033 "parser/parser.c"
    break;

  case 67: /* call_or_id_expr: func_call  */
#line 561 "parser/parser.y"
                           { (yyval.ast_node) = (yyvsp[0].ast_node); }
#line 2039 "parser/parser.c"
    break;

  case 68: /* func_call: ID LPAREN RPAREN  */
#line 565 "parser/parser.y"
                     {
            char *func_name = strdup((yyvsp[-2].string_val));
            if (!func_name) { yyerror("Memory allocation error."); YYABORT; }

            Simbolo *func_entry = buscarSimbolo(func_name);
            if (!func_entry) {
                fprintf(stderr, "Erro semântico na linha %d: Função '%s' não declarada.\n", yylineno, func_name);
                tem_erro = 1;
                (yyval.ast_node) = NULL;
            } else {
                (yyval.ast_node) = criarNoFuncCall(func_entry, NULL);
            }
            free(func_name); 
        }
#line 2058 "parser/parser.c"
    break;

  case 69: /* func_call: ID LPAREN expr_list RPAREN  */
#line 579 "parser/parser.y"
                                 {
            char *func_name = strdup((yyvsp[-3].string_val));
            if (!func_name) { yyerror("Memory allocation error."); YYABORT; }

            Simbolo *func_entry = buscarSimbolo(func_name);
            if (!func_entry) {
                fprintf(stderr, "Erro semântico na linha %d: Função '%s' não declarada.\n", yylineno, func_name);
                tem_erro = 1;
                (yyval.ast_node) = NULL;
            } else {
                (yyval.ast_node) = criarNoFuncCall(func_entry, (yyvsp[-1].ast_node));
            }
            free(func_name);
        }
#line 2077 "parser/parser.c"
    break;

  case 70: /* expr_list: expr  */
#line 596 "parser/parser.y"
         { (yyval.ast_node) = criarNoExprList((yyvsp[0].ast_node), NULL); }
#line 2083 "parser/parser.c"
    break;

  case 71: /* expr_list: expr_list COMMA expr  */
#line 597 "parser/parser.y"
                           {
        (yyval.ast_node) = criarNoExprList((yyvsp[0].ast_node), (yyvsp[-2].ast_node));
    }
#line 2091 "parser/parser.c"
    break;

  case 72: /* elsif_else_parts: elsif_clause_list optional_else_part  */
#line 604 "parser/parser.y"
                                         {
        // $1 é a cabeça da cadeia de elsifs (pode ser NULL)
        // $2 é o nó do else (pode ser NULL)

        if ((yyvsp[-1].ast_node) && (yyvsp[0].ast_node)) {
            // se tem elsifs e um else, conecta o último elsif ao else
            NoAST *current = (yyvsp[-1].ast_node);
            NoAST_if *current_data = (NoAST_if *)(current->data);
            while (current_data->next_branch != NULL) {
                current = current_data->next_branch;
                current_data = (NoAST_if *)(current->data);
            }
            current_data->next_branch = (yyvsp[0].ast_node);
            (yyval.ast_node) = (yyvsp[-1].ast_node); 
        } else if ((yyvsp[-1].ast_node)) {
            // caso 2: só tem elsifs
            (yyval.ast_node) = (yyvsp[-1].ast_node);
        } else if ((yyvsp[0].ast_node)) {
            // caso 3: tem else
            (yyval.ast_node) = (yyvsp[0].ast_node);
        } else {
            // último caso: tem nem elsifs nem else
            (yyval.ast_node) = NULL;
        }
    }
#line 2121 "parser/parser.c"
    break;

  case 73: /* elsif_clause_list: elsif_clause elsif_clause_list  */
#line 633 "parser/parser.y"
                                   {
        // $1: o elsif atual (o primeiro desta regra)
        // $2: a cabeça do resto da lista de elsifs
        NoAST_if *current_elsif_data = (NoAST_if *)((yyvsp[-1].ast_node)->data);
        current_elsif_data->next_branch = (yyvsp[0].ast_node); // Faz o elsif atual apontar para o próximo
        (yyval.ast_node) = (yyvsp[-1].ast_node); // Retorna o elsif atual
    }
#line 2133 "parser/parser.c"
    break;

  case 74: /* elsif_clause_list: %empty  */
#line 640 "parser/parser.y"
        {
        (yyval.ast_node) = NULL; 
    }
#line 2141 "parser/parser.c"
    break;

  case 75: /* elsif_clause: ELSIF expr EOL statements  */
#line 647 "parser/parser.y"
                             {
        // $2: condição do ELSIF
        // $4: bloco de statements do ELSIF
        // o último parâmetro é null pq será ligado na regra 'elsif_clause_list'
        (yyval.ast_node) = criarNoIfElseChain(ELSIF_NODE, (yyvsp[-2].ast_node), (yyvsp[0].ast_node), NULL);
    }
#line 2152 "parser/parser.c"
    break;

  case 76: /* optional_else_part: else_clause  */
#line 656 "parser/parser.y"
                { (yyval.ast_node) = (yyvsp[0].ast_node); }
#line 2158 "parser/parser.c"
    break;

  case 77: /* optional_else_part: %empty  */
#line 657 "parser/parser.y"
        { (yyval.ast_node) = NULL; }
#line 2164 "parser/parser.c"
    break;

  case 78: /* else_clause: ELSE EOL statements  */
#line 661 "parser/parser.y"
                        {
        // $3: bloco de statements do ELSE
        // condição é NULL para ELSE
        // o último parâmetro é null porque else é o final da cadeia
        (yyval.ast_node) = criarNoIfElseChain(ELSE_NODE, NULL, (yyvsp[0].ast_node), NULL);
    }
#line 2175 "parser/parser.c"
    break;


#line 2179 "parser/parser.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 669 "parser/parser.y"



void yyerror(const char *s) {
    fprintf(stderr, "Erro sintático na linha %d: %s\n", yylineno, s);
    tem_erro = 1;
}

int main(int argc, char **argv) {
    yydebug = 1;
    if (argc > 1) {
        yyin = fopen(argv[1], "r");
        if (!yyin) {
            fprintf(stderr, "Não foi possível abrir o arquivo: %s\n", argv[1]);
            return 1;
        }
    } else {
        fprintf(stderr, "Uso: %s <arquivo_entrada>\n", argv[0]);
        return 1;
    }

    enterScope(); // adicionado pra criar o escopo global
    inicializarTabelaBuiltins();

    yyparse();

    if (tem_erro) {
        fprintf(stderr, "Erros sintáticos ou semânticos encontrados. AST não foi gerada completamente.\n");
        exitScope();
        if (yyin != stdin) {
            fclose(yyin);
        }
        return 1;
    }

    if (!tem_erro && raiz != NULL) {
        printf("\nAnálise Sintática Concluída. AST gerada:\n");
        //imprimirAST(raiz, 0);
        printf("\n");
        imprimirTabelaEscopos();

        printf("\nIniciando Geração de Código C...\n");

        FILE *output_file = fopen("output.c", "w");
        if (!output_file) {
            fprintf(stderr, "Erro: Não foi possível criar o arquivo de saída 'output.c'\n");
            exitScope();
            fclose(yyin);
            return 1;
        }

        gerarCodigoC(raiz, output_file); // chama a função de geracao de codigo C (não tá completa ainda)

        fclose(output_file);
        printf("Código C gerado com sucesso em 'output.c'!\n");
    } else if (tem_erro) {
        fprintf(stderr, "Erros sintáticos ou semânticos encontrados. AST não foi gerada completamente.\n");
    } else {
        printf("Programa vazio. Nenhuma AST gerada.\n");
    }

    exitScope(); // antes de sair do programa, sai do escopo global tbm
    if (current_scope != NULL) {
        fprintf(stderr, "Erro de escopo: Nem todos os escopos foram fechados corretamente.\n");
    }

    if (yyin != stdin) {
        fclose(yyin);
    }
    return 0;
}
