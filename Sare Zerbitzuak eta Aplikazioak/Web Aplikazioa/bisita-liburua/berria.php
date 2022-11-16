<?php
	require_once('bisita_liburua.inc');
	
	// Jaso formularioko balioak eta testuei hasierako eta amaierako hutsuneak kendu (trim).
	$izena=trim($_POST['izena']);
	$eposta=trim($_POST['eposta']);
	$pribatua=isset($_POST['pribatua']);
	$iruzkina=trim($_POST['iruzkina']);

	//Balidatu formularioko datuak.
	$errorea = balidatu_berria($izena, $eposta, $iruzkina);
	if($errorea == '')
		if(!gorde_iruzkina($izena, $eposta, $pribatua, $iruzkina))	// Gorde iruzkina datu basean (XML fitxategia).
			$errorea = '<li>Ezin izan da iruzkina datu basean gorde.</li>';

	//erantzun web orria itzuli
	web_header(); //goiburua: logoa eta nabigazio menua

	if($errorea==''){
		echo '<p>Eskerrik asko zure iruzkina uzteagatik</p></div><br>';
    }
	else{
		echo '<p>Errorea iruzkin berria jasotzean</p></div><br>';
    }
    web_footer(); //beherako zatia
?>