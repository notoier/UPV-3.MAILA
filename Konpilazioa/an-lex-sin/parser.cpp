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
#line 1 "parser.y"

   #include <stdio.h>
   #include <iostream>
   #include <vector>
   #include <string>
   #include "Kodea.h"
   #include "Lag.h"
   using namespace std; 
   extern int yyerrornum;
   extern int yylex();
   extern int yylineno;
   extern char *yytext;
   void yyerror (const char *msg) {
     printf("line %d: %s at '%s'\n", yylineno, msg, yytext) ;
     yyerrornum++;
   }

      Kodea kodea;


#line 92 "parser.cpp"

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

#include "parser.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_TID = 3,                        /* TID  */
  YYSYMBOL_TKTE_INT = 4,                   /* TKTE_INT  */
  YYSYMBOL_TKTE_FLOAT32 = 5,               /* TKTE_FLOAT32  */
  YYSYMBOL_RMAIN = 6,                      /* RMAIN  */
  YYSYMBOL_RINT = 7,                       /* RINT  */
  YYSYMBOL_RFLOAT32 = 8,                   /* RFLOAT32  */
  YYSYMBOL_TCLT = 9,                       /* TCLT  */
  YYSYMBOL_TCLE = 10,                      /* TCLE  */
  YYSYMBOL_TCGT = 11,                      /* TCGT  */
  YYSYMBOL_TCGE = 12,                      /* TCGE  */
  YYSYMBOL_TMUL = 13,                      /* TMUL  */
  YYSYMBOL_TDIV = 14,                      /* TDIV  */
  YYSYMBOL_TADD = 15,                      /* TADD  */
  YYSYMBOL_TSUB = 16,                      /* TSUB  */
  YYSYMBOL_RPACK = 17,                     /* RPACK  */
  YYSYMBOL_RFUNC = 18,                     /* RFUNC  */
  YYSYMBOL_RVAR = 19,                      /* RVAR  */
  YYSYMBOL_RFOR = 20,                      /* RFOR  */
  YYSYMBOL_RBREAK = 21,                    /* RBREAK  */
  YYSYMBOL_RCONT = 22,                     /* RCONT  */
  YYSYMBOL_RREAD = 23,                     /* RREAD  */
  YYSYMBOL_RPRINT = 24,                    /* RPRINT  */
  YYSYMBOL_RRETURN = 25,                   /* RRETURN  */
  YYSYMBOL_RIF = 26,                       /* RIF  */
  YYSYMBOL_TRBRACE = 27,                   /* TRBRACE  */
  YYSYMBOL_TLBRACE = 28,                   /* TLBRACE  */
  YYSYMBOL_TASSIG = 29,                    /* TASSIG  */
  YYSYMBOL_TINITASSIG = 30,                /* TINITASSIG  */
  YYSYMBOL_TLPAR = 31,                     /* TLPAR  */
  YYSYMBOL_TRPAR = 32,                     /* TRPAR  */
  YYSYMBOL_TCOMMA = 33,                    /* TCOMMA  */
  YYSYMBOL_TCEQ = 34,                      /* TCEQ  */
  YYSYMBOL_TCNE = 35,                      /* TCNE  */
  YYSYMBOL_YYACCEPT = 36,                  /* $accept  */
  YYSYMBOL_programa = 37,                  /* programa  */
  YYSYMBOL_38_1 = 38,                      /* $@1  */
  YYSYMBOL_bloke_nag = 39,                 /* bloke_nag  */
  YYSYMBOL_40_2 = 40,                      /* @2  */
  YYSYMBOL_azpiprogramak = 41,             /* azpiprogramak  */
  YYSYMBOL_azpiprograma = 42,              /* azpiprograma  */
  YYSYMBOL_izena = 43,                     /* izena  */
  YYSYMBOL_blokea = 44,                    /* blokea  */
  YYSYMBOL_anon_azpi = 45,                 /* anon_azpi  */
  YYSYMBOL_anon = 46,                      /* anon  */
  YYSYMBOL_47_3 = 47,                      /* $@3  */
  YYSYMBOL_bl_eraz = 48,                   /* bl_eraz  */
  YYSYMBOL_eraz_l = 49,                    /* eraz_l  */
  YYSYMBOL_eraz = 50,                      /* eraz  */
  YYSYMBOL_id_zerrenda = 51,               /* id_zerrenda  */
  YYSYMBOL_id_zerrendaren_bestea = 52,     /* id_zerrendaren_bestea  */
  YYSYMBOL_mota = 53,                      /* mota  */
  YYSYMBOL_auk_mota = 54,                  /* auk_mota  */
  YYSYMBOL_argumentuak = 55,               /* argumentuak  */
  YYSYMBOL_par_zerrenda = 56,              /* par_zerrenda  */
  YYSYMBOL_par_zerrendaren_bestea = 57,    /* par_zerrendaren_bestea  */
  YYSYMBOL_sententzia_zerrenda = 58,       /* sententzia_zerrenda  */
  YYSYMBOL_sententzia = 59,                /* sententzia  */
  YYSYMBOL_aldagaia = 60,                  /* aldagaia  */
  YYSYMBOL_adi_zerrenda = 61,              /* adi_zerrenda  */
  YYSYMBOL_adi_zerrenda_bestea = 62,       /* adi_zerrenda_bestea  */
  YYSYMBOL_adierazpena = 63                /* adierazpena  */
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
typedef yytype_int8 yy_state_t;

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
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   178

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  36
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  28
/* YYNRULES -- Number of rules.  */
#define YYNRULES  66
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  126

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   290


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
      35
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    81,    81,    81,    86,    86,    90,    95,   100,   103,
     104,   107,   110,   111,   114,   114,   118,   119,   120,   123,
     124,   127,   130,   134,   137,   138,   141,   142,   145,   146,
     149,   152,   154,   156,   157,   160,   161,   164,   167,   168,
     169,   170,   171,   172,   173,   174,   175,   176,   179,   182,
     183,   186,   187,   190,   191,   192,   193,   194,   195,   196,
     197,   198,   199,   200,   204,   208,   211
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
  "\"end of file\"", "error", "\"invalid token\"", "TID", "TKTE_INT",
  "TKTE_FLOAT32", "RMAIN", "RINT", "RFLOAT32", "TCLT", "TCLE", "TCGT",
  "TCGE", "TMUL", "TDIV", "TADD", "TSUB", "RPACK", "RFUNC", "RVAR", "RFOR",
  "RBREAK", "RCONT", "RREAD", "RPRINT", "RRETURN", "RIF", "TRBRACE",
  "TLBRACE", "TASSIG", "TINITASSIG", "TLPAR", "TRPAR", "TCOMMA", "TCEQ",
  "TCNE", "$accept", "programa", "$@1", "bloke_nag", "@2", "azpiprogramak",
  "azpiprograma", "izena", "blokea", "anon_azpi", "anon", "$@3", "bl_eraz",
  "eraz_l", "eraz", "id_zerrenda", "id_zerrendaren_bestea", "mota",
  "auk_mota", "argumentuak", "par_zerrenda", "par_zerrendaren_bestea",
  "sententzia_zerrenda", "sententzia", "aldagaia", "adi_zerrenda",
  "adi_zerrenda_bestea", "adierazpena", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-52)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-33)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      -9,     8,    11,   -52,   -52,    29,    26,   -52,   -52,   -16,
      53,    29,    60,    56,    72,   -52,     0,   -52,   -52,   -52,
     -52,   -52,     6,    56,   -52,   -16,    29,   -52,   -52,   -52,
      45,   -52,   -52,   -52,     1,    60,    60,    50,   -52,    51,
      48,   -52,    29,   -52,    53,   -52,   -52,    60,   152,    48,
      39,    18,    23,   -52,    81,    82,    23,    23,   -52,   143,
     -52,    85,   -52,    97,    23,   -52,   -52,   -52,    23,   -52,
     -52,    49,   119,   114,    23,   119,    49,    89,   -52,   -52,
      47,   -52,    90,    76,    84,    23,    23,    23,    23,    23,
      23,    23,    23,    23,    23,   -52,    91,    92,   -52,    94,
     119,    45,   -52,    23,   -52,   -52,   127,   127,   127,   127,
     -52,   -52,    59,    59,   127,   127,   -52,   -52,    23,    60,
      76,   112,    51,   -52,   -52,   -52
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     2,     1,    18,    23,     3,     4,    25,
      23,    18,     0,     0,     0,    22,    23,    20,    17,    26,
      27,    21,     0,     5,     7,    25,    18,    19,    10,     9,
       0,     6,    24,    16,    23,    29,     0,     0,    28,     0,
      34,    30,    18,     8,    23,    31,    13,     0,     0,    34,
      48,     0,     0,    44,     0,     0,     0,     0,    12,     0,
      36,     0,    33,     0,    50,    48,    64,    65,     0,    42,
      63,     0,    43,     0,     0,    47,     0,    48,    11,    35,
       0,    14,     0,    52,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    41,     0,     0,    40,    48,
      38,     0,    39,     0,    49,    66,    55,    58,    54,    57,
      61,    62,    59,    60,    53,    56,    45,    46,    50,    29,
      52,     0,     0,    51,    37,    15
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -52,   -52,   -52,   -52,   -52,   -52,    98,   -52,   -51,   -52,
     -52,   -52,     5,   -52,     3,   -29,   120,    -2,    28,    55,
     -52,    99,   -52,    93,     7,    31,    30,   -50
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     2,     5,     7,    13,    23,    24,    30,    43,    48,
      58,   101,     8,    16,    11,    12,    15,    38,    39,    35,
      37,    45,    59,    60,    70,    82,   104,    83
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      69,    71,    72,     9,     9,    36,    75,    76,     1,    28,
      21,     4,    29,    17,     3,    47,    18,    14,    84,    27,
      95,    65,    66,    67,    97,    98,    65,    66,    67,     9,
     100,    33,    26,   -32,    40,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,    49,    42,    46,     6,    68,
      99,    66,    67,   120,    68,    61,     9,    10,    85,    86,
      87,    88,    89,    90,    91,    92,    61,    19,    20,    63,
      64,   125,    89,    90,    22,    25,    34,    42,    68,    42,
      96,    44,    41,    93,    94,    85,    86,    87,    88,    89,
      90,    91,    92,    85,    86,    87,    88,    89,    90,    91,
      92,    85,    86,    87,    88,    89,    90,    91,    92,   103,
      93,    94,    73,    74,    80,    81,   105,    65,    93,    94,
      64,    31,   102,   116,   117,   118,    93,    94,    85,    86,
      87,    88,    89,    90,    91,    92,   -33,   -33,   -33,   -33,
      89,    90,    91,    92,   124,    32,    77,   122,    62,   121,
     123,     0,    79,    93,    94,    50,   119,     0,     0,     0,
       0,   -33,   -33,    51,    52,    53,    54,    55,    56,    57,
      78,     0,    51,    52,    53,    54,    55,    56,    57
};

static const yytype_int8 yycheck[] =
{
      51,    51,    52,     3,     3,    34,    56,    57,    17,     3,
      12,     0,     6,    10,     6,    44,    11,    33,    68,    16,
      71,     3,     4,     5,    74,    76,     3,     4,     5,     3,
      80,    26,    32,    32,    36,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    47,    28,    42,    19,    31,
       3,     4,     5,   103,    31,    48,     3,    31,     9,    10,
      11,    12,    13,    14,    15,    16,    59,     7,     8,    30,
      31,   122,    13,    14,    18,     3,    31,    28,    31,    28,
      73,    33,    32,    34,    35,     9,    10,    11,    12,    13,
      14,    15,    16,     9,    10,    11,    12,    13,    14,    15,
      16,     9,    10,    11,    12,    13,    14,    15,    16,    33,
      34,    35,    31,    31,    29,    18,    32,     3,    34,    35,
      31,    23,    32,    32,    32,    31,    34,    35,     9,    10,
      11,    12,    13,    14,    15,    16,     9,    10,    11,    12,
      13,    14,    15,    16,    32,    25,     3,   119,    49,   118,
     120,    -1,    59,    34,    35,     3,   101,    -1,    -1,    -1,
      -1,    34,    35,    20,    21,    22,    23,    24,    25,    26,
      27,    -1,    20,    21,    22,    23,    24,    25,    26
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    17,    37,     6,     0,    38,    19,    39,    48,     3,
      31,    50,    51,    40,    33,    52,    49,    50,    48,     7,
       8,    53,    18,    41,    42,     3,    32,    50,     3,     6,
      43,    42,    52,    48,    31,    55,    51,    56,    53,    54,
      53,    32,    28,    44,    33,    57,    48,    51,    45,    53,
       3,    20,    21,    22,    23,    24,    25,    26,    46,    58,
      59,    60,    57,    30,    31,     3,     4,     5,    31,    44,
      60,    63,    63,    31,    31,    63,    63,     3,    27,    59,
      29,    18,    61,    63,    63,     9,    10,    11,    12,    13,
      14,    15,    16,    34,    35,    44,    60,    63,    44,     3,
      63,    47,    32,    33,    62,    32,    63,    63,    63,    63,
      63,    63,    63,    63,    63,    63,    32,    32,    31,    55,
      63,    61,    54,    62,    32,    44
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    36,    38,    37,    40,    39,    41,    41,    42,    43,
      43,    44,    45,    45,    47,    46,    48,    48,    48,    49,
      49,    50,    51,    51,    52,    52,    53,    53,    54,    54,
      55,    56,    56,    57,    57,    58,    58,    59,    59,    59,
      59,    59,    59,    59,    59,    59,    59,    59,    60,    61,
      61,    62,    62,    63,    63,    63,    63,    63,    63,    63,
      63,    63,    63,    63,    63,    63,    63
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     4,     0,     3,     2,     1,     5,     1,
       1,     5,     2,     0,     0,     7,     5,     3,     0,     2,
       1,     2,     2,     0,     3,     0,     1,     1,     1,     0,
       3,     3,     0,     4,     0,     2,     1,     6,     3,     4,
       3,     3,     2,     2,     1,     4,     4,     2,     1,     2,
       0,     3,     0,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     1,     1,     1,     3
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
  case 2: /* $@1: %empty  */
#line 81 "parser.y"
                       {kodea.agGehitu("proc main");}
#line 1233 "parser.cpp"
    break;

  case 3: /* programa: RPACK RMAIN $@1 bloke_nag  */
#line 82 "parser.y"
                       { kodea.agGehitu("halt"); 
                        kodea.idatzi();}
#line 1240 "parser.cpp"
    break;

  case 4: /* @2: %empty  */
#line 86 "parser.y"
                     { (yyval.erref) = kodea.lortuErref();
                      kodea.agGehitu("goto");}
#line 1247 "parser.cpp"
    break;

  case 6: /* azpiprogramak: azpiprogramak azpiprograma  */
#line 90 "parser.y"
                                           { (yyval.main)= new ErrefLista;
                                             (yyval.main)->splice((yyval.main)->end(),*(yyvsp[-1].main));
                                             (yyval.main)->push_back((yyvsp[0].mainbat));
                                           }
#line 1256 "parser.cpp"
    break;

  case 7: /* azpiprogramak: azpiprograma  */
#line 95 "parser.y"
                     { (yyval.main)= new ErrefLista;
                       (yyval.main)->push_back((yyvsp[0].mainbat)); 
                       }
#line 1264 "parser.cpp"
    break;

  case 9: /* izena: RMAIN  */
#line 103 "parser.y"
             {*(yyval.izena) = "main";}
#line 1270 "parser.cpp"
    break;

  case 10: /* izena: TID  */
#line 104 "parser.y"
            {*(yyval.izena) = *(yyvsp[0].izena);}
#line 1276 "parser.cpp"
    break;

  case 14: /* $@3: %empty  */
#line 114 "parser.y"
                            { kodea.agGehitu("proc" + *(yyvsp[-2].izena));}
#line 1282 "parser.cpp"
    break;

  case 15: /* anon: TID TINITASSIG RFUNC $@3 argumentuak auk_mota blokea  */
#line 115 "parser.y"
                            { kodea.agGehitu("endproc" + *(yyvsp[-6].izena));}
#line 1288 "parser.cpp"
    break;

  case 22: /* id_zerrenda: TID id_zerrendaren_bestea  */
#line 130 "parser.y"
                                        { (yyval.izenak)= new IdLista;
                                          (yyval.izenak)->push_back(*(yyvsp[-1].izena));
                                          (yyval.izenak)->splice( (yyval.izenak)->end(), *(yyvsp[0].izenak));
                                          }
#line 1297 "parser.cpp"
    break;

  case 23: /* id_zerrenda: %empty  */
#line 134 "parser.y"
              {(yyval.izenak) = new IdLista;}
#line 1303 "parser.cpp"
    break;

  case 25: /* id_zerrendaren_bestea: %empty  */
#line 138 "parser.y"
               {(yyval.izenak) = new IdLista;}
#line 1309 "parser.cpp"
    break;

  case 26: /* mota: RINT  */
#line 141 "parser.y"
            {*(yyval.izena) = "int";}
#line 1315 "parser.cpp"
    break;

  case 27: /* mota: RFLOAT32  */
#line 142 "parser.y"
                 {*(yyval.izena) = "real";}
#line 1321 "parser.cpp"
    break;

  case 28: /* auk_mota: mota  */
#line 145 "parser.y"
                {*(yyval.izena) = *(yyvsp[0].izena);}
#line 1327 "parser.cpp"
    break;

  case 29: /* auk_mota: %empty  */
#line 146 "parser.y"
                {(yyval.izena) = new string;}
#line 1333 "parser.cpp"
    break;

  case 37: /* sententzia: aldagaia TASSIG TID TLPAR adi_zerrenda TRPAR  */
#line 164 "parser.y"
                                                          { //kodea.erazagupenakGehitu("param", *$<izenak>5);
                                                            kodea.agGehitu(*(yyvsp[-5].izena) + ":=" + "call" + *(yyvsp[-3].izena));
                                                            /*FALTA BREAK Y CONTINUE*/}
#line 1341 "parser.cpp"
    break;

  case 48: /* aldagaia: TID  */
#line 179 "parser.y"
               { (yyval.izena) = (yyvsp[0].izena);}
#line 1347 "parser.cpp"
    break;

  case 53: /* adierazpena: adierazpena TCEQ adierazpena  */
#line 190 "parser.y"
                                          {(yyval.e)= sortuErlazionala((yyvsp[-2].e)->izena,*(yyvsp[-1].izena), (yyvsp[0].e)->izena);}
#line 1353 "parser.cpp"
    break;

  case 54: /* adierazpena: adierazpena TCGT adierazpena  */
#line 191 "parser.y"
                                     {(yyval.e)= sortuErlazionala((yyvsp[-2].e)->izena,*(yyvsp[-1].izena), (yyvsp[0].e)->izena);}
#line 1359 "parser.cpp"
    break;

  case 55: /* adierazpena: adierazpena TCLT adierazpena  */
#line 192 "parser.y"
                                     {(yyval.e)= sortuErlazionala((yyvsp[-2].e)->izena,*(yyvsp[-1].izena), (yyvsp[0].e)->izena);}
#line 1365 "parser.cpp"
    break;

  case 56: /* adierazpena: adierazpena TCNE adierazpena  */
#line 193 "parser.y"
                                     {(yyval.e)= sortuErlazionala((yyvsp[-2].e)->izena,*(yyvsp[-1].izena), (yyvsp[0].e)->izena);}
#line 1371 "parser.cpp"
    break;

  case 57: /* adierazpena: adierazpena TCGE adierazpena  */
#line 194 "parser.y"
                                     {(yyval.e)= sortuErlazionala((yyvsp[-2].e)->izena,*(yyvsp[-1].izena), (yyvsp[0].e)->izena);}
#line 1377 "parser.cpp"
    break;

  case 58: /* adierazpena: adierazpena TCLE adierazpena  */
#line 195 "parser.y"
                                     {(yyval.e)= sortuErlazionala((yyvsp[-2].e)->izena,*(yyvsp[-1].izena), (yyvsp[0].e)->izena);}
#line 1383 "parser.cpp"
    break;

  case 59: /* adierazpena: adierazpena TADD adierazpena  */
#line 196 "parser.y"
                                     {(yyval.e)= sortuAritmetikoa((yyvsp[-2].e)->izena,*(yyvsp[-1].izena), (yyvsp[0].e)->izena);}
#line 1389 "parser.cpp"
    break;

  case 60: /* adierazpena: adierazpena TSUB adierazpena  */
#line 197 "parser.y"
                                     {(yyval.e)= sortuAritmetikoa((yyvsp[-2].e)->izena,*(yyvsp[-1].izena), (yyvsp[0].e)->izena);}
#line 1395 "parser.cpp"
    break;

  case 61: /* adierazpena: adierazpena TMUL adierazpena  */
#line 198 "parser.y"
                                     {(yyval.e)= sortuAritmetikoa((yyvsp[-2].e)->izena,*(yyvsp[-1].izena), (yyvsp[0].e)->izena);}
#line 1401 "parser.cpp"
    break;

  case 62: /* adierazpena: adierazpena TDIV adierazpena  */
#line 199 "parser.y"
                                     {(yyval.e)= sortuAritmetikoa((yyvsp[-2].e)->izena,*(yyvsp[-1].izena), (yyvsp[0].e)->izena);}
#line 1407 "parser.cpp"
    break;

  case 63: /* adierazpena: aldagaia  */
#line 200 "parser.y"
                 { (yyval.e) = new adi;
                  (yyval.e)->izena = *(yyvsp[0].izena);
                  }
#line 1415 "parser.cpp"
    break;

  case 64: /* adierazpena: TKTE_INT  */
#line 204 "parser.y"
                 { (yyval.e) = new adi;
                  (yyval.e)->izena = *(yyvsp[0].izena);
                  }
#line 1423 "parser.cpp"
    break;

  case 65: /* adierazpena: TKTE_FLOAT32  */
#line 208 "parser.y"
                      { (yyval.e) = new adi;
                        (yyval.e)->izena = *(yyvsp[0].izena);
                        }
#line 1431 "parser.cpp"
    break;

  case 66: /* adierazpena: TLPAR adierazpena TRPAR  */
#line 211 "parser.y"
                                 { (yyval.e) = new adi;
                                  (yyval.e)->izena = (yyvsp[-1].e)->izena;
                                  (yyval.e)->truel = (yyvsp[-1].e)->truel;
                                  (yyval.e)->falsel = (yyvsp[-1].e)->falsel;
                                  }
#line 1441 "parser.cpp"
    break;


#line 1445 "parser.cpp"

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

#line 221 "parser.y"

