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
#line 1 "ToyParser.y" /* yacc.c:339  */

#include <cstdio>
#include <cstdlib>
#include <string>
#include <iostream>
extern int yylex();
extern char *yytext;
void yyerror(const char *s) {
	printf("Error: %s\n", s);
	printf("Error text: %s\n", yytext);
	exit(1);
}
using namespace std;
#define DEBUG

void debugInfo(const char* s){
	#ifdef DEBUG
		cout << "debug: " << s << endl;
	#endif
}

void debugInfo(string *s){
	debugInfo(s->c_str());
}

#line 92 "ToyParser.tab.c" /* yacc.c:339  */

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
   by #include "ToyParser.tab.h".  */
#ifndef YY_YY_TOYPARSER_TAB_H_INCLUDED
# define YY_YY_TOYPARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    IDENTIFIER = 258,
    DECIMAL_LITERAL = 259,
    HEX_LITERAL = 260,
    OCT_LITERAL = 261,
    BINARY_LITERAL = 262,
    FLOAT_LITERAL = 263,
    HEXFLOAT_LITERAL = 264,
    CHAR_LITERAL = 265,
    STRING_LITERAL = 266,
    ABSTRACT = 267,
    ASSERT = 268,
    AUTO = 269,
    BOOLEAN = 270,
    BREAK = 271,
    BYTE = 272,
    CASE = 273,
    CATCH = 274,
    CHAR = 275,
    CLASS = 276,
    CONST = 277,
    CONTINUE = 278,
    DEFAULT = 279,
    DO = 280,
    DOUBLE = 281,
    ELSE = 282,
    ENUM = 283,
    EXTENDS = 284,
    FINAL = 285,
    FINALLY = 286,
    FLOAT = 287,
    FOR = 288,
    IF = 289,
    GOTO = 290,
    IMPLEMENTS = 291,
    IMPORT = 292,
    INSTANCEOF = 293,
    INT = 294,
    INTERFACE = 295,
    LONG = 296,
    NATIVE = 297,
    NEW = 298,
    PACKAGE = 299,
    PRIVATE = 300,
    PROTECTED = 301,
    PUBLIC = 302,
    RETURN = 303,
    SHORT = 304,
    STATIC = 305,
    STRICTFP = 306,
    SUPER = 307,
    SWITCH = 308,
    SYNCHRONIZED = 309,
    THIS = 310,
    THROW = 311,
    THROWS = 312,
    TRANSIENT = 313,
    TRY = 314,
    VOID = 315,
    VOLATILE = 316,
    WHILE = 317,
    _AT = 318,
    _ELLIPSIS = 319,
    ASSIGN = 320,
    TILDE = 321,
    QUESTION = 322,
    DCOLON = 323,
    COLON = 324,
    LPAREN = 325,
    RPAREN = 326,
    LBRACE = 327,
    RBRACE = 328,
    LBRACK = 329,
    RBRACK = 330,
    DOT = 331,
    COMMA = 332,
    SEMIC = 333,
    BANG = 334,
    LT = 335,
    GT = 336,
    BITAND = 337,
    BITOR = 338,
    CARET = 339,
    ADD = 340,
    SUB = 341,
    MUL = 342,
    DIV = 343,
    MOD = 344,
    EQUAL = 345,
    NEQUAL = 346,
    LTOE = 347,
    GTOE = 348,
    AND = 349,
    OR = 350,
    LSHIFT = 351,
    RSHIFT = 352,
    INCRE = 353,
    DEFAULT_VAL = 354,
    ARROW = 355,
    DECRE = 356,
    ADD_ASSIGN = 357,
    SUB_ASSIGN = 358,
    MUL_ASSIGN = 359,
    DIV_ASSIGN = 360,
    AND_ASSIGN = 361,
    OR_ASSIGN = 362,
    XOR_ASSIGN = 363,
    MOD_ASSIGN = 364,
    LSHIFT_ASSIGN = 365,
    RSHIFT_ASSIGN = 366,
    URSHIFT = 367,
    URSHIFT_ASSIGN = 368,
    NULL_LITERAL = 369,
    TRUE_LITERAL = 370,
    FALSE_LITERAL = 371
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 28 "ToyParser.y" /* yacc.c:355  */

	std::string *string;
	int token;

#line 254 "ToyParser.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_TOYPARSER_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 271 "ToyParser.tab.c" /* yacc.c:358  */

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
#define YYFINAL  7
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1829

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  117
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  70
/* YYNRULES -- Number of rules.  */
#define YYNRULES  217
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  340

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   371

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
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    67,    67,    68,    72,    76,    77,    81,    82,    86,
      87,    91,    92,    97,    98,   102,   103,   104,   108,   109,
     113,   118,   119,   123,   124,   128,   129,   133,   134,   135,
     136,   137,   141,   142,   146,   147,   151,   152,   158,   159,
     163,   164,   165,   166,   167,   168,   169,   170,   171,   172,
     173,   174,   175,   176,   177,   178,   179,   180,   181,   182,
     183,   184,   185,   186,   187,   188,   189,   190,   191,   192,
     193,   194,   195,   196,   200,   201,   202,   203,   204,   205,
     206,   207,   208,   209,   210,   211,   216,   220,   221,   225,
     226,   227,   228,   229,   230,   235,   236,   240,   250,   251,
     257,   258,   262,   263,   267,   271,   272,   273,   277,   278,
     279,   284,   285,   289,   290,   294,   295,   296,   297,   298,
     304,   305,   309,   310,   315,   321,   322,   326,   327,   331,
     332,   333,   334,   335,   336,   337,   338,   342,   346,   347,
     352,   353,   357,   358,   362,   363,   368,   369,   374,   375,
     379,   380,   384,   385,   389,   390,   393,   394,   398,   399,
     400,   408,   409,   413,   414,   418,   419,   423,   424,   430,
     431,   432,   433,   434,   435,   436,   437,   442,   443,   444,
     445,   451,   452,   459,   460,   466,   467,   468,   469,   470,
     474,   475,   479,   480,   484,   485,   486,   487,   488,   489,
     490,   494,   495,   496,   497,   498,   499,   500,   504,   505,
     506,   507,   511,   512,   517,   518,   522,   523
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IDENTIFIER", "DECIMAL_LITERAL",
  "HEX_LITERAL", "OCT_LITERAL", "BINARY_LITERAL", "FLOAT_LITERAL",
  "HEXFLOAT_LITERAL", "CHAR_LITERAL", "STRING_LITERAL", "ABSTRACT",
  "ASSERT", "AUTO", "BOOLEAN", "BREAK", "BYTE", "CASE", "CATCH", "CHAR",
  "CLASS", "CONST", "CONTINUE", "DEFAULT", "DO", "DOUBLE", "ELSE", "ENUM",
  "EXTENDS", "FINAL", "FINALLY", "FLOAT", "FOR", "IF", "GOTO",
  "IMPLEMENTS", "IMPORT", "INSTANCEOF", "INT", "INTERFACE", "LONG",
  "NATIVE", "NEW", "PACKAGE", "PRIVATE", "PROTECTED", "PUBLIC", "RETURN",
  "SHORT", "STATIC", "STRICTFP", "SUPER", "SWITCH", "SYNCHRONIZED", "THIS",
  "THROW", "THROWS", "TRANSIENT", "TRY", "VOID", "VOLATILE", "WHILE",
  "_AT", "_ELLIPSIS", "ASSIGN", "TILDE", "QUESTION", "DCOLON", "COLON",
  "LPAREN", "RPAREN", "LBRACE", "RBRACE", "LBRACK", "RBRACK", "DOT",
  "COMMA", "SEMIC", "BANG", "LT", "GT", "BITAND", "BITOR", "CARET", "ADD",
  "SUB", "MUL", "DIV", "MOD", "EQUAL", "NEQUAL", "LTOE", "GTOE", "AND",
  "OR", "LSHIFT", "RSHIFT", "INCRE", "DEFAULT_VAL", "ARROW", "DECRE",
  "ADD_ASSIGN", "SUB_ASSIGN", "MUL_ASSIGN", "DIV_ASSIGN", "AND_ASSIGN",
  "OR_ASSIGN", "XOR_ASSIGN", "MOD_ASSIGN", "LSHIFT_ASSIGN",
  "RSHIFT_ASSIGN", "URSHIFT", "URSHIFT_ASSIGN", "NULL_LITERAL",
  "TRUE_LITERAL", "FALSE_LITERAL", "$accept", "CompilationUnit",
  "PackageDecl", "ImportDeclListOptional", "ImportDecl",
  "SingleImportDecl", "TypeImportDecl", "TypeDeclListOptional", "TypeDecl",
  "ClassDecl", "InterfaceDecl", "ClassBody", "ClassBodyDeclList",
  "ClassBodyDecl", "ForControl", "EnhancedForControl", "ForInitOptional",
  "ForInit", "MethodCall", "Expression", "AssignOperators",
  "ParExpression", "ExpressionList", "Primary", "ModifierList",
  "VariableModifier", "MethodBody", "InterfaceBody",
  "InterfaceBodyDeclList", "FieldDecl", "InterfaceBodyDecl",
  "InterfaceMemberDecl", "InterfaceMethodDecl",
  "InterfaceMethodModifierListOptional", "InterfaceMethodModifier",
  "FormalParams", "FormalParameterWithCommaList", "FormalParam",
  "QualifiedNameList", "VariableModifierList", "PrimitiveType",
  "ClassOrInterfaceType", "DotClassOrInterfaceTypeList", "TypeType",
  "TypeTypeOrVoid", "ConstructorDecl", "TypeList", "VariableDeclarators",
  "VariableDeclarator", "VariableDeclaratorId", "VariableInitializer",
  "VariableInitializerListWithComma", "ArrayInitializer", "Block",
  "BlockStatementList", "BlockStatement", "LocalVariableDecl", "Statement",
  "MemberDecl", "MethodDecl", "QualifiedName", "Modifier",
  "ClassOrInterfaceModifierListOptional", "ClassOrInterfaceModifierList",
  "ClassOrInterfaceModifier", "Literal", "IntegerLiteral", "FloatLiteral",
  "LRBrackListOptional", "LRBrackList", YY_NULLPTR
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
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   369,   370,   371
};
# endif

#define YYPACT_NINF -276

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-276)))

#define YYTABLE_NINF -140

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      -7,    35,    51,  -276,    25,  -276,     8,  -276,    25,    16,
    -276,  -276,  -276,    13,    72,  -276,    22,    35,    39,  -276,
    -276,  -276,  -276,  -276,  -276,  -276,  -276,  -276,     5,   119,
    -276,  -276,    57,     9,  -276,    74,    84,  -276,  -276,  -276,
      11,  -276,    15,   -19,    24,    40,  -276,   335,   202,  -276,
    1219,  -276,  -276,  -276,  -276,  -276,  -276,  -276,  -276,  -276,
    -276,  -276,    62,    62,  -276,     4,    67,  -276,  -276,  -276,
    -276,  -276,  -276,  -276,  1697,  -276,   947,  -276,   138,   139,
    -276,  -276,  -276,  -276,  -276,  -276,  -276,  -276,  -276,  1024,
    1729,  -276,  -276,  -276,  1769,    68,    70,  -276,    69,  -276,
     335,  -276,    75,   -30,  -276,  -276,  -276,  -276,    62,    34,
    -276,    82,    67,  -276,  -276,  -276,  -276,  -276,  -276,  -276,
    -276,  -276,  -276,   145,   148,  -276,    78,  -276,  -276,   -36,
    -276,   138,    35,   293,  -276,    69,   138,  -276,   735,    62,
      67,  -276,  -276,  -276,   335,  -276,    31,    79,    12,  -276,
    -276,  -276,  -276,  -276,  -276,  -276,  -276,  -276,    87,    88,
     820,  -276,  -276,  1177,  1177,  -276,  -276,  1177,  1177,  1177,
    1177,  1177,  -276,  -276,  -276,  -276,  1220,  -276,  -276,   583,
     138,    86,  -276,   395,  -276,    76,  -276,  -276,  -276,  -276,
    -276,   565,  1586,  -276,  -276,   110,    62,  -276,    35,  -276,
     905,  1007,  1177,   480,  -276,  1281,  1586,  1342,  1586,  1586,
    1586,  1586,  1586,   335,  -276,  1177,   168,  -276,  1177,  1177,
    1177,  1177,  1177,  1177,  1177,  1177,  1177,  1177,  1177,  1177,
    1177,  1177,  1177,  1177,  1177,  1177,  -276,  -276,  -276,  -276,
    -276,  -276,  -276,  -276,  -276,  -276,  -276,  -276,  1177,  -276,
    1177,  -276,   138,    95,   152,  -276,  -276,  -276,  -276,  -276,
      29,    35,   -33,    79,  -276,  1586,    -6,   105,  -276,   118,
    -276,   121,   583,   138,  -276,  1403,   172,  -276,  -276,  -276,
    1464,   130,  -276,  1586,  1586,  1586,  1586,  1586,  1586,  1586,
    1586,  1586,  1586,  1586,  1586,  1586,  1586,  1586,  1586,  1586,
    1586,  1586,  1586,    95,  -276,  -276,   650,    33,    35,  -276,
    -276,  -276,  -276,  1177,   480,  1092,   138,    20,  -276,   480,
    -276,  -276,  -276,    35,  -276,    33,  1586,  -276,  1177,  1525,
      44,  1177,  -276,  -276,   121,  1177,  1177,  1586,   121,  1586
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       6,     0,     0,     6,    14,   183,     0,     1,    14,     0,
       5,     7,     8,   191,     0,     4,   191,     0,     0,   198,
     199,   195,   196,   194,   197,   200,    17,    13,     0,   190,
     192,   184,     0,     0,     9,     0,     0,    15,    16,   193,
       0,    10,     0,     0,     0,     0,    11,     0,     0,    18,
     114,    20,    12,   139,   129,   131,   130,   136,   135,   133,
     134,   132,   215,   215,   146,     0,   139,   186,   187,   188,
     143,   189,    21,   180,     0,    23,     0,   178,     0,     0,
     179,    26,   177,    95,   185,   100,   107,   110,   109,   114,
     114,   102,   105,   108,     0,   137,     0,   141,   214,   140,
       0,    19,     0,     0,    22,    24,    25,    96,   153,     0,
     148,   150,     0,   106,   101,   103,   116,   117,   115,   118,
     119,   113,   142,     0,     0,   216,     0,   147,   121,     0,
     122,     0,     0,     0,   145,   152,     0,   104,     0,   215,
       0,   138,   217,   120,     0,   124,     0,   125,    93,   208,
     209,   210,   211,   212,   213,   203,   204,    97,     0,     0,
       0,    91,    90,     0,     0,   162,   175,     0,     0,     0,
       0,     0,   207,   205,   206,    44,     0,    40,   127,     0,
     142,     0,   169,     0,   163,     0,   166,    92,   201,   202,
     149,     0,   155,   151,   154,   182,   215,   123,     0,   144,
       0,    35,     0,     0,   174,     0,    51,     0,    52,    47,
      48,    49,    50,     0,    74,     0,     0,   176,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    45,    46,    75,    76,
      77,    78,    80,    81,    82,    79,    85,    83,     0,    84,
       0,   128,     0,   168,     0,   161,   164,   165,   160,   156,
       0,     0,     0,   126,    39,    87,     0,     0,    27,     0,
      34,    37,     0,   142,    36,     0,   171,   173,    89,    65,
       0,    41,    42,    61,    62,    68,    70,    69,    56,    57,
      53,    54,    55,    66,    67,    63,    64,    71,    72,    58,
      59,    60,    73,   167,    94,   159,     0,     0,     0,    99,
     112,    98,    38,     0,     0,     0,     0,   150,    86,     0,
      43,   158,   157,    99,   181,     0,    88,   172,    31,     0,
     150,     0,   170,   111,    29,    30,     0,    33,    28,    32
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -276,  -276,  -276,   198,  -276,  -276,  -276,   194,  -276,   175,
     -10,   141,  -276,   136,  -276,  -276,  -276,  -276,   -12,   -41,
    -276,  -276,  -196,  -276,   -29,  -168,  -275,  -276,  -276,  -276,
     122,   124,  -276,  -276,  -276,   -92,  -276,    71,  -238,    10,
    -276,  -276,  -276,   -45,   -20,  -276,  -276,   -77,    80,  -121,
    -185,  -276,  -276,   -99,  -276,    37,    23,  -194,   142,  -276,
      -1,   -40,  -276,  -276,    17,  -276,  -276,  -276,   -56,   113
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     4,    10,    11,    12,    13,    27,    87,
      73,    49,    74,    75,   267,   268,   269,   270,   175,   176,
     250,   203,   266,   177,    76,   178,   310,    51,    90,    77,
      91,    92,    93,    94,   121,   103,   129,   130,   146,   179,
      62,    63,    95,   122,   181,    80,    65,   253,   110,   111,
     193,   260,   194,   182,   183,   184,   185,   186,    81,    82,
     147,    83,    28,    29,    84,   187,   188,   189,    97,    98
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
       6,   109,    64,    78,   134,   271,   259,    99,    18,   276,
     145,   251,    31,    -3,    31,  -139,    32,    47,    38,     5,
     139,    89,    -2,   307,   308,    19,    35,   132,    79,    78,
      30,    78,   324,    30,    19,   143,   107,     1,     5,   133,
      88,   144,   133,    20,   309,    36,    39,   199,   196,   107,
     333,     7,    20,    48,    79,   127,    79,   131,    21,    22,
      23,    89,     9,    24,    25,   312,    17,    21,    22,    23,
     325,   313,    24,    25,   123,    31,    48,    43,    53,    88,
      88,   100,   200,   195,    14,   138,    15,    44,   180,   331,
      54,    26,    55,    46,    50,    56,    42,   192,    45,   131,
      26,    57,   305,   133,   251,   133,   306,    58,   198,   138,
     323,   136,   137,   336,    59,    33,    60,    34,    52,   205,
     327,   322,   206,   207,    61,   332,   208,   209,   210,   211,
     212,    19,   334,    40,   252,    41,    96,   102,   180,   338,
     262,   108,   112,   126,   124,   125,   128,   138,   140,    20,
     192,   141,   317,   142,   257,    14,   273,   201,   202,   265,
     265,   275,   254,   311,    21,    22,    23,   261,   279,    24,
      25,   281,   136,   304,   280,   303,   314,   283,   284,   285,
     286,   287,   288,   289,   290,   291,   292,   293,   294,   295,
     296,   297,   298,   299,   300,   330,   315,   263,   313,   319,
     200,     8,    16,    37,   282,    66,   101,   301,   311,   302,
     105,   272,   115,   113,    19,   197,   190,    54,   106,    55,
     256,   135,    56,     0,   274,     0,   311,   316,    57,     0,
       0,     0,    20,     0,    58,     0,     0,     0,     0,   303,
       0,    59,    36,    60,    67,     0,     0,    21,    22,    23,
       0,    61,    24,    25,     0,     0,    68,     0,     0,     0,
      69,     0,    70,    71,     0,   192,     0,     0,     0,     0,
       0,     0,   326,     0,   329,    72,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   265,     0,     0,
     337,     0,     0,     0,   265,   339,   148,   149,   150,   151,
     152,   153,   154,   155,   156,     0,     0,     0,    54,     0,
      55,     0,     0,    56,     0,     0,     0,     0,     0,    57,
       0,     0,   263,   157,     0,    58,   158,   159,     0,     0,
       0,     0,    59,     0,    60,     0,     0,     0,    53,     0,
       0,   160,    61,     0,     0,   161,     0,     0,   162,     0,
      54,     0,    55,    70,     0,    56,     0,     0,     0,   163,
       0,    57,     0,   164,     0,   133,   165,    58,     0,     0,
       0,   166,   167,     0,    59,     0,    60,     0,   168,   169,
       0,     0,     0,     0,    61,     0,     0,     0,     0,     0,
       0,   170,     0,     0,   171,     0,     0,     0,   148,   149,
     150,   151,   152,   153,   154,   155,   156,   172,   173,   174,
      54,     0,    55,     0,     0,    56,     0,     0,     0,     0,
       0,    57,     0,     0,     0,   157,     0,    58,   158,   159,
       0,     0,     0,     0,    59,     0,    60,     0,     0,     0,
       0,     0,     0,   160,    61,     0,     0,   161,     0,     0,
     162,     0,     0,     0,     0,    70,     0,     0,     0,     0,
       0,   163,     0,     0,     0,   164,     0,   133,   255,     0,
       0,     0,     0,   166,   167,     0,     0,     0,     0,     0,
     168,   169,     0,   148,   149,   150,   151,   152,   153,   154,
     155,   156,     0,   170,     0,    54,   171,    55,     0,     0,
      56,     0,     0,     0,     0,     0,    57,     0,     0,   172,
     173,   174,    58,   158,   159,     0,     0,     0,     0,    59,
       0,    60,     0,     0,     0,     0,     0,     0,   160,    61,
       0,     0,   161,     0,     0,   162,     0,     0,     0,     0,
      70,     0,     0,     0,     0,     0,   163,     0,     0,     0,
     164,     0,   133,     0,     0,     0,     0,     0,   166,   167,
       0,     0,     0,     0,     0,   168,   169,     0,   148,   149,
     150,   151,   152,   153,   154,   155,   156,     0,   170,     0,
      54,   171,    55,     0,     0,    56,    53,     0,     0,     0,
       0,    57,     0,     0,   172,   173,   174,    58,    54,     0,
      55,     0,     0,    56,    59,     0,    60,     0,     0,    57,
       0,     0,     0,   157,    61,    58,     0,   161,     0,     0,
     162,     0,    59,     0,    60,    70,     0,     0,     0,     0,
       0,   163,    61,     0,     0,   164,     0,   191,   258,     0,
       0,     0,     0,     0,   167,     0,     0,     0,     0,     0,
     168,   169,     0,   148,   149,   150,   151,   152,   153,   154,
     155,   156,     0,   170,     0,    54,   171,    55,     0,     0,
      56,     0,     0,     0,     0,     0,    57,     0,     0,   172,
     173,   174,    58,     0,     0,     0,     0,     0,     0,    59,
       0,    60,     0,     0,     0,     0,     0,     0,     0,    61,
       0,     0,   161,     0,     0,   162,     0,     0,     0,     0,
      70,     0,     0,     0,     0,     0,   163,     0,     0,     0,
     164,     0,   191,   321,     0,     0,     0,     0,     0,   167,
       0,     0,     0,     0,     0,   168,   169,     0,   148,   149,
     150,   151,   152,   153,   154,   155,   156,     0,   170,     0,
      54,   171,    55,     0,     0,    56,     0,     0,     0,     0,
       0,    57,     0,     0,   172,   173,   174,    58,     0,     0,
       0,     0,     0,     0,    59,     0,    60,     0,     0,     0,
       0,     0,     0,     0,    61,     0,     0,   161,     0,     0,
     162,     0,     0,     0,     0,    70,     0,     0,     0,     0,
       0,   163,     0,     0,     0,   164,     0,   191,     0,     0,
       0,     0,     0,     0,   167,     0,     0,     0,     0,     0,
     168,   169,     0,   148,   149,   150,   151,   152,   153,   154,
     155,   156,     0,   170,     0,    54,   171,    55,     0,     0,
      56,     0,     0,     0,     0,     0,    57,     0,     0,   172,
     173,   174,    58,     0,     0,     0,     0,     0,     0,    59,
       0,    60,     0,     0,     0,     0,     0,     0,     0,    61,
       0,     0,   161,     0,     0,   162,     0,     0,     0,     0,
      70,     0,     0,     0,     0,     0,   163,     0,     0,     0,
     164,     0,     0,     0,     0,     0,     0,     0,   204,   167,
       0,     0,     0,     0,     0,   168,   169,     0,   148,   149,
     150,   151,   152,   153,   154,   155,   156,     0,   170,     0,
      54,   171,    55,     0,     0,    56,     0,     0,     0,     0,
       0,    57,     0,     0,   172,   173,   174,    58,     0,     0,
       0,     0,     0,     0,    59,     0,    60,     0,     0,     0,
      66,     0,     0,     0,    61,     0,     0,   161,     0,    19,
     162,     0,    54,     0,    55,    70,     0,    56,     0,     0,
       0,   163,     0,    57,     0,   164,   264,    20,     0,    58,
       0,     0,     0,     0,   167,     0,    59,    36,    60,    67,
     168,   169,    21,    22,    23,     0,    61,    24,    25,     0,
       0,    68,     0,   170,     0,    69,   171,    70,    71,     0,
     148,   149,   150,   151,   152,   153,   154,   155,   156,   172,
     173,   174,    54,     0,    55,     0,     0,    56,     0,     0,
       0,     0,     0,    57,     0,     0,    19,   157,     0,    58,
       0,     0,     0,     0,     0,    35,    59,     0,    60,     0,
       0,     0,     0,     0,    20,     0,    61,     0,     0,   161,
       0,     0,   162,     0,    36,     0,    67,    70,     0,    21,
      22,    23,     0,   163,    24,    25,     0,   164,    68,     0,
       0,     0,    69,     0,     0,    71,   167,     0,     0,     0,
       0,     0,   168,   169,     0,   148,   149,   150,   151,   152,
     153,   154,   155,   156,     0,   170,     0,    54,   171,    55,
       0,     0,    56,     0,     0,     0,     0,     0,    57,     0,
       0,   172,   173,   174,    58,     0,     0,     0,     0,     0,
       0,    59,     0,    60,     0,     0,     0,     0,     0,     0,
       0,    61,     0,     0,   161,     0,     0,   162,     0,     0,
       0,     0,    70,     0,     0,     0,     0,     0,   163,     0,
       0,     0,   164,     0,     0,     0,     0,     0,     0,     0,
     328,   167,     0,     0,     0,     0,     0,   168,   169,     0,
     148,   149,   150,   151,   152,   153,   154,   155,   156,     0,
     170,     0,    54,   171,    55,     0,     0,    56,     0,     0,
       0,     0,     0,    57,     0,     0,   172,   173,   174,    58,
       0,     0,     0,     0,     0,     0,    59,     0,    60,     0,
       0,     0,     0,     0,     0,     0,    61,     0,     0,   161,
       0,    19,   162,     0,     0,     0,     0,    70,     0,     0,
      35,     0,     0,   163,     0,     0,     0,   164,     0,    20,
       0,     0,     0,     0,     0,     0,   167,     0,   213,    36,
       0,    67,   168,   169,    21,    22,    23,     0,     0,    24,
      25,     0,     0,    68,     0,   170,     0,    69,   171,     0,
      71,     0,     0,     0,     0,   214,     0,     0,     0,     0,
      85,   172,   173,   174,   215,     0,   216,    86,   217,     0,
     218,   219,   220,   221,   222,   223,   224,   225,   226,   227,
     228,   229,   230,   231,   232,   233,   234,   235,   236,   213,
       0,   237,   238,   239,   240,   241,   242,   243,   244,   245,
     246,   247,   248,   249,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   214,     0,     0,     0,
       0,     0,     0,     0,     0,   215,     0,   216,     0,   277,
       0,   218,   219,   220,   221,   222,   223,   224,   225,   226,
     227,   228,   229,   230,   231,   232,   233,   234,   235,   236,
     213,     0,   237,   238,   239,   240,   241,   242,   243,   244,
     245,   246,   247,   248,   249,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   214,     0,     0,
       0,     0,     0,   278,     0,     0,   215,     0,   216,     0,
       0,     0,   218,   219,   220,   221,   222,   223,   224,   225,
     226,   227,   228,   229,   230,   231,   232,   233,   234,   235,
     236,   213,     0,   237,   238,   239,   240,   241,   242,   243,
     244,   245,   246,   247,   248,   249,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   214,     0,
       0,     0,     0,     0,   318,     0,     0,   215,     0,   216,
       0,     0,     0,   218,   219,   220,   221,   222,   223,   224,
     225,   226,   227,   228,   229,   230,   231,   232,   233,   234,
     235,   236,   213,     0,   237,   238,   239,   240,   241,   242,
     243,   244,   245,   246,   247,   248,   249,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   214,
       0,     0,     0,     0,     0,     0,     0,     0,   215,   320,
     216,     0,     0,     0,   218,   219,   220,   221,   222,   223,
     224,   225,   226,   227,   228,   229,   230,   231,   232,   233,
     234,   235,   236,   213,     0,   237,   238,   239,   240,   241,
     242,   243,   244,   245,   246,   247,   248,   249,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     214,     0,     0,     0,     0,     0,     0,     0,     0,   215,
       0,   216,     0,   335,     0,   218,   219,   220,   221,   222,
     223,   224,   225,   226,   227,   228,   229,   230,   231,   232,
     233,   234,   235,   236,   213,     0,   237,   238,   239,   240,
     241,   242,   243,   244,   245,   246,   247,   248,   249,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   214,     0,     0,     0,     0,     0,     0,     0,     0,
     215,     0,   216,     0,     0,     0,   218,   219,   220,   221,
     222,   223,   224,   225,   226,   227,   228,   229,   230,   231,
     232,   233,   234,   235,   236,     0,     0,   237,   238,   239,
     240,   241,   242,   243,   244,   245,   246,   247,   248,   249,
      66,     0,     0,     0,     0,     0,     0,     0,     0,    19,
       0,     0,    54,     0,    55,     0,     0,    56,     0,     0,
       0,     0,     0,    57,     0,     0,     0,    20,     0,    58,
       0,     0,     0,     0,     0,     0,    59,    36,    60,    67,
       0,    19,    21,    22,    23,     0,    61,    24,    25,     0,
      35,    68,     0,     0,     0,    69,     0,    70,    71,    20,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    36,
     104,    67,    53,     0,    21,    22,    23,     0,     0,    24,
      25,   116,     0,    68,    54,     0,    55,    69,     0,    56,
      71,     0,     0,   117,     0,    57,     0,     0,     0,     0,
     114,    58,     0,     0,     0,     0,     0,    86,    59,     0,
      60,     0,     0,     0,     0,     0,   118,     0,    61,   119,
     120,     0,     0,     0,     0,     0,     0,     0,     0,    70
};

static const yytype_int16 yycheck[] =
{
       1,    78,    47,    48,   103,   201,   191,    63,     9,   203,
     131,   179,     3,     0,     3,     3,    17,    36,    28,     3,
     112,    50,     0,   261,    57,    12,    21,    57,    48,    74,
      13,    76,   307,    16,    12,    71,    76,    44,     3,    72,
      50,    77,    72,    30,    77,    40,    29,   146,   140,    89,
     325,     0,    30,    72,    74,   100,    76,   102,    45,    46,
      47,    90,    37,    50,    51,    71,    50,    45,    46,    47,
     308,    77,    50,    51,    94,     3,    72,     3,     3,    89,
      90,    77,    70,   139,    76,    65,    78,     3,   133,    69,
      15,    78,    17,    78,    70,    20,    87,   138,    87,   144,
      78,    26,    73,    72,   272,    72,    77,    32,    77,    65,
      77,    77,    78,    69,    39,    76,    41,    78,    78,   160,
     314,   306,   163,   164,    49,   319,   167,   168,   169,   170,
     171,    12,   328,    76,   179,    78,    74,    70,   183,   335,
     196,     3,     3,    74,    76,    75,    71,    65,     3,    30,
     191,     3,   273,    75,    78,    76,   201,    70,    70,   200,
     201,   202,    76,   262,    45,    46,    47,    57,   213,    50,
      51,     3,    77,    21,   215,   252,    71,   218,   219,   220,
     221,   222,   223,   224,   225,   226,   227,   228,   229,   230,
     231,   232,   233,   234,   235,   316,    78,   198,    77,    27,
      70,     3,     8,    28,   216,     3,    65,   248,   307,   250,
      74,   201,    90,    89,    12,   144,   136,    15,    76,    17,
     183,   108,    20,    -1,   201,    -1,   325,   272,    26,    -1,
      -1,    -1,    30,    -1,    32,    -1,    -1,    -1,    -1,   316,
      -1,    39,    40,    41,    42,    -1,    -1,    45,    46,    47,
      -1,    49,    50,    51,    -1,    -1,    54,    -1,    -1,    -1,
      58,    -1,    60,    61,    -1,   306,    -1,    -1,    -1,    -1,
      -1,    -1,   313,    -1,   315,    73,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   328,    -1,    -1,
     331,    -1,    -1,    -1,   335,   336,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    -1,    -1,    -1,    15,    -1,
      17,    -1,    -1,    20,    -1,    -1,    -1,    -1,    -1,    26,
      -1,    -1,   323,    30,    -1,    32,    33,    34,    -1,    -1,
      -1,    -1,    39,    -1,    41,    -1,    -1,    -1,     3,    -1,
      -1,    48,    49,    -1,    -1,    52,    -1,    -1,    55,    -1,
      15,    -1,    17,    60,    -1,    20,    -1,    -1,    -1,    66,
      -1,    26,    -1,    70,    -1,    72,    73,    32,    -1,    -1,
      -1,    78,    79,    -1,    39,    -1,    41,    -1,    85,    86,
      -1,    -1,    -1,    -1,    49,    -1,    -1,    -1,    -1,    -1,
      -1,    98,    -1,    -1,   101,    -1,    -1,    -1,     3,     4,
       5,     6,     7,     8,     9,    10,    11,   114,   115,   116,
      15,    -1,    17,    -1,    -1,    20,    -1,    -1,    -1,    -1,
      -1,    26,    -1,    -1,    -1,    30,    -1,    32,    33,    34,
      -1,    -1,    -1,    -1,    39,    -1,    41,    -1,    -1,    -1,
      -1,    -1,    -1,    48,    49,    -1,    -1,    52,    -1,    -1,
      55,    -1,    -1,    -1,    -1,    60,    -1,    -1,    -1,    -1,
      -1,    66,    -1,    -1,    -1,    70,    -1,    72,    73,    -1,
      -1,    -1,    -1,    78,    79,    -1,    -1,    -1,    -1,    -1,
      85,    86,    -1,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    -1,    98,    -1,    15,   101,    17,    -1,    -1,
      20,    -1,    -1,    -1,    -1,    -1,    26,    -1,    -1,   114,
     115,   116,    32,    33,    34,    -1,    -1,    -1,    -1,    39,
      -1,    41,    -1,    -1,    -1,    -1,    -1,    -1,    48,    49,
      -1,    -1,    52,    -1,    -1,    55,    -1,    -1,    -1,    -1,
      60,    -1,    -1,    -1,    -1,    -1,    66,    -1,    -1,    -1,
      70,    -1,    72,    -1,    -1,    -1,    -1,    -1,    78,    79,
      -1,    -1,    -1,    -1,    -1,    85,    86,    -1,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    -1,    98,    -1,
      15,   101,    17,    -1,    -1,    20,     3,    -1,    -1,    -1,
      -1,    26,    -1,    -1,   114,   115,   116,    32,    15,    -1,
      17,    -1,    -1,    20,    39,    -1,    41,    -1,    -1,    26,
      -1,    -1,    -1,    30,    49,    32,    -1,    52,    -1,    -1,
      55,    -1,    39,    -1,    41,    60,    -1,    -1,    -1,    -1,
      -1,    66,    49,    -1,    -1,    70,    -1,    72,    73,    -1,
      -1,    -1,    -1,    -1,    79,    -1,    -1,    -1,    -1,    -1,
      85,    86,    -1,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    -1,    98,    -1,    15,   101,    17,    -1,    -1,
      20,    -1,    -1,    -1,    -1,    -1,    26,    -1,    -1,   114,
     115,   116,    32,    -1,    -1,    -1,    -1,    -1,    -1,    39,
      -1,    41,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    49,
      -1,    -1,    52,    -1,    -1,    55,    -1,    -1,    -1,    -1,
      60,    -1,    -1,    -1,    -1,    -1,    66,    -1,    -1,    -1,
      70,    -1,    72,    73,    -1,    -1,    -1,    -1,    -1,    79,
      -1,    -1,    -1,    -1,    -1,    85,    86,    -1,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    -1,    98,    -1,
      15,   101,    17,    -1,    -1,    20,    -1,    -1,    -1,    -1,
      -1,    26,    -1,    -1,   114,   115,   116,    32,    -1,    -1,
      -1,    -1,    -1,    -1,    39,    -1,    41,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    49,    -1,    -1,    52,    -1,    -1,
      55,    -1,    -1,    -1,    -1,    60,    -1,    -1,    -1,    -1,
      -1,    66,    -1,    -1,    -1,    70,    -1,    72,    -1,    -1,
      -1,    -1,    -1,    -1,    79,    -1,    -1,    -1,    -1,    -1,
      85,    86,    -1,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    -1,    98,    -1,    15,   101,    17,    -1,    -1,
      20,    -1,    -1,    -1,    -1,    -1,    26,    -1,    -1,   114,
     115,   116,    32,    -1,    -1,    -1,    -1,    -1,    -1,    39,
      -1,    41,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    49,
      -1,    -1,    52,    -1,    -1,    55,    -1,    -1,    -1,    -1,
      60,    -1,    -1,    -1,    -1,    -1,    66,    -1,    -1,    -1,
      70,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    78,    79,
      -1,    -1,    -1,    -1,    -1,    85,    86,    -1,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    -1,    98,    -1,
      15,   101,    17,    -1,    -1,    20,    -1,    -1,    -1,    -1,
      -1,    26,    -1,    -1,   114,   115,   116,    32,    -1,    -1,
      -1,    -1,    -1,    -1,    39,    -1,    41,    -1,    -1,    -1,
       3,    -1,    -1,    -1,    49,    -1,    -1,    52,    -1,    12,
      55,    -1,    15,    -1,    17,    60,    -1,    20,    -1,    -1,
      -1,    66,    -1,    26,    -1,    70,    71,    30,    -1,    32,
      -1,    -1,    -1,    -1,    79,    -1,    39,    40,    41,    42,
      85,    86,    45,    46,    47,    -1,    49,    50,    51,    -1,
      -1,    54,    -1,    98,    -1,    58,   101,    60,    61,    -1,
       3,     4,     5,     6,     7,     8,     9,    10,    11,   114,
     115,   116,    15,    -1,    17,    -1,    -1,    20,    -1,    -1,
      -1,    -1,    -1,    26,    -1,    -1,    12,    30,    -1,    32,
      -1,    -1,    -1,    -1,    -1,    21,    39,    -1,    41,    -1,
      -1,    -1,    -1,    -1,    30,    -1,    49,    -1,    -1,    52,
      -1,    -1,    55,    -1,    40,    -1,    42,    60,    -1,    45,
      46,    47,    -1,    66,    50,    51,    -1,    70,    54,    -1,
      -1,    -1,    58,    -1,    -1,    61,    79,    -1,    -1,    -1,
      -1,    -1,    85,    86,    -1,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    -1,    98,    -1,    15,   101,    17,
      -1,    -1,    20,    -1,    -1,    -1,    -1,    -1,    26,    -1,
      -1,   114,   115,   116,    32,    -1,    -1,    -1,    -1,    -1,
      -1,    39,    -1,    41,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    49,    -1,    -1,    52,    -1,    -1,    55,    -1,    -1,
      -1,    -1,    60,    -1,    -1,    -1,    -1,    -1,    66,    -1,
      -1,    -1,    70,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      78,    79,    -1,    -1,    -1,    -1,    -1,    85,    86,    -1,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    -1,
      98,    -1,    15,   101,    17,    -1,    -1,    20,    -1,    -1,
      -1,    -1,    -1,    26,    -1,    -1,   114,   115,   116,    32,
      -1,    -1,    -1,    -1,    -1,    -1,    39,    -1,    41,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    49,    -1,    -1,    52,
      -1,    12,    55,    -1,    -1,    -1,    -1,    60,    -1,    -1,
      21,    -1,    -1,    66,    -1,    -1,    -1,    70,    -1,    30,
      -1,    -1,    -1,    -1,    -1,    -1,    79,    -1,    38,    40,
      -1,    42,    85,    86,    45,    46,    47,    -1,    -1,    50,
      51,    -1,    -1,    54,    -1,    98,    -1,    58,   101,    -1,
      61,    -1,    -1,    -1,    -1,    65,    -1,    -1,    -1,    -1,
      71,   114,   115,   116,    74,    -1,    76,    78,    78,    -1,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    38,
      -1,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    65,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    74,    -1,    76,    -1,    78,
      -1,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      38,    -1,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    -1,    -1,
      -1,    -1,    -1,    71,    -1,    -1,    74,    -1,    76,    -1,
      -1,    -1,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    38,    -1,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    -1,
      -1,    -1,    -1,    -1,    71,    -1,    -1,    74,    -1,    76,
      -1,    -1,    -1,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    38,    -1,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    74,    75,
      76,    -1,    -1,    -1,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    38,    -1,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      65,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    74,
      -1,    76,    -1,    78,    -1,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    38,    -1,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    65,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      74,    -1,    76,    -1,    -1,    -1,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    -1,    -1,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
       3,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    12,
      -1,    -1,    15,    -1,    17,    -1,    -1,    20,    -1,    -1,
      -1,    -1,    -1,    26,    -1,    -1,    -1,    30,    -1,    32,
      -1,    -1,    -1,    -1,    -1,    -1,    39,    40,    41,    42,
      -1,    12,    45,    46,    47,    -1,    49,    50,    51,    -1,
      21,    54,    -1,    -1,    -1,    58,    -1,    60,    61,    30,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    40,
      73,    42,     3,    -1,    45,    46,    47,    -1,    -1,    50,
      51,    12,    -1,    54,    15,    -1,    17,    58,    -1,    20,
      61,    -1,    -1,    24,    -1,    26,    -1,    -1,    -1,    -1,
      71,    32,    -1,    -1,    -1,    -1,    -1,    78,    39,    -1,
      41,    -1,    -1,    -1,    -1,    -1,    47,    -1,    49,    50,
      51,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    60
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    44,   118,   119,   120,     3,   177,     0,   120,    37,
     121,   122,   123,   124,    76,    78,   124,    50,   177,    12,
      30,    45,    46,    47,    50,    51,    78,   125,   179,   180,
     181,     3,   177,    76,    78,    21,    40,   126,   127,   181,
      76,    78,    87,     3,     3,    87,    78,    36,    72,   128,
      70,   144,    78,     3,    15,    17,    20,    26,    32,    39,
      41,    49,   157,   158,   160,   163,     3,    42,    54,    58,
      60,    61,    73,   127,   129,   130,   141,   146,   160,   161,
     162,   175,   176,   178,   181,    71,    78,   126,   127,   141,
     145,   147,   148,   149,   150,   159,    74,   185,   186,   185,
      77,   128,    70,   152,    73,   130,   175,   178,     3,   164,
     165,   166,     3,   148,    71,   147,    12,    24,    47,    50,
      51,   151,   160,   161,    76,    75,    74,   160,    71,   153,
     154,   160,    57,    72,   170,   186,    77,    78,    65,   152,
       3,     3,    75,    71,    77,   166,   155,   177,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    30,    33,    34,
      48,    52,    55,    66,    70,    73,    78,    79,    85,    86,
      98,   101,   114,   115,   116,   135,   136,   140,   142,   156,
     160,   161,   170,   171,   172,   173,   174,   182,   183,   184,
     165,    72,   136,   167,   169,   185,   152,   154,    77,   170,
      70,    70,    70,   138,    78,   136,   136,   136,   136,   136,
     136,   136,   136,    38,    65,    74,    76,    78,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     137,   142,   160,   164,    76,    73,   172,    78,    73,   167,
     168,    57,   185,   177,    71,   136,   139,   131,   132,   133,
     134,   139,   156,   160,   173,   136,   174,    78,    71,   160,
     136,     3,   135,   136,   136,   136,   136,   136,   136,   136,
     136,   136,   136,   136,   136,   136,   136,   136,   136,   136,
     136,   136,   136,   164,    21,    73,    77,   155,    57,    77,
     143,   170,    71,    77,    71,    78,   160,   166,    71,    27,
      75,    73,   167,    77,   143,   155,   136,   174,    78,   136,
     166,    69,   174,   143,   139,    78,    69,   136,   139,   136
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   117,   118,   118,   119,   120,   120,   121,   121,   122,
     122,   123,   123,   124,   124,   125,   125,   125,   126,   126,
     127,   128,   128,   129,   129,   130,   130,   131,   131,   131,
     131,   131,   132,   132,   133,   133,   134,   134,   135,   135,
     136,   136,   136,   136,   136,   136,   136,   136,   136,   136,
     136,   136,   136,   136,   136,   136,   136,   136,   136,   136,
     136,   136,   136,   136,   136,   136,   136,   136,   136,   136,
     136,   136,   136,   136,   137,   137,   137,   137,   137,   137,
     137,   137,   137,   137,   137,   137,   138,   139,   139,   140,
     140,   140,   140,   140,   140,   141,   141,   142,   143,   143,
     144,   144,   145,   145,   146,   147,   147,   147,   148,   148,
     148,   149,   149,   150,   150,   151,   151,   151,   151,   151,
     152,   152,   153,   153,   154,   155,   155,   156,   156,   157,
     157,   157,   157,   157,   157,   157,   157,   158,   159,   159,
     160,   160,   161,   161,   162,   162,   163,   163,   164,   164,
     165,   165,   166,   166,   167,   167,   168,   168,   169,   169,
     169,   170,   170,   171,   171,   172,   172,   173,   173,   174,
     174,   174,   174,   174,   174,   174,   174,   175,   175,   175,
     175,   176,   176,   177,   177,   178,   178,   178,   178,   178,
     179,   179,   180,   180,   181,   181,   181,   181,   181,   181,
     181,   182,   182,   182,   182,   182,   182,   182,   183,   183,
     183,   183,   184,   184,   185,   185,   186,   186
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     3,     2,     3,     2,     0,     1,     1,     3,
       4,     5,     6,     2,     0,     2,     2,     1,     3,     5,
       3,     2,     3,     1,     2,     2,     1,     1,     5,     4,
       4,     3,     5,     4,     1,     0,     1,     1,     4,     3,
       1,     3,     3,     4,     1,     2,     2,     2,     2,     2,
       2,     2,     2,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     1,     3,     3,
       1,     1,     1,     1,     3,     1,     2,     1,     1,     1,
       2,     3,     1,     2,     3,     1,     2,     1,     1,     1,
       1,     8,     6,     2,     0,     1,     1,     1,     1,     1,
       3,     2,     1,     3,     2,     1,     3,     1,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     3,     0,
       2,     2,     1,     1,     5,     3,     1,     3,     1,     3,
       1,     3,     2,     1,     1,     1,     1,     3,     4,     3,
       2,     3,     2,     1,     2,     2,     1,     3,     2,     1,
       5,     3,     5,     3,     2,     1,     2,     1,     1,     1,
       1,     7,     4,     1,     3,     1,     1,     1,     1,     1,
       1,     0,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     2,     3
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
        case 4:
#line 72 "ToyParser.y" /* yacc.c:1646  */
    { debugInfo("Reduced PackageDecl"); }
#line 1935 "ToyParser.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 76 "ToyParser.y" /* yacc.c:1646  */
    { debugInfo("Reduced ImportDeclListOptional"); }
#line 1941 "ToyParser.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 97 "ToyParser.y" /* yacc.c:1646  */
    { debugInfo("Reduced TypeDeclListOptional"); }
#line 1947 "ToyParser.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 102 "ToyParser.y" /* yacc.c:1646  */
    { debugInfo("Reduced TypeDecl"); }
#line 1953 "ToyParser.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 103 "ToyParser.y" /* yacc.c:1646  */
    { debugInfo("This is an Interface declaration"); }
#line 1959 "ToyParser.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 108 "ToyParser.y" /* yacc.c:1646  */
    { debugInfo("Reduced ClassDecl"); }
#line 1965 "ToyParser.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 119 "ToyParser.y" /* yacc.c:1646  */
    { debugInfo("Reduced ClassBody"); }
#line 1971 "ToyParser.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 123 "ToyParser.y" /* yacc.c:1646  */
    { debugInfo("the last classbodydecl"); }
#line 1977 "ToyParser.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 124 "ToyParser.y" /* yacc.c:1646  */
    { debugInfo("create one classbodydecl"); }
#line 1983 "ToyParser.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 128 "ToyParser.y" /* yacc.c:1646  */
    { debugInfo("Reduced ClassBodyDecl"); }
#line 1989 "ToyParser.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 134 "ToyParser.y" /* yacc.c:1646  */
    { debugInfo("three things all up"); }
#line 1995 "ToyParser.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 151 "ToyParser.y" /* yacc.c:1646  */
    { debugInfo("do local variable decl"); }
#line 2001 "ToyParser.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 164 "ToyParser.y" /* yacc.c:1646  */
    { debugInfo("."); debugInfo((yyvsp[0].string)); }
#line 2007 "ToyParser.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 165 "ToyParser.y" /* yacc.c:1646  */
    { debugInfo("."); debugInfo("methodCall"); }
#line 2013 "ToyParser.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 168 "ToyParser.y" /* yacc.c:1646  */
    { debugInfo("self increment"); }
#line 2019 "ToyParser.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 169 "ToyParser.y" /* yacc.c:1646  */
    { debugInfo("self decrement"); }
#line 2025 "ToyParser.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 179 "ToyParser.y" /* yacc.c:1646  */
    { debugInfo("add up"); }
#line 2031 "ToyParser.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 184 "ToyParser.y" /* yacc.c:1646  */
    { debugInfo("lessthan expression"); }
#line 2037 "ToyParser.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 229 "ToyParser.y" /* yacc.c:1646  */
    { debugInfo((yyvsp[0].string)); }
#line 2043 "ToyParser.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 235 "ToyParser.y" /* yacc.c:1646  */
    { debugInfo("Reduced ModifierList"); }
#line 2049 "ToyParser.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 236 "ToyParser.y" /* yacc.c:1646  */
    { debugInfo("Reduced ModifierList"); }
#line 2055 "ToyParser.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 250 "ToyParser.y" /* yacc.c:1646  */
    { debugInfo("it has something in methodbody"); }
#line 2061 "ToyParser.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 267 "ToyParser.y" /* yacc.c:1646  */
    { debugInfo("variable decl in class"); }
#line 2067 "ToyParser.tab.c" /* yacc.c:1646  */
    break;

  case 120:
#line 304 "ToyParser.y" /* yacc.c:1646  */
    { debugInfo("params"); }
#line 2073 "ToyParser.tab.c" /* yacc.c:1646  */
    break;

  case 133:
#line 335 "ToyParser.y" /* yacc.c:1646  */
    { debugInfo("int"); }
#line 2079 "ToyParser.tab.c" /* yacc.c:1646  */
    break;

  case 142:
#line 357 "ToyParser.y" /* yacc.c:1646  */
    { debugInfo("Reduced TypeTypeOrVoid"); }
#line 2085 "ToyParser.tab.c" /* yacc.c:1646  */
    break;

  case 143:
#line 358 "ToyParser.y" /* yacc.c:1646  */
    { debugInfo("Reduced TypeTypeOrVoid"); }
#line 2091 "ToyParser.tab.c" /* yacc.c:1646  */
    break;

  case 161:
#line 408 "ToyParser.y" /* yacc.c:1646  */
    { debugInfo("it has something in block"); }
#line 2097 "ToyParser.tab.c" /* yacc.c:1646  */
    break;

  case 163:
#line 413 "ToyParser.y" /* yacc.c:1646  */
    { debugInfo("last blockstatement"); }
#line 2103 "ToyParser.tab.c" /* yacc.c:1646  */
    break;

  case 164:
#line 414 "ToyParser.y" /* yacc.c:1646  */
    { debugInfo("create one blockstatement"); }
#line 2109 "ToyParser.tab.c" /* yacc.c:1646  */
    break;

  case 165:
#line 418 "ToyParser.y" /* yacc.c:1646  */
    { debugInfo("decl variable in method"); }
#line 2115 "ToyParser.tab.c" /* yacc.c:1646  */
    break;

  case 166:
#line 419 "ToyParser.y" /* yacc.c:1646  */
    { debugInfo("this is a statement"); }
#line 2121 "ToyParser.tab.c" /* yacc.c:1646  */
    break;

  case 170:
#line 431 "ToyParser.y" /* yacc.c:1646  */
    { debugInfo("if () else ()"); }
#line 2127 "ToyParser.tab.c" /* yacc.c:1646  */
    break;

  case 172:
#line 433 "ToyParser.y" /* yacc.c:1646  */
    { debugInfo("for statement"); }
#line 2133 "ToyParser.tab.c" /* yacc.c:1646  */
    break;

  case 174:
#line 435 "ToyParser.y" /* yacc.c:1646  */
    { debugInfo("return;"); }
#line 2139 "ToyParser.tab.c" /* yacc.c:1646  */
    break;

  case 177:
#line 442 "ToyParser.y" /* yacc.c:1646  */
    { debugInfo("Reduced MemberDecl"); }
#line 2145 "ToyParser.tab.c" /* yacc.c:1646  */
    break;

  case 178:
#line 443 "ToyParser.y" /* yacc.c:1646  */
    { debugInfo("Reduced from FieldDecl"); }
#line 2151 "ToyParser.tab.c" /* yacc.c:1646  */
    break;

  case 182:
#line 452 "ToyParser.y" /* yacc.c:1646  */
    { debugInfo("Reduced MethodDecl"); }
#line 2157 "ToyParser.tab.c" /* yacc.c:1646  */
    break;

  case 183:
#line 459 "ToyParser.y" /* yacc.c:1646  */
    { debugInfo((yyvsp[0].string)); }
#line 2163 "ToyParser.tab.c" /* yacc.c:1646  */
    break;

  case 184:
#line 460 "ToyParser.y" /* yacc.c:1646  */
    { debugInfo("."); debugInfo((yyvsp[0].string)); }
#line 2169 "ToyParser.tab.c" /* yacc.c:1646  */
    break;

  case 190:
#line 474 "ToyParser.y" /* yacc.c:1646  */
    { debugInfo("Reduced ClassOrInterfaceModifierListOptional"); }
#line 2175 "ToyParser.tab.c" /* yacc.c:1646  */
    break;

  case 194:
#line 484 "ToyParser.y" /* yacc.c:1646  */
    { debugInfo("public"); }
#line 2181 "ToyParser.tab.c" /* yacc.c:1646  */
    break;

  case 195:
#line 485 "ToyParser.y" /* yacc.c:1646  */
    { debugInfo("private"); }
#line 2187 "ToyParser.tab.c" /* yacc.c:1646  */
    break;

  case 196:
#line 486 "ToyParser.y" /* yacc.c:1646  */
    { debugInfo("protected"); }
#line 2193 "ToyParser.tab.c" /* yacc.c:1646  */
    break;

  case 197:
#line 487 "ToyParser.y" /* yacc.c:1646  */
    { debugInfo("static"); }
#line 2199 "ToyParser.tab.c" /* yacc.c:1646  */
    break;

  case 198:
#line 488 "ToyParser.y" /* yacc.c:1646  */
    { debugInfo("abstract"); }
#line 2205 "ToyParser.tab.c" /* yacc.c:1646  */
    break;

  case 199:
#line 489 "ToyParser.y" /* yacc.c:1646  */
    { debugInfo("final"); }
#line 2211 "ToyParser.tab.c" /* yacc.c:1646  */
    break;

  case 200:
#line 490 "ToyParser.y" /* yacc.c:1646  */
    { debugInfo("strictfp"); }
#line 2217 "ToyParser.tab.c" /* yacc.c:1646  */
    break;


#line 2221 "ToyParser.tab.c" /* yacc.c:1646  */
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
#line 528 "ToyParser.y" /* yacc.c:1906  */


// Hello
#define  YYFPRINTF (stderr, format, args) fprintf(, "11");
int main(){
	#define YYDEBUG 1
#ifdef YYDEBUG
  yydebug = 1;
#endif
	cout << yydebug << endl;
	yyparse();
}
