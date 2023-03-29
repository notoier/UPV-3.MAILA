#include "Lag.h"
#include "Kodea.h"

using namespace std; 

extern Kodea kodea;
  
adi *sortuAritmetikoa(string e1, string erag, string e2) {
 adi *emaitza; 
 emaitza = new adi; 
 emaitza->izena = kodea.idBerria() ;
 kodea.agGehitu(emaitza->izena + " := " + e1 + erag + e2) ; 
 return emaitza;
}


adi *sortuErlazionala(string e1, string erag, string e2) {
 adi *emaitza; 
 emaitza = new adi; 
 emaitza->truel.push_back(kodea.lortuErref()) ; 
 emaitza->falsel.push_back(kodea.lortuErref()+1) ;
 kodea.agGehitu("if " + e1 + erag + e2 + " goto") ;
 kodea.agGehitu("goto") ;
 return emaitza;
}
