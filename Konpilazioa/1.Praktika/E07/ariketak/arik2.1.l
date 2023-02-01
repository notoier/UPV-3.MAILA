
%%
[a-zA-Z](_?[0-9a-zA-Z]+)*	 { printf("%s:\tBAI\n",yytext); }
\n  ;
.+   	                         { printf("%s:\tEZ\n",yytext); }
%%

