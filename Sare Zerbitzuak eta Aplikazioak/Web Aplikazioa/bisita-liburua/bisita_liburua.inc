<?php
$BL_FILE='data/bisita_liburua.xml';		// Iruzkinak gordeko diren fitxategia.

// Balioztatu e-posta helbide baten formatua.
function formatua($helbidea)
{
	$at=strpos($helbidea,'@');
	if($at === false)	// Ez da '@' karakterea aurkitu.
		return false;
	if($at == 0)			// '@' karakterea lehenengoa da.
		return false;
	if($at != strrpos($helbidea,'@'))	// '@' karakterea behin baino gehiagotan aurkitu da.
		return false;
	$dot = strrpos($helbidea,'.');
	if($dot === false) 	// Ez dago punturik.
		return false;
	if($dot < $at)			// Ez dago punturik '@' karakterearen ondoren.
		return false;
	if($dot+2 > strlen($helbidea) - 1)	// Azkeneko puntuaren atzetik ez daude gutxienez 2 karaktere.
		return false;
	return true;
}

// Balioztatu iruzkin berri bat sortzeko formularioko datuak.
// Gogoratu nahiz eta balioztapen hau bezeroan egin den, zerbitzarian berriro egitea ezinbestekoa dela.
// Errorerik egonez gero errore mezu bat itzultzen du, bestela string hutsa.
function balidatu_berria($izena, $eposta, $iruzkina)
{
	$mezua = '';
	if($izena == '')	// Izena eremua ez da bete.
		$mezua = $mezua.'Izena eremua ez da bete';
	if($eposta != '' && !formatua($eposta))	// E-posta eremua bete da, baina bere formatua ez da zuzena.
		$mezua = $mezua.'Posta helbidearen formatua ez da zuzena.';
	if($iruzkina == '')	// Iruzkina eremua ez da bete.
		$mezua = $mezua.'Iruzkina eremua ez da bete.';
	return $mezua;
}

// Iruzkina datu basean gorde. Errorerik ezean true itzultzen du eta false bestela.
function gorde_iruzkina($izena, $eposta, $pribatua, $iruzkina)
{
	global $BL_FILE;	// Funtzio baten barrutik aldagai global erabiltzeko 'global' erabili behar da.
	
	if(!file_exists($BL_FILE))	// Iruzkinak gordetzeko XML fitxategia ez bada existitzen, sortu iruzkinik gabeko XML fitxategia.
		$bl=new SimpleXMLElement('<?xml version="1.0" encoding="UTF-8"?><!DOCTYPE bisitak SYSTEM "bisita_liburua.dtd"><bisitak azkenid="b0"></bisitak>');
	else	// Bestela, kargatu XML fitxategia.
		$bl=simplexml_load_file($BL_FILE);
	if(!$bl)
		return false;
	
	$id = "b" . ((int) substr($bl['azkenid'], 1) + 1);	// Kalkulatu iruzkin berriaren identifikadorea.
	$berria=$bl->addChild('bisita');	// Sortu 'bisita' etiketa.
	$berria['id']=$id;
	$berria->addChild('data',date('r'));	// Sortu 'bisita' etiketa barruko etiketak.
	$berria->addChild('izena',$izena);
	$berria->addChild('iruzkina',$iruzkina);
	if($eposta!='')
	{
		$ep=$berria->addChild('eposta',$eposta);
		$ep->addAttribute('erakutsi',$pribatua?'ez':'bai');
	}
	$bl['azkenid']=$id;	// Eguneratu erroko 'azkenid' atributua.
	return $bl->asXML($BL_FILE);	// Gorde aldaketak fitxategian.
}

function web_header(){
    echo '<!DOCTYPE html>';
    echo '<html>';
    echo '<head>';
    echo '<meta charset="utf-8">';
    echo '<title>SZAko Webgunea</title>';
    echo '<link href="css/main.css" rel="stylesheet">';
    echo '</head>';
    echo '<body>';
    echo '<div id="content">';
    echo '<!-- Logoa Informatika Fakultatea -->';
    echo '<div id="banner">';
    echo '<img class="hr" id="logo" src="img/fakultatea.jpg" alt="Informatika Fakultatearen eraikuntza kanpotik">';
    echo '</div>';
    echo '<!-- Nabigazio menua -->';
    echo '<ul id="menu">';
    echo '<li><a href="index.html">Hasiera</a>';
    echo '</li>';
    echo '<div id="menu">';
    echo '<li><a href="mezua.html">Iruzkina bidali</a></li>';

//OHARRA: Bisita Liburua esteka gehitu

    echo '</div>';
    echo '</ul>';
    echo '<!-- Edukia -->';
    echo '<div id="main">';
    echo '<div class="heading"><br><br><br>';
}

function web_footer(){
    echo '<img class="hr" src="img/line_gradient.gif">';
    echo 'SZA irakasgaia. Informatika Ingeniaritza Gradua. UPV-EHU';
    echo '</div><!--Main-->';
    echo '</div> <!-- content -->';
    echo '</body>';
    echo '</html>';
}
?>
