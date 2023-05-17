%{
 #include <iostream>
 #include <vector>
 using namespace std;
 //#include "parser.h"

 #include "Lag.h"
 #include "parser.hpp" 

 #define TOKEN(t) return t
 //#define COMMENT(c) printf("%s\n", c)
 extern "C" int yywrap() { return(1) ; }  
 extern int yyerror(const char *); 

/* Hau izena atributua dutenetarako:       */
 #define TOKENIZ(t) yylval.izena = new std::string(yytext, yyleng) ; return t 
 /* Hau balioa atributua dutenetarako:       */
 #define TOKENBAL(t) yylval.balioa = new std::string(yytext, yyleng) ; return t 
%}

%%
package			TOKEN(RPACK) ;
func		    TOKEN(RFUNC) ;
main			TOKEN(RMAIN) ;
var			    TOKEN(RVAR)  ;
int             TOKEN(RINT)  ;
float32         TOKEN(RFLOAT);
return          TOKEN(RRET);
if              TOKEN(RIF);
break           TOKEN(RBRK);
for             TOKEN(RFOR);
continue        TOKEN(RCNT);
read            TOKEN(RRD);
println         TOKEN(RPRT);
and             TOKEN(RAND);
or              TOKEN(ROR);
not             TOKEN(RNOT);


=               TOKEN(TASSIG);
:=			    TOKEN(TINITASSIG) ;
\{              TOKEN(TLBRACE);
\}              TOKEN(TRBRACE);
\(              TOKEN(TLPAR);
\)              TOKEN(TRPAR);

,               TOKEN(TCOMMA);

\*              TOKEN(TMUL);
\+              TOKEN(TADD);
\-              TOKEN(TSUB);
\/              TOKEN(TDIV);

\<              TOKEN(TCLT);
\>              TOKEN(TCGT);
\<=             TOKEN(TCLE);
\>=             TOKEN(TCGE);
==              TOKEN(TCEQ);
!=              TOKEN(TCNE);


[ \t\n]                     ;
\/\/.*\n                      
\/\*([^\*]|\*+[^\*\/])*\*+\/  

[a-zA-Z]([a-zA-Z0-9]|_[a-zA-Z0-9])*_?               TOKENIZ(TID) ; 

(0|[1-9][0-9]*)\.[0-9]+([eE][-+]?[0-9]+)?           TOKENBAL(TKTE_FLOAT32);
(0|[1-9][0-9]*)                                     TOKENBAL(TKTE_INT); 

.              { yyerror("Token ezezaguna");}
