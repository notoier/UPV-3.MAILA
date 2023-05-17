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

#ifndef YY_YY_PARSER_HPP_INCLUDED
# define YY_YY_PARSER_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    TKTE_FLOAT32 = 258,            /* TKTE_FLOAT32  */
    TKTE_INT = 259,                /* TKTE_INT  */
    TID = 260,                     /* TID  */
    RPACK = 261,                   /* RPACK  */
    RFUNC = 262,                   /* RFUNC  */
    RMAIN = 263,                   /* RMAIN  */
    RVAR = 264,                    /* RVAR  */
    RIF = 265,                     /* RIF  */
    RBRK = 266,                    /* RBRK  */
    RCNT = 267,                    /* RCNT  */
    RFOR = 268,                    /* RFOR  */
    RPRT = 269,                    /* RPRT  */
    RRD = 270,                     /* RRD  */
    RRET = 271,                    /* RRET  */
    TRBRACE = 272,                 /* TRBRACE  */
    TLBRACE = 273,                 /* TLBRACE  */
    TASSIG = 274,                  /* TASSIG  */
    TINITASSIG = 275,              /* TINITASSIG  */
    TLPAR = 276,                   /* TLPAR  */
    TRPAR = 277,                   /* TRPAR  */
    RINT = 278,                    /* RINT  */
    RFLOAT = 279,                  /* RFLOAT  */
    TCLT = 280,                    /* TCLT  */
    TCLE = 281,                    /* TCLE  */
    TCGT = 282,                    /* TCGT  */
    TCGE = 283,                    /* TCGE  */
    TCEQ = 284,                    /* TCEQ  */
    TCNE = 285,                    /* TCNE  */
    TMUL = 286,                    /* TMUL  */
    TDIV = 287,                    /* TDIV  */
    TADD = 288,                    /* TADD  */
    TSUB = 289,                    /* TSUB  */
    TCOMMA = 290,                  /* TCOMMA  */
    ROR = 291,                     /* ROR */
    RAND = 292,                    /* RAND */
    RNOT = 293,                     /* RNOT */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 32 "parser.y"

   string *izena; 
   string *mota;
   string *balioa;
   int erref;
   int main;
   IdLista *izenak;
   IdLista *param;
   IdLista *adi;
   ErrefLista *main_zer;
   adierazpena *e;
   izmain *im;
   breakcont *brcon;

#line 114 "parser.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_HPP_INCLUDED  */
