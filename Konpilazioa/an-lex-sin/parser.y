%{
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

%}

/* 
   Ikurrek izan ditzaketen atributu-mota guztiak hemen zehaztu.
   Oharra: union egiturak bakarrik onartzen ditu oinarrizko datu-motak,
   osoko, erreal, karaktere eta erakusleak. 

%union {
    string *izena ; 
}
*/
%union {
    string *izena ;
    adi *e ;
    int erref ;
    //int azpierref;
    IdLista *izenak ;
    ErrefLista *main;
    int mainbat;
    breakandcont *bc;
}

/* 
   Tokenak erazagutu. Honek tokens.l fitxategiarekin 
   bat etorri behar du.
   Tokenek atributuak badituzte, hemen zehaztu behar da.
   Adibidez, identifikadoreek izena atributua izango balute:
%token <izena> TID
   Analisi lexiko eta sintaktikorako atributurik ez.
*/

%token <izena> TID TKTE_INT TKTE_FLOAT32 RMAIN RINT RFLOAT32
%token <izena> TCLT TCLE TCGT TCGE TMUL TDIV TADD TSUB

%token RPACK RFUNC RVAR RFOR RBREAK RCONT RREAD RPRINT RRETURN RIF
%token TRBRACE TLBRACE TASSIG TINITASSIG TLPAR TRPAR
%token TCOMMA TCEQ TCNE

/* Hemen erazagutu atributuak dauzkaten ez-bukaerakoak. 
   Adibidez, aldagaia ez-bukaerakoak izena atributua izango balu:
%type <izena> aldagaia
   Analisi lexiko eta sintaktikorako atributurik ez.
*/

%type <e> adierazpena
%type <izena> aldagaia mota auk_mota
%type <izenak> id_zerrenda id_zerrendaren_bestea adi_zerrenda adi_zerrenda_bestea
%type <erref> M bloke_nag 
%type <bc> sententzia blokea sententzia_zerrenda
%type <main> azpiprogramak
%type <mainbat> azpiprograma

%nonassoc TCLT TCGT TCEQ TCLE TCGE TCNE
%left TADD TSUB
%left TMUL TDIV

%start programa


%%

programa : RPACK RMAIN {kodea.agGehitu("proc main");}
            bloke_nag  { kodea.agGehitu("halt"); 
                        kodea.idatzi();}
         ;

bloke_nag : bl_eraz  { $<erref>$ = kodea.lortuErref();
                      kodea.agGehitu("goto");} azpiprogramak
          ;

azpiprogramak : azpiprogramak azpiprograma { $<main>$= new ErrefLista;
                                             $<main>$->splice($<main>$->end(),*$<main>1);
                                             $<main>$->push_back($<mainbat>2);
                                           }

      | azpiprograma { $<main>$= new ErrefLista;
                       $<main>$->push_back($<mainbat>1); 
                       }
      ;

azpiprograma : RFUNC izena argumentuak auk_mota blokea 
      ;

izena : RMAIN{*$<izena>$ = "main";}
      | TID {*$<izena>$ = *$<izena>1;}
      ;

blokea : TLBRACE bl_eraz  anon_azpi sententzia_zerrenda TRBRACE
      ;

anon_azpi : anon_azpi anon
      | %empty
      ;

anon : TID TINITASSIG RFUNC { kodea.agGehitu("proc" + *$<izena>1);} argumentuak auk_mota blokea
                            { kodea.agGehitu("endproc" + *$<izena>1);} 
      ;

bl_eraz : RVAR TLPAR eraz_l TRPAR bl_eraz
      | RVAR eraz bl_eraz
      | %empty
      ;

eraz_l : eraz_l eraz
      | eraz
      ;

eraz : id_zerrenda mota //{kodea.erazagupenakGehitu(*$<izena>2, *$<izenak>1);}
      ;

id_zerrenda : TID id_zerrendaren_bestea { $<izenak>$= new IdLista;
                                          $<izenak>$->push_back(*$<izena>1);
                                          $<izenak>$->splice( $<izenak>$->end(), *$<izenak>2);
                                          }
      |%empty {$<izenak>$ = new IdLista;}
      ;

id_zerrendaren_bestea : TCOMMA TID id_zerrendaren_bestea
      | %empty {$<izenak>$ = new IdLista;}
      ;

mota : RINT {*$<izena>$ = "int";}
      | RFLOAT32 {*$<izena>$ = "real";}
      ;

auk_mota : mota {*$<izena>$ = *$<izena>1;}
      | %empty  {$<izena>$ = new string;}
      ;

argumentuak : TLPAR par_zerrenda TRPAR
      ;

par_zerrenda : id_zerrenda mota par_zerrendaren_bestea //{ kodea.parametroakGehitu(*$<izena>2, *$<izenak>1);
                                                       //}
      | %empty
      ;
 par_zerrendaren_bestea : TCOMMA id_zerrenda mota par_zerrendaren_bestea //{kodea.parametroakGehitu(*$<izena>3, *$<izenak>2);}
      | %empty
      ;

sententzia_zerrenda : sententzia_zerrenda sententzia
      | sententzia
      ;

sententzia : aldagaia TASSIG TID TLPAR adi_zerrenda TRPAR { //kodea.erazagupenakGehitu("param", *$<izenak>5);
                                                            kodea.agGehitu(*$<izena>1 + ":=" + "call" + *$<izena>3);
                                                            /*FALTA BREAK Y CONTINUE*/}
      | aldagaia TASSIG adierazpena;
      | TID TLPAR adi_zerrenda TRPAR
      | RIF adierazpena blokea
      | RFOR adierazpena blokea
      | RFOR blokea
      | RBREAK adierazpena
      | RCONT
      | RREAD TLPAR aldagaia TRPAR
      | RPRINT TLPAR adierazpena TRPAR
      | RRETURN adierazpena
      ;

aldagaia : TID { $<izena>$ = $<izena>1;}
      ;

adi_zerrenda : adierazpena adi_zerrenda_bestea
      | %empty
      ;

adi_zerrenda_bestea : TCOMMA adierazpena adi_zerrenda_bestea
      | %empty
      ;

adierazpena : adierazpena TCEQ adierazpena{$<e>$= sortuErlazionala($<e>1->izena,*$<izena>2, $<e>3->izena);}
      | adierazpena TCGT adierazpena {$<e>$= sortuErlazionala($<e>1->izena,*$<izena>2, $<e>3->izena);}
      | adierazpena TCLT adierazpena {$<e>$= sortuErlazionala($<e>1->izena,*$<izena>2, $<e>3->izena);}
      | adierazpena TCNE adierazpena {$<e>$= sortuErlazionala($<e>1->izena,*$<izena>2, $<e>3->izena);}
      | adierazpena TCGE adierazpena {$<e>$= sortuErlazionala($<e>1->izena,*$<izena>2, $<e>3->izena);}
      | adierazpena TCLE adierazpena {$<e>$= sortuErlazionala($<e>1->izena,*$<izena>2, $<e>3->izena);}
      | adierazpena TADD adierazpena {$<e>$= sortuAritmetikoa($<e>1->izena,*$<izena>2, $<e>3->izena);}
      | adierazpena TSUB adierazpena {$<e>$= sortuAritmetikoa($<e>1->izena,*$<izena>2, $<e>3->izena);}
      | adierazpena TMUL adierazpena {$<e>$= sortuAritmetikoa($<e>1->izena,*$<izena>2, $<e>3->izena);}
      | adierazpena TDIV adierazpena {$<e>$= sortuAritmetikoa($<e>1->izena,*$<izena>2, $<e>3->izena);}
      | aldagaia { $<e>$ = new adi;
                  $<e>$->izena = *$<izena>1;
                  }
      
      | TKTE_INT { $<e>$ = new adi;
                  $<e>$->izena = *$<izena>1;
                  }

      | TKTE_FLOAT32  { $<e>$ = new adi;
                        $<e>$->izena = *$<izena>1;
                        }
      | TLPAR adierazpena TRPAR  { $<e>$ = new adi;
                                  $<e>$->izena = $<e>2->izena;
                                  $<e>$->truel = $<e>2->truel;
                                  $<e>$->falsel = $<e>2->falsel;
                                  }

      ;

      M : { $<erref>$ = kodea.lortuErref(); }
  ;
%%
