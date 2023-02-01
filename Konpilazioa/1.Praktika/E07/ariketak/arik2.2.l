%%
[0-9]+\.[0-9]+([eE][-+]?[0-9]+)?	 { printf("%s:\tBAI\n",yytext); }
\n  ;
.+   	                         { printf("%s:\tEZ\n",yytext); }
%%

