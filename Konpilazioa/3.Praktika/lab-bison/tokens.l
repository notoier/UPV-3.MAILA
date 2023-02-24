%option yylineno 

%{
 #include <string>
 #include <iostream>
 #include <vector>
 using namespace std;
 #include "parser.hpp" 


 #define TOKEN(t) return t
 #define TOKENST(t) yylval.izena = new std::string(yytext, yyleng) ; return t 

 extern "C" int yywrap() { return(1) ; }  
 extern int yyerror(const char *) ; 

%}

%%
package			TOKEN(RPACK);
func			TOKEN(RFUNC);
main			TOKEN(RMAIN);
var			    TOKEN(RVAR);


=                       TOKEN(TASSIG);
:=			            TOKEN(TINITASSIG);
\{                      TOKEN(TLBRACE);
\}                      TOKEN(TRBRACE);
\(                      TOKEN(TLPAREN);
\)                      TOKEN(TRPAREN);

\*                      TOKEN(TMUL);
\+                      TOKEN(TADD);
\-                      TOKEN(TSUB);
\/                      TOKEN(TDIV);
==                      TOKEN(TEQU);

[ \t\n]                 ;

[a-zA-Z][a-zA-Z0-9]*    TOKENST(TID) ; 
[0-9]+\.[0-9]+          TOKENST(TKTE_FLOAT32);
[0-9]+                  TOKENST(TKTE_INT); 

.                       { yyerror("Token ezezaguna");}
%%

