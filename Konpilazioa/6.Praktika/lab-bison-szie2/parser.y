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
    IdLista *izenak ;
    ErrefLista *next ;
}

/*******************************************************************************/
/* Tokenak erazagutu. Honek tokens.l fitxategiarekin bat etorri behar du.      */
/* .izena atributua duten tokenak:                                             */

%token <izena> TID TNUM_INTEGER TNUM_FLOAT
%token <izena> TCLT TCLE TCGT TCGE TMUL TDIV TADD TSUB


/* Hauek ez dute atributurik:                                                  */

%token TLBRACE TRBRACE TLPAREN TRPAREN TCOMMA TCOLON TSEMIC TASSIG 
%token RFUNC RMAIN RVAR RINTEGER RFLOAT RIF RTHEN RELSE RDO RWHILE


/*******************************************************************************/


/* Hemen erazagutu atributuak dauzkaten ez-bukaerakoak.                        */
/* adibidez: expr-ek adi motako atributua (izena, true eta false biltzen ditu) */

%type <e> expr
%type <izena> exprbasecase type
%type <izenak> idlist
%type <next> N
%type <erref> M

/* Gainerako ez-bukaerakoek ez dute atributurik                                */

/*******************************************************************************/
/* Eragileen lehentasunak erazagutu:                                           */

%nonassoc TCLT TCLE TCGT TCGE
%left TADD TSUB
%left TMUL TDIV


/*******************************************************************************/

/* Hasierako ikurra erazagutu. Ez da derrigorrezkoa. Idazten ez bada,          */
/* lehenenego agertzen dena hartzen du.                                        */
%start mainprog
/*******************************************************************************/


%%

mainprog : RFUNC RMAIN TLPAREN TRPAREN { kodea.agGehitu("prog") ;} decls TLBRACE stmts TRBRACE
	   {
             kodea.agGehitu("halt");
	     kodea.idatzi() ; 
           }
         ;

decls : RVAR idlist TCOLON type {kodea.erazagupenakGehitu(*$4, *$2);} TSEMIC decls
      |
      ;

type : RFLOAT   { $<izena>$ = new string("float"); }      
     | RINTEGER { $<izena>$ = new string("int"); }
     ;

idlist : TID
	{ $<izenak>$ = new IdLista; $<izenak>$->push_back(*$<izena>1); delete $<izena>1; }
       | idlist TCOMMA TID 
        { $<izenak>$ = $<izenak>1 ; $<izenak>$->push_back(*$<izena>3); delete $<izena>3; }
       ;

stmts : stmt TSEMIC
      | stmts stmt TSEMIC
      ;

stmt :  TID TASSIG expr
        { 
          kodea.agGehitu(*$<izena>1 + " := " + $<e>3->izena) ; 
	  delete $<izena>1 ; delete $<e>3;
        }

     | RWHILE M expr RDO M TLBRACE stmts TRBRACE M 
	{ kodea.agOsatu($<e>3->truel,$<erref>5) ;
	  kodea.agOsatu($<e>3->falsel,$<erref>9 + 1) ;
    	  kodea.agGehitu("goto");
	  ErrefLista tmp1 ; tmp1.push_back($<erref>9) ;
    	  kodea.agOsatu(tmp1, $<erref>2) ;
	  delete $<e>3 ;
	}  
     ;


expr : expr TMUL expr
      {
	$<e>$ = sortuAritmetikoa($<e>1->izena, *$<izena>2, $<e>3->izena) ; 
        delete $<e>1; delete $<e>3;
      }

     | expr TDIV expr
      {
	$<e>$ = sortuAritmetikoa($<e>1->izena, *$<izena>2, $<e>3->izena) ; 
        delete $<e>1; delete $<e>3;
      }

     | expr TADD expr
      {
	$<e>$ = sortuAritmetikoa($<e>1->izena, *$<izena>2, $<e>3->izena) ; 
        delete $<e>1; delete $<e>3;
      }

     | expr TSUB expr
      {
	$<e>$ = sortuAritmetikoa($<e>1->izena, *$<izena>2, $<e>3->izena) ; 
        delete $<e>1; delete $<e>3;
      }

     | expr TCLT expr
      {
	$<e>$ = sortuErlazionala($<e>1->izena, *$<izena>2, $<e>3->izena) ; 
        delete $<e>1; delete $<e>3;
      }
      
     | expr TCLE expr
      {
	$<e>$ = sortuErlazionala($<e>1->izena, *$<izena>2, $<e>3->izena) ; 
        delete $<e>1; delete $<e>3;
      }
      
     | expr TCGT expr
      {
	$<e>$ = sortuErlazionala($<e>1->izena, *$<izena>2, $<e>3->izena) ; 
        delete $<e>1; delete $<e>3;
      }
      
     | expr TCGE expr
      {
	$<e>$ = sortuErlazionala($<e>1->izena, *$<izena>2, $<e>3->izena) ; 
        delete $<e>1; delete $<e>3;
      }
      
     | TLPAREN expr TRPAREN
      { $<e>$ = $<e>2; }
      
     | exprbasecase
      { 
	$<e>$ = new adi;
	$<e>$->izena = *$<izena>1;
      }

exprbasecase :  TID       
       { $<izena>$ = $<izena>1; }
       
     | TNUM_INTEGER
       { $<izena>$ = $<izena>1; }

     | TNUM_FLOAT
       { $<izena>$ = $<izena>1; }
     ;


M : { $<erref>$ = kodea.lortuErref(); }
  ;

N : {
      $<next>$ = new ErrefLista;
      $<next>$->push_back(kodea.lortuErref());
      kodea.agGehitu("goto");
    }
  ;

%%

