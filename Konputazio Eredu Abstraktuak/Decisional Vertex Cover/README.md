# DECISIONAL VERTEX COVER

[//]: <> (Gomendatzen da markdown irakurtzeko zerbaitekin irekitzea, markdown erabili izan baita)

Programa honetan, grafo batzuen Vertex Cover soluzioa aurkitzea nahi dugu. Horretarako, grafoa SAT formula baten moduan idatziko dugu, ondoren sat solver batekin ebazteko. **PySAT** liburutegia erabili dugu, haren ***CardEnc*** eta ***EncType***.

Erabilitako solver-a ***Glucose4*** izan da.
>Errendimendu handiko solver-a, problema handiak burutzeko gai da.

Erabilitako encoder-a ***Cardnetwork*** izan da.
>Bai grafo txikietzat bai grafo handientzat egokia da.

# Adierazpenak

Betebeharrezko eginkizun guztiak eginda daude eta programa guztiz funtzionatzen du.

# Fitxategiak

Programa hau bi fitxategietan banatuta dago, bata soluzioak lortzen dituena, ***decisional_vertex_cover.py***, eta bestea, grafoak emaitzarekin batera irudikatzen dituena, ***draw_graphs.py***.

Horrekin batera, bi datu pakete ditugu, grafo batzuekin. Hauek **mydata** karpeta batean daude.

## decisional_vertex_cover.py

   Fitxategi honetan egin beharreko 7 fitxategi daude:

- **reduce_VC_to_SAT**(graph, k)
- **answer_sat**(graph, k, allsolutions)
- **binary_search**(graph, low, high, allsolutions)
- **cover_2**(graph)
- **greedy**(graph)
- **isCoverRight**(graph, cover)
- **areCoversRight**(graph, cover)

Funtzio hauek eginbeharrezkoak dira, praktika burutzeko. Dena den, hauetatik gainera beste funtzio batzuk daude, batez ere, test-ak egin dituztenak, baina hauek jadanik eginda zeuden. Beraz, egin gabeko funtzio guztiak egin izan dira.

# Aldaketak eta arazoak

Praktika egin ahala, hainbat arazo eta aldaketak egon dira. Hasteko **isCoverRight(graph, length, cover)** bezala zegoen definituta, baina length erabiltzea ez denez beharrezkoa, kendu izan da, **isCoverRigth(graph, cover)** bezala hutsiz, gauza bera areCoversRight funtziorako. Erabilitako solver-ak eta encoder-ak askotan aldatuak izan dira. Ondoren, **greedy** eta **cover-2** hurbilpen algoritmoekin arazoak egon dira, izan ere, hasiera batean emaitza txarrak ematen zituen, adibidez, 9-10 eman behar zutenean, 1-1 edota 3-1 ematen zituzten. Azkenik, bueltak eman ostean, konponduak izan dira. Honekin batera, **answer_sat()** funtzioaren barruan, ez nuen erabiltzen **pysat**-eko **enum.models()** baizik eta soluzioak gehitzen joan eta hauk ezeztapenak cnf formulan sartu, komentatuta hutsi den kodean ikus daitekeen moduan. Azkenik, **binary_search()** egiteko, iteratiboki egitea zen ideia, baina azkenean errekurtsiboki egin da.

Bestalde, hasiera batean, ***Lingeling*** eta ***sortnetwrk*** erabiltzea erabaki zen, baina, denbora gehiegi behar zuenez, beste batzuekin probak egin ostean, azkenean ***Glucose4*** eta ***cardnetwrk*** erabili dira.

# Emaitzak

Programa hau exekutatu ostean, exekuzio denbora batzuk lortu ditugu, datu pakete bakoitzerako: 
>Kontuan izan behar da, programa hau Visual Studio Code-n exekutatu dela, eta han, grafoen marrazketak leiho aparte batean agertzen dira, banaka, hau da, ez da hurrengo irudia agertzen aurrekoa itxi arte. Beraz, bestelako lekuetan exekutatzen bada, honen exekuzio denborak txikiagoak izan beharko lirateke, irudiak batera marrazten baditu.

- Data pack 1, not all solutions:

 >Lehenengo data pack-a exekutatu dugu, grafo bakoitzeko soluzio guztiak bilatu gabe. **Exekuzio denbora:** 10.1907s

- Data pack 2, not all solutions:

 >Bigarren data pack-a  exekutatu dugu, grafo bakoitzeko soluzio guztiak bilatu gabe. **Exekuzio denbora**: 40.2217s

- Data pack 2, not all solutions with aproximation:

 >Kasu honetan, bigarren data pack-a exekutatzeko, aldez aurretik, bi algoritmo erabili ditugu, hurbilpen bat egiteko. Algoritmo hauek ***cover-2*** eta ***greedy*** algoritmoak dira. **Exekuzio denbora:** 43.3342s

- Data pack 1, all solutions:

 >Exekuzio honek, lehenengo data pack-erako grafo bakoitzeko soluzio guztiak bilatzea  du helburu, baina azken grafoa oso handia denez, denbora asko beharko du honen soluzio guztiak marrazteko. Hori dela eta, ezin dugu honen exekuzio denbora osoa lortu, baizik eta soilik soluzioak aurkitzeko behar duen denbora. **Exekuzio denbora:** 27.4350s (marraztu gabe)
