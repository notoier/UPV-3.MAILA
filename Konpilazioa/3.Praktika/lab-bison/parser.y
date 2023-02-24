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
*/
%union {
    string *izena ;
     
}
/*****/

/* 
   Tokenak eta bere atributuak erazagutu. Honek tokens.l fitxategiarekin 
   bat etorri behar du.
   Lexikoak atributua duten tokenetarako memoria alokatzen du,
   hemen askatu behar da.
*/


%token RPACK RFUNC RMAIN RVAR 
%token TRPAREN TLPAREN TRBRACE TLBRACE TASSIG TINITASSIG
%token TMUL TADD TSUB TDIV TEQU
%token <izena> TID TKTE_FLOAT32 TKTE_INT

/* Hemen erazagutu atributuak dauzkaten ez-bukaerakoak */
%type <izena> sententzia_zerrenda sententzia adierazpena bloke


/*** Hemen definitu eragileen lehentasunak, maila bakoitzeko lerro bat: */
/*** %left ezkerretik eskuinera ebaluatu                                */
/*** %nonassoc bakarrik eragile bat onartzen da                         */

%left TEQU
%left TADD TSUB
%left TMUL TDIV

%start programa

%%

programa : RPACK RMAIN RFUNC RMAIN TLPAREN TRPAREN bloke
         { 
          cout << "\n<programa>\n package main " + *$7 + "\n</programa>\n" << endl;
	  delete $7; 
         }
         ;


bloke : TLBRACE
        sententzia_zerrenda
        TRBRACE
      { 
       $$ = $2; 
      }
      ;


sententzia_zerrenda : sententzia
                { 
	          $$ = new string; *$$ = "\n<sententzia_zerrenda (OK)>\n" + *$1 + "\n</sententzia_zerrenda (OK)>\n";
	        }
              | sententzia sententzia_zerrenda
                {
                  $$ = new string; *$$ = "\n<sententzia_zerrenda (IP)>\n" + *$1 + *$2  + "\n</sententzia_zerrenda (IP)>\n";
	          delete $1; delete $2;
 	        }
              ;

sententzia : TID TASSIG adierazpena 
             {
	       $$ = new string ; *$$ = "\n<sententzia>\n" + *$1 + "=" + *$3 + "\n</sententzia>\n" ;
	       delete $1; delete $3;
	     }
           ;

adierazpena : adierazpena TMUL adierazpena 
      {
        $$ = new string; *$$ = "\n<adierazpena>\n" + *$1 + " * " + *$3 + "\n</adierazpena>\n" ;
        delete $1; delete $3;
      }

            | adierazpena TDIV adierazpena 
              {
                $$ = new string; *$$ = "\n<adierazpena>\n" + *$1 + " - " + *$3 + "\n</adierazpena>\n" ;
                delete $1; delete $3;
              }

            | adierazpena TADD adierazpena 
              {
                $$ = new string; *$$ = "\n<adierazpena>\n" + *$1 + " + " + *$3 + "\n</adierazpena>\n" ;
                delete $1; delete $3;
              }

            | adierazpena TSUB adierazpena 
              {
                $$ = new string; *$$ = "\n<adierazpena>\n" + *$1 + " - " + *$3 + "\n</adierazpena>\n" ;
                delete $1; delete $3;
              }

            | adierazpena TEQU adierazpena 
              {
                $$ = new string; *$$ = "\n<adierazpena>\n" + *$1 + " == " + *$3 + "\n</adierazpena>\n" ;
                delete $1; delete $3;
              }
              
            | TID           { $$ = $1; }
            | TKTE_INT      { $$ = $1; }
            | TKTE_FLOAT32  { $$ = $1; }
            ;


%%

