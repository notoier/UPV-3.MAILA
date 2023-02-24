
%{
 #include <string>
 #include <iostream>
 #include <vector>
 using namespace std;
 #include "parser.hpp" 


  #define TOKEN(t) return t
 extern "C" int yywrap() { return(1) ; }  
 extern int yyerror(const char *); 

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
\!=             TOKEN(TCNE);

[ \t\n]        ;
\/\/.*\n                      TOKEN(TCOMMENT1);
\/\*([^\*]|\*+[^\*\/])*\*+\/  TOKEN(TCOMMENT2);

[a-zA-Z][a-zA-Z0-9]*    TOKEN(TID) ; 
[0-9]+\.[0-9]+          TOKEN(TKTE_FLOAT32);
[0-9]+                  TOKEN(TKTE_INT); 

.              { yyerror("Token ezezaguna");}
