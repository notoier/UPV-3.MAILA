%define parse.error verbose
%{
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

%}

/* 
   Ikurrek izan ditzaketen atributu-mota guztiak hemen zehaztu.
   Oharra: union egiturak bakarrik onartzen ditu oinarrizko datu-motak,
   osoko, erreal, karaktere eta erakusleak. 
*/

%union {
   string *izena; 
   string *mota;
   string *z_izena;
   int erref;
   int main;
   IdLista *izenak;
   IdLista *param;
   IdLista *adi;
//   ErrefLista *main_zer;
   adierazpena *e;
   izmain *im;
   breakcont *brcon;
}


/* 
   Tokenak erazagutu. Honek tokens.l fitxategiarekin 
   bat etorri behar du.
   Tokenek atributuak badituzte, hemen zehaztu behar da.
   Adibidez, identifikadoreek izena atributua izango balute:
%token <izena> TID
   Analisi lexiko eta sintaktikorako atributurik ez.
*/

%token <z_izena> TKTE_FLOAT32 TKTE_INT
%token <izena> TID 

%token RPACK RFUNC RMAIN RVAR RIF RBRK RCNT RFOR RPRT RRD RRET 
%token TRBRACE TLBRACE TASSIG TINITASSIG TLPAR TRPAR
%token RINT RFLOAT TCLT TCLE TCGT TCGE TCEQ TCNE TMUL TDIV TADD TSUB 
%token TCOMMA
%token ROR RAND RNOT 

/* Hemen erazagutu atributuak dauzkaten ez-bukaerakoak. 
   Adibidez, aldagaia ez-bukaerakoak izena atributua izango balu:
%type <izena> aldagaia
   Analisi lexiko eta sintaktikorako atributurik ez.
   
*/
%type <e> adierazpena
%type <im> izena
%type <izena> aldagaia
%type <izenak> id_zerrenda id_zerrendaren_bestea
%type <erref> M
%type <mota> mota
%type <main> azpiprograma azpiprogramak
//%type <main_zer> bl_eraz
%type <adi> adi_zerrenda adi_zerrenda_bestea
//%type <param> par_zerrenda par_zerrendaren_bestea
%type <brcon> bloke sententzia sententzia_zerrenda

%left RNOT
%left RAND ROR
%nonassoc TCGE TCGT TCEQ TCNE TCLE TCLT
%left TADD TSUB
%left TMUL TDIV

%start programa

%%

programa : RPACK RMAIN {kodea.agGehitu("proc main");} bloke_nag 
            {kodea.agGehitu("halt"); 
            kodea.idatzi();}
         ;

bloke_nag : bl_eraz M {kodea.agGehitu("goto");} azpiprogramak 
            {ErrefLista *erreflista = new ErrefLista;
            erreflista->push_back($<erref>2);
            kodea.agOsatu(*erreflista, $<main>4);
           }
          ;

azpiprogramak : azpiprogramak azpiprograma {$<main>$ = $<main>1 + $<main>2;}
               | azpiprograma {$<main>$ = $<main>1;}

azpiprograma : RFUNC izena argumentuak auk_mota bloke
               {$<main>$ = $<im>2->main;
               if ($<main>$ == 0) kodea.agGehitu("endproc " + $<im>2->izena);}

izena : RMAIN 
         {$<im>$ = new izmain;
         $<im>$->main = kodea.lortuErref();}
      | TID 
         {$<im>$ = new izmain;
         $<im>$->izena = *$<izena>1;
         $<im>$->main = 0;
         kodea.agGehitu("proc " + *$<izena>1);}

bloke : TLBRACE bl_eraz anon_azpi sententzia_zerrenda TRBRACE
         {$<brcon>$ = new breakcont;
         //$<brcon>$->breakl.insert($<brcon>$->breakl.end(), $<brcon>2->breakl.begin(), $<brcon>2->breakl.end());
         $<brcon>$->breakl.insert($<brcon>$->breakl.end(), $<brcon>4->breakl.begin(), $<brcon>4->breakl.end());
         
         //$<brcon>$->continuel.insert($<brcon>$->continuel.end(), $<brcon>2->continuel.begin(), $<brcon>2->continuel.end());
         $<brcon>$->continuel.insert($<brcon>$->continuel.end(), $<brcon>4->continuel.begin(), $<brcon>4->continuel.end());

         }

anon_azpi : anon_azpi anon
           |

anon : TID TINITASSIG RFUNC {kodea.agGehitu("proc " + *$<izena>1);} argumentuak auk_mota bloke 
      {kodea.agGehitu("endproc " + *$<izena>1);}

bl_eraz : RVAR TLPAR eraz_l TRPAR bl_eraz 
            //{$<main_zer>$ = new ErrefLista;
            //$<main_zer>$ = $<main_zer>5;}
         | RVAR eraz bl_eraz 
            //{$<main_zer>$ = new ErrefLista;
            //$<main_zer>$ = $<main_zer>3;}

         | //{$<main_zer>$ = new ErrefLista;
           // $<main_zer>$->push_back(kodea.lortuErref());}

eraz_l : eraz_l eraz
       | eraz

eraz : id_zerrenda mota
      {kodea.erazagupenakGehitu(*$<mota>2, *$<izenak>1);}

id_zerrenda : TID id_zerrendaren_bestea
               {$<izenak>$ = new IdLista;
               $<izenak>$->insert($<izenak>$->end(), $<izenak>2->begin(), $<izenak>2->end());
               $<izenak>$->push_front(*$<izena>1);}

id_zerrendaren_bestea : TCOMMA TID id_zerrendaren_bestea
                        {$<izenak>$ = new IdLista;
                        $<izenak>$->insert($<izenak>$->end(), $<izenak>3->begin(), $<izenak>3->end());
                        $<izenak>$->push_front(*$<izena>2);}
                      | {$<izenak>$ = new IdLista;}

mota : RINT {$<mota>$ = new string("int");}
     | RFLOAT {$<mota>$ = new string("real");}

auk_mota : mota
         |

argumentuak : TLPAR par_zerrenda TRPAR 
            
par_zerrenda : id_zerrenda mota {kodea.parametroakGehitu(*$<mota>2, *$<izenak>1);} par_zerrendaren_bestea
             | 

par_zerrendaren_bestea : TCOMMA id_zerrenda mota {kodea.parametroakGehitu(*$<mota>3, *$<izenak>2);} par_zerrendaren_bestea 
                       | 

sententzia_zerrenda : sententzia_zerrenda sententzia
                        {$<brcon>$ = new breakcont;
                        $<brcon>$->breakl.insert($<brcon>$->breakl.end(), $<brcon>1->breakl.begin(), $<brcon>1->breakl.end());
                        $<brcon>$->breakl.insert($<brcon>$->breakl.end(), $<brcon>2->breakl.begin(), $<brcon>2->breakl.end());
                        
                        $<brcon>$->continuel.insert($<brcon>$->continuel.end(), $<brcon>1->continuel.begin(), $<brcon>1->continuel.end());
                        $<brcon>$->continuel.insert($<brcon>$->continuel.end(), $<brcon>2->continuel.begin(), $<brcon>2->continuel.end());

                        }

                        
                    | sententzia 
                        //{$<brcon>$ = new breakcont;
                        {$<brcon>$ = $<brcon>1;}

sententzia : aldagaia TASSIG TID TLPAR adi_zerrenda TRPAR
            {$<brcon>$ = new breakcont;
            kodea.parametroekinDeitu(*$<adi>5);
            kodea.agGehitu(*$<izena>1 + " := call " + *$<izena>3);}

           | aldagaia TASSIG adierazpena
               {$<brcon>$ = new breakcont;
               kodea.agGehitu(*$<izena>1 + " := " + $<e>3->izena);}

           | TID TLPAR adi_zerrenda TRPAR
               {$<brcon>$ = new breakcont;
               kodea.parametroekinDeitu(*$<adi>3);
               kodea.agGehitu("call " + *$<izena>1);}

           | RIF adierazpena M bloke M
               {$<brcon>$ = $<brcon>4;
               //kodea.agOsatu($<brcon>5->breakl, $<erref>3);
               //kodea.agOsatu($<brcon>5->continuel, $<erref>5);
               kodea.agOsatu($<e>2->truel, $<erref>3);
               kodea.agOsatu($<e>2->falsel, $<erref>5);}

           | RFOR M bloke M
               {$<brcon>$ = new breakcont;
               kodea.agOsatu($<brcon>3->breakl, $<erref>4 + 1);
               kodea.agOsatu($<brcon>3->continuel, $<erref>2);
               kodea.agGehitu("goto " + to_string($<erref>2));}

           | RFOR M adierazpena M bloke M
               {$<brcon>$ = new breakcont;
               kodea.agOsatu($<brcon>5->breakl, $<erref>6 + 1);
               kodea.agOsatu($<brcon>5->continuel, $<erref>2);
               kodea.agOsatu($<e>3->truel, $<erref>4);
               kodea.agOsatu($<e>3->falsel, $<erref>6 + 1);
               kodea.agGehitu("goto " + to_string($<erref>2));}
           | RBRK adierazpena
               {$<brcon>$ = new breakcont;
               $<brcon>$->breakl = $<e>2->truel;
               kodea.agOsatu($<e>2->falsel, kodea.lortuErref());}
           | RCNT
               {$<brcon>$ = new breakcont;
               $<brcon>$->continuel.push_back(kodea.lortuErref());
               kodea.agGehitu("goto");}
           | RRD TLPAR aldagaia TRPAR 
               {$<brcon>$ = new breakcont;
               kodea.agGehitu("read " + $<e>3->izena);}
           | RPRT TLPAR adierazpena TRPAR
               {$<brcon>$ = new breakcont;
               kodea.agGehitu("write " + $<e>3->izena);
               kodea.agGehitu("writeln");}
           | RRET adierazpena 
               {$<brcon>$ = new breakcont;
               kodea.agGehitu("return " + $<e>2->izena);}

aldagaia : TID {$<izena>$ = $<izena>1 ;}

adi_zerrenda : adierazpena adi_zerrenda_bestea
                  {$<adi>$ = new IdLista;
                  $<adi>$->insert($<adi>$->end(), $<adi>2->begin(), $<adi>2->end());
                  $<adi>$->push_front(*$<izena>1);}
             | {$<adi>$ = new IdLista;}

adi_zerrenda_bestea : TCOMMA adierazpena adi_zerrenda_bestea
                        {$<adi>$ = new IdLista;
                        $<adi>$->insert($<adi>$->end(), $<adi>3->begin(), $<adi>3->end());
                        $<adi>$->push_front($<e>2->izena);}
                    | {$<adi>$ = new IdLista;}
                                
adierazpena : adierazpena TADD adierazpena
               {$<e>$ = new adierazpena;
               $<e>$->izena = kodea.idBerria() ;
               kodea.agGehitu($<e>$->izena + " := " + $<e>1->izena + "+" + $<e>3->izena) ;}
            | adierazpena TSUB adierazpena
               {$<e>$ = new adierazpena;
               $<e>$->izena = kodea.idBerria() ;
               kodea.agGehitu($<e>$->izena + " := " + $<e>1->izena + "-" + $<e>3->izena) ;}
            | adierazpena TMUL adierazpena
               {$<e>$ = new adierazpena;
               $<e>$->izena = kodea.idBerria() ;
               kodea.agGehitu($<e>$->izena + " := " + $<e>1->izena + "*" + $<e>3->izena) ;}
            | adierazpena TDIV adierazpena
               {$<e>$ = new adierazpena;
               $<e>$->izena = kodea.idBerria() ;
               kodea.agGehitu($<e>$->izena + " := " + $<e>1->izena + "/" + $<e>3->izena) ;}

            | adierazpena TCEQ adierazpena 
               {//$<e>$ = new adierazpena;
                $<e>$ = sortuErlazionala($<e>1->izena, " == ", $<e>3->izena) ; } 
            | adierazpena TCGT adierazpena
               {//$<e>$ = new adierazpena;
                $<e>$ = sortuErlazionala($<e>1->izena ," > ", $<e>3->izena)  ;} 
            | adierazpena TCLT adierazpena
               {//$<e>$ = new adierazpena;
                $<e>$ = sortuErlazionala($<e>1->izena ," < ", $<e>3->izena) ; } 
            | adierazpena TCGE adierazpena
               {//$<e>$ = new adierazpena;
                $<e>$ = sortuErlazionala($<e>1->izena ," >= ", $<e>3->izena) ; } 
            | adierazpena TCLE adierazpena
               {//$<e>$ = new adierazpena;
                $<e>$ = sortuErlazionala($<e>1->izena ," <= ", $<e>3->izena) ; } 
            | adierazpena TCNE adierazpena  
               {//$<e>$ = new adierazpena;
                $<e>$ = sortuErlazionala($<e>1->izena ," != ", $<e>3->izena) ; }
            
            | adierazpena ROR M adierazpena
               {$<e>$ = new adierazpena; 
               kodea.agOsatu($<e>1->falsel, $<erref>3);
               $<e>$->truel.insert($<e>$->truel.end(), $<e>1->truel.begin(), $<e>1->truel.end());
               $<e>$->truel.insert($<e>$->truel.end(), $<e>4->truel.begin(), $<e>4->truel.end());
               $<e>$->falsel = $<e>4->falsel;}
               
            | adierazpena RAND M adierazpena
               {$<e>$ = new adierazpena; 
               kodea.agOsatu($<e>1->truel, $<erref>3);
               $<e>$->falsel.insert($<e>$->falsel.end(), $<e>1->falsel.begin(), $<e>1->falsel.end());
               $<e>$->falsel.insert($<e>$->falsel.end(), $<e>4->falsel.begin(), $<e>4->falsel.end());
               $<e>$->truel = $<e>4->truel; }

            | RNOT adierazpena 
               {$<e>$ = new adierazpena; 
               $<e>$->falsel = $<e>2->truel;
               $<e>$->truel = $<e>2->falsel;}

            | TLPAR adierazpena TRPAR 
               {$<e>$ = $<e>2;}
            | aldagaia  
               {$<e>$ = new adierazpena; 
               $<e>$->izena = *$<izena>1;}
            | TKTE_INT  
               {$<e>$ = new adierazpena; 
               $<e>$->izena = *$<z_izena>1;}
            | TKTE_FLOAT32 
               {$<e>$ = new adierazpena; 
               $<e>$->izena = *$<z_izena>1;}

M  : {$<erref>$ = kodea.lortuErref();}
   ;
%%
