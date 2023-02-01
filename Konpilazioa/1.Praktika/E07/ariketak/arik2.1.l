
%%
<<<<<IKASLEAK BETE DEZAN>>>>>	 { printf("%s:\tBAI\n",yytext); }
\n  ;
.+   	                         { printf("%s:\tEZ\n",yytext); }
%%

