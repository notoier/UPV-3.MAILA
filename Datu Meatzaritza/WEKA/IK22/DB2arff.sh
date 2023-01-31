#!/usr/bin/env bash

echo "Ongi etorri DMv1 Aplikaziora"
echo "Autorea: Mikel Iceta Tena"

if [ $# -lt 1 ]
then
  echo "Erabilera: $0 [ARGAZKI KARPETA DIREKTORIOA]"
  exit 1
fi

if [ ! -d "./irteera" ]
  then
    mkdir irteera
fi
echo ""
echo "Main: aplikazioa hasi da"
echo "DB karpeta: $1"
echo ""

if [ ! -d $1 ]
  then
    echo "Karpeta txarra. Agur."
    exit 1
fi

  echo "Argazkiak ordenatzera. irteera direktorioan topatuko duzu:"

#!/usr/bin/env bash

#Argazkiak ordenatzeko shell script-a

#Sarrera: direktorio bat
#Pre: direktorioa existitzen da
#Irteera: direktorio horren barruan dauden direktorioen argazkiak
# ordenatuta

EXTENSION=".jpg"

#ARFF fitxategia sortzen dugu existitzen ez bada
irteerarff="./irteera/ImageFilter_$1.arff"
touch $irteerarff

#ARFF fitxategia hasieratu egiten dugu klaseekin
echo "" > $irteerarff
echo "@RELATION dm_prak" >> $irteerarff
echo "" >> $irteerarff
echo "@ATTRIBUTE filename string" >> $irteerarff
echo "@ATTRIBUTE class {K1, K2, K3, K4, K5, K6, K7, K8}" >> $irteerarff
echo "" >> $irteerarff
echo "@DATA" >> $irteerarff

#Irteerako karpeta sortu behar da ez badago
ordenatudir="./irteera/ordenatuak"
if [ ! -e $ordenatudir ]
then
  mkdir $ordenatudir
fi

#Miramos cada carpeta que hay en la carpeta
KLASE=1
for karpeta in $1/*
do
  PREFIX="K$KLASE"
  COUNTER=10
  if [ ! -d $karpeta ] #Karpeta bat ez bada agur
  then
    continue
  fi
    #Copiamos cada archivo a la carpeta destino
  for fitx in $karpeta/*
  do
    if [ -f $fitx ]
    then
      berria="$ordenatudir/$PREFIX-$COUNTER$EXTENSION"
      #Registramos la foto con su clase en el arff
      echo "$PREFIX-$COUNTER$EXTENSION, $PREFIX" >> $irteerarff
      #Copiamos el archivo a la carpeta destino
      cp $fitx $berria
      #echo "--> $berria"
      COUNTER=$((COUNTER + 1))
    fi
  done
    KLASE=$((KLASE += 1))
done
#    sh ./ordenatu.sh $1

  echo "irteera/ordanatuak direktorioan: argazkiak izena aldatuta K1, K2,... bezala"
  echo "irteera direktorioan: ImageFilter_$1.arff WEKarako fitxategia"

exit 0

