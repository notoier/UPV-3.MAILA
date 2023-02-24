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
   Ikurrek izan ditzaketen atributu-mota guztiak hemen zehaztu.
   Oharra: union egiturak bakarrik onartzen ditu oinarrizko datu-motak,
   osoko, erreal, karaktere eta erakusleak. 

%union {
    string *izena ; 
}
*/

/* 
   Tokenak erazagutu. Honek tokens.l fitxategiarekin 
   bat etorri behar du.
   Tokenek atributuak badituzte, hemen zehaztu behar da.
   Adibidez, identifikadoreek izena atributua izango balute:
%token <izena> TID
   Analisi lexiko eta sintaktikorako atributurik ez.
*/

%token RPACK RFUNC RMAIN RVAR RIF RBRK RCNT RFOR RPRT RRD RRET
%token TRBRACE TLBRACE TASSIG TINITASSIG TLPAR TRPAR
%token RINT RFLOAT
%token TCOMMA
%token TMUL TADD TSUB TDIV TCGE TCGT TCLE TCLT TCEQ TCNE
%token TID TKTE_FLOAT32 TKTE_INT

/* Hemen erazagutu atributuak dauzkaten ez-bukaerakoak. 
   Adibidez, aldagaia ez-bukaerakoak izena atributua izango balu:
%type <izena> aldagaia
   Analisi lexiko eta sintaktikorako atributurik ez.
*/
%left 


%start programa


%%

programa : RPACK RMAIN bloke_nag 
         ;

bloke_nag : bl_eraz azpiprogramak
          ;

azpiprogramak : azpiprogramak azpiprograma
               | azpiprograma 

azpiprograma : RFUNC izena argumentuak auk_mota bloke

izena : RMAIN 
      | TID

bloke : TLBRACE bl_eraz anon_azpi sententzia_zerrenda TRBRACE

anon_azpi : anon_azpi anon
           |

anon : TID TINITASSIG RFUNC argumentuak auk_mota bloke

bl_eraz : RVAR TLPAR eraz_l TRPAR bl_eraz
         | RVAR eraz bl_eraz
         |

eraz_l : eraz_l eraz
       | eraz

eraz : id_zerrenda mota

id_zerrenda : TID id_zerrendaren_bestea

id_zerrendaren_bestea : TCOMMA TID id_zerrendaren_bestea
                      |

mota : RINT
     | RFLOAT

auk_mota : mota
         |

argumentuak : TLPAR par_zerrenda TRPAR

par_zerrenda : id_zerrenda mota par_zerrendaren_bestea
             |

par_zerrendaren_bestea : TCOMMA id_zerrenda mota par_zerrendaren_bestea
                       |

sententzia_zerrenda : sententzia_zerrenda sententzia
                    | sententzia

sententzia : aldagaia TASSIG TID TLPAR adi_zerrenda TRPAR
           | aldagaia TASSIG adierazpena
           | TID TLPAR adi_zerrenda TRPAR
           | RIF adierazpena bloke
           | RFOR bloke
           | RFOR adierazpena bloke
           | RBRK adierazpena
           | RCNT
           | RRD TLPAR aldagaia TRPAR
           | RPRT TLPAR adierazpena TRPAR
           | RRET adierazpena

aldagaia : TID

adi_zerrenda : adierazpena adi_zerrenda_bestea
             |

adi_zerrenda_bestea : TCOMMA adierazpena adi_zerrenda_bestea
                    |
               
adierazpena : adierazpena TADD adierazpena
            | adierazpena TSUB adierazpena
            | adierazpena TMUL adierazpena
            | adierazpena TDIV adierazpena
            | adierazpena TCEQ adierazpena
            | adierazpena TCGT adierazpena
            | adierazpena TCLT adierazpena
            | adierazpena TCGE adierazpena
            | adierazpena TCLE adierazpena
            | adierazpena TCNE adierazpena
            | aldagaia
            | TKTE_INT
            | TKTE_FLOAT32
            | TLPAR adierazpena TRPAR


%%
