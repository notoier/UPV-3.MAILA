function balidatu(f)
{
	// Formularioko balioak irakurri
	var izena = f.izena.value;
	var eposta = f.eposta.value;
	var pribatua = f.pribatua.checked;
	var iruzkina = f.iruzkina.value;
	
	// Ziurtatu beteta egon behar diren eremuak beteta daudela.
	var errorea = "";
	if(izena=="")
		errorea += "\tIzena eremua bete behar duzu.\n";
	if(iruzkina=="")
		errorea += "\tIruzkina eremua bete behar duzu.\n";
	
	// Ziurtatu eposta helbidearen formatua zuzena dela.
	if(eposta != "" && !helbide_formatua(eposta))
		errorea += "\tEposta helbidearen formatua ez da zuzena.\n";
		
	// Errorerik badago, mezua erakutsi.
	if(errorea != "")
	{
		alert("Formularioa ez duzu ondo bete:\n" + errorea);
		return false;
	}
	else
		return true;
}

// E-posta helbidearen formatua zuzena bada true itzultzen du eta false bestela.
function helbide_formatua(helbidea)
{
	// Ziurtatu '@' karakterea behin, eta behin bakarrik, agertzen dela.
	if(helbidea.split("@").length != 2)
		return false;
	// Ziurtatu '@' karakterea ez dela lehena.
	if(helbidea.indexOf("@") == 0)
		return false;
	// Ziurtatu '@' karakterearen ondoren '.' karaktereren bat badagoela.
	if(helbidea.lastIndexOf(".") < helbidea.lastIndexOf("@"))
		return false;
	// Ziurtatu azkeneko puntuaren atzetik gutxienez beste 2 karaktere daudela.
	if(helbidea.lastIndexOf(".") + 2 > helbidea.length - 1)
		return false;
	return true;
}
