
%{
 #include <string>
 #include <iostream>
 #include <vector>
 using namespace std;
 #include "Lag.h"
 #include "parser.hpp" 


#define TOKEN(t) return t 
#define TOKENST(t) yylval.izena = new std::string(yytext, yyleng); return t 

 extern "C" int yywrap() { return(1) ; }  
 extern int yyerror(const char *); 

%}


%%
package			TOKEN(RPACK) ;
func			TOKEN(RFUNC) ;
main			TOKENST(RMAIN) ;
var			    TOKEN(RVAR) ;
int             TOKENST(RINT) ;
float32         TOKENST(RFLOAT32);
for             TOKEN(RFOR);
break           TOKEN(RBREAK);
continue        TOKEN(RCONT);
read            TOKEN(RREAD);
println         TOKEN(RPRINT);
return          TOKEN(RRETURN);
if              TOKEN(RIF);

=               TOKEN(TASSIG);
:=			    TOKEN(TINITASSIG) ;
\{              TOKEN(TLBRACE);
\}              TOKEN(TRBRACE);
\(              TOKEN(TLPAR);
\)              TOKEN(TRPAR);

\*              TOKENST(TMUL);
\+              TOKENST(TADD);
\-              TOKENST(TSUB);
\/              TOKENST(TDIV);
,               TOKEN(TCOMMA);

==              TOKEN(TCEQ);
!=              TOKEN(TCNE);
>=              TOKENST(TCGE);
\<=             TOKENST(TCLE);
>               TOKENST(TCGT);
\<              TOKENST(TCLT);


[ \t\n]                 ;

[a-zA-Z](_?[a-zA-Z0-9]+)*_?   TOKENST(TID) ;
([1-9]+|0).[0-9]+([eE][+-]?[0-9]+)?          TOKENST(TKTE_FLOAT32);
[0-9]+                  TOKENST(TKTE_INT); 
\/\/.*\n         ;
\/\*([^\*]|\*+[^\*\/])*\*+\/ ;





.                       { yyerror("Token ezezaguna");}
%%

