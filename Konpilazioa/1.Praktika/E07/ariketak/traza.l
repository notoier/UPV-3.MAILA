%%
[Pp][Rr][Oo][Cc][Ee][Dd][Uu][Rr][Ee] {printf("[PROCEDURE]");}
[Bb][Ee][Gg][Ii][Nn]                 {printf("[BEGIN]");}
[Ee][Nn][Dd]                         {printf("[END]");}
[Tt][Rr][Aa][Zz][Aa]                 {printf("[TRAZA]");}
[a-zA-Z][a-zA-Z0-9]*                 {printf("[ID]");}
\t+		             	     ;
\n				     {printf("\n");}
.                                    ECHO;
%%
