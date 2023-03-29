#ifndef LAG_H_
#define LAG_H_

#include <string>
#include <list>

typedef std::list<std::string> IdLista;
typedef std::list<int> ErrefLista;

struct adi {
  std::string izena ;
  ErrefLista truel ;  // true hitz erreserbatua c-z
  ErrefLista falsel ; // false hitz erreserbatua c-z
};

adi* sortuAritmetikoa(std::string, std::string, std::string);
adi* sortuErlazionala(std::string, std::string, std::string);

#endif /* LAG_H_ */