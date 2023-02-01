%%
[0-9]+  {printf("%s:\tBAI\n", yytext);}
\n      ;
.+      {printf("%s:\tEZ\n", yytext);}
%%