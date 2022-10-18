# -*- coding: utf-8 -*-
"""
Spyder Editor

This is a temporary script file.
"""
#Aldagaien izenak aldaratu izan dira, ariketa guztien emaitzak
#aldi berean ikus ahal izateko

import math
from random import randrange


#1.ARIKETA      Zenbaki baten balio absolutua
a = -15    
b = abs(a)

#2.ARIKETA      Bi zenbakien arteko gehiketa
c = a + b

#3.ARIKETA      Celsius -> Farenheit aldaketa
tCelsius = 25
tFarenheit = 9/5 * tCelsius + 32

#4.ARIKETA      Circunferentzia baten azaleraren kalkulua
erradioa = 5
azalera = 4 * math.pi * erradioa ** 2

#5.ARIKETA      'Assert' konprobaketak
d = 7
e = 7
f = 9

assert d == e
assert e < f
assert f > d

#6.ARIKETA      Bi puntuen arteko distantzia euklidearraren kalkulua
x1, y1 = 2, 3

x2, y2 = 4, 9

p = math.sqrt((x2- x1) ** 2 + (y2-y1)**2)

#7.ARIKETA      5*x³+sqrt(x²+y²) + e^ln(x) adierazpenaren kalkulua 
x,y = 7, 9

res = 5 * x ** 3 + math.sqrt(x**2 + y**2) + math.exp(math.log(x))

#8.ARIKETA      Datu bilduma baten sorrera
bilduma = [1,2,3,4,5]
    #List motakoa da
    
#9.ARIKETA      Zerrendako '4' zenbakiak '10'-rekin ordeztu, List Comprehension erabiliz
lau_bilduma = [1,3,8,4,5,3,4,5,9,4,2,4]

z2 = [10 if lau_bilduma[i] == 4 else lau_bilduma[i] for i in range(0, len(lau_bilduma))]

#10.ARIKETA     Emandako zerrendako zenbakiak '1'-era laburtzeko beharrezko pausuak zenbatzen dituen funtzioak
z1 = [6,11,27,32,33]
def laburtu(x):
    kont = 0
    while x != 1:
        if x % 2 == 0:
            x = x / 2
        else:
            x = x*3+1
        kont += 1 
    return kont
z3 = [laburtu(z1[i]) for i in range(0, len(z1))]

#11.ARIKETA

#Funtzio honekin, matrize bat sortuko dugu, 6x3-koa. Posizioak iteratuko ditugu eta une bakoitzean, posizio horretan ranrange(-5,5) 
#erabiliz -5 eta 5 tartea dagoen zenbaki bat esarriko dugu, aleatorioki. Randrange funtzioa random liburutegitik dator.

def tarteak5():
    matrix = [[randrange(-5,5) for i in range(0,6)] for j in range (0,3)]
    return matrix

#12.ARIKETA

#Funtzio honetan, matrize batean zenbaki bat errepikatzen den kopurua zenbatuko dugu. 
#Horretarako, funtzioari matrize bat eta zenbatu nahi dugun zenbakia pasatuko diogu.
#Ondoren matrizea iteratuko dugu eta posizio horretan gure zenbakia badago 1 zenbatuko dugu.

def errepikapenak(m, x):
    kop = 0
    kop = [[kop + 1 if m[j][i] == x else kop for i in range(0, len(m[0])) for j in range(0, len(m))]]
    return kop[0].count(1)


#13.ARIKETA

#Funtzio honi, matrize bat pasatuko diogu, zenbakiz osatuta. Matrizea iteratuko dugu, for egitura bi aldiz erabiliz, lerroentzat eta zutabeentzat. 
#Ondoren, aurkitua lortutako lista izango dugu, eta honetan True-ren bat badago, konprobatuko dugu, any() funtzioa erabiliz

def artean4eta7(m):
    aurkitua = [[ True if m[j][i] <= 7 and m[j][i] >= 4  else False for i in range(0, len(m[0])) for j in range(0, len(m))]]
    return any(aurkitua[0])

#14.ARIKETA

#Funtzio honek, bi matrize emanda, bata zenbaki osoez osatuta eta bestea True/False boolearrekin, 
#biak baliokiddeak direnean(Bi matrizeen posizio berean zenbaki positibo bat eta True bat, edo alderantziz),
#1 edo 0 idatziko du baliokide deitutako lista berrian (2, aurreko kasua ez bada). Beraz bi matrizeetatik iteratu ondoren (for erabiliz <bi aldiz>)
#1 eta 0 zenbakien agerpenak zenbatuko dira, baliokidetasun kopuruak lortzeko.

def baliokideak(m,m2):
    baliokide = [[ 1 if m2[j][i] == True and m[j][i] >= 0  else 0 if m2[j][i] == False and m[j][i] <= 0 else 2 for i in range(0, len(m[0])) for j in range(0, len(m))]]
    kopuruak = [baliokide[0].count(1), baliokide[0].count(0)]
    return kopuruak


#MAIN ()                        VSCode-n probak egiteko

z1 = [6,11,27,32,33]

m = [[3,1],[1,5],[1,2]]
x = 1

m2 = [[11,8],[1,9],[4,2]]

m3 = [[11,8],[-1,9],[-4,2]]
m4 = [[True,True],[True,False],[False,True]]

def main():
    print(tarteak5())
    print(errepikapenak(m,x))
    print(artean4eta7(m2))
    print(baliokideak(m3,m4))
    
    
if __name__ == "__main__":
    main()    