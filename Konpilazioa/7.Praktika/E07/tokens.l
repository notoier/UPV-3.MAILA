%option yylineno

%{
 #include <iostream>
 using namespace std ;
 #include "Lag.h"
 #include "parser.h"

 /* Hau atributurik ez duten tokenentarako: */
 #define TOKEN(t) return t
 
 /* Hau izena atributua dutenetarako:       */
 #define TOKENST(t) yylval.izena = new std::string(yytext, yyleng) ; return t 
 
%}

%%
func                    TOKEN( RFUNC ) ;
main                    TOKEN( RMAIN ) ;
var                     TOKEN( RVAR ) ;
integer                 TOKEN( RINTEGER ) ;
float                   TOKEN( RFLOAT ) ;
if                      TOKEN( RIF ) ;
loop                    TOKEN( RLOOP ) ;
exit			TOKEN( REXIT ) ;

\{                      TOKEN( TLBRACE );
\}                      TOKEN( TRBRACE );
\(                      TOKEN( TLPAREN ) ;
\)                      TOKEN( TRPAREN ) ;
,                       TOKEN( TCOMMA ) ;    
:                       TOKEN( TCOLON ) ;
;                       TOKEN( TSEMIC ) ;

=                       TOKEN( TASSIG );

\+                      TOKENST( TADD );
-                       TOKENST( TSUB );
\*                      TOKENST( TMUL );
\/                      TOKENST( TDIV );
\<                      TOKENST( TCLT ) ;
\<=                     TOKENST( TCLE ) ;
>                       TOKENST( TCGT ) ;
>=                      TOKENST( TCGE ) ;
 
[ \t\n]                 ;

[a-zA-Z][a-zA-Z0-9_]*   TOKENST(TID) ; 
[0-9]+\.[0-9]+          TOKENST(TNUM_FLOAT);
[0-9]+                  TOKENST(TNUM_INTEGER);


.                       {printf("Token ezezaguna!\n"); yyterminate();}

%%

