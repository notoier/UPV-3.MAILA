#include <iostream>
extern int yyparse();
using namespace std;

int yyerrornum = 0;

int main(int argc, char **argv)
{
  cout << "hasi da..." << endl << endl ;
  if (yyparse() == 0 && yyerrornum == 0) { 
    cout << "ONDO bukatu da..." << endl << endl ;
  }
  else {
    cout << "GAIZKI bukatu da." << endl << "Errore kopurua: " << yyerrornum << endl << endl ;
  }
  return 0;
}
