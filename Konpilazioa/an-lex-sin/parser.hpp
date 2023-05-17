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
    TID = 258,                     /* TID  */
    TKTE_INT = 259,                /* TKTE_INT  */
    TKTE_FLOAT32 = 260,            /* TKTE_FLOAT32  */
    RMAIN = 261,                   /* RMAIN  */
    RINT = 262,                    /* RINT  */
    RFLOAT32 = 263,                /* RFLOAT32  */
    TCLT = 264,                    /* TCLT  */
    TCLE = 265,                    /* TCLE  */
    TCGT = 266,                    /* TCGT  */
    TCGE = 267,                    /* TCGE  */
    TMUL = 268,                    /* TMUL  */
    TDIV = 269,                    /* TDIV  */
    TADD = 270,                    /* TADD  */
    TSUB = 271,                    /* TSUB  */
    RPACK = 272,                   /* RPACK  */
    RFUNC = 273,                   /* RFUNC  */
    RVAR = 274,                    /* RVAR  */
    RFOR = 275,                    /* RFOR  */
    RBREAK = 276,                  /* RBREAK  */
    RCONT = 277,                   /* RCONT  */
    RREAD = 278,                   /* RREAD  */
    RPRINT = 279,                  /* RPRINT  */
    RRETURN = 280,                 /* RRETURN  */
    RIF = 281,                     /* RIF  */
    TRBRACE = 282,                 /* TRBRACE  */
    TLBRACE = 283,                 /* TLBRACE  */
    TASSIG = 284,                  /* TASSIG  */
    TINITASSIG = 285,              /* TINITASSIG  */
    TLPAR = 286,                   /* TLPAR  */
    TRPAR = 287,                   /* TRPAR  */
    TCOMMA = 288,                  /* TCOMMA  */
    TCEQ = 289,                    /* TCEQ  */
    TCNE = 290                     /* TCNE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 31 "parser.y"

    string *izena ;
    adi *e ;
    int erref ;
    //int azpierref;
    IdLista *izenak ;
    ErrefLista *main;
    int mainbat;
    breakandcont *bc;

#line 110 "parser.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_HPP_INCLUDED  */
