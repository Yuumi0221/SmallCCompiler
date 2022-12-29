
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 3 "smallC.y"

#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<memory.h>
#include<string.h>

#define bool int
#define true 1
#define false 0

#define txmax 100     /* 符号表容量 */
#define al 10         /* 标识符的最大长度 */
#define amax 2048     /* 地址上界*/
#define levmax 3      /* 最大允许过程嵌套声明层数*/
#define cxmax 200     /* 最多的虚拟机代码数 */
#define stacksize 500 /* 运行时数据栈元素最多为500个 */

/* 符号表中的类型 */
enum object {
    constant, 
    variable, 
    procedure,
};

/* 符号表结构 */
struct tablestruct
{
   char name[al];      /* 名字 */
   enum object kind;   /* 类型：const，var或procedure */
   int val;            /* 数值，仅const使用 */
	 int level;          /* 所处层，仅const不使用 */ 
	 int adr;            /* 地址，仅const不使用 */
	 int size;           /* 需要分配的数据区空间, 仅procedure使用 */
};
struct tablestruct table[txmax]; /* 符号表 */

/* 虚拟机代码指令 */
enum fct {
    lit,     opr,     lod, 
    sto,     cal,     ini, 
    jmp,     jpc,     jpn,
};

/* 虚拟机代码结构 */
struct instruction
{
	enum fct f;   /* 虚拟机代码指令 */
	int l;        /* 引用层与声明层的层次差 */
	int a;        /* 根据f的不同而不同 */
};
struct instruction code[cxmax]; /* 存放虚拟机代码的数组 */

int tx;         /* 符号表当前尾指针 */
int cx;         /* 虚拟机代码指针, 取值范围[0, cxmax-1] */
int px;         /* 嵌套过程索引表proctable的指针 */
int lev;        /* 层次记录 */
int proctable[3];   /* 嵌套过程索引表，最多嵌套三层 */
char id[al];
int num;
bool listswitch;   /* 显示虚拟机代码与否 */
bool tableswitch;  /* 显示符号表与否 */

FILE* fin;      /* 输入源文件 */
FILE* ftable;	  /* 输出符号表 */
FILE* fcode;    /* 输出虚拟机代码 */
FILE* foutput;  /* 输出出错示意（如有错） */
FILE* fresult;  /* 输出执行结果 */
FILE* finput;	/* 输入内容 */
char fname[al];
int err;
extern int line; 

void init();
void enter(enum object k);
int position(char *s);
void setdx(int n);
void gen(enum fct x, int y, int z);
void listall();
void displaytable();
void interpret();
int base(int l, int* s, int b);

int yylex(void);
void yyerror(char *s);
int redirectInput(FILE*);


/* Line 189 of yacc.c  */
#line 162 "y.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     CALLSYM = 258,
     CONSTSYM = 259,
     IFSYM = 260,
     PROCSYM = 261,
     READSYM = 262,
     INTSYM = 263,
     WHILESYM = 264,
     WRITESYM = 265,
     FORSYM = 266,
     DOSYM = 267,
     WHENSYM = 268,
     REPEATSYM = 269,
     UNTILSYM = 270,
     LSS = 271,
     LEQ = 272,
     GTR = 273,
     GEQ = 274,
     PLUS = 275,
     MINUS = 276,
     TIMES = 277,
     SLASH = 278,
     LPAREN = 279,
     RPAREN = 280,
     EQL = 281,
     COMMA = 282,
     PERIOD = 283,
     NEQ = 284,
     SEMICOLON = 285,
     NOT = 286,
     EQUALS = 287,
     ELSESYM = 288,
     LBRACE = 289,
     RBRACE = 290,
     MOD = 291,
     XOR = 292,
     ODDSYM = 293,
     MOREPLUS = 294,
     MOREMINUS = 295,
     AND = 296,
     OR = 297,
     CONTINUESYM = 298,
     EXITSYM = 299,
     BREAKSYM = 300,
     LOWER_THAN_ELSE = 301,
     LOWER_THAN_MORE = 302,
     LOWER_THAN_SEMICOLON = 303,
     IDENT = 304,
     NUMBER = 305
   };
#endif
/* Tokens.  */
#define CALLSYM 258
#define CONSTSYM 259
#define IFSYM 260
#define PROCSYM 261
#define READSYM 262
#define INTSYM 263
#define WHILESYM 264
#define WRITESYM 265
#define FORSYM 266
#define DOSYM 267
#define WHENSYM 268
#define REPEATSYM 269
#define UNTILSYM 270
#define LSS 271
#define LEQ 272
#define GTR 273
#define GEQ 274
#define PLUS 275
#define MINUS 276
#define TIMES 277
#define SLASH 278
#define LPAREN 279
#define RPAREN 280
#define EQL 281
#define COMMA 282
#define PERIOD 283
#define NEQ 284
#define SEMICOLON 285
#define NOT 286
#define EQUALS 287
#define ELSESYM 288
#define LBRACE 289
#define RBRACE 290
#define MOD 291
#define XOR 292
#define ODDSYM 293
#define MOREPLUS 294
#define MOREMINUS 295
#define AND 296
#define OR 297
#define CONTINUESYM 298
#define EXITSYM 299
#define BREAKSYM 300
#define LOWER_THAN_ELSE 301
#define LOWER_THAN_MORE 302
#define LOWER_THAN_SEMICOLON 303
#define IDENT 304
#define NUMBER 305




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 93 "smallC.y"

char *ident;
int number;



/* Line 214 of yacc.c  */
#line 305 "y.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 317 "y.tab.c"

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
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
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
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   203

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  51
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  51
/* YYNRULES -- Number of rules.  */
#define YYNRULES  99
/* YYNRULES -- Number of states.  */
#define YYNSTATES  176

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   305

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
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
      45,    46,    47,    48,    49,    50
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     6,     7,     8,    19,    23,    26,
      27,    29,    33,    37,    41,    44,    45,    47,    51,    53,
      57,    58,    63,    68,    70,    71,    73,    76,    78,    80,
      82,    84,    86,    88,    90,    92,    94,    96,    98,   102,
     105,   107,   109,   113,   115,   117,   120,   121,   122,   133,
     136,   137,   138,   147,   155,   163,   164,   165,   166,   183,
     187,   188,   191,   194,   196,   200,   203,   205,   209,   213,
     215,   218,   222,   226,   230,   234,   238,   242,   246,   249,
     252,   254,   258,   262,   264,   268,   272,   276,   278,   281,
     284,   287,   289,   291,   295,   297,   298,   299,   300,   301
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      52,     0,    -1,    53,    -1,    -1,    -1,    -1,    54,    97,
      34,    57,    60,    63,    55,    66,    56,    35,    -1,     4,
      58,    30,    -1,     4,    58,    -1,    -1,    59,    -1,    58,
      27,    59,    -1,    49,    26,    50,    -1,     8,    61,    30,
      -1,     8,    61,    -1,    -1,    62,    -1,    61,    27,    62,
      -1,    49,    -1,    63,    64,    65,    -1,    -1,   100,     6,
      49,    30,    -1,    99,    53,   101,    30,    -1,    67,    -1,
      -1,    68,    -1,    67,    68,    -1,    73,    -1,    69,    -1,
      74,    -1,    78,    -1,    87,    -1,    89,    -1,    70,    -1,
      72,    -1,    82,    -1,    80,    -1,    81,    -1,    34,    66,
      35,    -1,    71,    30,    -1,    71,    -1,    30,    -1,    96,
      26,    90,    -1,    90,    -1,    44,    -1,     3,    96,    -1,
      -1,    -1,     5,    24,    71,    25,    98,    75,    68,    98,
      76,    77,    -1,    33,    68,    -1,    -1,    -1,     9,    98,
      24,    71,    25,    98,    79,    68,    -1,    12,    98,    68,
      13,    24,    71,    25,    -1,    14,    98,    68,    15,    24,
      71,    25,    -1,    -1,    -1,    -1,    11,    24,    86,    30,
      98,    71,    98,    83,    30,    98,    84,    98,    71,    85,
      25,    68,    -1,    96,    26,    90,    -1,    -1,     7,    88,
      -1,    96,    30,    -1,    96,    -1,    10,    71,    30,    -1,
      10,    71,    -1,    91,    -1,    91,    41,    91,    -1,    91,
      42,    91,    -1,    92,    -1,    38,    92,    -1,    92,    16,
      92,    -1,    92,    17,    92,    -1,    92,    18,    92,    -1,
      92,    19,    92,    -1,    92,    32,    92,    -1,    92,    29,
      92,    -1,    92,    37,    92,    -1,    20,    93,    -1,    21,
      93,    -1,    93,    -1,    92,    20,    93,    -1,    92,    21,
      93,    -1,    94,    -1,    93,    22,    94,    -1,    93,    23,
      94,    -1,    93,    36,    94,    -1,    95,    -1,    31,    95,
      -1,    96,    39,    -1,    96,    40,    -1,    96,    -1,    50,
      -1,    24,    71,    25,    -1,    49,    -1,    -1,    -1,    -1,
      -1,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   126,   126,   129,   136,   144,   129,   152,   153,   157,
     161,   162,   166,   175,   180,   187,   193,   197,   204,   213,
     214,   218,   227,   231,   232,   236,   237,   241,   242,   243,
     244,   245,   246,   247,   248,   249,   250,   251,   257,   260,
     261,   265,   269,   281,   285,   292,   308,   312,   307,   323,
     324,   329,   328,   340,   347,   369,   373,   377,   368,   389,
     401,   405,   409,   414,   423,   428,   437,   438,   442,   449,
     450,   454,   458,   462,   466,   470,   474,   478,   485,   486,
     490,   491,   495,   502,   503,   507,   511,   518,   519,   526,
     546,   566,   582,   586,   588,   594,   599,   605,   612,   617
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "CALLSYM", "CONSTSYM", "IFSYM",
  "PROCSYM", "READSYM", "INTSYM", "WHILESYM", "WRITESYM", "FORSYM",
  "DOSYM", "WHENSYM", "REPEATSYM", "UNTILSYM", "LSS", "LEQ", "GTR", "GEQ",
  "PLUS", "MINUS", "TIMES", "SLASH", "LPAREN", "RPAREN", "EQL", "COMMA",
  "PERIOD", "NEQ", "SEMICOLON", "NOT", "EQUALS", "ELSESYM", "LBRACE",
  "RBRACE", "MOD", "XOR", "ODDSYM", "MOREPLUS", "MOREMINUS", "AND", "OR",
  "CONTINUESYM", "EXITSYM", "BREAKSYM", "LOWER_THAN_ELSE",
  "LOWER_THAN_MORE", "LOWER_THAN_SEMICOLON", "IDENT", "NUMBER", "$accept",
  "program", "block", "@1", "$@2", "$@3", "constdecl", "constlist",
  "constdef", "vardecl", "varlist", "vardef", "procdecls", "procdecl",
  "procbody", "statement_decl", "statement_list", "statement",
  "compound_stat", "expression_stat", "expression", "exit_stat", "callstm",
  "if_stat", "$@4", "$@5", "else_stat", "while_stat", "$@6",
  "do_when_stat", "repeat_until_stat", "for_stat", "$@7", "$@8", "$@9",
  "for_init", "read_stat", "readvar", "write_stat", "andOr_expr",
  "bool_expr", "additive_expr", "term", "notTerm", "factor", "ident",
  "get_table_addr", "get_code_addr", "inc_level", "inc_px", "dec_level_px", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    51,    52,    54,    55,    56,    53,    57,    57,    57,
      58,    58,    59,    60,    60,    60,    61,    61,    62,    63,
      63,    64,    65,    66,    66,    67,    67,    68,    68,    68,
      68,    68,    68,    68,    68,    68,    68,    68,    69,    70,
      70,    70,    71,    71,    72,    73,    75,    76,    74,    77,
      77,    79,    78,    80,    81,    83,    84,    85,    82,    86,
      86,    87,    88,    88,    89,    89,    90,    90,    90,    91,
      91,    91,    91,    91,    91,    91,    91,    91,    92,    92,
      92,    92,    92,    93,    93,    93,    93,    94,    94,    95,
      95,    95,    95,    95,    96,    97,    98,    99,   100,   101
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     0,     0,    10,     3,     2,     0,
       1,     3,     3,     3,     2,     0,     1,     3,     1,     3,
       0,     4,     4,     1,     0,     1,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     2,
       1,     1,     3,     1,     1,     2,     0,     0,    10,     2,
       0,     0,     8,     7,     7,     0,     0,     0,    16,     3,
       0,     2,     2,     1,     3,     2,     1,     3,     3,     1,
       2,     3,     3,     3,     3,     3,     3,     3,     2,     2,
       1,     3,     3,     1,     3,     3,     3,     1,     2,     2,
       2,     1,     1,     3,     1,     0,     0,     0,     0,     0
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     2,    95,     1,     0,     9,     0,    15,     0,
       8,    10,     0,    20,     0,     0,     7,    18,    14,    16,
       4,    12,    11,     0,    13,    24,    97,     0,    17,     0,
       0,     0,    96,     0,     0,    96,    96,     0,     0,     0,
      41,     0,    24,     0,    44,    94,    92,     5,    23,    25,
      28,    33,    40,    34,    27,    29,    30,    36,    37,    35,
      31,    32,    43,    66,    69,    80,    83,    87,    91,    19,
       3,     0,    45,     0,    61,    63,     0,    65,    60,     0,
       0,    78,    91,    79,     0,    88,     0,    70,     0,    26,
      39,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    89,    90,    99,     0,
       0,    62,     0,    64,     0,     0,     0,     0,    93,    38,
       6,    67,    68,    71,    72,    73,    74,    81,    82,    76,
      75,    77,    84,    85,    86,    42,     0,    21,    96,     0,
      96,     0,     0,     0,    22,    46,    96,     0,    59,     0,
       0,     0,    51,    96,     0,     0,    96,     0,    55,    53,
      54,    47,    52,     0,    50,    96,     0,    48,    56,    49,
      96,     0,    57,     0,     0,    58
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,     3,    25,    88,     8,    10,    11,    13,
      18,    19,    20,    26,    69,    47,    48,    49,    50,    51,
      52,    53,    54,    55,   151,   164,   167,    56,   157,    57,
      58,    59,   163,   170,   173,   114,    60,    74,    61,    62,
      63,    64,    65,    66,    67,    82,     5,    76,    70,    27,
     136
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -103
static const yytype_int16 yypact[] =
{
    -103,     5,  -103,  -103,  -103,   -23,    26,   -29,    38,    62,
      -8,  -103,    15,  -103,    39,   -29,  -103,  -103,     2,  -103,
      84,  -103,  -103,    15,  -103,   153,  -103,    85,  -103,    43,
      69,    43,  -103,     7,    71,  -103,  -103,    11,    11,     7,
    -103,    -6,   153,    16,  -103,  -103,  -103,  -103,   153,  -103,
    -103,  -103,    66,  -103,  -103,  -103,  -103,  -103,  -103,  -103,
    -103,  -103,  -103,   -26,    65,   -10,  -103,  -103,    23,  -103,
    -103,    49,  -103,     7,  -103,    70,    75,    73,    43,   153,
     153,   -10,    19,   -10,    76,  -103,    72,    47,    74,  -103,
    -103,     7,     7,    16,    16,    16,    16,    11,    11,    16,
      16,    16,    11,    11,    11,     7,  -103,  -103,  -103,    78,
      79,  -103,     7,  -103,    80,    86,    93,    98,  -103,  -103,
    -103,  -103,  -103,    47,    47,    47,    47,   -10,   -10,    47,
      47,    47,  -103,  -103,  -103,  -103,    89,  -103,  -103,    91,
    -103,     7,    90,    97,  -103,  -103,  -103,     7,  -103,     7,
       7,   153,  -103,  -103,   105,   106,  -103,   153,  -103,  -103,
    -103,  -103,  -103,   103,   101,  -103,   153,  -103,  -103,  -103,
    -103,     7,  -103,   111,   153,  -103
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -103,  -103,    53,  -103,  -103,  -103,  -103,  -103,   122,  -103,
    -103,   115,  -103,  -103,  -103,   102,  -103,   -46,  -103,  -103,
     -32,  -103,  -103,  -103,  -103,  -103,  -103,  -103,  -103,  -103,
    -103,  -103,  -103,  -103,  -103,  -103,  -103,  -103,  -103,  -102,
     -16,   -22,   -28,   -52,    99,   -25,  -103,   -11,  -103,  -103,
    -103
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -99
static const yytype_int16 yytable[] =
{
      68,    77,    89,   135,    72,     4,    75,    84,    68,    81,
      83,     6,   102,   103,    68,    91,    92,    68,    39,    15,
       9,    87,    16,    68,    79,    80,   104,    37,    38,    23,
       7,    39,    24,   116,   117,    39,    37,    38,    41,   148,
      39,   110,    41,    45,    46,    43,    12,    41,    68,   105,
     132,   133,   134,   115,    68,    68,    45,    46,   106,   107,
      45,    46,   106,   107,    17,    45,    46,    97,    98,   127,
     128,   123,   124,   125,   126,   121,   122,   129,   130,   131,
     139,    93,    94,    95,    96,    97,    98,    68,    14,    21,
     -98,    71,    45,    73,    99,    78,    90,   100,   109,   112,
     111,   118,   101,   113,   138,   156,   142,   119,   137,   120,
     140,   162,   141,   143,   149,   153,   146,   154,   155,   144,
     169,   150,    68,   108,    68,    68,    68,   145,   175,   147,
     159,   160,    68,   165,   166,   152,   174,    22,    28,   172,
      85,    68,   158,     0,    86,   161,    68,     0,     0,    68,
       0,     0,     0,     0,   168,     0,    29,     0,    30,   171,
      31,     0,    32,    33,    34,    35,     0,    36,     0,     0,
       0,     0,     0,    37,    38,     0,     0,    39,     0,     0,
       0,     0,     0,    40,    41,     0,     0,    42,     0,     0,
       0,    43,     0,     0,     0,     0,     0,    44,     0,     0,
       0,     0,    45,    46
};

static const yytype_int16 yycheck[] =
{
      25,    33,    48,   105,    29,     0,    31,    39,    33,    37,
      38,    34,    22,    23,    39,    41,    42,    42,    24,    27,
      49,    43,    30,    48,    35,    36,    36,    20,    21,    27,
       4,    24,    30,    79,    80,    24,    20,    21,    31,   141,
      24,    73,    31,    49,    50,    38,     8,    31,    73,    26,
     102,   103,   104,    78,    79,    80,    49,    50,    39,    40,
      49,    50,    39,    40,    49,    49,    50,    20,    21,    97,
      98,    93,    94,    95,    96,    91,    92,    99,   100,   101,
     112,    16,    17,    18,    19,    20,    21,   112,    26,    50,
       6,     6,    49,    24,    29,    24,    30,    32,    49,    24,
      30,    25,    37,    30,    25,   151,    13,    35,    30,    35,
      30,   157,    26,    15,    24,   147,    25,   149,   150,    30,
     166,    24,   147,    70,   149,   150,   151,   138,   174,   140,
      25,    25,   157,    30,    33,   146,    25,    15,    23,   171,
      41,   166,   153,    -1,    42,   156,   171,    -1,    -1,   174,
      -1,    -1,    -1,    -1,   165,    -1,     3,    -1,     5,   170,
       7,    -1,     9,    10,    11,    12,    -1,    14,    -1,    -1,
      -1,    -1,    -1,    20,    21,    -1,    -1,    24,    -1,    -1,
      -1,    -1,    -1,    30,    31,    -1,    -1,    34,    -1,    -1,
      -1,    38,    -1,    -1,    -1,    -1,    -1,    44,    -1,    -1,
      -1,    -1,    49,    50
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    52,    53,    54,     0,    97,    34,     4,    57,    49,
      58,    59,     8,    60,    26,    27,    30,    49,    61,    62,
      63,    50,    59,    27,    30,    55,    64,   100,    62,     3,
       5,     7,     9,    10,    11,    12,    14,    20,    21,    24,
      30,    31,    34,    38,    44,    49,    50,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    78,    80,    81,    82,
      87,    89,    90,    91,    92,    93,    94,    95,    96,    65,
      99,     6,    96,    24,    88,    96,    98,    71,    24,    98,
      98,    93,    96,    93,    71,    95,    66,    92,    56,    68,
      30,    41,    42,    16,    17,    18,    19,    20,    21,    29,
      32,    37,    22,    23,    36,    26,    39,    40,    53,    49,
      71,    30,    24,    30,    86,    96,    68,    68,    25,    35,
      35,    91,    91,    92,    92,    92,    92,    93,    93,    92,
      92,    92,    94,    94,    94,    90,   101,    30,    25,    71,
      30,    26,    13,    15,    30,    98,    25,    98,    90,    24,
      24,    75,    98,    71,    71,    71,    68,    79,    98,    25,
      25,    98,    68,    83,    76,    30,    33,    77,    98,    68,
      84,    98,    71,    85,    25,    68
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
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
  int yytoken;
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

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

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
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
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
  *++yyvsp = yylval;

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
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 3:

/* Line 1455 of yacc.c  */
#line 129 "smallC.y"
    {               
                table[tx].adr = cx;				  /* 记录当前层代码的开始位置 */  
                (yyval.number) = cx;
               	gen(jmp, 0 , 0);            /* 产生跳转指令，跳转位置未知暂时填0 */
               }
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 136 "smallC.y"
    {
               	code[(yyvsp[(1) - (6)].number)].a = cx;            /* 把前面生成的跳转语句的跳转位置改成当前位置 */
               	table[(yyvsp[(2) - (6)].number)].adr = cx;         /* 记录当前过程代码地址 */
               	table[(yyvsp[(2) - (6)].number)].size = (yyvsp[(5) - (6)].number) + 3;    /* 记录当前过程分配数据大小 */
               	gen(ini, 0, (yyvsp[(5) - (6)].number) + 3);
               	displaytable();
               }
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 144 "smallC.y"
    {
               	gen(opr, 0 , 0);               	
               	tx = proctable[px];
               }
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 154 "smallC.y"
    {
				yyerror("You may have missed a ';'");
			}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 167 "smallC.y"
    {
               	strcpy(id,(yyvsp[(1) - (3)].ident));   
               	num = (yyvsp[(3) - (3)].number);
               	enter(constant);
               }
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 176 "smallC.y"
    {
                (yyval.number) = (yyvsp[(2) - (3)].number);         /* 传递变量声明的个数 */
                setdx((yyvsp[(2) - (3)].number));       /* 分配变量相对地址 */
            }
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 181 "smallC.y"
    {
                (yyval.number) = (yyvsp[(2) - (2)].number);         /* 传递变量声明的个数 */
                setdx((yyvsp[(2) - (2)].number));       /* 分配变量相对地址 */
				yyerror("You may have missed a ';'");
               }
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 187 "smallC.y"
    {
          		(yyval.number) = 0;          /* 没有变量声明 */
          	}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 194 "smallC.y"
    {
               	(yyval.number) = (yyvsp[(1) - (1)].number);
               }
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 198 "smallC.y"
    {
               	(yyval.number) = (yyvsp[(1) - (3)].number) + (yyvsp[(3) - (3)].number);  /* 变量声明的个数相加 */
               }
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 205 "smallC.y"
    {
              	strcpy(id, (yyvsp[(1) - (1)].ident)); 
              	enter(variable); 
              	(yyval.number) = 1;
            }
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 219 "smallC.y"
    {                 
                 strcpy(id, (yyvsp[(3) - (4)].ident));
	               enter(procedure); 
	               proctable[px] = tx;                
               }
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 262 "smallC.y"
    {
						yyerror("You may have missed a ';'");
					}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 270 "smallC.y"
    {
                 if ((yyvsp[(1) - (3)].number) == 0)
                       yyerror("Symbol does not exist");
                 else
                    {
                       if (table[(yyvsp[(1) - (3)].number)].kind != variable)
                           yyerror("Symbol should be a variable");
                       else
                           gen(sto, lev - table[(yyvsp[(1) - (3)].number)].level, table[(yyvsp[(1) - (3)].number)].adr);
                    }
               }
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 286 "smallC.y"
    {
				gen(jmp, 0 , 0);
			}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 293 "smallC.y"
    {
                 if ((yyvsp[(2) - (2)].number) == 0)
                       yyerror("call Symbol does not exist");
                 else
                    {
                       if (table[(yyvsp[(2) - (2)].number)].kind != procedure)
                           yyerror("Symbol should be a procedure");
                       else
                           gen (cal, lev - table[(yyvsp[(2) - (2)].number)].level, table[(yyvsp[(2) - (2)].number)].adr);    
                    }
              }
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 308 "smallC.y"
    {
               	gen(jpc, 0, 0);
               }
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 312 "smallC.y"
    {
				gen(jmp, 0, 0);
               	code[(yyvsp[(5) - (8)].number)].a = cx;
               }
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 317 "smallC.y"
    {
				code[(yyvsp[(8) - (10)].number)].a = cx;
			   }
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 329 "smallC.y"
    {
               	gen(jpc, 0 , 0);
               }
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 333 "smallC.y"
    {
               	gen(jmp, 0, (yyvsp[(2) - (8)].number));
               	code[(yyvsp[(6) - (8)].number)].a = cx;
               }
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 341 "smallC.y"
    {
						gen(jpn, 0 , (yyvsp[(2) - (7)].number));
					}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 348 "smallC.y"
    {
						gen(jpc, 0 , (yyvsp[(2) - (7)].number));
					}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 369 "smallC.y"
    {
               	gen(jpc, 0 , 0);
               }
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 373 "smallC.y"
    {
				gen(jmp, 0, 0);
			   }
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 377 "smallC.y"
    {
				gen(jmp, 0, (yyvsp[(5) - (13)].number));
				code[(yyvsp[(10) - (13)].number)].a = cx;
			   }
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 382 "smallC.y"
    {
               	gen(jmp, 0, (yyvsp[(12) - (16)].number));
               	code[(yyvsp[(7) - (16)].number)].a = cx;
               }
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 390 "smallC.y"
    {
                 if ((yyvsp[(1) - (3)].number) == 0)
                       yyerror("Symbol does not exist");
                 else
                    {
                       if (table[(yyvsp[(1) - (3)].number)].kind != variable)
                           yyerror("Symbol should be a variable");
                       else
                           gen(sto, lev - table[(yyvsp[(1) - (3)].number)].level, table[(yyvsp[(1) - (3)].number)].adr);
                    }
               }
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 410 "smallC.y"
    {
			 gen(opr, 0, 16);
			 gen(sto, lev - table[(yyvsp[(1) - (2)].number)].level, table[(yyvsp[(1) - (2)].number)].adr);
			}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 415 "smallC.y"
    {
			 gen(opr, 0, 16);
			 gen(sto, lev - table[(yyvsp[(1) - (1)].number)].level, table[(yyvsp[(1) - (1)].number)].adr);
			 yyerror("You may have missed a ';'");
			}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 424 "smallC.y"
    {
			 gen(opr, 0, 14);
			 gen(opr, 0, 15);
			}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 429 "smallC.y"
    {
			 gen(opr, 0, 14);
			 gen(opr, 0, 15);
			 yyerror("You may have missed a ';'");
			}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 439 "smallC.y"
    {
               	gen(opr, 0, 21);
               }
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 443 "smallC.y"
    {
               	gen(opr, 0, 22);
               }
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 451 "smallC.y"
    {
               	gen(opr, 0, 6);
               }
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 455 "smallC.y"
    {
               	gen(opr, 0, 10);
               }
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 459 "smallC.y"
    {
               	gen(opr, 0, 13);
               }
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 463 "smallC.y"
    {
               	gen(opr, 0, 12);
               }
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 467 "smallC.y"
    {
               	gen(opr, 0, 11);
               }
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 471 "smallC.y"
    {
               	gen(opr, 0, 8);
               }
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 475 "smallC.y"
    {
               	gen(opr, 0, 9);
               }
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 479 "smallC.y"
    {
               	gen(opr, 0, 18);
               }
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 487 "smallC.y"
    {
               	gen(opr, 0, 1);
               }
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 492 "smallC.y"
    {
               	gen(opr, 0, 2);
               }
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 496 "smallC.y"
    {
               	gen(opr, 0, 3);
               }
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 504 "smallC.y"
    {
		gen(opr, 0, 4);
		}
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 508 "smallC.y"
    {
		gen(opr, 0, 5);
		}
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 512 "smallC.y"
    {
		gen(opr, 0, 17);
		}
    break;

  case 88:

/* Line 1455 of yacc.c  */
#line 520 "smallC.y"
    {
			 gen(opr, 0, 7);
			}
    break;

  case 89:

/* Line 1455 of yacc.c  */
#line 527 "smallC.y"
    { if ((yyvsp[(1) - (2)].number) == 0)
					yyerror("Symbol does not exist");
				else
				{
					if (table[(yyvsp[(1) - (2)].number)].kind == procedure)
						yyerror("Symbol should not be a procedure");
					else
						{
						if(table[(yyvsp[(1) - (2)].number)].kind == constant)
							yyerror("Symbol should not be a constant");
						else{
							gen(lod, lev - table[(yyvsp[(1) - (2)].number)].level, table[(yyvsp[(1) - (2)].number)].adr);
							gen(opr, 0, 19);
							gen(sto, lev - table[(yyvsp[(1) - (2)].number)].level, table[(yyvsp[(1) - (2)].number)].adr);
							gen(lod, lev - table[(yyvsp[(1) - (2)].number)].level, table[(yyvsp[(1) - (2)].number)].adr);
						 }
						}
				}
			}
    break;

  case 90:

/* Line 1455 of yacc.c  */
#line 547 "smallC.y"
    { if ((yyvsp[(1) - (2)].number) == 0)
					yyerror("Symbol does not exist");
				else
				{
					if (table[(yyvsp[(1) - (2)].number)].kind == procedure)
						yyerror("Symbol should not be a procedure");
					else
						{
						if(table[(yyvsp[(1) - (2)].number)].kind == constant)
							yyerror("Symbol should not be a constant");
						else{
							gen(lod, lev - table[(yyvsp[(1) - (2)].number)].level, table[(yyvsp[(1) - (2)].number)].adr);
							gen(opr, 0, 20);
							gen(sto, lev - table[(yyvsp[(1) - (2)].number)].level, table[(yyvsp[(1) - (2)].number)].adr);
							gen(lod, lev - table[(yyvsp[(1) - (2)].number)].level, table[(yyvsp[(1) - (2)].number)].adr);
						 }
						}
				}
			}
    break;

  case 91:

/* Line 1455 of yacc.c  */
#line 567 "smallC.y"
    { if ((yyvsp[(1) - (1)].number) == 0)
					yyerror("Symbol does not exist");
				else
				{
					if (table[(yyvsp[(1) - (1)].number)].kind == procedure)
						yyerror("Symbol should not be a procedure");
					else
						{
							if(table[(yyvsp[(1) - (1)].number)].kind == constant)
							gen(lit, 0, table[(yyvsp[(1) - (1)].number)].val);
						else
							gen(lod, lev - table[(yyvsp[(1) - (1)].number)].level, table[(yyvsp[(1) - (1)].number)].adr);
						}
				}
			}
    break;

  case 92:

/* Line 1455 of yacc.c  */
#line 583 "smallC.y"
    {
			 gen(lit, 0, (yyvsp[(1) - (1)].number));
			}
    break;

  case 94:

/* Line 1455 of yacc.c  */
#line 589 "smallC.y"
    {
                (yyval.number) = position ((yyvsp[(1) - (1)].ident)); 
               }
    break;

  case 95:

/* Line 1455 of yacc.c  */
#line 594 "smallC.y"
    {
                (yyval.number) = tx;
               }
    break;

  case 96:

/* Line 1455 of yacc.c  */
#line 599 "smallC.y"
    {
               	(yyval.number) = cx;
               }
    break;

  case 97:

/* Line 1455 of yacc.c  */
#line 605 "smallC.y"
    {
               	lev++;               
               	if (lev > levmax)		/* 嵌套层数过多 */
                     yyerror("Lev is too big");    
               }
    break;

  case 98:

/* Line 1455 of yacc.c  */
#line 612 "smallC.y"
    {
               px++;              
              }
    break;

  case 99:

/* Line 1455 of yacc.c  */
#line 617 "smallC.y"
    {
              	lev--;
              	px--;              
              }
    break;



/* Line 1455 of yacc.c  */
#line 2314 "y.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
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

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
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

  *++yyvsp = yylval;


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

#if !defined(yyoverflow) || YYERROR_VERBOSE
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
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 626 "smallC.y"

void yyerror(char *s)
{
	err = err + 1;
    printf("%s in line %d\n", s, line);
	fprintf(foutput, "%s in line %d\n", s, line);
	/* return 0; */
}

/* 初始化 */
void init()
{
	tx = 0;
	cx = 0;
	px = 0;  
  lev = 0;   
  proctable[0] = 0;
  num = 0;
  err = 0;
}

/* 在符号表中加入一项 */
void enter(enum object k)
{
	tx = tx + 1;
	strcpy(table[tx].name, id);
	table[tx].kind = k;
	switch (k)
	{
		case constant:	/* 常量 */			
			table[tx].val = num; /* 登记常数的值 */
			break;
		case variable:	/* 变量 */
			table[tx].level = lev;	
			break;
		case procedure:	/* 过程 */
			table[tx].level = lev;
			break;
	}
}

/* 查找标识符在符号表中的位置 */
int position(char *s)
{
	int i;
	strcpy(table[0].name, s);
	i = tx;
	while(strcmp(table[i].name, s) != 0)
		i--;
	return i;
}

/* 为本层变量分配相对地址，从3开始分配 */
void setdx(int n)
{
	int i;
	for(i = 1; i <= n; i++)
		table[tx - i + 1].adr = n - i + 3;
}

/* 生成虚拟机代码 */
void gen(enum fct x, int y, int z)
{
	if (cx >= cxmax)
	{
		printf("Program is too long!\n");	/* 生成的虚拟机代码程序过长 */
		exit(1);
	}
	if ( z >= amax)
	{
		printf("Displacement address is too big!\n");	/* 地址偏移越界 */
		exit(1);
	}
	code[cx].f = x;
	code[cx].l = y;
	code[cx].a = z;
	cx++;
}

/* 输出所有目标代码  */
void listall()
{
	int i;
	char name[][5]=
	{
		{"lit"},{"opr"},{"lod"},{"sto"},{"cal"},{"int"},{"jmp"},{"jpc"},{"jpn"},
	};
	/* if (listswitch)
	{ */
		for (i = 0; i < cx; i++)
		{
			printf("%d %s %d %d\n", i, name[code[i].f], code[i].l, code[i].a);
			fprintf(fcode,"%d %s %d %d\n", i, name[code[i].f], code[i].l, code[i].a);
			
		}
	/* } */
}

/* 输出符号表 */
void displaytable()
{
	int i;
/* if (tableswitch)		// 输出符号表
	{ */
	
	for (i = 1; i <= tx; i++)
		{
			switch (table[i].kind)
			{
				case constant:
					printf("    %d const %s ", i, table[i].name);
					printf("val=%d\n", table[i].val);
					fprintf(ftable, "    %d const %s ", i, table[i].name);
					fprintf(ftable, "val=%d\n", table[i].val);
					break;
				case variable:
					printf("    %d var   %s ", i, table[i].name);
					printf("lev=%d addr=%d\n", table[i].level, table[i].adr);
					fprintf(ftable, "    %d var   %s ", i, table[i].name);
					fprintf(ftable, "lev=%d addr=%d\n", table[i].level, table[i].adr);
					break;
				case procedure:
					printf("    %d proc  %s ", i, table[i].name);
					printf("lev=%d addr=%d size=%d\n", table[i].level, table[i].adr, table[i].size);
					fprintf(ftable,"    %d proc  %s ", i, table[i].name);
					fprintf(ftable,"lev=%d addr=%d size=%d\n", table[i].level, table[i].adr, table[i].size);
					break;
			}
		}
		printf("\n");
		fprintf(ftable, "\n");
	}

/* } */

/* 解释程序 */
void interpret()
{
	int p = 0; /* 指令指针 */
	int b = 1; /* 指令基址 */
	int t = 0; /* 栈顶指针 */
	struct instruction i;	/* 存放当前指令 */
	int s[stacksize];	/* 栈 */

	printf("Start smallC\n");
	/* fprintf(fresult,"Start smallC\n"); */
	s[0] = 0; /* s[0]不用 */
	s[1] = 0; /* 主程序的三个联系单元均置为0 */
	s[2] = 0;
	s[3] = 0;
	do {
	    i = code[p];	/* 读当前指令 */
		p = p + 1;
		switch (i.f)
		{
			case lit:	/* 将常量a的值取到栈顶 */
				t = t + 1;
				s[t] = i.a;				
				break;
			case opr:	/* 数学、逻辑运算 */
				switch (i.a)
				{
					case 0:  /* 函数调用结束后返回 */
						t = b - 1;
						p = s[t + 3];
						b = s[t + 2];
						break;
					case 1: /* 栈顶元素取反 */
						s[t] = - s[t];
						break;
					case 2: /* 次栈顶项加上栈顶项，退两个栈元素，相加值进栈 */
						t = t - 1;
						s[t] = s[t] + s[t + 1];
						break;
					case 3:/* 次栈顶项减去栈顶项 */
						t = t - 1;
						s[t] = s[t] - s[t + 1];
						break;
					case 4:/* 次栈顶项乘以栈顶项 */
						t = t - 1;
						s[t] = s[t] * s[t + 1];
						break;
					case 5:/* 次栈顶项除以栈顶项 */
						t = t - 1;
						s[t] = s[t] / s[t + 1];
						break;
					case 6:/* 栈顶元素的奇偶判断 */
						s[t] = s[t] % 2;
						break;
					case 7: /* 栈顶元素取非 */
						s[t] = !s[t];
						break;
					case 8:/* 次栈顶项与栈顶项是否相等 */
						t = t - 1;
						s[t] = (s[t] == s[t + 1]);
						break;
					case 9:/* 次栈顶项与栈顶项是否不等 */
						t = t - 1;
						s[t] = (s[t] != s[t + 1]);
						break;
					case 10:/* 次栈顶项是否小于栈顶项 */
						t = t - 1;
						s[t] = (s[t] < s[t + 1]);
						break;
					case 11:/* 次栈顶项是否大于等于栈顶项 */
						t = t - 1;
						s[t] = (s[t] >= s[t + 1]);
						break;
					case 12:/* 次栈顶项是否大于栈顶项 */
						t = t - 1;
						s[t] = (s[t] > s[t + 1]);
						break;
					case 13: /* 次栈顶项是否小于等于栈顶项 */
						t = t - 1;
						s[t] = (s[t] <= s[t + 1]);
						break;
					case 14:/* 栈顶值输出 */
						printf("%d", s[t]);
						fprintf(fresult, "%d", s[t]);
						t = t - 1;
						break;
					case 15:/* 输出换行符 */
						printf("\n");
						fprintf(fresult,"\n");
						break;
					case 16:/* 读入一个输入置于栈顶 */
						t = t + 1;
						printf("?");
						/* fprintf(finput, "?"); */
						fscanf(finput, "%d", &(s[t]));
						/* fprintf(finput, "%d\n", s[t]); */
						break;
					case 17:/* 次栈顶项模栈顶项 */
						t = t - 1;
						s[t] = s[t] % s[t + 1];
						break;
					case 18:/* 次栈顶项异或栈顶项 */
						t = t - 1;
						s[t] = s[t] ^ s[t + 1];
						break;
					case 19: /* 栈顶元素自增1 */
						s[t] = s[t] + 1;
						break;
					case 20: /* 栈顶元素自减1 */
						s[t] = s[t] - 1;
						break;
					case 21:/* 次栈顶项与栈顶项逻辑与 */
						t = t - 1;
						s[t] = (s[t] && s[t + 1]);
						break;
					case 22:/* 次栈顶项与栈顶项逻辑或 */
						t = t - 1;
						s[t] = (s[t] || s[t + 1]);
						break;
				}
				break;
			case lod:	/* 取相对当前过程的数据基地址为a的内存的值到栈顶 */
				t = t + 1;
				s[t] = s[base(i.l,s,b) + i.a];				
				break;
			case sto:	/* 栈顶的值存到相对当前过程的数据基地址为a的内存 */
				s[base(i.l, s, b) + i.a] = s[t];
				t = t - 1;
				break;
			case cal:	/* 调用子过程 */
				s[t + 1] = base(i.l, s, b);	/* 将父过程基地址入栈，即建立静态链 */
				s[t + 2] = b;	/* 将本过程基地址入栈，即建立动态链 */
				s[t + 3] = p;	/* 将当前指令指针入栈，即保存返回地址 */
				b = t + 1;	/* 改变基地址指针值为新过程的基地址 */
				p = i.a;	/* 跳转 */
				break;
			case ini:	/* 在数据栈中为被调用的过程开辟a个单元的数据区 */
				t = t + i.a;	
				break;
			case jmp:	/* 直接跳转 */
				p = i.a;
				break;
			case jpc:	/* 条件跳转 */
				if (s[t] == 0) 
					p = i.a;
				t = t - 1;
				break;
			case jpn:	/* 条件跳转 */
				if (s[t] != 0) 
					p = i.a;
				t = t - 1;
				break;
		}
	} while (p != 0);
	printf("End smallC\n");
	/* fprintf(fresult,"End smallC\n"); */
}

/* 通过过程基址求上l层过程的基址 */
int base(int l, int* s, int b)
{
	int b1;
	b1 = b;
	while (l > 0)
	{
		b1 = s[b1];
		l--;
	}
	return b1;
}

int main(void)
{
	// printf("Input pl/0 file?   ");
	// scanf("%s", fname);		/* 输入文件名 */

	// if ((fin = fopen(fname, "r")) == NULL)
	if ((fin = fopen("c_o_d_e.txt", "r")) == NULL)
	{
		printf("Can't open the input file!\n");
		exit(1);
	}	
	if ((foutput = fopen("foutput.txt", "w")) == NULL)
  	{
		printf("Can't open the output file!\n");
		exit(1);
	}
	if ((ftable = fopen("ftable.txt", "w")) == NULL)
	{
		printf("Can't open ftable.txt file!\n");
		exit(1);
	}
	if ((finput = fopen("finput.txt", "r")) == NULL)
	{
		printf("Can't open finput.txt file!\n");
		exit(1);
	}
	
	/* printf("List object codes?(Y/N)");	// 是否输出虚拟机代码
	scanf("%s", fname);
	listswitch = (fname[0]=='y' || fname[0]=='Y'); */
	/* listswitch = 'y'; */

	/* printf("List symbol table?(Y/N)");	// 是否输出符号表
	scanf("%s", fname);
	tableswitch = (fname[0]=='y' || fname[0]=='Y'); */
	/* tableswitch = 'y'; */
	
	redirectInput(fin);		
	init();
  	yyparse();
	if(err == 0)
	{
		printf("\n===Parsing success!===\n");
		fprintf(foutput, "\n===Parsing success!===\n");
		if ((fcode = fopen("fcode.txt", "w")) == NULL)
		{
			printf("Can't open fcode.txt file!\n");
			exit(1);
		}		

		if ((fresult = fopen("fresult.txt", "w")) == NULL)
		{
			printf("Can't open fresult.txt file!\n");
			exit(1);
		}
		
		listall();  /* 输出所有代码 */
		fclose(fcode);
		
		interpret();	/* 调用解释执行程序 */        	
		fclose(fresult);
	}
  	else
	{
		printf("%d errors in smallC program\n", err);
		fprintf(foutput, "%d errors in smallC program\n", err);
		
	}
	
	fclose(ftable);
  	fclose(foutput);
	fclose(finput);
	fclose(fin);
	return 0;
}




