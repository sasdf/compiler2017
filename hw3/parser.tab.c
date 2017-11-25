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
#define YYLAST   252

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  38
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  41
/* YYNRULES -- Number of rules.  */
#define YYNRULES  111
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  215

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
     205,   211,   220,   224,   231,   236,   245,   249,   255,   261,
     266,   272,   277,   282,   288,   293,   300,   304,   310,   316,
     324,   330,   338,   342,   348,   352,   357,   364,   372,   377,
     396,   401,   407,   413,   419,   425,   432,   438,   445,   450,
     457,   461,   467,   475,   481,   489,   495,   501,   507,   513,
     519,   527,   534,   541,   546,   552,   560,   566,   571,   577,
     591,   598,   605,   609,   616,   621,   629,   634,   642,   647,
     652,   657,   662,   667,   675,   681,   686,   692,   700,   706,
     713,   717,   723,   729,   736,   741,   748,   754,   760,   766,
     772,   780,   788,   796,   805,   814,   820,   826,   834,   839,
     848,   853
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

#define YYPACT_NINF -131

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-131)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     161,     8,    30,  -131,  -131,   190,    39,   161,  -131,  -131,
     161,  -131,  -131,  -131,    49,    57,    78,    47,     8,     8,
    -131,  -131,  -131,  -131,    33,   166,  -131,    13,    79,   117,
    -131,    31,   168,   171,   125,    73,    79,   133,  -131,  -131,
      13,   123,   181,  -131,    13,    57,   108,   104,  -131,   159,
    -131,  -131,    61,  -131,    24,    28,   125,    68,   174,  -131,
     160,   183,  -131,  -131,   172,   120,    50,  -131,    84,    13,
      13,  -131,    13,    13,   146,    79,    90,   188,   165,   121,
     125,   125,   148,    96,  -131,   125,  -131,   129,  -131,   125,
    -131,    29,   125,   125,  -131,  -131,  -131,  -131,  -131,  -131,
    -131,  -131,   125,   125,  -131,  -131,   125,    90,   189,  -131,
     181,   181,  -131,  -131,  -131,    21,   192,   193,   195,    90,
    -131,   106,   186,    90,   133,    10,  -131,   178,    90,  -131,
     125,   196,   162,    68,   197,   198,   125,   125,    51,   125,
      55,  -131,   174,  -131,   187,   183,  -131,   200,    90,   125,
     125,   125,   128,   201,  -131,     0,  -131,    10,   132,  -131,
     125,   202,   207,   187,   125,  -131,  -131,   125,   164,   199,
    -131,   206,  -131,  -131,   205,   208,    64,    75,    86,   191,
     209,  -131,    68,  -131,  -131,    15,  -131,  -131,   170,    68,
    -131,  -131,  -131,  -131,   210,    10,    10,   125,   125,   128,
    -131,  -131,  -131,   217,  -131,    68,   211,  -131,    10,  -131,
     128,  -131,   213,    10,  -131
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     0,    32,    33,     0,     0,     2,     5,     7,
       0,    25,    26,    27,     0,    34,     0,     0,     0,     0,
       1,     4,     6,    24,    50,     0,    48,     0,    37,     0,
      31,     0,     0,     0,     0,     0,    51,     0,    30,    46,
       0,     0,    42,    45,     0,    35,     0,     0,    13,     0,
      29,    28,   108,    99,     0,     0,     0,    52,    72,    74,
      76,    89,    93,   105,     0,     0,    50,    49,     0,     0,
       0,    39,     0,     0,     0,    36,    23,     0,     0,    14,
       0,    85,   109,   108,   101,     0,   107,   108,   100,     0,
     106,     0,     0,     0,    78,    81,    82,    83,    79,    80,
      90,    91,     0,     0,    94,    95,     0,    23,     0,    47,
      40,    41,    43,    44,    38,   108,     0,     0,     0,    23,
      63,     0,     0,    22,     0,    21,    54,     0,    23,    12,
      19,    15,     0,    87,     0,    84,     0,    85,     0,    85,
       0,    96,    73,    75,    77,    88,    92,     0,    23,    85,
       0,     0,    67,     0,    64,     0,    11,    20,   108,    53,
       0,     0,     0,    18,     0,   111,   102,     0,     0,     0,
      98,     0,    97,    10,     0,     0,     0,     0,   108,     0,
      66,    69,    71,    57,    65,     0,     9,    16,     0,    86,
     110,   104,   103,     8,     0,     0,     0,     0,    85,     0,
      60,    17,    62,    56,    58,    70,     0,    68,     0,    61,
      67,    55,     0,     0,    59
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -131,  -131,  -131,   221,   220,   204,   163,  -131,  -131,  -103,
     138,    -4,  -131,  -131,     5,   194,    11,    27,   145,   144,
    -131,   203,   124,  -131,  -122,    36,  -131,    52,   -34,   156,
     157,  -131,  -130,  -131,   -72,  -131,   149,  -131,   143,   -53,
    -131
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     6,     7,     8,     9,    47,    48,   131,   162,   122,
     123,    11,    12,    13,   124,    16,    36,    41,    42,    43,
      25,    26,   125,   209,   126,   179,   180,   181,   133,    58,
      59,   102,   134,   135,    60,   103,    61,   106,    62,    63,
      82
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      57,    86,    90,   159,   147,    14,    23,   169,   132,   171,
      19,    15,    14,   158,    92,    14,   153,    39,   116,   175,
     117,   118,    91,   127,    15,   161,    28,    83,    84,    92,
     144,    87,    88,    17,   184,   159,    49,     3,     4,    20,
      49,   119,    40,    92,   120,   174,    34,   121,    80,   200,
     149,   138,    24,    85,   127,   140,    75,    89,   163,   141,
      27,    46,    35,    34,   168,    92,   127,    68,   206,    92,
     127,    74,   127,   203,   204,   127,    31,    27,    92,     3,
       4,   170,    92,    49,    27,   172,   211,   155,    80,    92,
      81,   214,   188,   115,   195,   127,     3,     4,   116,   197,
     117,   118,     5,    64,   127,   196,    44,    69,    70,    52,
      53,    29,    30,    80,   109,    81,   176,   177,   182,    23,
      45,   119,    54,    80,   120,   137,   185,   121,    52,    53,
      55,   178,    53,   189,    77,    56,    66,    78,    10,    76,
     154,    54,   127,   127,    54,    10,    69,    70,   130,    55,
     108,    71,    55,    78,    56,   127,    80,    56,   139,    80,
     127,   149,    79,   205,     1,   182,     2,     3,     4,    69,
      70,     3,     4,     5,   114,   136,   182,    94,    95,    96,
      97,    98,    99,   100,   101,   100,   101,   100,   101,    93,
     165,   160,   190,   100,   101,    18,     3,     4,   201,    37,
      38,    29,    50,   107,    29,    51,    72,    73,   104,   105,
     100,   101,    32,    33,   110,   111,   112,   113,   156,   128,
     148,   150,   151,   164,   152,   198,   208,   166,    21,   191,
      22,   167,   173,   183,   186,   187,   192,   193,   194,    65,
      67,   129,   199,   213,   202,   210,   212,   157,   142,   146,
     143,   207,   145
};

static const yytype_uint8 yycheck[] =
{
      34,    54,    55,   125,   107,     0,    10,   137,    80,   139,
       5,     3,     7,     3,    14,    10,   119,     4,     8,   149,
      10,    11,    56,    76,     3,   128,    15,     3,     4,    14,
     102,     3,     4,     3,    34,   157,    31,     6,     7,     0,
      35,    31,    29,    14,    34,   148,    13,    37,    27,    34,
      29,    85,     3,    29,   107,    89,    45,    29,   130,    30,
      27,    30,    29,    13,   136,    14,   119,    40,   198,    14,
     123,    44,   125,   195,   196,   128,    29,    27,    14,     6,
       7,    30,    14,    78,    27,    30,   208,   121,    27,    14,
      29,   213,   164,     3,    30,   148,     6,     7,     8,    13,
      10,    11,    12,    30,   157,    30,    27,    23,    24,     3,
       4,    33,    34,    27,    30,    29,   150,   151,   152,   123,
       3,    31,    16,    27,    34,    29,   160,    37,     3,     4,
      24,     3,     4,   167,    30,    29,     3,    33,     0,    31,
      34,    16,   195,   196,    16,     7,    23,    24,    27,    24,
      30,    28,    24,    33,    29,   208,    27,    29,    29,    27,
     213,    29,     3,   197,     3,   199,     5,     6,     7,    23,
      24,     6,     7,    12,    28,    27,   210,    17,    18,    19,
      20,    21,    22,    23,    24,    23,    24,    23,    24,    15,
      28,    13,    28,    23,    24,     5,     6,     7,    28,    33,
      34,    33,    34,    31,    33,    34,    25,    26,    25,    26,
      23,    24,    18,    19,    69,    70,    72,    73,    32,    31,
      31,    29,    29,    27,    29,    34,     9,    30,     7,    30,
      10,    33,    32,    32,    32,    28,    30,    32,    30,    35,
      37,    78,    33,    30,    34,    34,   210,   123,    92,   106,
      93,   199,   103
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     5,     6,     7,    12,    39,    40,    41,    42,
      48,    49,    50,    51,    52,     3,    53,     3,     5,    52,
       0,    41,    42,    49,     3,    58,    59,    27,    54,    33,
      34,    29,    53,    53,    13,    29,    54,    33,    34,     4,
      29,    55,    56,    57,    27,     3,    30,    43,    44,    52,
      34,    34,     3,     4,    16,    24,    29,    66,    67,    68,
      72,    74,    76,    77,    30,    43,     3,    59,    55,    23,
      24,    28,    25,    26,    55,    54,    31,    30,    33,     3,
      27,    29,    78,     3,     4,    29,    77,     3,     4,    29,
      77,    66,    14,    15,    17,    18,    19,    20,    21,    22,
      23,    24,    69,    73,    25,    26,    75,    31,    30,    30,
      56,    56,    57,    57,    28,     3,     8,    10,    11,    31,
      34,    37,    47,    48,    52,    60,    62,    77,    31,    44,
      27,    45,    72,    66,    70,    71,    27,    29,    66,    29,
      66,    30,    67,    68,    72,    74,    76,    47,    31,    29,
      29,    29,    29,    47,    34,    66,    32,    60,     3,    62,
      13,    47,    46,    72,    27,    28,    30,    33,    72,    70,
      30,    70,    30,    32,    47,    70,    66,    66,     3,    63,
      64,    65,    66,    32,    34,    66,    32,    28,    72,    66,
      28,    30,    30,    32,    30,    30,    30,    13,    34,    33,
      34,    28,    34,    62,    62,    66,    70,    65,     9,    61,
      34,    62,    63,    30,    62
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    38,    39,    39,    40,    40,    41,    41,    42,    42,
      42,    42,    43,    43,    44,    44,    45,    45,    46,    46,
      47,    47,    47,    47,    48,    48,    49,    49,    50,    50,
      51,    51,    52,    52,    53,    53,    53,    53,    54,    54,
      55,    55,    55,    56,    56,    56,    57,    57,    58,    58,
      59,    59,    59,    60,    60,    61,    61,    62,    62,    62,
      62,    62,    62,    62,    62,    62,    63,    63,    64,    64,
      65,    65,    66,    66,    67,    67,    68,    68,    69,    69,
      69,    69,    69,    69,    70,    70,    71,    71,    72,    72,
      73,    73,    74,    74,    75,    75,    76,    76,    76,    76,
      76,    76,    76,    76,    76,    76,    76,    76,    77,    77,
      78,    78
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     2,     1,     2,     1,     8,     8,
       7,     7,     3,     1,     2,     3,     3,     4,     1,     0,
       2,     1,     1,     0,     2,     1,     1,     1,     4,     4,
       3,     3,     1,     1,     1,     3,     4,     2,     4,     3,
       3,     3,     1,     3,     3,     1,     1,     3,     1,     3,
       1,     2,     3,     2,     1,     2,     0,     3,     5,     9,
       4,     6,     5,     1,     2,     3,     1,     0,     3,     1,
       3,     1,     1,     3,     1,     3,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     0,     3,     1,     3,     1,
       1,     1,     3,     1,     1,     1,     3,     4,     4,     1,
       2,     2,     4,     5,     5,     1,     2,     2,     1,     2,
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
                    AST_NODE *id = makeIDNode((yyvsp[-1].lexeme), NORMAL_ID);
                    makeFamily((yyval.node), 2, (yyvsp[-2].node), id);
                    makeChild(id, (yyvsp[0].node));
                }
#line 1631 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 246 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = (yyvsp[-1].node);
                }
#line 1639 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 250 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeSibling((yyvsp[-3].node), (yyvsp[-1].node));
                }
#line 1647 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 256 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                    (yyval.node) = (yyvsp[0].node);
                }
#line 1656 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 261 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = Allocate(NUL_NODE); 
                }
#line 1664 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 267 "parser.y" /* yacc.c:1646  */
    {
                        /*TODO*/
                        (yyval.node) = Allocate(BLOCK_NODE);
                        makeFamily((yyval.node), 2, makeChild(Allocate(VARIABLE_DECL_LIST_NODE), (yyvsp[-1].node)), makeChild(Allocate(STMT_LIST_NODE), (yyvsp[0].node)));
                    }
#line 1674 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 273 "parser.y" /* yacc.c:1646  */
    {
                        (yyval.node) = Allocate(BLOCK_NODE);
                        makeChild((yyval.node), makeChild(Allocate(STMT_LIST_NODE), (yyvsp[0].node)));
                    }
#line 1683 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 278 "parser.y" /* yacc.c:1646  */
    {
                        (yyval.node) = Allocate(BLOCK_NODE);
                        makeChild((yyval.node), makeChild(Allocate(VARIABLE_DECL_LIST_NODE), (yyvsp[0].node)));
                    }
#line 1692 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 282 "parser.y" /* yacc.c:1646  */
    {
                        /*TODO*/
                        (yyval.node) = Allocate(BLOCK_NODE); 
                    }
#line 1701 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 289 "parser.y" /* yacc.c:1646  */
    {
                        /*TODO*/
                        (yyval.node) = makeSibling((yyvsp[-1].node), (yyvsp[0].node));
                }
#line 1710 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 294 "parser.y" /* yacc.c:1646  */
    {
                        /*TODO*/
                        (yyval.node) = (yyvsp[0].node);
                }
#line 1719 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 301 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = (yyvsp[0].node);
                }
#line 1727 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 305 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = (yyvsp[0].node);
                }
#line 1735 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 311 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO jizz*/
                    (yyval.node) = makeDeclNode(TYPE_DECL);
                    makeFamily((yyval.node), 2, (yyvsp[-2].node), (yyvsp[-1].node));
                }
#line 1745 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 317 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO jizz*/
                    (yyval.node) = makeDeclNode(TYPE_DECL);
                    makeFamily((yyval.node), 2, makeIDNode("void", NORMAL_ID), (yyvsp[-1].node));
                }
#line 1755 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 325 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                    (yyval.node) = makeDeclNode(VARIABLE_DECL);
                    makeFamily((yyval.node), 2, (yyvsp[-2].node), (yyvsp[-1].node));
                }
#line 1765 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 331 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                    (yyval.node) = makeDeclNode(VARIABLE_DECL);
                    makeFamily((yyval.node), 2, makeIDNode((yyvsp[-2].lexeme), NORMAL_ID), (yyvsp[-1].node));
                }
#line 1775 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 339 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeIDNode("int", NORMAL_ID);  
                }
#line 1783 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 343 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeIDNode("float", NORMAL_ID);
                }
#line 1791 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 349 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeIDNode((yyvsp[0].lexeme), NORMAL_ID);
                }
#line 1799 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 353 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                    (yyval.node) = makeSibling((yyvsp[-2].node), makeIDNode((yyvsp[0].lexeme), NORMAL_ID));
                }
#line 1808 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 358 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO jizz*/
                    AST_NODE* id = makeIDNode((yyvsp[-1].lexeme), ARRAY_ID);
                    makeChild(id, (yyvsp[0].node));
                    (yyval.node) = makeSibling((yyvsp[-3].node), id);
                }
#line 1819 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 365 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO jizz*/
                    (yyval.node) = makeIDNode((yyvsp[-1].lexeme), ARRAY_ID);
                    makeChild((yyval.node), (yyvsp[0].node));
                }
#line 1829 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 373 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                    (yyval.node) = makeSibling((yyvsp[-3].node), (yyvsp[-1].node));
                }
#line 1838 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 378 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = (yyvsp[-1].node);
                }
#line 1846 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 397 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_ADD);
                    makeFamily((yyval.node), 2, (yyvsp[-2].node), (yyvsp[0].node));
                }
#line 1855 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 402 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_SUB);
                    makeFamily((yyval.node), 2, (yyvsp[-2].node), (yyvsp[0].node));
                }
#line 1865 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 408 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                    (yyval.node) = (yyvsp[0].node);
                }
#line 1874 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 414 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_MUL);
                    makeFamily((yyval.node), 2, (yyvsp[-2].node), (yyvsp[0].node));
                }
#line 1884 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 420 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_DIV);
                    makeFamily((yyval.node), 2, (yyvsp[-2].node), (yyvsp[0].node));
                }
#line 1894 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 426 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                    (yyval.node) = (yyvsp[0].node);
                }
#line 1903 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 433 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                    (yyval.node) = Allocate(CONST_VALUE_NODE);
                    (yyval.node)->semantic_value.const1=(yyvsp[0].const1);
                }
#line 1913 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 439 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                    (yyval.node) = (yyvsp[-1].node);
                }
#line 1922 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 446 "parser.y" /* yacc.c:1646  */
    {
                        /*TODO*/
                        (yyval.node) = (yyvsp[0].node);
                    }
#line 1931 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 451 "parser.y" /* yacc.c:1646  */
    {
                        /*TODO*/
                        (yyval.node) = makeSibling((yyvsp[-2].node), (yyvsp[0].node));
                    }
#line 1940 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 458 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeIDNode((yyvsp[0].lexeme), NORMAL_ID);
                }
#line 1948 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 462 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO jizz*/
                    (yyval.node) = makeIDNode((yyvsp[-1].lexeme), ARRAY_ID);
                    makeChild((yyval.node), (yyvsp[0].node));
                }
#line 1958 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 468 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO jizz*/
                    (yyval.node) = makeIDNode((yyvsp[-2].lexeme), NORMAL_ID);
                    makeChild((yyval.node), (yyvsp[0].node));
                }
#line 1968 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 476 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                    (yyval.node) = (yyvsp[-1].node);
                    makeSibling((yyval.node), (yyvsp[0].node));
                }
#line 1978 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 482 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                    (yyval.node) = (yyvsp[0].node);
                }
#line 1987 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 490 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                    (yyval.node) = (yyvsp[0].node);
                }
#line 1996 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 495 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                    (yyval.node) = Allocate(NUL_NODE); 
                }
#line 2005 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 502 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                    (yyval.node) = (yyvsp[-1].node);
                }
#line 2014 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 508 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                    (yyval.node) = makeStmtNode(WHILE_STMT);
                    makeFamily((yyval.node), 2, (yyvsp[-2].node), (yyvsp[0].node));
                }
#line 2024 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 514 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                    (yyval.node) = makeStmtNode(FOR_STMT);
                    makeFamily((yyval.node), 4, (yyvsp[-6].node), (yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node));
                }
#line 2034 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 520 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                    (yyval.node) = makeStmtNode(ASSIGN_STMT);
                    makeFamily((yyval.node), 2, (yyvsp[-3].node), (yyvsp[-1].node));
                }
#line 2044 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 528 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                    (yyval.node) = makeStmtNode(IF_STMT);
                    makeFamily((yyval.node), 3, (yyvsp[-3].node), (yyvsp[-1].node), (yyvsp[0].node));
                }
#line 2054 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 535 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                    (yyval.node) = makeStmtNode(FUNCTION_CALL_STMT);
                    AST_NODE* func = makeIDNode((yyvsp[-4].lexeme), NORMAL_ID);
                    makeFamily((yyval.node), 2, func, (yyvsp[-2].node));
                }
#line 2065 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 542 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                    (yyval.node) = Allocate(NUL_NODE); 
                }
#line 2074 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 547 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                    (yyval.node) = makeStmtNode(RETURN_STMT);
                    makeChild((yyval.node), Allocate(NUL_NODE));
                }
#line 2084 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 553 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                    (yyval.node) = makeStmtNode(RETURN_STMT);
                    makeChild((yyval.node), (yyvsp[-1].node));
                }
#line 2094 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 561 "parser.y" /* yacc.c:1646  */
    {
                        /*TODO*/
                        (yyval.node) = (yyvsp[0].node);
                     }
#line 2103 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 566 "parser.y" /* yacc.c:1646  */
    {
                         (yyval.node) = Allocate(NUL_NODE); 
                     }
#line 2111 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 572 "parser.y" /* yacc.c:1646  */
    {
                                        /*TODO*/
                                        (yyval.node) = (yyvsp[-2].node);
                                        makeSibling((yyvsp[-2].node)->child, (yyvsp[0].node));
                                    }
#line 2121 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 578 "parser.y" /* yacc.c:1646  */
    {
                                        /*TODO*/
                                        (yyval.node) = Allocate(NONEMPTY_ASSIGN_EXPR_LIST_NODE);
                                        makeFamily((yyval.node), 1, (yyvsp[0].node));
                                    }
#line 2131 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 592 "parser.y" /* yacc.c:1646  */
    {
                        /*TODO*/
                        (yyval.node) = makeStmtNode(ASSIGN_STMT);
                        AST_NODE* id = makeIDNode((yyvsp[-2].lexeme), NORMAL_ID);
                        makeFamily((yyval.node), 2, id, (yyvsp[0].node));
                    }
#line 2142 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 599 "parser.y" /* yacc.c:1646  */
    {
                        /*TODO*/
                        (yyval.node) = (yyvsp[0].node);
                    }
#line 2151 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 606 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = (yyvsp[0].node);
                }
#line 2159 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 610 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_OR);
                    makeFamily((yyval.node), 2, (yyvsp[-2].node), (yyvsp[0].node));
                }
#line 2168 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 617 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                    (yyval.node) = (yyvsp[0].node);
                }
#line 2177 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 622 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_AND);
                    makeFamily((yyval.node), 2, (yyvsp[-2].node), (yyvsp[0].node));
                }
#line 2187 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 630 "parser.y" /* yacc.c:1646  */
    {
                        /*TODO*/
                        (yyval.node) = (yyvsp[0].node);
                    }
#line 2196 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 635 "parser.y" /* yacc.c:1646  */
    {
                        /*TODO*/
                        makeFamily((yyvsp[-1].node), 2, (yyvsp[-2].node), (yyvsp[0].node));
                        (yyval.node) = (yyvsp[-1].node);
                    }
#line 2206 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 643 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_EQ);
                }
#line 2215 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 648 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_GE);
                }
#line 2224 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 653 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_LE);
                }
#line 2233 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 658 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_NE);
                }
#line 2242 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 663 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_GT);
                }
#line 2251 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 668 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_LT);
                }
#line 2260 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 676 "parser.y" /* yacc.c:1646  */
    {
                        /*TODO*/
                        (yyval.node) = (yyvsp[0].node);
                    }
#line 2269 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 681 "parser.y" /* yacc.c:1646  */
    {
                        (yyval.node) = Allocate(NUL_NODE);
                    }
#line 2277 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 687 "parser.y" /* yacc.c:1646  */
    {
                                    /*TODO*/
                                    (yyval.node) = (yyvsp[-2].node);
                                    makeSibling((yyvsp[-2].node)->child, (yyvsp[0].node));
                                }
#line 2287 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 693 "parser.y" /* yacc.c:1646  */
    {
                                    /*TODO*/
                                    (yyval.node) = Allocate(NONEMPTY_RELOP_EXPR_LIST_NODE);
                                    makeFamily((yyval.node), 1, (yyvsp[0].node));
                                }
#line 2297 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 701 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                    makeFamily((yyvsp[-1].node), 2, (yyvsp[-2].node), (yyvsp[0].node));
                    (yyval.node) = (yyvsp[-1].node);
                }
#line 2307 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 707 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                    (yyval.node) = (yyvsp[0].node);
                }
#line 2316 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 714 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_ADD);
                }
#line 2324 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 718 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_SUB);
                }
#line 2332 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 724 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                    makeFamily((yyvsp[-1].node), 2, (yyvsp[-2].node), (yyvsp[0].node));
                    (yyval.node) = (yyvsp[-1].node);
                }
#line 2342 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 730 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                    (yyval.node) = (yyvsp[0].node);
                }
#line 2351 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 737 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_MUL);
                }
#line 2360 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 742 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_DIV);
                }
#line 2369 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 749 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                    (yyval.node) = (yyvsp[-1].node);
                }
#line 2378 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 755 "parser.y" /* yacc.c:1646  */
    {   
                    /*TODO*/
                    (yyval.node) = makeExprNode(UNARY_OPERATION, UNARY_OP_NEGATIVE);
                    makeFamily((yyval.node), 1, (yyvsp[-1].node));
                }
#line 2388 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 761 "parser.y" /* yacc.c:1646  */
    {   
                    /*TODO*/
                    (yyval.node) = makeExprNode(UNARY_OPERATION, UNARY_OP_LOGICAL_NEGATION);
                    makeFamily((yyval.node), 1, (yyvsp[-1].node));
                }
#line 2398 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 767 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = Allocate(CONST_VALUE_NODE);
                    (yyval.node)->semantic_value.const1=(yyvsp[0].const1);
                }
#line 2407 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 773 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                    AST_NODE* c = Allocate(CONST_VALUE_NODE);
                    c->semantic_value.const1=(yyvsp[0].const1);
                    (yyval.node) = makeExprNode(UNARY_OPERATION, UNARY_OP_NEGATIVE);
                    makeFamily((yyval.node), 1, c);
                }
#line 2419 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 781 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                    AST_NODE* c = Allocate(CONST_VALUE_NODE);
                    c->semantic_value.const1=(yyvsp[0].const1);
                    (yyval.node) = makeExprNode(UNARY_OPERATION, UNARY_OP_LOGICAL_NEGATION);
                    makeFamily((yyval.node), 1, c);
                }
#line 2431 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 102:
#line 789 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                    (yyval.node) = makeStmtNode(FUNCTION_CALL_STMT);
                    AST_NODE* func = makeIDNode((yyvsp[-3].lexeme), NORMAL_ID);
                    makeFamily((yyval.node), 2, func, (yyvsp[-1].node));
                }
#line 2442 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 797 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                    (yyval.node) = makeExprNode(UNARY_OPERATION, UNARY_OP_NEGATIVE);
                    AST_NODE* stmt = makeStmtNode(FUNCTION_CALL_STMT);
                    AST_NODE* func = makeIDNode((yyvsp[-3].lexeme), NORMAL_ID);
                    makeFamily((yyval.node), 1, stmt);
                    makeFamily(stmt, 2, func, (yyvsp[-1].node));
                }
#line 2455 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 806 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                    (yyval.node) = makeExprNode(UNARY_OPERATION, UNARY_OP_LOGICAL_NEGATION);
                    AST_NODE* stmt = makeStmtNode(FUNCTION_CALL_STMT);
                    AST_NODE* func = makeIDNode((yyvsp[-3].lexeme), NORMAL_ID);
                    makeFamily((yyval.node), 1, stmt);
                    makeFamily(stmt, 2, func, (yyvsp[-1].node));
                }
#line 2468 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 105:
#line 815 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                    (yyval.node) = (yyvsp[0].node);
                }
#line 2477 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 106:
#line 821 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                    (yyval.node) = makeExprNode(UNARY_OPERATION, UNARY_OP_NEGATIVE);
                    makeFamily((yyval.node), 1, (yyvsp[0].node));
                }
#line 2487 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 107:
#line 827 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                    (yyval.node) = makeExprNode(UNARY_OPERATION, UNARY_OP_LOGICAL_NEGATION);
                    makeFamily((yyval.node), 1, (yyvsp[0].node));
                }
#line 2497 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 108:
#line 835 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                    (yyval.node) = makeIDNode((yyvsp[0].lexeme), NORMAL_ID);
                }
#line 2506 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 109:
#line 840 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                    (yyval.node) = makeIDNode((yyvsp[-1].lexeme), ARRAY_ID);
                    makeChild((yyval.node), (yyvsp[0].node));
                }
#line 2516 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 110:
#line 849 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                    (yyval.node) = makeSibling((yyvsp[-3].node), (yyvsp[-1].node));
                }
#line 2525 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 111:
#line 854 "parser.y" /* yacc.c:1646  */
    {
                    /*TODO*/
                    (yyval.node) = (yyvsp[-1].node);
                }
#line 2534 "parser.tab.c" /* yacc.c:1646  */
    break;


#line 2538 "parser.tab.c" /* yacc.c:1646  */
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
#line 861 "parser.y" /* yacc.c:1906  */


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