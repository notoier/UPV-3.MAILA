
%{
   #include "Kodea.h"
   #include "Lag.h"

   Kodea kodea;

   using namespace std; 

   extern int yylex();
   extern int yylineno;
   extern char *yytext;
   extern int yyerrornum;
   void yyerror (const char *msg) {
     cout << "line " << yylineno <<": " << msg << " at token " << yytext << endl ;
     yyerrornum++;
   }

%}

/*******************************************************************************/
/* Ikurrek zein atributu-mota izan dezaketen.                                  */
/* Gogoratu ikur bakoitzak bakarra eta oinarrizko motak (osoko, erreal,        */
/* karaktere, erakusle).                                                       */

%union {
    string *izena ;
   
}

/*******************************************************************************/
/* Tokenak erazagutu. Honek tokens.l fitxategiarekin bat etorri behar du.      */
/* .izena atributua duten tokenak:                                             */

%token <izena> TID TNUM_FLOAT TNUM_INTEGER

/* Hauek ez dute atributurik:                                                  */

%token RFUNC RMAIN TLBRACE TRBRACE TASSIG TADD TSUB TMUL TDIV

/* Hemen erazagutu atributuak dauzkaten ez-bukaerakoak.                        */

%type <izena> expr


/*******************************************************************************/
/* Eragileen lehentasunak erazagutu:                                           */
/* Inplementazioa errazten du baina ez du aldatzen espezifikazioa              */

%left TADD TSUB
%left TMUL TDIV                                                            


/*******************************************************************************/

/* Hasierako ikurra erazagutu. Ez da derrigorrezkoa. Idazten ez bada,          */
/* lehenenego agertzen dena hartzen du.                                        */

%start main_prog
/*******************************************************************************/


%%



main_prog : RFUNC RMAIN { kodea.agGehitu("prog") ;} 
           TLBRACE stmts TRBRACE
	   {
             kodea.agGehitu("halt");
	     kodea.idatzi() ; 
           }
         ;


stmts : stmt 
      | stmts stmt 
      ;

stmt :  TID TASSIG expr
        {
          kodea.agGehitu(*$<izena>1 + " := " + *$<izena>3);
        delete $<izena>1;
        delete $<izena>3;
        }
     ;


expr : TID       
       {
        $<izena>$ = $<izena>1;
       }

      |TNUM_INTEGER
       {
        $<izena>$ = $<izena>1;
       }
       
      |TNUM_FLOAT       
       {
        $<izena>$ = $<izena>1;
       }
       
      | expr TMUL expr 
       { 
      	$<izena>$ = new string;
        *$<izena>$ = kodea.idBerria() ;
        kodea.agGehitu(*$<izena>$ + " := " + *$<izena>1 + " * " + *$<izena>3) ;
        delete $<izena>1;
        delete $<izena>3;
       }
    
      | expr TDIV expr 
       { 
      	$<izena>$ = new string;
        *$<izena>$ = kodea.idBerria() ;
        kodea.agGehitu(*$<izena>$ + " := " + *$<izena>1 + " / " + *$<izena>3) ;
        delete $<izena>1;
        delete $<izena>3;
       }
    
      | expr TADD expr 
       { 
      	$<izena>$ = new string;
        *$<izena>$ = kodea.idBerria() ;
        kodea.agGehitu(*$<izena>$ + " := " + *$<izena>1 + " + " + *$<izena>3) ;
        delete $<izena>1;
        delete $<izena>3;
       }
    
      | expr TSUB expr 
       { 
      	$<izena>$ = new string;
        *$<izena>$ = kodea.idBerria() ;
        kodea.agGehitu(*$<izena>$ + " := " + *$<izena>1 + " - " + *$<izena>3) ;
        delete $<izena>1;
        delete $<izena>3;
       }
     ;




%%


