/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 4 "parser.y" /* yacc.c:339  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "header.h"
int linenumber = 1;
AST_NODE *prog;

extern int g_anyErrorOccur;

static inline AST_NODE* makeSibling(AST_NODE *a, AST_NODE *b)
{ 
    while (a->rightSibling) {
        a = a->rightSibling;
    }
    if (b == NULL) {
        return a;
    }
    b = b->leftmostSibling;
    a->rightSibling = b;
    
    b->leftmostSibling = a->leftmostSibling;
    b->parent = a->parent;
    while (b->rightSibling) {
        b = b->rightSibling;
        b->leftmostSibling = a->leftmostSibling;
        b->parent = a->parent;
    }
    return b;
}

static inline AST_NODE* makeChild(AST_NODE *parent, AST_NODE *child)
{
    if (child == NULL) {
        return parent;
    }
    if (parent->child) {
        makeSibling(parent->child, child);
    } else {
        child = child->leftmostSibling;
        parent->child = child;
        while (child) {
            child->parent = parent;
            child = child->rightSibling;
        }
    }
    return parent;
}

static AST_NODE* makeFamily(AST_NODE *parent, int childrenCount, ...)
{
    va_list childrenList;
    va_start(childrenList, childrenCount);
    AST_NODE* child = va_arg(childrenList, AST_NODE*);
    makeChild(parent, child);
    AST_NODE* tmp = child;
    int index = 1;
    for (index = 1; index < childrenCount; ++index) {
        child = va_arg(childrenList, AST_NODE*);
        tmp = makeSibling(tmp, child);
    }
    va_end(childrenList);
    return parent;
}

static inline AST_NODE* makeIDNode(char *lexeme, IDENTIFIER_KIND idKind)
{
    AST_NODE* identifier = Allocate(IDENTIFIER_NODE);
    identifier->semantic_value.identifierSemanticValue.identifierName = lexeme;
    identifier->semantic_value.identifierSemanticValue.kind = idKind;
    identifier->semantic_value.identifierSemanticValue.symbolTableEntry = NULL;
    return identifier;                        
}

static inline AST_NODE* makeStmtNode(STMT_KIND stmtKind)
{
    AST_NODE* stmtNode = Allocate(STMT_NODE);
    stmtNode->semantic_value.stmtSemanticValue.kind = stmtKind;
    return stmtNode;                        
}

static inline AST_NODE* makeDeclNode(DECL_KIND declKind)
{
    AST_NODE* declNode = Allocate(DECLARATION_NODE);
    declNode->semantic_value.declSemanticValue.kind = declKind;
    return declNode;                        
}

static inline AST_NODE* makeExprNode(EXPR_KIND exprKind, int operationEnumValue)
{
    AST_NODE* exprNode = Allocate(EXPR_NODE);
    exprNode->semantic_value.exprSemanticValue.isConstEval = 0;
    exprNode->semantic_value.exprSemanticValue.kind = exprKind;
    if (exprKind == BINARY_OPERATION) {
        exprNode->semantic_value.exprSemanticValue.op.binaryOp = operationEnumValue;
    } else if (exprKind == UNARY_OPERATION) {
        exprNode->semantic_value.exprSemanticValue.op.unaryOp = operationEnumValue;
    } else {
        printf("Error in static inline AST_NODE* makeExprNode(EXPR_KIND exprKind, int operationEnumValue)\n");
    }
    return exprNode;                        
}


#line 172 "parser.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "parser.tab.h".  */
#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    ID = 258,
    CONST = 259,
    VOID = 260,
    INT = 261,
    FLOAT = 262,
    IF = 263,
    ELSE = 264,
    WHILE = 265,
    FOR = 266,
    TYPEDEF = 267,
    OP_ASSIGN = 268,
    OP_OR = 269,
    OP_AND = 270,
    OP_NOT = 271,
    OP_EQ = 272,
    OP_NE = 273,
    OP_GT = 274,
    OP_LT = 275,
    OP_GE = 276,
    OP_LE = 277,
    OP_PLUS = 278,
    OP_MINUS = 279,
    OP_TIMES = 280,
    OP_DIVIDE = 281,
    MK_LB = 282,
    MK_RB = 283,
    MK_LPAREN = 284,
    MK_RPAREN = 285,
    MK_LBRACE = 286,
    MK_RBRACE = 287,
    MK_COMMA = 288,
    MK_SEMICOLON = 289,
    MK_DOT = 290,
    ERROR = 291,
    RETURN = 292
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 112 "parser.y" /* yacc.c:355  */

	char *lexeme;
	CON_Type  *const1;
	AST_NODE  *node;

#line 256 "parser.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 273 "parser.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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


#if ! defined yyoverflow || YYERROR_VERBOSE

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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
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
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  20
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   254

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  38
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  41
/* YYNRULES -- Number of rules.  */
#define YYNRULES  111
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  214

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   292

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
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
      35,    36,    37
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   166,   166,   167,   170,   174,   180,   184,   190,   197,
     205,   211,   220,   224,   231,   236,   243,   247,   253,   259,
     264,   270,   275,   280,   286,   291,   298,   302,   308,   314,
     322,   328,   336,   340,   346,   350,   355,   362,   370,   378,
     383,   388,   394,   400,   406,   412,   419,   425,   432,   437,
     444,   448,   454,   462,   466,   473,   478,   485,   491,   497,
     503,   509,   517,   524,   531,   536,   542,   550,   556,   561,
     567,   581,   588,   595,   599,   606,   611,   619,   624,   632,
     637,   642,   647,   652,   657,   665,   671,   676,   682,   690,
     696,   703,   707,   713,   719,   726,   731,   738,   744,   750,
     756,   762,   770,   778,   786,   795,   801,   807,   815,   820,
     829,   834
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ID", "CONST", "VOID", "INT", "FLOAT",
  "IF", "ELSE", "WHILE", "FOR", "TYPEDEF", "OP_ASSIGN", "OP_OR", "OP_AND",
  "OP_NOT", "OP_EQ", "OP_NE", "OP_GT", "OP_LT", "OP_GE", "OP_LE",
  "OP_PLUS", "OP_MINUS", "OP_TIMES", "OP_DIVIDE", "MK_LB", "MK_RB",
  "MK_LPAREN", "MK_RPAREN", "MK_LBRACE", "MK_RBRACE", "MK_COMMA",
  "MK_SEMICOLON", "MK_DOT", "ERROR", "RETURN", "$accept", "program",
  "global_decl_list", "global_decl", "function_decl", "param_list",
  "param", "dim_fn", "expr_null", "block", "decl_list", "decl",
  "type_decl", "var_decl", "type", "id_list", "dim_decl", "cexpr",
  "mcexpr", "cfactor", "init_id_list", "init_id", "stmt_list", "elseif",
  "stmt", "assign_expr_list", "nonempty_assign_expr_list", "assign_expr",
  "relop_expr", "relop_term", "relop_factor", "rel_op", "relop_expr_list",
  "nonempty_relop_expr_list", "expr", "add_op", "term", "mul_op", "factor",
  "var_ref", "dim_list", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292
};
# endif

#define YYPACT_NINF -124

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-124)))

#define YYTABLE_NINF -40

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     145,     6,    11,  -124,  -124,   184,    20,   145,  -124,  -124,
     145,  -124,  -124,  -124,    59,    39,   102,    46,     6,     6,
    -124,  -124,  -124,  -124,    24,   132,  -124,    78,   121,  -124,
      80,   135,   160,   110,   111,    78,   143,  -124,    12,    39,
     125,    67,  -124,   180,  -124,  -124,    45,  -124,     7,    42,
     110,   171,   144,  -124,   154,   170,  -124,  -124,   176,    74,
     195,  -124,  -124,    12,   139,   172,  -124,    78,    23,   181,
     193,   186,   110,   110,   187,   100,  -124,   110,  -124,   188,
    -124,   110,  -124,    82,   110,   110,  -124,  -124,  -124,  -124,
    -124,  -124,  -124,  -124,   110,   110,  -124,  -124,   110,    23,
     189,   114,    12,    12,  -124,    12,    12,    36,   182,   190,
     192,    23,  -124,    87,   191,    23,   143,    48,  -124,   203,
      23,  -124,   110,   197,   156,   171,   196,   194,   110,   110,
     117,   119,  -124,   144,  -124,   178,   170,  -124,   198,    23,
    -124,   172,   172,  -124,  -124,   110,   110,   110,   116,   199,
    -124,    -2,  -124,    48,   126,  -124,   110,   200,   201,   178,
     110,  -124,  -124,   110,   158,   204,  -124,  -124,  -124,   205,
     206,   208,   209,    54,   183,   202,  -124,   171,  -124,  -124,
      75,  -124,  -124,   164,   171,  -124,  -124,  -124,  -124,    48,
      48,   110,   110,   116,  -124,  -124,   213,  -124,   171,   207,
    -124,    91,  -124,   116,   211,  -124,   212,   110,    48,   214,
    -124,    48,   213,  -124
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     0,    32,    33,     0,     0,     2,     5,     7,
       0,    25,    26,    27,     0,    34,     0,     0,     0,     0,
       1,     4,     6,    24,    39,     0,    48,    37,     0,    31,
       0,     0,     0,     0,     0,    51,     0,    30,     0,    35,
       0,     0,    13,     0,    29,    28,   108,   100,     0,     0,
       0,    52,    73,    75,    77,    90,    94,   105,     0,     0,
      39,    49,    46,     0,     0,    42,    45,    36,    23,     0,
       0,    14,     0,    86,   109,   108,   102,     0,   107,   108,
     101,     0,   106,     0,     0,     0,    79,    82,    83,    84,
      80,    81,    91,    92,     0,     0,    95,    96,     0,    23,
       0,     0,     0,     0,    38,     0,     0,   108,     0,     0,
       0,    23,    64,     0,     0,    22,     0,    21,    54,     0,
      23,    12,    19,    15,     0,    88,     0,    85,     0,    86,
       0,     0,    97,    74,    76,    78,    89,    93,     0,    23,
      47,    40,    41,    43,    44,    86,    86,    86,    68,     0,
      65,     0,    11,    20,   108,    53,     0,     0,     0,    18,
       0,   111,   103,     0,     0,     0,    99,    98,    10,     0,
       0,     0,     0,   108,     0,    67,    70,    72,    58,    66,
       0,     9,    16,     0,    87,   110,   104,     8,    63,     0,
       0,     0,    86,     0,    61,    17,    57,    59,    71,     0,
      69,     0,    62,    68,     0,    55,     0,    86,     0,     0,
      60,     0,    57,    56
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -124,  -124,  -124,   218,   223,   215,   148,  -124,  -124,   -92,
      43,    -7,  -124,  -124,     8,   185,    10,   165,   103,   104,
    -124,   210,   128,    33,  -113,    44,  -124,    55,   -33,   166,
     167,  -124,  -123,  -124,   -67,  -124,   159,  -124,   153,   -47,
    -124
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     6,     7,     8,     9,    41,    42,   123,   158,   114,
     115,    11,    12,    13,   116,    16,    35,    64,    65,    66,
      25,    26,   117,   202,   118,   174,   175,   176,   125,    52,
      53,    94,   126,   127,    54,    95,    55,    98,    56,    57,
      74
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      51,    78,    82,    23,   155,   124,   165,   138,    14,    15,
      75,    76,    84,    19,    17,    14,    62,    83,    14,   149,
      20,   119,   170,   171,   172,    27,   107,   135,   157,     3,
       4,   108,   179,   109,   110,     5,    77,    33,    43,    15,
     155,    63,    43,    10,   130,    79,    80,   169,   131,    67,
      10,   154,   119,    34,   111,   159,   108,   112,   109,   110,
     113,   164,    24,    72,   119,   145,   -39,   191,   119,   199,
     119,    81,    72,   119,    73,    30,   196,   197,    43,   111,
     151,    72,   112,    73,   209,   113,     3,     4,   205,    84,
      46,    47,   119,   183,   154,   210,    84,    69,   212,   204,
      70,   109,   110,    48,   100,    38,   119,    70,    23,   194,
      40,    49,   132,    46,    47,   177,    50,     3,     4,   173,
      47,   150,   111,   180,    39,   112,    48,    72,   113,   129,
     184,    84,    48,    84,    49,    28,    29,   102,   103,    50,
      49,    58,   119,   119,   140,    50,    60,   166,     1,   167,
       2,     3,     4,    72,   119,   145,    68,     5,   198,    85,
     177,   119,   102,   103,   119,    36,    37,   104,    28,    44,
     177,    86,    87,    88,    89,    90,    91,    92,    93,    92,
      93,    92,    93,    71,   161,    84,   185,    92,    93,    18,
       3,     4,   195,    28,    45,    96,    97,   105,   106,     3,
       4,    92,    93,    31,    32,   141,   142,    99,    33,   143,
     144,   146,   120,   122,   128,    72,   156,   192,   121,   147,
     139,   148,   201,   152,   160,    21,   162,   163,   101,   182,
     168,   178,   181,    22,   186,   193,   188,   187,   189,   190,
     207,   203,   208,   153,   211,   213,    61,   206,   200,    59,
     133,   137,   134,     0,   136
};

static const yytype_int16 yycheck[] =
{
      33,    48,    49,    10,   117,    72,   129,    99,     0,     3,
       3,     4,    14,     5,     3,     7,     4,    50,    10,   111,
       0,    68,   145,   146,   147,    15,     3,    94,   120,     6,
       7,     8,    34,    10,    11,    12,    29,    13,    30,     3,
     153,    29,    34,     0,    77,     3,     4,   139,    81,    39,
       7,     3,    99,    29,    31,   122,     8,    34,    10,    11,
      37,   128,     3,    27,   111,    29,    27,    13,   115,   192,
     117,    29,    27,   120,    29,    29,   189,   190,    70,    31,
     113,    27,    34,    29,   207,    37,     6,     7,   201,    14,
       3,     4,   139,   160,     3,   208,    14,    30,   211,     8,
      33,    10,    11,    16,    30,    27,   153,    33,   115,    34,
      30,    24,    30,     3,     4,   148,    29,     6,     7,     3,
       4,    34,    31,   156,     3,    34,    16,    27,    37,    29,
     163,    14,    16,    14,    24,    33,    34,    23,    24,    29,
      24,    30,   189,   190,    30,    29,     3,    30,     3,    30,
       5,     6,     7,    27,   201,    29,    31,    12,   191,    15,
     193,   208,    23,    24,   211,    33,    34,    28,    33,    34,
     203,    17,    18,    19,    20,    21,    22,    23,    24,    23,
      24,    23,    24,     3,    28,    14,    28,    23,    24,     5,
       6,     7,    28,    33,    34,    25,    26,    25,    26,     6,
       7,    23,    24,    18,    19,   102,   103,    31,    13,   105,
     106,    29,    31,    27,    27,    27,    13,    34,    70,    29,
      31,    29,     9,    32,    27,     7,    30,    33,    63,    28,
      32,    32,    32,    10,    30,    33,    30,    32,    30,    30,
      29,    34,    30,   115,    30,   212,    36,   203,   193,    34,
      84,    98,    85,    -1,    95
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     5,     6,     7,    12,    39,    40,    41,    42,
      48,    49,    50,    51,    52,     3,    53,     3,     5,    52,
       0,    41,    42,    49,     3,    58,    59,    54,    33,    34,
      29,    53,    53,    13,    29,    54,    33,    34,    27,     3,
      30,    43,    44,    52,    34,    34,     3,     4,    16,    24,
      29,    66,    67,    68,    72,    74,    76,    77,    30,    43,
       3,    59,     4,    29,    55,    56,    57,    54,    31,    30,
      33,     3,    27,    29,    78,     3,     4,    29,    77,     3,
       4,    29,    77,    66,    14,    15,    17,    18,    19,    20,
      21,    22,    23,    24,    69,    73,    25,    26,    75,    31,
      30,    55,    23,    24,    28,    25,    26,     3,     8,    10,
      11,    31,    34,    37,    47,    48,    52,    60,    62,    77,
      31,    44,    27,    45,    72,    66,    70,    71,    27,    29,
      66,    66,    30,    67,    68,    72,    74,    76,    47,    31,
      30,    56,    56,    57,    57,    29,    29,    29,    29,    47,
      34,    66,    32,    60,     3,    62,    13,    47,    46,    72,
      27,    28,    30,    33,    72,    70,    30,    30,    32,    47,
      70,    70,    70,     3,    63,    64,    65,    66,    32,    34,
      66,    32,    28,    72,    66,    28,    30,    32,    30,    30,
      30,    13,    34,    33,    34,    28,    62,    62,    66,    70,
      65,     9,    61,    34,     8,    62,    63,    29,    30,    70,
      62,    30,    62,    61
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    38,    39,    39,    40,    40,    41,    41,    42,    42,
      42,    42,    43,    43,    44,    44,    45,    45,    46,    46,
      47,    47,    47,    47,    48,    48,    49,    49,    50,    50,
      51,    51,    52,    52,    53,    53,    53,    53,    54,    54,
      55,    55,    55,    56,    56,    56,    57,    57,    58,    58,
      59,    59,    59,    60,    60,    61,    61,    61,    62,    62,
      62,    62,    62,    62,    62,    62,    62,    63,    63,    64,
      64,    65,    65,    66,    66,    67,    67,    68,    68,    69,
      69,    69,    69,    69,    69,    70,    70,    71,    71,    72,
      72,    73,    73,    74,    74,    75,    75,    76,    76,    76,
      76,    76,    76,    76,    76,    76,    76,    76,    77,    77,
      78,    78
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     2,     1,     2,     1,     8,     8,
       7,     7,     3,     1,     2,     3,     3,     4,     1,     0,
       2,     1,     1,     0,     2,     1,     1,     1,     4,     4,
       3,     3,     1,     1,     1,     3,     4,     2,     4,     0,
       3,     3,     1,     3,     3,     1,     1,     3,     1,     3,
       1,     2,     3,     2,     1,     2,     7,     0,     3,     5,
       9,     4,     6,     4,     1,     2,     3,     1,     0,     3,
       1,     3,     1,     1,     3,     1,     3,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     0,     3,     1,     3,
       1,     1,     1,     3,     1,     1,     1,     3,     4,     4,
       1,     2,     2,     4,     5,     1,     2,     2,     1,     2,
       4,     3
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
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
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
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
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
| yyreduce -- Do a reduction.  |
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
        case 2:
#line 166 "parser.y" /* yacc.c:1646  */
    { (yyval.node)=Allocate(PROGRAM_NODE);  makeChild((yyval.node),(yyvsp[0].node)); prog=(yyval.node);}
#line 1511 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 167 "parser.y" /* yacc.c:1646  */
    { (yyval.node)=Allocate(PROGRAM_NODE); prog=(yyval.node);}
#line 1517 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 171 "parser.y" /* yacc.c:1646  */
    {
                        (yyval.node) = makeSibling((yyvsp[-1].node), (yyvsp[0].node));
                    }
#line 1525 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 175 "parser.y" /* yacc.c:1646  */
    {
                        (yyval.node) = (yyvsp[0].node);
                    }
#line 1533 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 181 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeSibling(makeChild(Allocate(VARIABLE_DECL_LIST_NODE), (yyvsp[-1].node)), (yyvsp[0].node));
                }
#line 1541 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 185 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = (yyvsp[0].node);
                }
#line 1549 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 191 "parser.y" /* yacc.c:1646  */
    {
                        (yyval.node) = makeDeclNode(FUNCTION_DECL);
                        AST_NODE* parameterList = Allocate(PARAM_LIST_NODE);
                        makeChild(parameterList, (yyvsp[-4].node));
                        makeFamily((yyval.node), 4, (yyvsp[-7].node), makeIDNode((yyvsp[-6].lexeme), NORMAL_ID), parameterList, (yyvsp[-1].node));
                    }
#line 1560 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 198 "parser.y" /* yacc.c:1646  */
    {
                        /*TODO*/
                        (yyval.node) = makeDeclNode(FUNCTION_DECL);
                        AST_NODE* parameterList = Allocate(PARAM_LIST_NODE);
                        makeChild(parameterList, (yyvsp[-4].node));
                        makeFamily((yyval.node), 4, makeIDNode("void", NORMAL_ID), makeIDNode((yyvsp[-6].lexeme), NORMAL_ID), parameterList, (yyvsp[-1].node));
                    }
#line 1572 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 206 "parser.y" /* yacc.c:1646  */
    {
                        (yyval.node) = makeDeclNode(FUNCTION_DECL);
                        AST_NODE* emptyParameterList = Allocate(PARAM_LIST_NODE);
                        makeFamily((yyval.node), 4, (yyvsp[-6].node), makeIDNode((yyvsp[-5].lexeme), NORMAL_ID), emptyParameterList, (yyvsp[-1].node));
                    }
#line 1582 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 212 "parser.y" /* yacc.c:1646  */
    {
                        /*TODO*/
                        (yyval.node) = makeDeclNode(FUNCTION_DECL);
                        AST_NODE* emptyParameterList = Allocate(PARAM_LIST_NODE);
                        makeFamily((yyval.node), 4, makeIDNode("void", NORMAL_ID), makeIDNode((yyvsp[-5].lexeme), NORMAL_ID), emptyParameterList, (yyvsp[-1].node));
                    }
#line 1593 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 221 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeSibling((yyvsp[-2].node), (yyvsp[0].node));
                }
#line 1601 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 225 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                    (yyval.node) = (yyvsp[0].node);
                }
#line 1610 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 232 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeDeclNode(FUNCTION_PARAMETER_DECL);
                    makeFamily((yyval.node), 2, (yyvsp[-1].node), makeIDNode((yyvsp[0].lexeme), NORMAL_ID));
                }
#line 1619 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 237 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO jizz*/
                    (yyval.node) = makeDeclNode(FUNCTION_PARAMETER_DECL);
                    makeFamily((yyval.node), 3, (yyvsp[-2].node), makeIDNode((yyvsp[-1].lexeme), NORMAL_ID), (yyvsp[0].node));
                }
#line 1629 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 244 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = (yyvsp[-1].node);
                }
#line 1637 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 248 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeSibling((yyvsp[-3].node), (yyvsp[-1].node));
                }
#line 1645 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 254 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                    (yyval.node) = (yyvsp[0].node);
                }
#line 1654 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 259 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = Allocate(NUL_NODE); 
                }
#line 1662 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 265 "parser.y" /* yacc.c:1646  */
    {
                        /*TODO*/
                        (yyval.node) = Allocate(BLOCK_NODE);
                        makeFamily((yyval.node), 2, makeChild(Allocate(VARIABLE_DECL_LIST_NODE), (yyvsp[-1].node)), makeChild(Allocate(STMT_LIST_NODE), (yyvsp[0].node)));
                    }
#line 1672 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 271 "parser.y" /* yacc.c:1646  */
    {
                        (yyval.node) = Allocate(BLOCK_NODE);
                        makeChild((yyval.node), makeChild(Allocate(STMT_LIST_NODE), (yyvsp[0].node)));
                    }
#line 1681 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 276 "parser.y" /* yacc.c:1646  */
    {
                        (yyval.node) = Allocate(BLOCK_NODE);
                        makeChild((yyval.node), makeChild(Allocate(VARIABLE_DECL_LIST_NODE), (yyvsp[0].node)));
                    }
#line 1690 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 280 "parser.y" /* yacc.c:1646  */
    {
                        /*TODO*/
                        (yyval.node) = Allocate(NUL_NODE); 
                    }
#line 1699 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 287 "parser.y" /* yacc.c:1646  */
    {
                        /*TODO*/
                        (yyval.node) = makeSibling((yyvsp[-1].node), (yyvsp[0].node));
                }
#line 1708 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 292 "parser.y" /* yacc.c:1646  */
    {
                        /*TODO*/
                        (yyval.node) = (yyvsp[0].node);
                }
#line 1717 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 299 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = (yyvsp[0].node);
                }
#line 1725 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 303 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = (yyvsp[0].node);
                }
#line 1733 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 309 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO jizz*/
                    (yyval.node) = makeDeclNode(TYPE_DECL);
                    makeFamily((yyval.node), 2, (yyvsp[-2].node), (yyvsp[-1].node));
                }
#line 1743 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 315 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO jizz*/
                    (yyval.node) = makeDeclNode(TYPE_DECL);
                    makeFamily((yyval.node), 2, makeIDNode("void", NORMAL_ID), (yyvsp[-1].node));
                }
#line 1753 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 323 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                    (yyval.node) = makeDeclNode(VARIABLE_DECL);
                    makeFamily((yyval.node), 2, (yyvsp[-2].node), (yyvsp[-1].node));
                }
#line 1763 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 329 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                    (yyval.node) = makeDeclNode(VARIABLE_DECL);
                    makeFamily((yyval.node), 2, (yyvsp[-2].lexeme), (yyvsp[-1].node));
                }
#line 1773 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 337 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeIDNode("int", NORMAL_ID);  
                }
#line 1781 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 341 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeIDNode("float", NORMAL_ID);
                }
#line 1789 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 347 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeIDNode((yyvsp[0].lexeme), NORMAL_ID);
                }
#line 1797 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 351 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                    (yyval.node) = makeSibling((yyvsp[-2].node), makeIDNode((yyvsp[0].lexeme), NORMAL_ID));
                }
#line 1806 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 356 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO jizz*/
                    AST_NODE* id = makeIDNode((yyvsp[-1].lexeme), ARRAY_ID);
                    makeChild(id, (yyvsp[0].node));
                    (yyval.node) = makeSibling((yyvsp[-3].node), id);
                }
#line 1817 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 363 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO jizz*/
                    (yyval.node) = makeIDNode((yyvsp[-1].lexeme), ARRAY_ID);
                    makeChild((yyval.node), (yyvsp[0].node));
                }
#line 1827 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 371 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                    (yyval.node) = makeSibling((yyvsp[-3].node), (yyvsp[-1].node));
                }
#line 1836 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 378 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                    (yyval.node) = Allocate(NUL_NODE); 
                }
#line 1845 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 384 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_ADD);
                    makeFamily((yyval.node), 2, (yyvsp[-2].node), (yyvsp[0].node));
                }
#line 1854 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 389 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_SUB);
                    makeFamily((yyval.node), 2, (yyvsp[-2].node), (yyvsp[0].node));
                }
#line 1864 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 395 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                    (yyval.node) = (yyvsp[0].node);
                }
#line 1873 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 401 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_MUL);
                    makeFamily((yyval.node), 2, (yyvsp[-2].node), (yyvsp[0].node));
                }
#line 1883 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 407 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_DIV);
                    makeFamily((yyval.node), 2, (yyvsp[-2].node), (yyvsp[0].node));
                }
#line 1893 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 413 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                    (yyval.node) = (yyvsp[0].node);
                }
#line 1902 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 420 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                    (yyval.node) = Allocate(CONST_VALUE_NODE);
                    (yyval.node)->semantic_value.const1=(yyvsp[0].const1);
                }
#line 1912 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 426 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                    (yyval.node) = (yyvsp[-1].node);
                }
#line 1921 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 433 "parser.y" /* yacc.c:1646  */
    {
                        /*TODO*/
                        (yyval.node) = (yyvsp[0].node);
                    }
#line 1930 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 438 "parser.y" /* yacc.c:1646  */
    {
                        /*TODO*/
                        (yyval.node) = makeSibling((yyvsp[-2].node), (yyvsp[0].node));
                    }
#line 1939 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 445 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeIDNode((yyvsp[0].lexeme), NORMAL_ID);
                }
#line 1947 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 449 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO jizz*/
                    (yyval.node) = makeIDNode((yyvsp[-1].lexeme), ARRAY_ID);
                    makeChild((yyval.node), (yyvsp[0].node));
                }
#line 1957 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 455 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO jizz*/
                    (yyval.node) = makeIDNode((yyvsp[-2].lexeme), NORMAL_ID);
                    makeChild((yyval.node), (yyvsp[0].node));
                }
#line 1967 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 463 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                }
#line 1975 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 467 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                }
#line 1983 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 474 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                    (yyval.node) = (yyvsp[0].node);
                }
#line 1992 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 479 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                    (yyval.node) = makeStmtNode(IF_STMT);
                    makeFamily((yyval.node), 3, (yyvsp[-3].node), (yyvsp[-1].node), (yyvsp[0].node));
                }
#line 2002 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 485 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                    (yyval.node) = Allocate(NUL_NODE); 
                }
#line 2011 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 492 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                    (yyval.node) = (yyvsp[-1].node);
                }
#line 2020 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 498 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                    (yyval.node) = makeStmtNode(WHILE_STMT);
                    makeFamily((yyval.node), 2, (yyvsp[-2].node), (yyvsp[0].node));
                }
#line 2030 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 504 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                    (yyval.node) = makeStmtNode(FOR_STMT);
                    makeFamily((yyval.node), 4, (yyvsp[-6].node), (yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node));
                }
#line 2040 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 510 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                    (yyval.node) = makeStmtNode(ASSIGN_STMT);
                    makeFamily((yyval.node), 2, (yyvsp[-3].node), (yyvsp[-1].node));
                }
#line 2050 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 518 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                    (yyval.node) = makeStmtNode(IF_STMT);
                    makeFamily((yyval.node), 3, (yyvsp[-3].node), (yyvsp[-1].node), (yyvsp[0].node));
                }
#line 2060 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 525 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                    (yyval.node) = makeStmtNode(FUNCTION_CALL_STMT);
                    AST_NODE* func = makeIDNode((yyvsp[-3].lexeme), NORMAL_ID);
                    makeFamily((yyval.node), 2, func, (yyvsp[-1].node));
                }
#line 2071 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 532 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                    (yyval.node) = Allocate(NUL_NODE); 
                }
#line 2080 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 537 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                    (yyval.node) = makeStmtNode(RETURN_STMT);
                    makeChild((yyval.node), Allocate(NUL_NODE));
                }
#line 2090 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 543 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                    (yyval.node) = makeStmtNode(RETURN_STMT);
                    makeChild((yyval.node), (yyvsp[-1].node));
                }
#line 2100 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 551 "parser.y" /* yacc.c:1646  */
    {
                        /*TODO*/
                        (yyval.node) = (yyvsp[0].node);
                     }
#line 2109 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 556 "parser.y" /* yacc.c:1646  */
    {
                         (yyval.node) = Allocate(NUL_NODE); 
                     }
#line 2117 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 562 "parser.y" /* yacc.c:1646  */
    {
                                        /*TODO*/
                                        (yyval.node) = (yyvsp[-2].node);
                                        makeSibling((yyvsp[-2].node)->child, (yyvsp[0].node));
                                    }
#line 2127 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 568 "parser.y" /* yacc.c:1646  */
    {
                                        /*TODO*/
                                        (yyval.node) = Allocate(NONEMPTY_ASSIGN_EXPR_LIST_NODE);
                                        makeFamily((yyval.node), 1, (yyvsp[0].node));
                                    }
#line 2137 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 582 "parser.y" /* yacc.c:1646  */
    {
                        /*TODO*/
                        (yyval.node) = makeStmtNode(ASSIGN_STMT);
                        AST_NODE* id = makeIDNode((yyvsp[-2].lexeme), NORMAL_ID);
                        makeFamily((yyval.node), 2, id, (yyvsp[0].node));
                    }
#line 2148 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 589 "parser.y" /* yacc.c:1646  */
    {
                        /*TODO*/
                        (yyval.node) = (yyvsp[0].node);
                    }
#line 2157 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 596 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = (yyvsp[0].node);
                }
#line 2165 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 600 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_OR);
                    makeFamily((yyval.node), 2, (yyvsp[-2].node), (yyvsp[0].node));
                }
#line 2174 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 607 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                    (yyval.node) = (yyvsp[0].node);
                }
#line 2183 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 612 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_AND);
                    makeFamily((yyval.node), 2, (yyvsp[-2].node), (yyvsp[0].node));
                }
#line 2193 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 620 "parser.y" /* yacc.c:1646  */
    {
                        /*TODO*/
                        (yyval.node) = (yyvsp[0].node);
                    }
#line 2202 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 625 "parser.y" /* yacc.c:1646  */
    {
                        /*TODO*/
                        makeFamily((yyvsp[-1].node), 2, (yyvsp[-2].node), (yyvsp[0].node));
                        (yyval.node) = (yyvsp[-1].node);
                    }
#line 2212 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 633 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_EQ);
                }
#line 2221 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 638 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_GE);
                }
#line 2230 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 643 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_LE);
                }
#line 2239 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 648 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_NE);
                }
#line 2248 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 653 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_GT);
                }
#line 2257 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 658 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_LT);
                }
#line 2266 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 666 "parser.y" /* yacc.c:1646  */
    {
                        /*TODO*/
                        (yyval.node) = (yyvsp[0].node);
                    }
#line 2275 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 671 "parser.y" /* yacc.c:1646  */
    {
                        (yyval.node) = Allocate(NUL_NODE);
                    }
#line 2283 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 677 "parser.y" /* yacc.c:1646  */
    {
                                    /*TODO*/
                                    (yyval.node) = (yyvsp[-2].node);
                                    makeSibling((yyvsp[-2].node)->child, (yyvsp[0].node));
                                }
#line 2293 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 683 "parser.y" /* yacc.c:1646  */
    {
                                    /*TODO*/
                                    (yyval.node) = Allocate(NONEMPTY_RELOP_EXPR_LIST_NODE);
                                    makeFamily((yyval.node), 1, (yyvsp[0].node));
                                }
#line 2303 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 691 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                    makeFamily((yyvsp[-1].node), 2, (yyvsp[-2].node), (yyvsp[0].node));
                    (yyval.node) = (yyvsp[-1].node);
                }
#line 2313 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 697 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                    (yyval.node) = (yyvsp[0].node);
                }
#line 2322 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 704 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_ADD);
                }
#line 2330 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 708 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_SUB);
                }
#line 2338 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 714 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                    makeFamily((yyvsp[-1].node), 2, (yyvsp[-2].node), (yyvsp[0].node));
                    (yyval.node) = (yyvsp[-1].node);
                }
#line 2348 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 720 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                    (yyval.node) = (yyvsp[0].node);
                }
#line 2357 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 727 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_MUL);
                }
#line 2366 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 732 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_DIV);
                }
#line 2375 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 739 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                    (yyval.node) = (yyvsp[-1].node);
                }
#line 2384 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 745 "parser.y" /* yacc.c:1646  */
    {   
                    /*TODO*/
                    (yyval.node) = makeExprNode(UNARY_OPERATION, UNARY_OP_NEGATIVE);
                    makeFamily((yyval.node), 1, (yyvsp[-1].node));
                }
#line 2394 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 751 "parser.y" /* yacc.c:1646  */
    {   
                    /*TODO*/
                    (yyval.node) = makeExprNode(UNARY_OPERATION, UNARY_OP_LOGICAL_NEGATION);
                    makeFamily((yyval.node), 1, (yyvsp[-1].node));
                }
#line 2404 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 757 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = Allocate(CONST_VALUE_NODE);
                    (yyval.node)->semantic_value.const1=(yyvsp[0].const1);
                }
#line 2413 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 763 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                    AST_NODE* c = Allocate(CONST_VALUE_NODE);
                    c->semantic_value.const1=(yyvsp[0].const1);
                    (yyval.node) = makeExprNode(UNARY_OPERATION, UNARY_OP_NEGATIVE);
                    makeFamily((yyval.node), 1, c);
                }
#line 2425 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 102:
#line 771 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                    AST_NODE* c = Allocate(CONST_VALUE_NODE);
                    c->semantic_value.const1=(yyvsp[0].const1);
                    (yyval.node) = makeExprNode(UNARY_OPERATION, UNARY_OP_LOGICAL_NEGATION);
                    makeFamily((yyval.node), 1, c);
                }
#line 2437 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 779 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                    (yyval.node) = makeStmtNode(FUNCTION_CALL_STMT);
                    AST_NODE* func = makeIDNode((yyvsp[-3].lexeme), NORMAL_ID);
                    makeFamily((yyval.node), 2, func, (yyvsp[-1].node));
                }
#line 2448 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 787 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                    (yyval.node) = makeExprNode(UNARY_OPERATION, UNARY_OP_LOGICAL_NEGATION);
                    AST_NODE* stmt = makeStmtNode(FUNCTION_CALL_STMT);
                    AST_NODE* func = makeIDNode((yyvsp[-3].lexeme), NORMAL_ID);
                    makeFamily((yyval.node), 1, stmt);
                    makeFamily(stmt, 2, func, (yyvsp[-1].node));
                }
#line 2461 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 105:
#line 796 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                    (yyval.node) = (yyvsp[0].node);
                }
#line 2470 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 106:
#line 802 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                    (yyval.node) = makeExprNode(UNARY_OPERATION, UNARY_OP_NEGATIVE);
                    makeFamily((yyval.node), 1, (yyvsp[0].node));
                }
#line 2480 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 107:
#line 808 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                    (yyval.node) = makeExprNode(UNARY_OPERATION, UNARY_OP_LOGICAL_NEGATION);
                    makeFamily((yyval.node), 1, (yyvsp[0].node));
                }
#line 2490 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 108:
#line 816 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                    (yyval.node) = makeIDNode((yyvsp[0].lexeme), NORMAL_ID);
                }
#line 2499 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 109:
#line 821 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                    (yyval.node) = makeIDNode((yyvsp[-1].lexeme), ARRAY_ID);
                    makeChild((yyval.node), (yyvsp[0].node));
                }
#line 2509 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 110:
#line 830 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                    (yyval.node) = makeSibling((yyvsp[-3].node), (yyvsp[-1].node));
                }
#line 2518 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 111:
#line 835 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                    (yyval.node) = (yyvsp[-1].node);
                }
#line 2527 "parser.tab.c" /* yacc.c:1646  */
    break;


#line 2531 "parser.tab.c" /* yacc.c:1646  */
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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
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
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 842 "parser.y" /* yacc.c:1906  */


#include "lex.yy.c"
main (argc, argv)
int argc;
char *argv[];
{
     yyin = fopen(argv[1],"r");
     yyparse();
	 printf("%s\n", "Parsing completed. No errors found.");
	 printGV(prog, NULL);
} /* main */


int yyerror (mesg)
char *mesg;
{
    printf("%s\t%d\t%s\t%s\n", "Error found in Line ", linenumber, "next token: ", yytext );
    exit(1);
}
