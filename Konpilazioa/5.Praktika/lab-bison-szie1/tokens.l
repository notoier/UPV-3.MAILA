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
func                    TOKEN(RFUNC) ;
main                    TOKEN(RMAIN) ;
[ \t\n]                 ;

[a-zA-Z][a-zA-Z0-9_]*   TOKENST(TID) ; 
[0-9]+\.[0-9]+          TOKENST(TNUM_FLOAT);
[0-9]+                  TOKENST(TNUM_INTEGER);


\{                      TOKEN(TLBRACE);
\}                      TOKEN(TRBRACE);


=                       TOKEN(TASSIG);
\+                      TOKEN(TADD);
-                       TOKEN(TSUB);
\*                      TOKEN(TMUL);
\/                      TOKEN(TDIV);

.                       {cout << "Token ezezaguna!" << endl; yyterminate();}

%%

