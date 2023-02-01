%{
  int identifiers = 0;
  int reals = 0;
%}

%%
[Pp][Rr][Oo][Cc][Ee][Dd][Uu][Rr][Ee] ;
[Bb][Ee][Gg][Ii][Nn]                 ;
[Ee][Nn][Dd]                         ;
[Tt][Rr][Aa][Zz][Aa]                 ;
#[^#\n]*\n                           ;
[a-zA-Z](_?[a-zA-Z0-9]+)*            {++identifiers;}
[0-9]+\.[0-9]+([eE][-+]?[0-9]+)?	   {++reals;}
\n     ;
.      ;

%%

int main() {
  yylex();
  printf("Number of identifiers: %d \n", identifiers);
  printf("Count of real numbers: %d \n", reals);
}
