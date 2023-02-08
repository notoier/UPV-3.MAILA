%{
   #include <stdio.h>
   #include <iostream>
   #include <vector>
   #include <string>
   using namespace std; 
   extern int yyerrornum;
   extern int yylex();
   extern int yylineno;
   extern char *yytext;
   void yyerror (const char *msg) {
     printf("line %d: %s at '%s'\n", yylineno, msg, yytext) ;
     yyerrornum++;
   }

%}

/* 
   Ikurrek zein atributu-mota duten 

%union {
    string *izena ; 
}
*/

/* 
   Tokenak erazagutu. Honek tokens.l fitxategiarekin 
   bat etorri behar du.
*/

%token RPACK RFUNC RMAIN RVAR 
%token TRBRACE TLBRACE TASSIG TINITASSIG
%token TMUL
%token TID TKTE_FLOAT32 TKTE_INT
%token RINT TLPAR TRPAR TCOMMENT1 TCOMMENT2 TCOMA TADD TSUB TLESS TMORE TDIV


%start programa



%%

programa : programa token_bat
         | token_bat
         ;
token_bat : RPACK | RFUNC | RMAIN | RVAR | TASSIG | TINITASSIG 
	  | TLBRACE| TRBRACE | TMUL | TID | TKTE_FLOAT32 | TKTE_INT 
     | RINT | TLPAR | TRPAR | TCOMMENT1 | TCOMMENT2 | TCOMA | TADD | TSUB | TLESS | TMORE | TDIV
          ;
%%
