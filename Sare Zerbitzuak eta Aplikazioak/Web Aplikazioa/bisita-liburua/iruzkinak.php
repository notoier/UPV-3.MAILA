<?php
	require_once("bisita_liburua.inc");
    web_header();
?>

		<p>Bisita liburua</p><br></div>
		<?php
			if(!file_exists($BL_FILE))
			{
				echo('<p><br><br>Bisita liburua hutsik dago.</p>');
			}
			elseif(!($bl=simplexml_load_file($BL_FILE)))
			{
				echo('<p><br><br>Errore bat gertatu datu bisita liburua irakurtzean. Barkatu eragozpenak</p>');
			}
			else
			{

				$kop=0;
				echo '<p><br>';
				foreach($bl->bisita as $bisita)
				{
					// Iruzkin bat pantailaratzeko 2 baldintza hauetako bat bete behar
					// da (lehenengoa betetzen bada, bigarrena ez da ebaluatzen):
					//   · 'erab' eremua ez da bidali (iruzkin zerrenda osoa eskatu da).
					//   · 'erab' eremuako balioa eta iruzkinari dagokion izena berdinak
					//      dira (minuskulak eta maiuskulak kontuan ez hartzeko bi
					//      balioak minuskulara pasatzen dira).

					if(!isset($_POST['erab']) ||
					   (strtolower($_POST['erab']) == strtolower($bisita->izena)))
					{
						$kop++;

						echo('Data:'.$bisita->data."<br>");
						echo('Izena: '.$bisita->izena.'<br>');
						if($bisita->eposta && $bisita->eposta['erakutsi']=="bai")
							echo('E-posta: '.$bisita->eposta.'<br>');


						echo('Iruzkina: '.$bisita->iruzkina.'<br>');

					}
					echo '<br><br>';
				}
				// Erakutsi mezu bat ez bada iruzkinik aurkitu.
				if($kop==0)
					echo('Ez da aurkitu '.$_POST['erab'].' izeneko erabiltzailerik.');
			}
			echo '</p></div><br>';
	web_footer();
		?>

