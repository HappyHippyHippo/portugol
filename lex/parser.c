/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

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
#define YYBISON_VERSION "3.0.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "lex/portugol.y" /* yacc.c:339  */

#include <stdio.h>
#include <stdint.h>

#include <internal/portugol/lex/lex.h>

extern int yylex();
extern int yyget_lineno();
void yyerror(const char *msg) {
    printf("ERROR: %s at line %d\n", msg, yyget_lineno());
    ast_error = 1;
}


#line 81 "lex/parser.c" /* yacc.c:339  */

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
   by #include "parser.h".  */
#ifndef YY_YY_LEX_PARSER_H_INCLUDED
# define YY_YY_LEX_PARSER_H_INCLUDED
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
    TOK_EOL = 258,
    TOK_VAL_TRUE = 259,
    TOK_VAL_FALSE = 260,
    TOK_VAL_NUMBER = 261,
    TOK_VAL_FPNUMBER = 262,
    TOK_VAL_TEXT = 263,
    TOK_OP_NOT = 264,
    TOK_OP_ADD = 265,
    TOK_OP_SUBTRACT = 266,
    TOK_OP_MULTIPLY = 267,
    TOK_OP_DIVIDE = 268,
    TOK_OP_REMAINDER = 269,
    TOK_OP_EQUAL = 270,
    TOK_OP_INEQUAL = 271,
    TOK_OP_GREATER = 272,
    TOK_OP_GREATER_OR_EQUAL = 273,
    TOK_OP_LESSER = 274,
    TOK_OP_LESSER_OR_EQUAL = 275,
    TOK_OP_AND = 276,
    TOK_OP_OR = 277,
    TOK_OP_XOR = 278,
    TOK_OP_ASSIGN = 279,
    TOK_IDENTIFIER = 280,
    TOK_COMMA = 281,
    TOK_COLON = 282,
    TOK_BOOLEAN = 283,
    TOK_INT32 = 284,
    TOK_FLOAT32 = 285,
    TOK_TEXT = 286,
    TOK_END = 287,
    TOK_OF = 288,
    TOK_IF = 289,
    TOK_THEN = 290,
    TOK_ELSE = 291,
    TOK_FOR = 292,
    TOK_TO = 293,
    TOK_STEP = 294,
    TOK_WHILE = 295,
    TOK_RETURN = 296,
    TOK_FUNCTION = 297,
    TOK_PROGRAM = 298,
    TOK_IMPORT = 299,
    TOK_OPEN_PAREN = 300,
    TOK_CLOSE_PAREN = 301
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 16 "lex/portugol.y" /* yacc.c:355  */

    AST_Node*                 ast;
    AST_ParamList*            fparams;
    LexParam                  fparam;
    AST_ArgList*              fargs;
    LexToken                  token;
    LexVarType                vtype;

#line 177 "lex/parser.c" /* yacc.c:355  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_LEX_PARSER_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 206 "lex/parser.c" /* yacc.c:358  */

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
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  14
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   593

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  47
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  23
/* YYNRULES -- Number of rules.  */
#define YYNRULES  69
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  170

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   301

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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   105,   105,   111,   119,   120,   121,   122,   123,   126,
     129,   135,   136,   137,   138,   139,   140,   141,   142,   145,
     154,   164,   173,   184,   187,   193,   204,   212,   224,   234,
     243,   254,   272,   289,   297,   305,   306,   312,   318,   324,
     330,   336,   342,   348,   354,   360,   366,   372,   378,   384,
     390,   396,   402,   403,   404,   407,   414,   423,   425,   430,
     433,   434,   435,   443,   451,   455,   459,   461,   463,   465
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TOK_EOL", "TOK_VAL_TRUE",
  "TOK_VAL_FALSE", "TOK_VAL_NUMBER", "TOK_VAL_FPNUMBER", "TOK_VAL_TEXT",
  "TOK_OP_NOT", "TOK_OP_ADD", "TOK_OP_SUBTRACT", "TOK_OP_MULTIPLY",
  "TOK_OP_DIVIDE", "TOK_OP_REMAINDER", "TOK_OP_EQUAL", "TOK_OP_INEQUAL",
  "TOK_OP_GREATER", "TOK_OP_GREATER_OR_EQUAL", "TOK_OP_LESSER",
  "TOK_OP_LESSER_OR_EQUAL", "TOK_OP_AND", "TOK_OP_OR", "TOK_OP_XOR",
  "TOK_OP_ASSIGN", "TOK_IDENTIFIER", "TOK_COMMA", "TOK_COLON",
  "TOK_BOOLEAN", "TOK_INT32", "TOK_FLOAT32", "TOK_TEXT", "TOK_END",
  "TOK_OF", "TOK_IF", "TOK_THEN", "TOK_ELSE", "TOK_FOR", "TOK_TO",
  "TOK_STEP", "TOK_WHILE", "TOK_RETURN", "TOK_FUNCTION", "TOK_PROGRAM",
  "TOK_IMPORT", "TOK_OPEN_PAREN", "TOK_CLOSE_PAREN", "$accept", "globals",
  "global", "locals", "local", "import", "program", "function", "fparams",
  "fparam", "if", "while", "for", "decl", "assign", "return", "expr",
  "fcall", "fargs", "farg", "constant", "variable", "vartype", YY_NULLPTR
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
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301
};
# endif

#define YYPACT_NINF -48

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-48)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       1,   -48,   -17,    13,    15,     3,   -48,   -48,   -48,   -48,
     -48,   110,   363,   -48,   -48,   -48,   -48,   -48,   -48,   -48,
     -11,    24,   -48,   -48,   -48,   -48,   -48,   -48,    77,    77,
     -15,    77,    40,    77,    77,    77,   161,   -48,    46,    63,
      71,    73,    74,    84,   544,   -48,   -48,    65,   -10,    77,
      47,   -48,   -48,    19,   116,   371,   466,    58,   492,   558,
     408,    60,   -48,   -48,   -48,   -48,   -48,   -48,   -48,   -48,
      77,    77,    77,    77,    77,    77,    77,    77,    77,    77,
      77,    77,    77,    77,    77,    54,   -21,   -48,    75,   558,
     -48,   558,   -19,   -48,    98,    77,   100,   -48,    62,    19,
      19,   -48,   -48,   -48,    59,    59,    27,    27,    27,    27,
     506,   572,   572,   558,   116,   116,    70,   -48,    77,   -48,
     363,   452,   363,   103,   112,   -48,   116,   -48,   151,    77,
     204,   -48,   363,   114,    80,   121,   422,    92,   214,   363,
      94,   363,   127,    77,    93,    99,   257,   -48,   267,   363,
     518,   -48,   106,   102,   109,   310,   147,   -48,   119,   117,
     130,   363,   -48,   -48,   134,   320,   -48,   140,   137,   -48
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     8,     0,     0,     0,     0,     3,     4,     6,     7,
       5,     0,     0,    19,     1,     2,    66,    67,    68,    69,
       0,    31,    18,    60,    61,    62,    63,    64,     0,     0,
      65,     0,     0,     0,     0,     0,     0,    10,     0,     0,
       0,     0,     0,     0,     0,    52,    53,    54,     0,     0,
      65,    50,    54,    51,     0,     0,     0,     0,     0,    34,
       0,     0,     9,    11,    12,    13,    16,    14,    15,    17,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    24,     0,    32,
      56,    59,     0,    58,     0,     0,     0,    35,     0,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    33,     0,     0,     0,    25,     0,    55,
       0,     0,     0,     0,     0,    23,     0,    57,     0,     0,
       0,    20,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    26,     0,     0,
       0,    28,     0,     0,     0,     0,     0,    22,     0,     0,
       0,     0,    21,    27,     0,     0,    29,     0,     0,    30
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -48,   -48,   170,   -42,   -34,   -48,   -48,   -48,   -48,    64,
     -48,   -48,   -48,    17,   -48,   -48,   -20,   -48,   -48,    66,
     -48,   -12,   -47
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     5,     6,    36,    37,     7,     8,     9,    86,    87,
      38,    39,    40,    41,    42,    43,    44,    45,    92,    93,
      46,    52,    21
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      47,    88,    62,    14,     1,   115,     1,   118,    51,    53,
      11,    56,    54,    58,    59,    60,    12,    10,    16,    17,
      18,    19,    10,    13,    47,   116,     2,   119,     2,    89,
      55,    72,    73,    74,    48,    91,    85,    70,    71,    72,
      73,    74,    75,    76,     3,     4,     3,     4,    49,    63,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,    57,    64,   124,    88,    70,
      71,    72,    73,    74,    65,   121,    66,    67,   128,   133,
     130,    23,    24,    25,    26,    27,    28,    68,    29,    84,
     138,    95,    55,    98,    62,   114,    62,   146,    91,   148,
     117,   120,    50,   122,    62,   123,   131,   155,    47,   136,
      47,   126,    62,   140,    62,   132,    47,   139,    47,   165,
      47,    62,    35,   150,   141,   144,    47,    47,   147,    47,
     149,    62,   152,   151,    47,   158,    47,    47,    16,    17,
      18,    19,   159,    47,    16,    17,    18,    19,   157,    47,
     161,   163,    20,    47,    22,    23,    24,    25,    26,    27,
      28,   162,    29,   164,    22,    23,    24,    25,    26,    27,
      28,   166,    29,   168,   169,    15,    30,     0,     0,   125,
       0,     0,     0,   134,   127,    31,    30,   135,    32,     0,
       0,    33,    34,    61,     0,    31,    35,     0,    32,     0,
       0,    33,    34,     0,     0,     0,    35,    22,    23,    24,
      25,    26,    27,    28,     0,    29,     0,    22,    23,    24,
      25,    26,    27,    28,     0,    29,     0,     0,     0,    30,
       0,     0,     0,     0,     0,     0,   137,     0,    31,    30,
       0,    32,     0,     0,    33,    34,   145,     0,    31,    35,
       0,    32,     0,     0,    33,    34,     0,     0,     0,    35,
      22,    23,    24,    25,    26,    27,    28,     0,    29,     0,
      22,    23,    24,    25,    26,    27,    28,     0,    29,     0,
       0,     0,    30,     0,     0,     0,     0,     0,     0,   153,
       0,    31,    30,     0,    32,     0,     0,    33,    34,   154,
       0,    31,    35,     0,    32,     0,     0,    33,    34,     0,
       0,     0,    35,    22,    23,    24,    25,    26,    27,    28,
       0,    29,     0,    22,    23,    24,    25,    26,    27,    28,
       0,    29,     0,     0,     0,    30,     0,     0,     0,     0,
       0,     0,   160,     0,    31,    30,     0,    32,     0,     0,
      33,    34,   167,     0,    31,    35,     0,    32,     0,     0,
      33,    34,     0,     0,     0,    35,    22,    23,    24,    25,
      26,    27,    28,     0,    29,    23,    24,    25,    26,    27,
      28,     0,    29,     0,     0,     0,     0,     0,    30,     0,
       0,     0,     0,     0,     0,     0,    50,    31,     0,     0,
      32,     0,     0,    33,    34,     0,     0,     0,    35,     0,
       0,     0,     0,     0,     0,     0,    35,    90,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,     0,     0,     0,     0,
       0,     0,     0,     0,    97,     0,     0,   142,     0,     0,
       0,   143,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
     129,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    94,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    96,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,     0,     0,     0,     0,     0,    69,     0,     0,
       0,     0,     0,   156,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81
};

static const yytype_int16 yycheck[] =
{
      12,    48,    36,     0,     3,    26,     3,    26,    28,    29,
      27,    31,    27,    33,    34,    35,     3,     0,    28,    29,
      30,    31,     5,     8,    36,    46,    25,    46,    25,    49,
      45,    12,    13,    14,    45,    55,    46,    10,    11,    12,
      13,    14,    15,    16,    43,    44,    43,    44,    24,     3,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    25,     3,   114,   115,    10,
      11,    12,    13,    14,     3,    95,     3,     3,   120,   126,
     122,     4,     5,     6,     7,     8,     9,     3,    11,    24,
     132,    33,    45,    33,   128,    41,   130,   139,   118,   141,
      25,     3,    25,     3,   138,    43,     3,   149,   120,   129,
     122,    41,   146,    33,   148,     3,   128,     3,   130,   161,
     132,   155,    45,   143,     3,    33,   138,   139,    34,   141,
       3,   165,    33,    40,   146,    33,   148,   149,    28,    29,
      30,    31,    33,   155,    28,    29,    30,    31,    42,   161,
       3,    34,    42,   165,     3,     4,     5,     6,     7,     8,
       9,    42,    11,    33,     3,     4,     5,     6,     7,     8,
       9,    37,    11,    33,    37,     5,    25,    -1,    -1,   115,
      -1,    -1,    -1,    32,   118,    34,    25,    36,    37,    -1,
      -1,    40,    41,    32,    -1,    34,    45,    -1,    37,    -1,
      -1,    40,    41,    -1,    -1,    -1,    45,     3,     4,     5,
       6,     7,     8,     9,    -1,    11,    -1,     3,     4,     5,
       6,     7,     8,     9,    -1,    11,    -1,    -1,    -1,    25,
      -1,    -1,    -1,    -1,    -1,    -1,    32,    -1,    34,    25,
      -1,    37,    -1,    -1,    40,    41,    32,    -1,    34,    45,
      -1,    37,    -1,    -1,    40,    41,    -1,    -1,    -1,    45,
       3,     4,     5,     6,     7,     8,     9,    -1,    11,    -1,
       3,     4,     5,     6,     7,     8,     9,    -1,    11,    -1,
      -1,    -1,    25,    -1,    -1,    -1,    -1,    -1,    -1,    32,
      -1,    34,    25,    -1,    37,    -1,    -1,    40,    41,    32,
      -1,    34,    45,    -1,    37,    -1,    -1,    40,    41,    -1,
      -1,    -1,    45,     3,     4,     5,     6,     7,     8,     9,
      -1,    11,    -1,     3,     4,     5,     6,     7,     8,     9,
      -1,    11,    -1,    -1,    -1,    25,    -1,    -1,    -1,    -1,
      -1,    -1,    32,    -1,    34,    25,    -1,    37,    -1,    -1,
      40,    41,    32,    -1,    34,    45,    -1,    37,    -1,    -1,
      40,    41,    -1,    -1,    -1,    45,     3,     4,     5,     6,
       7,     8,     9,    -1,    11,     4,     5,     6,     7,     8,
       9,    -1,    11,    -1,    -1,    -1,    -1,    -1,    25,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    25,    34,    -1,    -1,
      37,    -1,    -1,    40,    41,    -1,    -1,    -1,    45,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    45,    46,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    46,    -1,    -1,    35,    -1,    -1,
      -1,    39,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      38,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    35,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    35,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    -1,    -1,    -1,    -1,    -1,     3,    -1,    -1,
      -1,    -1,    -1,    35,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    25,    43,    44,    48,    49,    52,    53,    54,
      60,    27,     3,     8,     0,    49,    28,    29,    30,    31,
      42,    69,     3,     4,     5,     6,     7,     8,     9,    11,
      25,    34,    37,    40,    41,    45,    50,    51,    57,    58,
      59,    60,    61,    62,    63,    64,    67,    68,    45,    24,
      25,    63,    68,    63,    27,    45,    63,    25,    63,    63,
      63,    32,    51,     3,     3,     3,     3,     3,     3,     3,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    46,    55,    56,    69,    63,
      46,    63,    65,    66,    35,    33,    35,    46,    33,    63,
      63,    63,    63,    63,    63,    63,    63,    63,    63,    63,
      63,    63,    63,    63,    41,    26,    46,    25,    26,    46,
       3,    63,     3,    43,    69,    56,    41,    66,    50,    38,
      50,     3,     3,    69,    32,    36,    63,    32,    50,     3,
      33,     3,    35,    39,    33,    32,    50,    34,    50,     3,
      63,    40,    33,    32,    32,    50,    35,    42,    33,    33,
      32,     3,    42,    34,    33,    50,    37,    32,    33,    37
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    47,    48,    48,    49,    49,    49,    49,    49,    50,
      50,    51,    51,    51,    51,    51,    51,    51,    51,    52,
      53,    54,    54,    55,    55,    56,    57,    57,    58,    59,
      59,    60,    60,    61,    62,    63,    63,    63,    63,    63,
      63,    63,    63,    63,    63,    63,    63,    63,    63,    63,
      63,    63,    63,    63,    63,    64,    64,    65,    65,    66,
      67,    67,    67,    67,    67,    68,    69,    69,    69,    69
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     1,     1,     1,     1,     1,     1,     2,
       1,     2,     2,     2,     2,     2,     2,     2,     1,     2,
       7,    13,    12,     3,     1,     2,     8,    11,     8,    12,
      14,     3,     5,     3,     2,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       2,     2,     1,     1,     1,     4,     3,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1
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


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


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


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static unsigned
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  unsigned res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (yylocationp);
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
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
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
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
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
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
       'yyls': related to locations.

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

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
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
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yyls1, yysize * sizeof (*yylsp),
                    &yystacksize);

        yyls = yyls1;
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
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

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
  *++yylsp = yylloc;
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

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 105 "lex/portugol.y" /* yacc.c:1646  */
    { if ((yyvsp[0].ast) != NULL)
                           {
                               if (!ast_lex)
                                   ast_lex = ast_file(ast_filepath);
                               ast_push_instr(ast_lex, (yyvsp[0].ast));
                           } }
#line 1580 "lex/parser.c" /* yacc.c:1646  */
    break;

  case 3:
#line 111 "lex/portugol.y" /* yacc.c:1646  */
    { if ((yyvsp[0].ast) != NULL)
                           {
                               if (!ast_lex)
                                   ast_lex = ast_file(ast_filepath);
                               ast_push_instr(ast_lex, (yyvsp[0].ast));
                           } }
#line 1591 "lex/parser.c" /* yacc.c:1646  */
    break;

  case 4:
#line 119 "lex/portugol.y" /* yacc.c:1646  */
    { (yyval.ast) = (yyvsp[0].ast); }
#line 1597 "lex/parser.c" /* yacc.c:1646  */
    break;

  case 5:
#line 120 "lex/portugol.y" /* yacc.c:1646  */
    { (yyval.ast) = (yyvsp[0].ast); }
#line 1603 "lex/parser.c" /* yacc.c:1646  */
    break;

  case 6:
#line 121 "lex/portugol.y" /* yacc.c:1646  */
    { (yyval.ast) = (yyvsp[0].ast); }
#line 1609 "lex/parser.c" /* yacc.c:1646  */
    break;

  case 7:
#line 122 "lex/portugol.y" /* yacc.c:1646  */
    { (yyval.ast) = (yyvsp[0].ast); }
#line 1615 "lex/parser.c" /* yacc.c:1646  */
    break;

  case 8:
#line 123 "lex/portugol.y" /* yacc.c:1646  */
    { (yyval.ast) = NULL; }
#line 1621 "lex/parser.c" /* yacc.c:1646  */
    break;

  case 9:
#line 126 "lex/portugol.y" /* yacc.c:1646  */
    { if ((yyvsp[0].ast) != NULL)
                            ast_push_instr((yyvsp[-1].ast), (yyvsp[0].ast));
                        (yyval.ast) = (yyvsp[-1].ast); }
#line 1629 "lex/parser.c" /* yacc.c:1646  */
    break;

  case 10:
#line 129 "lex/portugol.y" /* yacc.c:1646  */
    { AST_Node* scope = ast_scope();
                        if ((yyvsp[0].ast) != NULL)
                            ast_push_instr(scope, (yyvsp[0].ast));
                        (yyval.ast) = scope; }
#line 1638 "lex/parser.c" /* yacc.c:1646  */
    break;

  case 11:
#line 135 "lex/portugol.y" /* yacc.c:1646  */
    { (yyval.ast) = (yyvsp[-1].ast); }
#line 1644 "lex/parser.c" /* yacc.c:1646  */
    break;

  case 12:
#line 136 "lex/portugol.y" /* yacc.c:1646  */
    { (yyval.ast) = (yyvsp[-1].ast); }
#line 1650 "lex/parser.c" /* yacc.c:1646  */
    break;

  case 13:
#line 137 "lex/portugol.y" /* yacc.c:1646  */
    { (yyval.ast) = (yyvsp[-1].ast); }
#line 1656 "lex/parser.c" /* yacc.c:1646  */
    break;

  case 14:
#line 138 "lex/portugol.y" /* yacc.c:1646  */
    { (yyval.ast) = (yyvsp[-1].ast); }
#line 1662 "lex/parser.c" /* yacc.c:1646  */
    break;

  case 15:
#line 139 "lex/portugol.y" /* yacc.c:1646  */
    { (yyval.ast) = (yyvsp[-1].ast); }
#line 1668 "lex/parser.c" /* yacc.c:1646  */
    break;

  case 16:
#line 140 "lex/portugol.y" /* yacc.c:1646  */
    { (yyval.ast) = (yyvsp[-1].ast); }
#line 1674 "lex/parser.c" /* yacc.c:1646  */
    break;

  case 17:
#line 141 "lex/portugol.y" /* yacc.c:1646  */
    { (yyval.ast) = (yyvsp[-1].ast); }
#line 1680 "lex/parser.c" /* yacc.c:1646  */
    break;

  case 18:
#line 142 "lex/portugol.y" /* yacc.c:1646  */
    { (yyval.ast) = NULL; }
#line 1686 "lex/parser.c" /* yacc.c:1646  */
    break;

  case 19:
#line 145 "lex/portugol.y" /* yacc.c:1646  */
    { AST_Pos pos;
                                   pos.line.start   = (yyvsp[-1].token).pos.line.start;
                                   pos.column.start = (yyvsp[-1].token).pos.column.start;
                                   pos.line.stop    = (yyvsp[0].token).pos.line.stop;
                                   pos.column.stop  = (yyvsp[0].token).pos.column.stop;
                                   (yyval.ast) = ast_import(pos, (yyvsp[0].token).text);
                                   free((yyvsp[0].token).text); }
#line 1698 "lex/parser.c" /* yacc.c:1646  */
    break;

  case 20:
#line 156 "lex/portugol.y" /* yacc.c:1646  */
    { AST_Pos pos;
                                               pos.line.start   = (yyvsp[-6].token).pos.line.start;
                                               pos.column.start = (yyvsp[-6].token).pos.column.start;
                                               pos.line.stop    = (yyvsp[-1].token).pos.line.stop;
                                               pos.column.stop  = (yyvsp[-1].token).pos.column.stop;
                                               (yyval.ast) = ast_function(pos, "programa", ast_param_list(), VINT32, (yyvsp[-4].ast)); }
#line 1709 "lex/parser.c" /* yacc.c:1646  */
    break;

  case 21:
#line 166 "lex/portugol.y" /* yacc.c:1646  */
    { AST_Pos pos;
                                         pos.line.start   = (yyvsp[-12].token).pos.line.start;
                                         pos.column.start = (yyvsp[-12].token).pos.column.start;
                                         pos.line.stop    = (yyvsp[0].token).pos.line.stop;
                                         pos.column.stop  = (yyvsp[0].token).pos.column.stop;
                                         (yyval.ast) = ast_function(pos, (yyvsp[-12].token).text, (yyvsp[-8].fparams), (yyvsp[-5].vtype).type, (yyvsp[-3].ast));
                                         free((yyvsp[-12].token).text); }
#line 1721 "lex/parser.c" /* yacc.c:1646  */
    break;

  case 22:
#line 175 "lex/portugol.y" /* yacc.c:1646  */
    { AST_Pos pos;
                                         pos.line.start   = (yyvsp[-11].token).pos.line.start;
                                         pos.column.start = (yyvsp[-11].token).pos.column.start;
                                         pos.line.stop    = (yyvsp[0].token).pos.line.stop;
                                         pos.column.stop  = (yyvsp[0].token).pos.column.stop;
                                         (yyval.ast) = ast_function(pos, (yyvsp[-11].token).text, ast_param_list(), (yyvsp[-5].vtype).type, (yyvsp[-3].ast));
                                         free((yyvsp[-11].token).text); }
#line 1733 "lex/parser.c" /* yacc.c:1646  */
    break;

  case 23:
#line 184 "lex/portugol.y" /* yacc.c:1646  */
    { ast_param_list_add((yyvsp[-2].fparams), (yyvsp[0].fparam).pos, (yyvsp[0].fparam).type, (yyvsp[0].fparam).name);
                                     free((yyvsp[0].fparam).name);
                                     (yyval.fparams) = (yyvsp[-2].fparams); }
#line 1741 "lex/parser.c" /* yacc.c:1646  */
    break;

  case 24:
#line 187 "lex/portugol.y" /* yacc.c:1646  */
    { AST_ParamList* list = ast_param_list();
                                     ast_param_list_add(list, (yyvsp[0].fparam).pos, (yyvsp[0].fparam).type, (yyvsp[0].fparam).name);
                                     free((yyvsp[0].fparam).name);
                                     (yyval.fparams) = list; }
#line 1750 "lex/parser.c" /* yacc.c:1646  */
    break;

  case 25:
#line 193 "lex/portugol.y" /* yacc.c:1646  */
    { AST_Pos pos;
                                  pos.line.start   = (yyvsp[-1].vtype).pos.line.start;
                                  pos.column.start = (yyvsp[-1].vtype).pos.column.start;
                                  pos.line.stop    = (yyvsp[0].token).pos.line.stop;
                                  pos.column.stop  = (yyvsp[0].token).pos.column.stop;

                                  (yyval.fparam).pos = pos;
                                  (yyval.fparam).type = (yyvsp[-1].vtype).type;
                                  (yyval.fparam).name = (yyvsp[0].token).text; }
#line 1764 "lex/parser.c" /* yacc.c:1646  */
    break;

  case 26:
#line 206 "lex/portugol.y" /* yacc.c:1646  */
    { AST_Pos pos;
                             pos.line.start   = (yyvsp[-7].token).pos.line.start;
                             pos.column.start = (yyvsp[-7].token).pos.column.start;
                             pos.line.stop    = (yyvsp[0].token).pos.line.stop;
                             pos.column.stop  = (yyvsp[0].token).pos.column.stop;
                             (yyval.ast) = ast_if(pos, (yyvsp[-6].ast), (yyvsp[-3].ast), NULL); }
#line 1775 "lex/parser.c" /* yacc.c:1646  */
    break;

  case 27:
#line 216 "lex/portugol.y" /* yacc.c:1646  */
    { AST_Pos pos;
                             pos.line.start   = (yyvsp[-10].token).pos.line.start;
                             pos.column.start = (yyvsp[-10].token).pos.column.start;
                             pos.line.stop    = (yyvsp[0].token).pos.line.stop;
                             pos.column.stop  = (yyvsp[0].token).pos.column.stop;
                             (yyval.ast) = ast_if(pos, (yyvsp[-9].ast), (yyvsp[-6].ast), (yyvsp[-3].ast)); }
#line 1786 "lex/parser.c" /* yacc.c:1646  */
    break;

  case 28:
#line 226 "lex/portugol.y" /* yacc.c:1646  */
    { AST_Pos pos;
                                   pos.line.start   = (yyvsp[-7].token).pos.line.start;
                                   pos.column.start = (yyvsp[-7].token).pos.column.start;
                                   pos.line.stop    = (yyvsp[0].token).pos.line.stop;
                                   pos.column.stop  = (yyvsp[0].token).pos.column.stop;
                                   (yyval.ast) = ast_while(pos, (yyvsp[-6].ast), (yyvsp[-3].ast)); }
#line 1797 "lex/parser.c" /* yacc.c:1646  */
    break;

  case 29:
#line 236 "lex/portugol.y" /* yacc.c:1646  */
    { AST_Pos pos;
                               pos.line.start   = (yyvsp[-11].token).pos.line.start;
                               pos.column.start = (yyvsp[-11].token).pos.column.start;
                               pos.line.stop    = (yyvsp[0].token).pos.line.stop;
                               pos.column.stop  = (yyvsp[0].token).pos.column.stop;
                               (yyval.ast) = ast_for(pos, (yyvsp[-10].token).text, (yyvsp[-8].ast), (yyvsp[-6].ast), NULL, (yyvsp[-3].ast));
                               free((yyvsp[-10].token).text); }
#line 1809 "lex/parser.c" /* yacc.c:1646  */
    break;

  case 30:
#line 245 "lex/portugol.y" /* yacc.c:1646  */
    { AST_Pos pos;
                               pos.line.start   = (yyvsp[-13].token).pos.line.start;
                               pos.column.start = (yyvsp[-13].token).pos.column.start;
                               pos.line.stop    = (yyvsp[0].token).pos.line.stop;
                               pos.column.stop  = (yyvsp[0].token).pos.column.stop;
                               (yyval.ast) = ast_for(pos, (yyvsp[-12].token).text, (yyvsp[-10].ast), (yyvsp[-8].ast), (yyvsp[-6].ast), (yyvsp[-3].ast));
                               free((yyvsp[-12].token).text); }
#line 1821 "lex/parser.c" /* yacc.c:1646  */
    break;

  case 31:
#line 254 "lex/portugol.y" /* yacc.c:1646  */
    { AST_Pos pos;
                                                             pos.line.start   = (yyvsp[-2].token).pos.line.start;
                                                             pos.column.start = (yyvsp[-2].token).pos.column.start;
                                                             pos.line.stop    = (yyvsp[0].vtype).pos.line.stop;
                                                             pos.column.stop  = (yyvsp[0].vtype).pos.column.stop;

                                                             AST_Pos aux = {{0, 0}, {0, 0}};

                                                             switch ((yyvsp[0].vtype).type)
                                                             {
                                                                 case VBOOLEAN: (yyval.ast) = ast_decl_boolean(pos, (yyvsp[-2].token).text, ast_boolean(aux, 0));    break;
                                                                 case VINT32:   (yyval.ast) = ast_decl_int32(pos, (yyvsp[-2].token).text, ast_int32(aux, 0));        break;
                                                                 case VFLOAT32: (yyval.ast) = ast_decl_float32(pos, (yyvsp[-2].token).text, ast_float32(aux, 0.0f)); break;
                                                                 case VTEXT:    (yyval.ast) = ast_decl_text(pos, (yyvsp[-2].token).text, ast_text(aux, ""));         break;
                                                                 default:                                                                    break;
                                                             }

                                                             free((yyvsp[-2].token).text); }
#line 1844 "lex/parser.c" /* yacc.c:1646  */
    break;

  case 32:
#line 272 "lex/portugol.y" /* yacc.c:1646  */
    { AST_Pos pos;
                                                             pos.line.start   = (yyvsp[-4].token).pos.line.start;
                                                             pos.column.start = (yyvsp[-4].token).pos.column.start;
                                                             pos.line.stop    = ast_get_position((yyvsp[0].ast)).line.stop;
                                                             pos.column.stop  = ast_get_position((yyvsp[0].ast)).column.stop;

                                                             switch ((yyvsp[-2].vtype).type)
                                                             {
                                                                 case VBOOLEAN: (yyval.ast) = ast_decl_boolean(pos, (yyvsp[-4].token).text, (yyvsp[0].ast)); break;
                                                                 case VINT32:   (yyval.ast) = ast_decl_int32(pos, (yyvsp[-4].token).text, (yyvsp[0].ast));   break;
                                                                 case VFLOAT32: (yyval.ast) = ast_decl_float32(pos, (yyvsp[-4].token).text, (yyvsp[0].ast)); break;
                                                                 case VTEXT:    (yyval.ast) = ast_decl_text(pos, (yyvsp[-4].token).text, (yyvsp[0].ast));    break;
                                                                 default:                                                break;
                                                             }
                                                             free((yyvsp[-4].token).text); }
#line 1864 "lex/parser.c" /* yacc.c:1646  */
    break;

  case 33:
#line 289 "lex/portugol.y" /* yacc.c:1646  */
    { AST_Pos pos;
                                       pos.line.start   = ast_get_position((yyvsp[-2].ast)).line.start;
                                       pos.column.start = ast_get_position((yyvsp[-2].ast)).column.start;
                                       pos.line.stop    = ast_get_position((yyvsp[0].ast)).line.stop;
                                       pos.column.stop  = ast_get_position((yyvsp[0].ast)).column.stop;
                                       (yyval.ast) = ast_op_assign(pos, (yyvsp[-2].ast), (yyvsp[0].ast)); }
#line 1875 "lex/parser.c" /* yacc.c:1646  */
    break;

  case 34:
#line 297 "lex/portugol.y" /* yacc.c:1646  */
    { AST_Pos pos;
                           pos.line.start   = (yyvsp[-1].token).pos.line.start;
                           pos.column.start = (yyvsp[-1].token).pos.column.start;
                           pos.line.stop    = ast_get_position((yyvsp[0].ast)).line.stop;
                           pos.column.stop  = ast_get_position((yyvsp[0].ast)).column.stop;
                           (yyval.ast) = ast_return(pos, (yyvsp[0].ast)); }
#line 1886 "lex/parser.c" /* yacc.c:1646  */
    break;

  case 35:
#line 305 "lex/portugol.y" /* yacc.c:1646  */
    { (yyval.ast) = (yyvsp[-1].ast); }
#line 1892 "lex/parser.c" /* yacc.c:1646  */
    break;

  case 36:
#line 306 "lex/portugol.y" /* yacc.c:1646  */
    { AST_Pos pos;
                                             pos.line.start   = ast_get_position((yyvsp[-2].ast)).line.start;
                                             pos.column.start = ast_get_position((yyvsp[-2].ast)).column.start;
                                             pos.line.stop    = ast_get_position((yyvsp[0].ast)).line.stop;
                                             pos.column.stop  = ast_get_position((yyvsp[0].ast)).column.stop;
                                             (yyval.ast) = ast_op_add(pos, (yyvsp[-2].ast), (yyvsp[0].ast)); }
#line 1903 "lex/parser.c" /* yacc.c:1646  */
    break;

  case 37:
#line 312 "lex/portugol.y" /* yacc.c:1646  */
    { AST_Pos pos;
                                             pos.line.start   = ast_get_position((yyvsp[-2].ast)).line.start;
                                             pos.column.start = ast_get_position((yyvsp[-2].ast)).column.start;
                                             pos.line.stop    = ast_get_position((yyvsp[0].ast)).line.stop;
                                             pos.column.stop  = ast_get_position((yyvsp[0].ast)).column.stop;
                                             (yyval.ast) = ast_op_subtract(pos, (yyvsp[-2].ast), (yyvsp[0].ast)); }
#line 1914 "lex/parser.c" /* yacc.c:1646  */
    break;

  case 38:
#line 318 "lex/portugol.y" /* yacc.c:1646  */
    { AST_Pos pos;
                                             pos.line.start   = ast_get_position((yyvsp[-2].ast)).line.start;
                                             pos.column.start = ast_get_position((yyvsp[-2].ast)).column.start;
                                             pos.line.stop    = ast_get_position((yyvsp[0].ast)).line.stop;
                                             pos.column.stop  = ast_get_position((yyvsp[0].ast)).column.stop;
                                             (yyval.ast) = ast_op_multiply(pos, (yyvsp[-2].ast), (yyvsp[0].ast)); }
#line 1925 "lex/parser.c" /* yacc.c:1646  */
    break;

  case 39:
#line 324 "lex/portugol.y" /* yacc.c:1646  */
    { AST_Pos pos;
                                             pos.line.start   = ast_get_position((yyvsp[-2].ast)).line.start;
                                             pos.column.start = ast_get_position((yyvsp[-2].ast)).column.start;
                                             pos.line.stop    = ast_get_position((yyvsp[0].ast)).line.stop;
                                             pos.column.stop  = ast_get_position((yyvsp[0].ast)).column.stop;
                                             (yyval.ast) = ast_op_divide(pos, (yyvsp[-2].ast), (yyvsp[0].ast)); }
#line 1936 "lex/parser.c" /* yacc.c:1646  */
    break;

  case 40:
#line 330 "lex/portugol.y" /* yacc.c:1646  */
    { AST_Pos pos;
                                             pos.line.start   = ast_get_position((yyvsp[-2].ast)).line.start;
                                             pos.column.start = ast_get_position((yyvsp[-2].ast)).column.start;
                                             pos.line.stop    = ast_get_position((yyvsp[0].ast)).line.stop;
                                             pos.column.stop  = ast_get_position((yyvsp[0].ast)).column.stop;
                                             (yyval.ast) = ast_op_remainder(pos, (yyvsp[-2].ast), (yyvsp[0].ast)); }
#line 1947 "lex/parser.c" /* yacc.c:1646  */
    break;

  case 41:
#line 336 "lex/portugol.y" /* yacc.c:1646  */
    { AST_Pos pos;
                                             pos.line.start   = ast_get_position((yyvsp[-2].ast)).line.start;
                                             pos.column.start = ast_get_position((yyvsp[-2].ast)).column.start;
                                             pos.line.stop    = ast_get_position((yyvsp[0].ast)).line.stop;
                                             pos.column.stop  = ast_get_position((yyvsp[0].ast)).column.stop;
                                             (yyval.ast) = ast_op_equal(pos, (yyvsp[-2].ast), (yyvsp[0].ast)); }
#line 1958 "lex/parser.c" /* yacc.c:1646  */
    break;

  case 42:
#line 342 "lex/portugol.y" /* yacc.c:1646  */
    { AST_Pos pos;
                                             pos.line.start   = ast_get_position((yyvsp[-2].ast)).line.start;
                                             pos.column.start = ast_get_position((yyvsp[-2].ast)).column.start;
                                             pos.line.stop    = ast_get_position((yyvsp[0].ast)).line.stop;
                                             pos.column.stop  = ast_get_position((yyvsp[0].ast)).column.stop;
                                             (yyval.ast) = ast_op_inequal(pos, (yyvsp[-2].ast), (yyvsp[0].ast)); }
#line 1969 "lex/parser.c" /* yacc.c:1646  */
    break;

  case 43:
#line 348 "lex/portugol.y" /* yacc.c:1646  */
    { AST_Pos pos;
                                             pos.line.start   = ast_get_position((yyvsp[-2].ast)).line.start;
                                             pos.column.start = ast_get_position((yyvsp[-2].ast)).column.start;
                                             pos.line.stop    = ast_get_position((yyvsp[0].ast)).line.stop;
                                             pos.column.stop  = ast_get_position((yyvsp[0].ast)).column.stop;
                                             (yyval.ast) = ast_op_greater(pos, (yyvsp[-2].ast), (yyvsp[0].ast)); }
#line 1980 "lex/parser.c" /* yacc.c:1646  */
    break;

  case 44:
#line 354 "lex/portugol.y" /* yacc.c:1646  */
    { AST_Pos pos;
                                             pos.line.start   = ast_get_position((yyvsp[-2].ast)).line.start;
                                             pos.column.start = ast_get_position((yyvsp[-2].ast)).column.start;
                                             pos.line.stop    = ast_get_position((yyvsp[0].ast)).line.stop;
                                             pos.column.stop  = ast_get_position((yyvsp[0].ast)).column.stop;
                                             (yyval.ast) = ast_op_greater_or_equal(pos, (yyvsp[-2].ast), (yyvsp[0].ast)); }
#line 1991 "lex/parser.c" /* yacc.c:1646  */
    break;

  case 45:
#line 360 "lex/portugol.y" /* yacc.c:1646  */
    { AST_Pos pos;
                                             pos.line.start   = ast_get_position((yyvsp[-2].ast)).line.start;
                                             pos.column.start = ast_get_position((yyvsp[-2].ast)).column.start;
                                             pos.line.stop    = ast_get_position((yyvsp[0].ast)).line.stop;
                                             pos.column.stop  = ast_get_position((yyvsp[0].ast)).column.stop;
                                             (yyval.ast) = ast_op_lesser(pos, (yyvsp[-2].ast), (yyvsp[0].ast)); }
#line 2002 "lex/parser.c" /* yacc.c:1646  */
    break;

  case 46:
#line 366 "lex/portugol.y" /* yacc.c:1646  */
    { AST_Pos pos;
                                             pos.line.start   = ast_get_position((yyvsp[-2].ast)).line.start;
                                             pos.column.start = ast_get_position((yyvsp[-2].ast)).column.start;
                                             pos.line.stop    = ast_get_position((yyvsp[0].ast)).line.stop;
                                             pos.column.stop  = ast_get_position((yyvsp[0].ast)).column.stop;
                                             (yyval.ast) = ast_op_lesser_or_equal(pos, (yyvsp[-2].ast), (yyvsp[0].ast)); }
#line 2013 "lex/parser.c" /* yacc.c:1646  */
    break;

  case 47:
#line 372 "lex/portugol.y" /* yacc.c:1646  */
    { AST_Pos pos;
                                             pos.line.start   = ast_get_position((yyvsp[-2].ast)).line.start;
                                             pos.column.start = ast_get_position((yyvsp[-2].ast)).column.start;
                                             pos.line.stop    = ast_get_position((yyvsp[0].ast)).line.stop;
                                             pos.column.stop  = ast_get_position((yyvsp[0].ast)).column.stop;
                                             (yyval.ast) = ast_op_and(pos, (yyvsp[-2].ast), (yyvsp[0].ast)); }
#line 2024 "lex/parser.c" /* yacc.c:1646  */
    break;

  case 48:
#line 378 "lex/portugol.y" /* yacc.c:1646  */
    { AST_Pos pos;
                                             pos.line.start   = ast_get_position((yyvsp[-2].ast)).line.start;
                                             pos.column.start = ast_get_position((yyvsp[-2].ast)).column.start;
                                             pos.line.stop    = ast_get_position((yyvsp[0].ast)).line.stop;
                                             pos.column.stop  = ast_get_position((yyvsp[0].ast)).column.stop;
                                             (yyval.ast) = ast_op_or(pos, (yyvsp[-2].ast), (yyvsp[0].ast)); }
#line 2035 "lex/parser.c" /* yacc.c:1646  */
    break;

  case 49:
#line 384 "lex/portugol.y" /* yacc.c:1646  */
    { AST_Pos pos;
                                             pos.line.start   = ast_get_position((yyvsp[-2].ast)).line.start;
                                             pos.column.start = ast_get_position((yyvsp[-2].ast)).column.start;
                                             pos.line.stop    = ast_get_position((yyvsp[0].ast)).line.stop;
                                             pos.column.stop  = ast_get_position((yyvsp[0].ast)).column.stop;
                                             (yyval.ast) = ast_op_xor(pos, (yyvsp[-2].ast), (yyvsp[0].ast)); }
#line 2046 "lex/parser.c" /* yacc.c:1646  */
    break;

  case 50:
#line 390 "lex/portugol.y" /* yacc.c:1646  */
    { AST_Pos pos;
                                             pos.line.start   = (yyvsp[-1].token).pos.line.start;
                                             pos.column.start = (yyvsp[-1].token).pos.column.start;
                                             pos.line.stop    = ast_get_position((yyvsp[0].ast)).line.stop;
                                             pos.column.stop  = ast_get_position((yyvsp[0].ast)).column.stop;
                                             (yyval.ast) = ast_op_negate(pos, (yyvsp[0].ast)); }
#line 2057 "lex/parser.c" /* yacc.c:1646  */
    break;

  case 51:
#line 396 "lex/portugol.y" /* yacc.c:1646  */
    { AST_Pos pos;
                                             pos.line.start   = (yyvsp[-1].token).pos.line.start;
                                             pos.line.stop    = ast_get_position((yyvsp[0].ast)).line.stop;
                                             pos.column.start = (yyvsp[-1].token).pos.column.start;
                                             pos.column.stop  = ast_get_position((yyvsp[0].ast)).column.stop;
                                             (yyval.ast) = ast_op_negative(pos, (yyvsp[0].ast)); }
#line 2068 "lex/parser.c" /* yacc.c:1646  */
    break;

  case 52:
#line 402 "lex/portugol.y" /* yacc.c:1646  */
    { (yyval.ast) = (yyvsp[0].ast); }
#line 2074 "lex/parser.c" /* yacc.c:1646  */
    break;

  case 53:
#line 403 "lex/portugol.y" /* yacc.c:1646  */
    { (yyval.ast) = (yyvsp[0].ast); }
#line 2080 "lex/parser.c" /* yacc.c:1646  */
    break;

  case 54:
#line 404 "lex/portugol.y" /* yacc.c:1646  */
    { (yyval.ast) = (yyvsp[0].ast); }
#line 2086 "lex/parser.c" /* yacc.c:1646  */
    break;

  case 55:
#line 407 "lex/portugol.y" /* yacc.c:1646  */
    { AST_Pos pos;
                                                              pos.line.start   = (yyvsp[-3].token).pos.line.start;
                                                              pos.line.stop    = (yyvsp[-3].token).pos.line.stop;
                                                              pos.column.start = (yyvsp[0].token).pos.column.start;
                                                              pos.column.stop  = (yyvsp[0].token).pos.column.stop;
                                                              (yyval.ast) = ast_function_call(pos, (yyvsp[-3].token).text, (yyvsp[-1].fargs));
                                                              free((yyvsp[-3].token).text); }
#line 2098 "lex/parser.c" /* yacc.c:1646  */
    break;

  case 56:
#line 414 "lex/portugol.y" /* yacc.c:1646  */
    { AST_Pos pos;
                                                              pos.line.start   = (yyvsp[-2].token).pos.line.start;
                                                              pos.line.stop    = (yyvsp[-2].token).pos.line.stop;
                                                              pos.column.start = (yyvsp[0].token).pos.column.start;
                                                              pos.column.stop  = (yyvsp[0].token).pos.column.stop;
                                                              (yyval.ast) = ast_function_call(pos, (yyvsp[-2].token).text, ast_arg_list());
                                                              free((yyvsp[-2].token).text); }
#line 2110 "lex/parser.c" /* yacc.c:1646  */
    break;

  case 57:
#line 423 "lex/portugol.y" /* yacc.c:1646  */
    { ast_arg_list_add((yyvsp[-2].fargs), (yyvsp[0].ast));
                               (yyval.fargs) = (yyvsp[-2].fargs); }
#line 2117 "lex/parser.c" /* yacc.c:1646  */
    break;

  case 58:
#line 425 "lex/portugol.y" /* yacc.c:1646  */
    { AST_ArgList* list = ast_arg_list();
                               ast_arg_list_add(list, (yyvsp[0].ast));
                               (yyval.fargs) = list; }
#line 2125 "lex/parser.c" /* yacc.c:1646  */
    break;

  case 59:
#line 430 "lex/portugol.y" /* yacc.c:1646  */
    { (yyval.ast) = (yyvsp[0].ast); }
#line 2131 "lex/parser.c" /* yacc.c:1646  */
    break;

  case 60:
#line 433 "lex/portugol.y" /* yacc.c:1646  */
    { (yyval.ast) = ast_boolean((yyvsp[0].token).pos, 1); }
#line 2137 "lex/parser.c" /* yacc.c:1646  */
    break;

  case 61:
#line 434 "lex/portugol.y" /* yacc.c:1646  */
    { (yyval.ast) = ast_boolean((yyvsp[0].token).pos, 0); }
#line 2143 "lex/parser.c" /* yacc.c:1646  */
    break;

  case 62:
#line 435 "lex/portugol.y" /* yacc.c:1646  */
    { int value;
#ifdef _MSC_VER
                              sscanf_s((yyvsp[0].token).text, "%d", &value);
#else
                              sscanf((yyvsp[0].token).text, "%d", &value);
#endif /* _MSC_VER */
                              (yyval.ast) = ast_int32((yyvsp[0].token).pos, value);
                              free((yyvsp[0].token).text); }
#line 2156 "lex/parser.c" /* yacc.c:1646  */
    break;

  case 63:
#line 443 "lex/portugol.y" /* yacc.c:1646  */
    { float value;
#ifdef _MSC_VER
                              sscanf_s((yyvsp[0].token).text, "%f", &value);
#else
                              sscanf((yyvsp[0].token).text, "%f", &value);
#endif /* _MSC_VER */
                              (yyval.ast) = ast_float32((yyvsp[0].token).pos, value);
                              free((yyvsp[0].token).text); }
#line 2169 "lex/parser.c" /* yacc.c:1646  */
    break;

  case 64:
#line 451 "lex/portugol.y" /* yacc.c:1646  */
    { (yyval.ast) = ast_text((yyvsp[0].token).pos, (yyvsp[0].token).text);
                              free((yyvsp[0].token).text); }
#line 2176 "lex/parser.c" /* yacc.c:1646  */
    break;

  case 65:
#line 455 "lex/portugol.y" /* yacc.c:1646  */
    { (yyval.ast) = ast_variable((yyvsp[0].token).pos, (yyvsp[0].token).text);
                            free((yyvsp[0].token).text); }
#line 2183 "lex/parser.c" /* yacc.c:1646  */
    break;

  case 66:
#line 459 "lex/portugol.y" /* yacc.c:1646  */
    { (yyval.vtype).pos = (yyvsp[0].token).pos;
                        (yyval.vtype).type = VBOOLEAN; }
#line 2190 "lex/parser.c" /* yacc.c:1646  */
    break;

  case 67:
#line 461 "lex/portugol.y" /* yacc.c:1646  */
    { (yyval.vtype).pos = (yyvsp[0].token).pos;
                        (yyval.vtype).type = VINT32; }
#line 2197 "lex/parser.c" /* yacc.c:1646  */
    break;

  case 68:
#line 463 "lex/portugol.y" /* yacc.c:1646  */
    { (yyval.vtype).pos = (yyvsp[0].token).pos;
                        (yyval.vtype).type = VFLOAT32; }
#line 2204 "lex/parser.c" /* yacc.c:1646  */
    break;

  case 69:
#line 465 "lex/portugol.y" /* yacc.c:1646  */
    { (yyval.vtype).pos = (yyvsp[0].token).pos;
                        (yyval.vtype).type = VTEXT; }
#line 2211 "lex/parser.c" /* yacc.c:1646  */
    break;


#line 2215 "lex/parser.c" /* yacc.c:1646  */
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
  *++yylsp = yyloc;

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

  yyerror_range[1] = yylloc;

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
                      yytoken, &yylval, &yylloc);
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

  yyerror_range[1] = yylsp[1-yylen];
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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

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
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp, yylsp);
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
#line 469 "lex/portugol.y" /* yacc.c:1906  */

