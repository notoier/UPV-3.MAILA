
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
func			TOKEN(RFUNC) ;
main			TOKEN(RMAIN) ;
var			    TOKEN(RVAR) ;
int             TOKEN(RINT) ;


=                       TOKEN(TASSIG) ;
:=			            TOKEN(TINITASSIG) ;
\{                      TOKEN(TLBRACE) ;
\}                      TOKEN(TRBRACE) ;
\(                      TOKEN(TLPAR) ;
\)                      TOKEN(TRPAR) ;

,                       TOKEN(TCOMA);

\*                      TOKEN(TMUL) ;
\+                      TOKEN(TADD);
\-                      TOKEN(TSUB);
\<                      TOKEN(TLESS);
\>                      TOKEN(TMORE);
\/                      TOKEN(TDIV);

[ \t\n]                 ;
\/\/.*\n                        TOKEN(TCOMMENT1);
\/\*([^\/\*]|(\*[\*]*[^\/\*]))*\*[\*]\/        TOKEN(TCOMMENT2);


[a-zA-Z](_?[a-zA-Z0-9]+)*_?                                 TOKEN(TID) ; 
([1-9][0-9]*|0)\.[0-9]+([eE][-+]?[1-9][0-9]+)?                  TOKEN(TKTE_FLOAT32);
([1-9][0-9]*|0)                                                 TOKEN(TKTE_INT); 

.                       { yyerror("Token ezezaguna");}
%%

