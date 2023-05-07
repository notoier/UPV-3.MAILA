#ifndef KODEA_H_
#define KODEA_H_
#include <iostream>
#include <sstream>
#include <fstream>
#include <set>
#include <vector>
#include <list>
#include "Lag.h"

/* Sortuko den kodea kudeatzeko egitura. Kodea zuzenean idatzi beharrean, egitura honetan gordeko da, eta amaieran,
 * dena fitxategi batean idatziko da.
 */
class Kodea {

private:

	/**************************/
	/* BARNE ERREPRESENTAZIOA */
	/**************************/

	/* Kodea osatzen duten aginduak. */
	std::vector<std::string> aginduak;

	/* Identifikadore berriak sortzeko gakoa. Id bat sortzen den bakoitzean inkrementatuko da. */
	int hurId;


public:

	/*****************************/
	/* KODEA KUDEATZEKO METODOAK */
	/*****************************/

	/* Eraikitzailea */
	Kodea();

	/* Identifikadore berri bat sortzen du, "_t1, _t2, ..." modukoa eta beti desberdina. */
	std::string idBerria() ;

	/* Agindu berri bat gehitzen du egituran. */
	void agGehitu(const std::string &agKatea);

	/* Aldagai zerrenda eta mota emanda erazagupen aginduak sortu eta gehitu */
	void erazagupenakGehitu(const std::string &motaIzena, const IdLista &idIzenak);

	/* Parametro zerrenda eta mota emanda parametro erazagupen aginduak sortu eta gehitu */
	void parametroakGehitu(const std::string &motaIzena, const IdLista &idIzenak) ;

	void parametroekinDeitu(const IdLista &idIzenak) ;

	/* Adierazitako aginduei falta zaien erreferentzia gehitzen die.
	 * Adibidez: "goto" => "goto 20;" */
	void agOsatu(ErrefLista &agZenbakiak, const int balioa);

	/* Egituran metatutako aginduak fitxategian idazten ditu. */
	void idatzi();

	/* Hurrengo aginduaren zenbakia itzultzen du. */
	int lortuErref() const;

};

#endif /* KODEA_H_ */
