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
#line 2 "parser.y"

   #include "Kodea.h"
   #include "Lag.h"
   #include <stdio.h>
   #include <iostream>
   #include <vector>
   #include <string>
 

   Kodea kodea;


   using namespace std; 
   extern int yyerrornum;
   extern int yylex();
   extern int yylineno;
   extern char *yytext;
   void yyerror (const char *msg) {
     printf("line %d: %s at '%s'\n", yylineno, msg, yytext) ;
     yyerrornum++;
   }


#line 95 "parser.cpp"

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
  YYSYMBOL_TKTE_FLOAT32 = 3,               /* TKTE_FLOAT32  */
  YYSYMBOL_TKTE_INT = 4,                   /* TKTE_INT  */
  YYSYMBOL_TID = 5,                        /* TID  */
  YYSYMBOL_RPACK = 6,                      /* RPACK  */
  YYSYMBOL_RFUNC = 7,                      /* RFUNC  */
  YYSYMBOL_RMAIN = 8,                      /* RMAIN  */
  YYSYMBOL_RVAR = 9,                       /* RVAR  */
  YYSYMBOL_RIF = 10,                       /* RIF  */
  YYSYMBOL_RBRK = 11,                      /* RBRK  */
  YYSYMBOL_RCNT = 12,                      /* RCNT  */
  YYSYMBOL_RFOR = 13,                      /* RFOR  */
  YYSYMBOL_RPRT = 14,                      /* RPRT  */
  YYSYMBOL_RRD = 15,                       /* RRD  */
  YYSYMBOL_RRET = 16,                      /* RRET  */
  YYSYMBOL_TRBRACE = 17,                   /* TRBRACE  */
  YYSYMBOL_TLBRACE = 18,                   /* TLBRACE  */
  YYSYMBOL_TASSIG = 19,                    /* TASSIG  */
  YYSYMBOL_TINITASSIG = 20,                /* TINITASSIG  */
  YYSYMBOL_TLPAR = 21,                     /* TLPAR  */
  YYSYMBOL_TRPAR = 22,                     /* TRPAR  */
  YYSYMBOL_RINT = 23,                      /* RINT  */
  YYSYMBOL_RFLOAT = 24,                    /* RFLOAT  */
  YYSYMBOL_TCLT = 25,                      /* TCLT  */
  YYSYMBOL_TCLE = 26,                      /* TCLE  */
  YYSYMBOL_TCGT = 27,                      /* TCGT  */
  YYSYMBOL_TCGE = 28,                      /* TCGE  */
  YYSYMBOL_TCEQ = 29,                      /* TCEQ  */
  YYSYMBOL_TCNE = 30,                      /* TCNE  */
  YYSYMBOL_TMUL = 31,                      /* TMUL  */
  YYSYMBOL_TDIV = 32,                      /* TDIV  */
  YYSYMBOL_TADD = 33,                      /* TADD  */
  YYSYMBOL_TSUB = 34,                      /* TSUB  */
  YYSYMBOL_TCOMMA = 35,                    /* TCOMMA  */
  YYSYMBOL_ROR = 36,                       /* ROR  */
  YYSYMBOL_RAND = 37,                      /* RAND  */
  YYSYMBOL_RNOT = 38,                      /* RNOT  */
  YYSYMBOL_YYACCEPT = 39,                  /* $accept  */
  YYSYMBOL_programa = 40,                  /* programa  */
  YYSYMBOL_41_1 = 41,                      /* $@1  */
  YYSYMBOL_bloke_nag = 42,                 /* bloke_nag  */
  YYSYMBOL_43_2 = 43,                      /* $@2  */
  YYSYMBOL_azpiprogramak = 44,             /* azpiprogramak  */
  YYSYMBOL_azpiprograma = 45,              /* azpiprograma  */
  YYSYMBOL_izena = 46,                     /* izena  */
  YYSYMBOL_bloke = 47,                     /* bloke  */
  YYSYMBOL_anon_azpi = 48,                 /* anon_azpi  */
  YYSYMBOL_anon = 49,                      /* anon  */
  YYSYMBOL_50_3 = 50,                      /* $@3  */
  YYSYMBOL_bl_eraz = 51,                   /* bl_eraz  */
  YYSYMBOL_eraz_l = 52,                    /* eraz_l  */
  YYSYMBOL_eraz = 53,                      /* eraz  */
  YYSYMBOL_id_zerrenda = 54,               /* id_zerrenda  */
  YYSYMBOL_id_zerrendaren_bestea = 55,     /* id_zerrendaren_bestea  */
  YYSYMBOL_mota = 56,                      /* mota  */
  YYSYMBOL_auk_mota = 57,                  /* auk_mota  */
  YYSYMBOL_argumentuak = 58,               /* argumentuak  */
  YYSYMBOL_par_zerrenda = 59,              /* par_zerrenda  */
  YYSYMBOL_60_4 = 60,                      /* $@4  */
  YYSYMBOL_par_zerrendaren_bestea = 61,    /* par_zerrendaren_bestea  */
  YYSYMBOL_62_5 = 62,                      /* $@5  */
  YYSYMBOL_sententzia_zerrenda = 63,       /* sententzia_zerrenda  */
  YYSYMBOL_sententzia = 64,                /* sententzia  */
  YYSYMBOL_aldagaia = 65,                  /* aldagaia  */
  YYSYMBOL_adi_zerrenda = 66,              /* adi_zerrenda  */
  YYSYMBOL_adi_zerrenda_bestea = 67,       /* adi_zerrenda_bestea  */
  YYSYMBOL_adierazpena = 68,               /* adierazpena  */
  YYSYMBOL_M = 69                          /* M  */
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

#if 1

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
#endif /* 1 */

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
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   191

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  39
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  31
/* YYNRULES -- Number of rules.  */
#define YYNRULES  71
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  143

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   293


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
      35,    36,    37,    38
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    94,    94,    94,    99,    99,   106,   107,   109,   113,
     116,   122,   132,   133,   135,   135,   138,   141,   145,   148,
     149,   151,   154,   159,   163,   165,   166,   168,   169,   171,
     173,   173,   174,   176,   176,   177,   179,   190,   194,   199,
     203,   208,   215,   221,   228,   232,   236,   239,   243,   247,
     249,   253,   255,   259,   261,   265,   269,   273,   278,   281,
     284,   287,   290,   293,   297,   303,   310,   315,   317,   320,
     323,   327
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "TKTE_FLOAT32",
  "TKTE_INT", "TID", "RPACK", "RFUNC", "RMAIN", "RVAR", "RIF", "RBRK",
  "RCNT", "RFOR", "RPRT", "RRD", "RRET", "TRBRACE", "TLBRACE", "TASSIG",
  "TINITASSIG", "TLPAR", "TRPAR", "RINT", "RFLOAT", "TCLT", "TCLE", "TCGT",
  "TCGE", "TCEQ", "TCNE", "TMUL", "TDIV", "TADD", "TSUB", "TCOMMA", "ROR",
  "RAND", "RNOT", "$accept", "programa", "$@1", "bloke_nag", "$@2",
  "azpiprogramak", "azpiprograma", "izena", "bloke", "anon_azpi", "anon",
  "$@3", "bl_eraz", "eraz_l", "eraz", "id_zerrenda",
  "id_zerrendaren_bestea", "mota", "auk_mota", "argumentuak",
  "par_zerrenda", "$@4", "par_zerrendaren_bestea", "$@5",
  "sententzia_zerrenda", "sententzia", "aldagaia", "adi_zerrenda",
  "adi_zerrenda_bestea", "adierazpena", "M", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-67)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      -4,    12,    29,   -67,   -67,    24,    11,   -67,   -67,   -28,
      60,    24,    44,   -67,    64,   -67,     1,   -67,   -67,   -67,
     -67,   -67,    69,   -28,    24,   -67,    32,    69,   -67,   -67,
     -67,   -67,   -67,    56,   -67,    60,    44,    44,    57,   -67,
      65,   -67,   -67,    24,   -67,    43,   -67,    60,   -67,   142,
      44,     4,     7,     7,   -67,   -67,    75,   100,     7,   -67,
      77,   -67,    67,   -67,   143,     7,   -67,   -67,   -67,     7,
       7,   -67,   112,   112,     0,     7,   146,   112,   158,   -67,
     -67,    59,    43,   -67,   159,    99,    73,   112,     7,     7,
       7,     7,     7,     7,     7,     7,     7,     7,   -67,   -67,
      65,   -67,   112,    86,   160,   162,   112,   -67,    56,   -67,
       7,   -67,   -67,   134,   134,   134,   134,   134,   134,   -67,
     -67,    42,    42,     7,     7,   -67,   -67,    65,   -67,   -67,
       7,    44,    99,   144,   144,   -67,   -67,   163,    65,   -67,
     -67,   -67,   -67
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     2,     1,    18,     0,     3,    71,    24,
       0,    18,     0,     4,     0,    22,     0,    20,    17,    25,
      26,    21,     0,    24,    18,    19,     0,     5,     7,    23,
      16,    10,     9,     0,     6,    32,    28,     0,     0,    27,
       0,    30,    29,    18,     8,    35,    13,     0,    31,     0,
       0,    49,     0,     0,    45,    71,     0,     0,     0,    12,
       0,    37,     0,    33,     0,    51,    70,    69,    49,     0,
       0,    68,    71,    44,     0,     0,     0,    48,    49,    11,
      36,     0,    35,    14,     0,    53,     0,    66,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    71,    71,
       0,    71,    71,     0,     0,    49,    39,    34,     0,    40,
       0,    50,    67,    60,    62,    59,    61,    58,    63,    56,
      57,    54,    55,     0,     0,    71,    42,     0,    47,    46,
      51,    28,    53,    64,    65,    41,    71,     0,     0,    52,
      43,    38,    15
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -67,   -67,   -67,   -67,   -67,   -67,   153,   -67,   -66,   -67,
     -67,   -67,    -2,   -67,    50,   -20,   161,   -11,    55,    79,
     -67,   -67,   106,   -67,   -67,   129,    -1,    61,    58,   -39,
     -55
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     2,     5,     7,    22,    27,    28,    33,    44,    49,
      59,   108,     8,    16,    11,    12,    15,    39,    40,    36,
      38,    45,    48,    82,    60,    61,    71,    84,   111,    85,
      13
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      74,    21,     1,    66,    67,    68,     9,    14,   101,    18,
      66,    67,    68,    72,    73,    37,     9,   100,    43,    77,
       3,    69,    30,    24,    64,    65,    41,    50,    69,     4,
      86,    87,    10,     6,   125,   102,   103,    31,    70,    63,
      32,    46,   106,   123,   124,    70,   126,   127,    62,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,    62,
      17,   136,    66,    67,   105,     9,    25,    19,    20,    23,
     135,   132,   142,    94,    95,   104,    26,    35,    47,    42,
      69,   140,    78,    43,   133,   134,    81,    52,    53,    54,
      55,    56,    57,    58,    79,   112,    75,    70,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,   128,    98,
      99,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    76,    98,    99,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,   110,    98,    99,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    51,    98,    99,
      83,    68,    52,    53,    54,    55,    56,    57,    58,    -1,
      -1,    -1,    -1,    -1,    -1,    94,    95,    96,    97,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    65,
      34,   109,   129,   130,    29,   141,   138,   131,   107,    80,
     139,   137
};

static const yytype_uint8 yycheck[] =
{
      55,    12,     6,     3,     4,     5,     5,    35,    74,    11,
       3,     4,     5,    52,    53,    35,     5,    72,    18,    58,
       8,    21,    24,    22,    20,    21,    37,    47,    21,     0,
      69,    70,    21,     9,   100,    74,    75,     5,    38,    50,
       8,    43,    81,    98,    99,    38,   101,   102,    49,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    60,
      10,   127,     3,     4,     5,     5,    16,    23,    24,     5,
     125,   110,   138,    31,    32,    76,     7,    21,    35,    22,
      21,   136,     5,    18,   123,   124,    19,    10,    11,    12,
      13,    14,    15,    16,    17,    22,    21,    38,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    22,    36,
      37,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    21,    36,    37,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,     5,    36,    37,
       7,     5,    10,    11,    12,    13,    14,    15,    16,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    21,
      27,    22,    22,    21,    23,    22,   131,   108,    82,    60,
     132,   130
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     6,    40,     8,     0,    41,     9,    42,    51,     5,
      21,    53,    54,    69,    35,    55,    52,    53,    51,    23,
      24,    56,    43,     5,    22,    53,     7,    44,    45,    55,
      51,     5,     8,    46,    45,    21,    58,    54,    59,    56,
      57,    56,    22,    18,    47,    60,    51,    35,    61,    48,
      54,     5,    10,    11,    12,    13,    14,    15,    16,    49,
      63,    64,    65,    56,    20,    21,     3,     4,     5,    21,
      38,    65,    68,    68,    69,    21,    21,    68,     5,    17,
      64,    19,    62,     7,    66,    68,    68,    68,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    36,    37,
      69,    47,    68,    68,    65,     5,    68,    61,    50,    22,
      35,    67,    22,    68,    68,    68,    68,    68,    68,    68,
      68,    68,    68,    69,    69,    47,    69,    69,    22,    22,
      21,    58,    68,    68,    68,    69,    47,    66,    57,    67,
      69,    22,    47
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    39,    41,    40,    43,    42,    44,    44,    45,    46,
      46,    47,    48,    48,    50,    49,    51,    51,    51,    52,
      52,    53,    54,    55,    55,    56,    56,    57,    57,    58,
      60,    59,    59,    62,    61,    61,    63,    63,    64,    64,
      64,    64,    64,    64,    64,    64,    64,    64,    64,    65,
      66,    66,    67,    67,    68,    68,    68,    68,    68,    68,
      68,    68,    68,    68,    68,    68,    68,    68,    68,    68,
      68,    69
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     4,     0,     4,     2,     1,     5,     1,
       1,     5,     2,     0,     0,     7,     5,     3,     0,     2,
       1,     2,     2,     3,     0,     1,     1,     1,     0,     3,
       0,     4,     0,     0,     5,     0,     2,     1,     6,     3,
       4,     5,     4,     6,     2,     1,     4,     4,     2,     1,
       2,     0,     3,     0,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     4,     4,     2,     3,     1,     1,
       1,     0
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


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
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
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
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
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
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
            else
              goto append;

          append:
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

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
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
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
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
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


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

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

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
  case 2: /* $@1: %empty  */
#line 94 "parser.y"
                       {kodea.agGehitu("proc main");}
#line 1528 "parser.cpp"
    break;

  case 3: /* programa: RPACK RMAIN $@1 bloke_nag  */
#line 95 "parser.y"
            {kodea.agGehitu("halt"); 
            kodea.idatzi();}
#line 1535 "parser.cpp"
    break;

  case 4: /* $@2: %empty  */
#line 99 "parser.y"
                      {kodea.agGehitu("goto");}
#line 1541 "parser.cpp"
    break;

  case 5: /* bloke_nag: bl_eraz M $@2 azpiprogramak  */
#line 100 "parser.y"
            {ErrefLista *erreflista = new ErrefLista;
            erreflista->push_back((yyvsp[-2].erref));
            kodea.agOsatu(*erreflista, (yyvsp[0].main));
           }
#line 1550 "parser.cpp"
    break;

  case 6: /* azpiprogramak: azpiprogramak azpiprograma  */
#line 106 "parser.y"
                                           {(yyval.main) = (yyvsp[-1].main) + (yyvsp[0].main);}
#line 1556 "parser.cpp"
    break;

  case 7: /* azpiprogramak: azpiprograma  */
#line 107 "parser.y"
                              {(yyval.main) = (yyvsp[0].main);}
#line 1562 "parser.cpp"
    break;

  case 8: /* azpiprograma: RFUNC izena argumentuak auk_mota bloke  */
#line 110 "parser.y"
               {(yyval.main) = (yyvsp[-3].im)->main;
               if ((yyval.main) == 0) kodea.agGehitu("endproc " + (yyvsp[-3].im)->izena);}
#line 1569 "parser.cpp"
    break;

  case 9: /* izena: RMAIN  */
#line 114 "parser.y"
         {(yyval.im) = new izmain;
         (yyval.im)->main = kodea.lortuErref();}
#line 1576 "parser.cpp"
    break;

  case 10: /* izena: TID  */
#line 117 "parser.y"
         {(yyval.im) = new izmain;
         (yyval.im)->izena = *(yyvsp[0].izena);
         (yyval.im)->main = 0;
         kodea.agGehitu("proc " + *(yyvsp[0].izena));}
#line 1585 "parser.cpp"
    break;

  case 11: /* bloke: TLBRACE bl_eraz anon_azpi sententzia_zerrenda TRBRACE  */
#line 123 "parser.y"
         {(yyval.brcon) = new breakcont;
         //$<brcon>$->breakl.insert($<brcon>$->breakl.end(), $<brcon>2->breakl.begin(), $<brcon>2->breakl.end());
         (yyval.brcon)->breakl.insert((yyval.brcon)->breakl.end(), (yyvsp[-1].brcon)->breakl.begin(), (yyvsp[-1].brcon)->breakl.end());
         
         //$<brcon>$->continuel.insert($<brcon>$->continuel.end(), $<brcon>2->continuel.begin(), $<brcon>2->continuel.end());
         (yyval.brcon)->continuel.insert((yyval.brcon)->continuel.end(), (yyvsp[-1].brcon)->continuel.begin(), (yyvsp[-1].brcon)->continuel.end());

         }
#line 1598 "parser.cpp"
    break;

  case 14: /* $@3: %empty  */
#line 135 "parser.y"
                            {kodea.agGehitu("proc " + *(yyvsp[-2].izena));}
#line 1604 "parser.cpp"
    break;

  case 15: /* anon: TID TINITASSIG RFUNC $@3 argumentuak auk_mota bloke  */
#line 136 "parser.y"
      {kodea.agGehitu("endproc " + *(yyvsp[-6].izena));}
#line 1610 "parser.cpp"
    break;

  case 21: /* eraz: id_zerrenda mota  */
#line 152 "parser.y"
      {kodea.erazagupenakGehitu(*(yyvsp[0].mota), *(yyvsp[-1].izenak));}
#line 1616 "parser.cpp"
    break;

  case 22: /* id_zerrenda: TID id_zerrendaren_bestea  */
#line 155 "parser.y"
               {(yyval.izenak) = new IdLista;
               (yyval.izenak)->insert((yyval.izenak)->end(), (yyvsp[0].izenak)->begin(), (yyvsp[0].izenak)->end());
               (yyval.izenak)->push_front(*(yyvsp[-1].izena));}
#line 1624 "parser.cpp"
    break;

  case 23: /* id_zerrendaren_bestea: TCOMMA TID id_zerrendaren_bestea  */
#line 160 "parser.y"
                        {(yyval.izenak) = new IdLista;
                        (yyval.izenak)->insert((yyval.izenak)->end(), (yyvsp[0].izenak)->begin(), (yyvsp[0].izenak)->end());
                        (yyval.izenak)->push_front(*(yyvsp[-1].izena));}
#line 1632 "parser.cpp"
    break;

  case 24: /* id_zerrendaren_bestea: %empty  */
#line 163 "parser.y"
                        {(yyval.izenak) = new IdLista;}
#line 1638 "parser.cpp"
    break;

  case 25: /* mota: RINT  */
#line 165 "parser.y"
            {(yyval.mota) = new string("int");}
#line 1644 "parser.cpp"
    break;

  case 26: /* mota: RFLOAT  */
#line 166 "parser.y"
              {(yyval.mota) = new string("real");}
#line 1650 "parser.cpp"
    break;

  case 30: /* $@4: %empty  */
#line 173 "parser.y"
                                {kodea.parametroakGehitu(*(yyvsp[0].mota), *(yyvsp[-1].izenak));}
#line 1656 "parser.cpp"
    break;

  case 33: /* $@5: %empty  */
#line 176 "parser.y"
                                                 {kodea.parametroakGehitu(*(yyvsp[0].mota), *(yyvsp[-1].izenak));}
#line 1662 "parser.cpp"
    break;

  case 36: /* sententzia_zerrenda: sententzia_zerrenda sententzia  */
#line 180 "parser.y"
                        {(yyval.brcon) = new breakcont;
                        (yyval.brcon)->breakl.insert((yyval.brcon)->breakl.end(), (yyvsp[-1].brcon)->breakl.begin(), (yyvsp[-1].brcon)->breakl.end());
                        (yyval.brcon)->breakl.insert((yyval.brcon)->breakl.end(), (yyvsp[0].brcon)->breakl.begin(), (yyvsp[0].brcon)->breakl.end());
                        
                        (yyval.brcon)->continuel.insert((yyval.brcon)->continuel.end(), (yyvsp[-1].brcon)->continuel.begin(), (yyvsp[-1].brcon)->continuel.end());
                        (yyval.brcon)->continuel.insert((yyval.brcon)->continuel.end(), (yyvsp[0].brcon)->continuel.begin(), (yyvsp[0].brcon)->continuel.end());

                        }
#line 1675 "parser.cpp"
    break;

  case 37: /* sententzia_zerrenda: sententzia  */
#line 192 "parser.y"
                        {(yyval.brcon) = (yyvsp[0].brcon);}
#line 1681 "parser.cpp"
    break;

  case 38: /* sententzia: aldagaia TASSIG TID TLPAR adi_zerrenda TRPAR  */
#line 195 "parser.y"
            {(yyval.brcon) = new breakcont;
            kodea.parametroekinDeitu(*(yyvsp[-1].adi));
            kodea.agGehitu(*(yyvsp[-5].izena) + " := call " + *(yyvsp[-3].izena));}
#line 1689 "parser.cpp"
    break;

  case 39: /* sententzia: aldagaia TASSIG adierazpena  */
#line 200 "parser.y"
               {(yyval.brcon) = new breakcont;
               kodea.agGehitu(*(yyvsp[-2].izena) + " := " + (yyvsp[0].e)->izena);}
#line 1696 "parser.cpp"
    break;

  case 40: /* sententzia: TID TLPAR adi_zerrenda TRPAR  */
#line 204 "parser.y"
               {(yyval.brcon) = new breakcont;
               kodea.parametroekinDeitu(*(yyvsp[-1].adi));
               kodea.agGehitu("call " + *(yyvsp[-3].izena));}
#line 1704 "parser.cpp"
    break;

  case 41: /* sententzia: RIF adierazpena M bloke M  */
#line 209 "parser.y"
               {(yyval.brcon) = (yyvsp[-1].brcon);
               //kodea.agOsatu($<brcon>5->breakl, $<erref>3);
               //kodea.agOsatu($<brcon>5->continuel, $<erref>5);
               kodea.agOsatu((yyvsp[-3].e)->truel, (yyvsp[-2].erref));
               kodea.agOsatu((yyvsp[-3].e)->falsel, (yyvsp[0].erref));}
#line 1714 "parser.cpp"
    break;

  case 42: /* sententzia: RFOR M bloke M  */
#line 216 "parser.y"
               {(yyval.brcon) = new breakcont;
               kodea.agOsatu((yyvsp[-1].brcon)->breakl, (yyvsp[0].erref) + 1);
               kodea.agOsatu((yyvsp[-1].brcon)->continuel, (yyvsp[-2].erref));
               kodea.agGehitu("goto " + to_string((yyvsp[-2].erref)));}
#line 1723 "parser.cpp"
    break;

  case 43: /* sententzia: RFOR M adierazpena M bloke M  */
#line 222 "parser.y"
               {(yyval.brcon) = new breakcont;
               kodea.agOsatu((yyvsp[-1].brcon)->breakl, (yyvsp[0].erref) + 1);
               kodea.agOsatu((yyvsp[-1].brcon)->continuel, (yyvsp[-4].erref));
               kodea.agOsatu((yyvsp[-3].e)->truel, (yyvsp[-2].erref));
               kodea.agOsatu((yyvsp[-3].e)->falsel, (yyvsp[0].erref) + 1);
               kodea.agGehitu("goto " + to_string((yyvsp[-4].erref)));}
#line 1734 "parser.cpp"
    break;

  case 44: /* sententzia: RBRK adierazpena  */
#line 229 "parser.y"
               {(yyval.brcon) = new breakcont;
               (yyval.brcon)->breakl = (yyvsp[0].e)->truel;
               kodea.agOsatu((yyvsp[0].e)->falsel, kodea.lortuErref());}
#line 1742 "parser.cpp"
    break;

  case 45: /* sententzia: RCNT  */
#line 233 "parser.y"
               {(yyval.brcon) = new breakcont;
               (yyval.brcon)->continuel.push_back(kodea.lortuErref());
               kodea.agGehitu("goto");}
#line 1750 "parser.cpp"
    break;

  case 46: /* sententzia: RRD TLPAR aldagaia TRPAR  */
#line 237 "parser.y"
               {(yyval.brcon) = new breakcont;
               kodea.agGehitu("read " + (yyvsp[-1].e)->izena);}
#line 1757 "parser.cpp"
    break;

  case 47: /* sententzia: RPRT TLPAR adierazpena TRPAR  */
#line 240 "parser.y"
               {(yyval.brcon) = new breakcont;
               kodea.agGehitu("write " + (yyvsp[-1].e)->izena);
               kodea.agGehitu("writeln");}
#line 1765 "parser.cpp"
    break;

  case 48: /* sententzia: RRET adierazpena  */
#line 244 "parser.y"
               {(yyval.brcon) = new breakcont;
               kodea.agGehitu("return " + (yyvsp[0].e)->izena);}
#line 1772 "parser.cpp"
    break;

  case 49: /* aldagaia: TID  */
#line 247 "parser.y"
               {(yyval.izena) = (yyvsp[0].izena) ;}
#line 1778 "parser.cpp"
    break;

  case 50: /* adi_zerrenda: adierazpena adi_zerrenda_bestea  */
#line 250 "parser.y"
                  {(yyval.adi) = new IdLista;
                  (yyval.adi)->insert((yyval.adi)->end(), (yyvsp[0].adi)->begin(), (yyvsp[0].adi)->end());
                  (yyval.adi)->push_front(*(yyvsp[-1].izena));}
#line 1786 "parser.cpp"
    break;

  case 51: /* adi_zerrenda: %empty  */
#line 253 "parser.y"
               {(yyval.adi) = new IdLista;}
#line 1792 "parser.cpp"
    break;

  case 52: /* adi_zerrenda_bestea: TCOMMA adierazpena adi_zerrenda_bestea  */
#line 256 "parser.y"
                        {(yyval.adi) = new IdLista;
                        (yyval.adi)->insert((yyval.adi)->end(), (yyvsp[0].adi)->begin(), (yyvsp[0].adi)->end());
                        (yyval.adi)->push_front((yyvsp[-1].e)->izena);}
#line 1800 "parser.cpp"
    break;

  case 53: /* adi_zerrenda_bestea: %empty  */
#line 259 "parser.y"
                      {(yyval.adi) = new IdLista;}
#line 1806 "parser.cpp"
    break;

  case 54: /* adierazpena: adierazpena TADD adierazpena  */
#line 262 "parser.y"
               {(yyval.e) = new adierazpena;
               (yyval.e)->izena = kodea.idBerria() ;
               kodea.agGehitu((yyval.e)->izena + " := " + (yyvsp[-2].e)->izena + "+" + (yyvsp[0].e)->izena) ;}
#line 1814 "parser.cpp"
    break;

  case 55: /* adierazpena: adierazpena TSUB adierazpena  */
#line 266 "parser.y"
               {(yyval.e) = new adierazpena;
               (yyval.e)->izena = kodea.idBerria() ;
               kodea.agGehitu((yyval.e)->izena + " := " + (yyvsp[-2].e)->izena + "-" + (yyvsp[0].e)->izena) ;}
#line 1822 "parser.cpp"
    break;

  case 56: /* adierazpena: adierazpena TMUL adierazpena  */
#line 270 "parser.y"
               {(yyval.e) = new adierazpena;
               (yyval.e)->izena = kodea.idBerria() ;
               kodea.agGehitu((yyval.e)->izena + " := " + (yyvsp[-2].e)->izena + "*" + (yyvsp[0].e)->izena) ;}
#line 1830 "parser.cpp"
    break;

  case 57: /* adierazpena: adierazpena TDIV adierazpena  */
#line 274 "parser.y"
               {(yyval.e) = new adierazpena;
               (yyval.e)->izena = kodea.idBerria() ;
               kodea.agGehitu((yyval.e)->izena + " := " + (yyvsp[-2].e)->izena + "/" + (yyvsp[0].e)->izena) ;}
#line 1838 "parser.cpp"
    break;

  case 58: /* adierazpena: adierazpena TCEQ adierazpena  */
#line 279 "parser.y"
               {//$<e>$ = new adierazpena;
                (yyval.e) = sortuErlazionala((yyvsp[-2].e)->izena, " == ", (yyvsp[0].e)->izena) ; }
#line 1845 "parser.cpp"
    break;

  case 59: /* adierazpena: adierazpena TCGT adierazpena  */
#line 282 "parser.y"
               {//$<e>$ = new adierazpena;
                (yyval.e) = sortuErlazionala((yyvsp[-2].e)->izena ," > ", (yyvsp[0].e)->izena)  ;}
#line 1852 "parser.cpp"
    break;

  case 60: /* adierazpena: adierazpena TCLT adierazpena  */
#line 285 "parser.y"
               {//$<e>$ = new adierazpena;
                (yyval.e) = sortuErlazionala((yyvsp[-2].e)->izena ," < ", (yyvsp[0].e)->izena) ; }
#line 1859 "parser.cpp"
    break;

  case 61: /* adierazpena: adierazpena TCGE adierazpena  */
#line 288 "parser.y"
               {//$<e>$ = new adierazpena;
                (yyval.e) = sortuErlazionala((yyvsp[-2].e)->izena ," >= ", (yyvsp[0].e)->izena) ; }
#line 1866 "parser.cpp"
    break;

  case 62: /* adierazpena: adierazpena TCLE adierazpena  */
#line 291 "parser.y"
               {//$<e>$ = new adierazpena;
                (yyval.e) = sortuErlazionala((yyvsp[-2].e)->izena ," <= ", (yyvsp[0].e)->izena) ; }
#line 1873 "parser.cpp"
    break;

  case 63: /* adierazpena: adierazpena TCNE adierazpena  */
#line 294 "parser.y"
               {//$<e>$ = new adierazpena;
                (yyval.e) = sortuErlazionala((yyvsp[-2].e)->izena ," != ", (yyvsp[0].e)->izena) ; }
#line 1880 "parser.cpp"
    break;

  case 64: /* adierazpena: adierazpena ROR M adierazpena  */
#line 298 "parser.y"
               {(yyval.e) = new adierazpena; 
               kodea.agOsatu((yyvsp[-3].e)->falsel, (yyvsp[-1].erref));
               (yyval.e)->truel.insert((yyval.e)->truel.end(), (yyvsp[-3].e)->truel.begin(), (yyvsp[-3].e)->truel.end());
               (yyval.e)->truel.insert((yyval.e)->truel.end(), (yyvsp[0].e)->truel.begin(), (yyvsp[0].e)->truel.end());
               (yyval.e)->falsel = (yyvsp[0].e)->falsel;}
#line 1890 "parser.cpp"
    break;

  case 65: /* adierazpena: adierazpena RAND M adierazpena  */
#line 304 "parser.y"
               {(yyval.e) = new adierazpena; 
               kodea.agOsatu((yyvsp[-3].e)->truel, (yyvsp[-1].erref));
               (yyval.e)->falsel.insert((yyval.e)->falsel.end(), (yyvsp[-3].e)->falsel.begin(), (yyvsp[-3].e)->falsel.end());
               (yyval.e)->falsel.insert((yyval.e)->falsel.end(), (yyvsp[0].e)->falsel.begin(), (yyvsp[0].e)->falsel.end());
               (yyval.e)->truel = (yyvsp[0].e)->truel; }
#line 1900 "parser.cpp"
    break;

  case 66: /* adierazpena: RNOT adierazpena  */
#line 311 "parser.y"
               {(yyval.e) = new adierazpena; 
               (yyval.e)->falsel = (yyvsp[0].e)->truel;
               (yyval.e)->truel = (yyvsp[0].e)->falsel;}
#line 1908 "parser.cpp"
    break;

  case 67: /* adierazpena: TLPAR adierazpena TRPAR  */
#line 316 "parser.y"
               {(yyval.e) = (yyvsp[-1].e);}
#line 1914 "parser.cpp"
    break;

  case 68: /* adierazpena: aldagaia  */
#line 318 "parser.y"
               {(yyval.e) = new adierazpena; 
               (yyval.e)->izena = *(yyvsp[0].izena);}
#line 1921 "parser.cpp"
    break;

  case 69: /* adierazpena: TKTE_INT  */
#line 321 "parser.y"
               {(yyval.e) = new adierazpena; 
               (yyval.e)->izena = *(yyvsp[0].z_izena);}
#line 1928 "parser.cpp"
    break;

  case 70: /* adierazpena: TKTE_FLOAT32  */
#line 324 "parser.y"
               {(yyval.e) = new adierazpena; 
               (yyval.e)->izena = *(yyvsp[0].z_izena);}
#line 1935 "parser.cpp"
    break;

  case 71: /* M: %empty  */
#line 327 "parser.y"
     {(yyval.erref) = kodea.lortuErref();}
#line 1941 "parser.cpp"
    break;


#line 1945 "parser.cpp"

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
      {
        yypcontext_t yyctx
          = {yyssp, yytoken};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
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
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 329 "parser.y"

