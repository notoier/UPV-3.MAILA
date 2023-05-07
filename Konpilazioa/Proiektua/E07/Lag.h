#ifndef LAG_H_
#define LAG_H_

#include <string>
#include <list>

typedef std::list<std::string> IdLista;
typedef std::list<int> ErrefLista;

struct adierazpena {
  std::string izena;
  ErrefLista truel;  // true hitz erreserbatua c-z
  ErrefLista falsel; // false hitz erreserbatua c-z
};

struct izmain {
  std::string izena;
  int main;
};

struct breakcont {
  ErrefLista breakl; //break hitz erreserbatua
  ErrefLista continuel; //continue hitz erreserbatua
};


adierazpena* sortuErlazionala(std::string, std::string, std::string);

#endif /* LAG_H_ */
