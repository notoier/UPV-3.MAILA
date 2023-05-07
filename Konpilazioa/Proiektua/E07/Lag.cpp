#include "Lag.h"
#include "Kodea.h"

using namespace std; 

extern Kodea kodea;
  

adierazpena *sortuErlazionala(string e1, string erag, string e2) {
 adierazpena *emaitza; 
 emaitza = new adierazpena; 
 emaitza->truel.push_back(kodea.lortuErref()) ; 
 emaitza->falsel.push_back(kodea.lortuErref()+1) ;
 kodea.agGehitu("if " + e1 + erag + e2 + " goto") ;
 kodea.agGehitu("goto") ;
 return emaitza;
}
