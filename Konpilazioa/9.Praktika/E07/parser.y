%define parse.error verbose
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
/* Gogoratu ikur bakoitzak atributu bakarra eta oinarrizko motetakoak          */
/* (osoko, erreal, karaktere, erakusle).                                       */

%union {
    string *izena ;
    adi *e ;
    int erref ;
    ErrefLista *next ;
    ErrefLista *zatizero;
}

/*******************************************************************************/
/* Tokenak erazagutu. Honek tokens.l fitxategiarekin bat etorri behar du.      */
/* .izena atributua duten tokenak:                                             */

%token <izena> TID TNUM_INTEGER TNUM_FLOAT
%token <izena> TCLT TCLE TCGT TCGE TMUL TDIV TADD TSUB


/* Hauek ez dute atributurik:                                                  */

%token TLBRACE TRBRACE TLPAREN TRPAREN TCOMMA TCOLON TSEMIC TASSIG 
%token RFUNC RMAIN RVAR RINTEGER RFLOAT RIF RLOOP REXIT


/*******************************************************************************/


/* Hemen erazagutu atributuak dauzkaten ez-bukaerakoak.                        */
/* adibidez: expr-ek adi motako atributua (izena, true eta false biltzen ditu) */

%type <e> expr
%type <izena> exprbasecase
%type <erref> M
%type <zatizero> stmts stmt

/* Gainerako ez-bukaerakoek ez dute atributurik                                */

/*******************************************************************************/
/* Eragileen lehentasunak erazagutu:                                           */

%nonassoc TCGE TCGT TCLE TCLT
%left TADD TSUB
%left TMUL TDIV

/*******************************************************************************/

/* Hasierako ikurra erazagutu. Ez da derrigorrezkoa. Idazten ez bada,          */
/* lehenenego agertzen dena hartzen du.                                        */
%start mainprog
/*******************************************************************************/


%%

mainprog : RFUNC RMAIN TLPAREN TRPAREN { kodea.agGehitu("prog") ;}
           TLBRACE stmts TRBRACE M {
              kodea.agGehitu("halt");

              kodea.agOsatu(*$<zatizero>7, kodea.lortuErref());
              kodea.agGehitu("write \"zerorekin zatiketa gertatu da\"");
              kodea.agGehitu("writeln");
              kodea.agGehitu("goto " + to_string($<erref>9));

	            kodea.idatzi() ; 

              delete $<zatizero>7;
            }
         ;

stmts : stmt TSEMIC {$<zatizero>$ = $<zatizero>1;}
      | stmts stmt TSEMIC {
        $<zatizero>$ = new ErrefLista;

        // bildu
        $<zatizero>$->insert($<zatizero>$->end(), $<zatizero>1->begin(), $<zatizero>1->end());
        $<zatizero>$->insert($<zatizero>$->end(), $<zatizero>2->begin(), $<zatizero>2->end());

       // delete $<zatizero>1;
       // delete $<zatizero>2;
      }
      ;

stmt : TID TASSIG expr{ 
        $<zatizero>$ = new ErrefLista;

        kodea.agGehitu(*$<izena>1 + " := " + $<e>3->izena) ;

        $<zatizero>$->insert($<zatizero>$->end(), $<e>3->zatizero.begin(), $<e>3->zatizero.end());

	      delete $<izena>1 ; 
        delete $<e>3;
      }

     | RIF expr M TLBRACE stmts TRBRACE M {
          $<zatizero>$ = new ErrefLista;
          
          kodea.agOsatu($<e>2->truel, $<erref>3);
          kodea.agOsatu($<e>2->falsel, $<erref>7);

          $<zatizero>$->insert($<zatizero>$->end(), $<e>2->zatizero.begin(), $<e>2->zatizero.end());
          $<zatizero>$->insert($<zatizero>$->end(), $<zatizero>5->begin(), $<zatizero>5->end());

          delete $<e>2;
        //  delete $<zatizero>5;
      }
        
     ;


expr : expr TMUL expr {
        $<e>$ = new adi;
        $<e>$->izena = kodea.idBerria() ;
        kodea.agGehitu($<e>$->izena + " := " + $<e>1->izena + *$<izena>2 + $<e>3->izena) ; 	

        $<e>$->zatizero.insert($<e>$->zatizero.end(), $<e>1->zatizero.begin(), $<e>1->zatizero.end());
        $<e>$->zatizero.insert($<e>$->zatizero.end(), $<e>3->zatizero.begin(), $<e>3->zatizero.end());

        delete $<e>1; 
        delete $<e>3;
      }

     | expr TDIV expr {
        $<e>$ = new adi;
        $<e>$->izena = kodea.idBerria() ;

        $<e>$->zatizero.push_back(kodea.lortuErref());
        $<e>$->zatizero.insert($<e>$->zatizero.end(), $<e>1->zatizero.begin(), $<e>1->zatizero.end());
        $<e>$->zatizero.insert($<e>$->zatizero.end(), $<e>3->zatizero.begin(), $<e>3->zatizero.end());

        kodea.agGehitu("if " + $<e>3->izena + " == 0 goto");
        kodea.agGehitu($<e>$->izena + " := " + $<e>1->izena + *$<izena>2 + $<e>3->izena) ; 	


        delete $<e>1; 
        delete $<e>3;
      }

     | expr TADD expr {
        $<e>$ = new adi;
        $<e>$->izena = kodea.idBerria() ;
        kodea.agGehitu($<e>$->izena + " := " + $<e>1->izena + *$<izena>2 + $<e>3->izena) ; 	

        $<e>$->zatizero.insert($<e>$->zatizero.end(), $<e>1->zatizero.begin(), $<e>1->zatizero.end());
        $<e>$->zatizero.insert($<e>$->zatizero.end(), $<e>3->zatizero.begin(), $<e>3->zatizero.end());

        delete $<e>1; 
        delete $<e>3;
      }

     | expr TSUB expr {
        $<e>$ = new adi;
        $<e>$->izena = kodea.idBerria() ;
        kodea.agGehitu($<e>$->izena + " := " + $<e>1->izena + *$<izena>2 + $<e>3->izena) ; 	

        $<e>$->zatizero.insert($<e>$->zatizero.end(), $<e>1->zatizero.begin(), $<e>1->zatizero.end());
        $<e>$->zatizero.insert($<e>$->zatizero.end(), $<e>3->zatizero.begin(), $<e>3->zatizero.end());

        delete $<e>1; 
        delete $<e>3;
      }

     | expr TCLT expr {
	      $<e>$ = sortuErlazionala($<e>1->izena, *$<izena>2, $<e>3->izena);

        $<e>$->zatizero.insert($<e>$->zatizero.end(), $<e>1->zatizero.begin(), $<e>1->zatizero.end());
        $<e>$->zatizero.insert($<e>$->zatizero.end(), $<e>3->zatizero.begin(), $<e>3->zatizero.end());
        
        delete $<e>1; 
        delete $<e>3;
      }
      
     | expr TCLE expr {
	      $<e>$ = sortuErlazionala($<e>1->izena, *$<izena>2, $<e>3->izena) ; 

        $<e>$->zatizero.insert($<e>$->zatizero.end(), $<e>1->zatizero.begin(), $<e>1->zatizero.end());
        $<e>$->zatizero.insert($<e>$->zatizero.end(), $<e>3->zatizero.begin(), $<e>3->zatizero.end());

        delete $<e>1; 
        delete $<e>3;
      }
      
     | expr TCGT expr {
	      $<e>$ = sortuErlazionala($<e>1->izena, *$<izena>2, $<e>3->izena) ; 

        $<e>$->zatizero.insert($<e>$->zatizero.end(), $<e>1->zatizero.begin(), $<e>1->zatizero.end());
        $<e>$->zatizero.insert($<e>$->zatizero.end(), $<e>3->zatizero.begin(), $<e>3->zatizero.end());

        delete $<e>1; 
        delete $<e>3;
      }
      
     | expr TCGE expr {
	      $<e>$ = sortuErlazionala($<e>1->izena, *$<izena>2, $<e>3->izena) ; 

        $<e>$->zatizero.insert($<e>$->zatizero.end(), $<e>1->zatizero.begin(), $<e>1->zatizero.end());
        $<e>$->zatizero.insert($<e>$->zatizero.end(), $<e>3->zatizero.begin(), $<e>3->zatizero.end());

        delete $<e>1; 
        delete $<e>3;
      }
      
     | TLPAREN expr TRPAREN { 
        $<e>$ = $<e>2; 
      }
      
     | exprbasecase { 
	      $<e>$ = new adi;
	      $<e>$->izena = *$<izena>1;
      }

exprbasecase :  TID { 
      $<izena>$ = $<izena>1; 
    }
       
     | TNUM_INTEGER { 
      $<izena>$ = $<izena>1; 
    }

     | TNUM_FLOAT { 
      $<izena>$ = $<izena>1; 
    }
     ;


M : { $<erref>$ = kodea.lortuErref(); }
  ;

%%

