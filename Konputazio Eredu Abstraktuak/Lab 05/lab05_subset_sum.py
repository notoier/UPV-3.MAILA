from time import time
import itertools

# has_sum funtzioak zenbaki positiboen bilduma bat eta "value" balioa jasotzen ditu
# eta zenbaki positiboen azpibilduma baten baturak "value" ematen duen
# erabakitzen du.  
def has_sum(value, collection):
    if value == 0: #Balioa 0 bada, hau da, balio duen azpibildumaren bat aurkitu badugu, 
        return True #orduan True bueltatu
    elif not collection or value < 0: #Aldiz, ematen diguten bilduma amaitu badugo (balioa 0 ez bada) edota balioa negatiboa bada,
        return False #orduan False bueltatu, ez baitugu balio duen azpibildumarik aurkitu
    else: #Bestela, errekurtsiboki funtsio bera deitu, batean bildamako uneko posizioko balioa erabiliz, eta bestean balio hori erabili gabe
        return has_sum(value-collection[0],collection[1:]) or has_sum(value, collection[1:]) 
    
# subset funtzioak, zenbaki positiboen bilduma bat eta "value" balioa jasotzen ditu
# eta zenbaki positiboen azpibilduma baten baturak "value" ematen badu, azpibilduma hori
# itzultzen du. Horrelako azpibildumarik ez balego, [None] lista itzultzen du. 
def subset(value, collection):
    if value == 0: #Balioa 0 bada, hau da, balio duen azpibildumaren bat aurkitu badugu, 
        return [] #orduan zerrenda hutsa bueltatu
    elif not collection or value < 0: #Aldiz, ematen diguten bilduma amaitu badugo (balioa 0 ez bada) edota balioa negatiboa bada,
        return [None] #orduan None balioa duen zerrenda bueltatu, ez baitugu balio duen azpibildumarik aurkitu
    else: #Bestela, errekurtsiboki funtsio bera deitu,
        y = subset(value - collection[0], collection[1:]) #batean bildamako uneko posizioko balioa erabiliz,
        n = subset(value, collection[1:]) #eta bestean balio hori erabili gabe
        if y != [None]: #Jasotako zerrenda [None] ez bada, hau da, jarraitzekoatan azpibildumarik egongo denean
            y.append(collection[0]) #y zerrendan bildumatik erabilitako balioa sartu
            return y #y zerrenda bueltatu
    return n #Bestelako kasuetan n bueltatu, hau da, bildumako balioa erabili ez dugun zerrenda
#Funtzio honek behar izan duen denbora (azken bilduma erabiliz, gardenkiak esaten duten moduan), 3.3495251846 segundo izan dira konkretuki
#Aldiz, test() guztirako, soilik, 3.3700108528 segundo behar izan dira


# all_subsets funtzioak zenbaki positiboen bilduma bat eta "value" balio bat emanda, 
# "value" batzen duten azpimultzo guztiak itzultzen ditu. Soluziorik ez badago, [None] itzultzen du.                      
def all_subsets(value, collection):
    subsets = [] #Subsets zerrenda hasieratu
    for i in range(0, len(collection)): #Collection osoa iteratuko dugu, izan ere, soluzio guztiak behar ditugu
        badago = False #badago boolearra hasieratu
        sol = subset(value, collection) #Uneko collection-tik soluzio bat aterako dugu
        
        #Collection aldatuko dugu, hasieran duen elementua amaieran jarriz. Honekin, subset() funtzioa puntu desberdinetik hasiko da 
        #eta modu honetan, soluzio guztiak lortuko dira
        collection.append(collection.pop(0)) 
        
        if sol != [None]: #Soluzioa [None] ez bada, hau da, soluzio bat aurkitu badugu
            all_sol = [list(t) for t in itertools.permutations(sol)] #Lortutako soluzioaren permutazioak lortuko ditugu. Izan ere, [8, 2, 4] eta [4, 8, 2] soluzioak berdinak dira
        
            for subset_ in subsets: #Gure emaitzen azpibildumako soluzioak iteratuko ditugu
        
                if subset_ in all_sol: #Emaitza jadanik badugu orduan 
                    badago = True #Soluzio hau jadanik sartuta dugula adieraziko dugu
                    break #Iterazioak amaituko dira, soluzio badagoela konprobatu baitugu
        
            if not badago: #Soluzioa ez badago gure azpibildumen zerrendan sartuta   
                subsets.append(sol) #Orduan emaitza hori sartuko dugu
    
    if not subsets: #Soluziorik aurkitu ez badira,
        return [None] #orduan [None] bueltatuko dugu
    return subsets #Bestela, gure emaitzen zerrenda bueltatuko dugu

   
def test(): 
    #  0 bilduma
    collection0 = [3, 11, 8, 13, 16, 1, 6]
    value0 = 59
    
    # 1 bilduma
    collection1 = [3, 11, 8, 13, 16, 1, 6]
    value1 = 21
    

    sol11 = [3, 11, 1, 6]
    perm11 = [list(t) for t in itertools.permutations(sol11)]
    perm12 = [[13, 8], [8, 13]]
   
    # 2 bilduma
    collection2 = [518533, 1037066, 2074132, 1648264,
                   796528, 1593056, 686112, 1372224,
                   244448, 488896, 977792, 1955584,
                   1411168, 322336, 644672, 1289344,
                   78688, 157376, 314752, 629504, 1259008]
    value2 = 2463098
    
    sol21 = [1037066, 796528, 629504] 
    perm21 = [list(t) for t in itertools.permutations(sol21)]
    
    # 3 bilduma
    collection3 = [15, 22, 14, 26, 32, 9, 16, 8]
    value3 = 53
    
    
    sol31 = [15, 22, 16]
    perm31 = [list(t) for t in itertools.permutations(sol31)]
    
    # sol31ko balio guztien batura 53 denez, emaitza permutazio posible guztiak
    # Berdin azpiko bi aukerekin
    sol32 = [14, 15, 16, 8]
    perm32 = [list(t) for t in itertools.permutations(sol32)]
    sol33 = [9, 22, 14, 8]
    perm33 = [list(t) for t in itertools.permutations(sol33)]
    
    # 4. bilduma
    collection4 = [1,5,6]
    value4 = 6
    perm41 = [[6], [1, 5], [5, 1]] # Eskuz pentsatua
    
    # 5.bilduma
    collection5 = [4,5,1]
    value5 = 6
    perm51 = [[1, 5], [5, 1]]
    
  
#   HAS_SUM PROBATZEKO KOMENTARIOAK KENDU
#######################################################  
    assert not has_sum(value0, collection0)
    assert has_sum(value1, collection1)
    assert has_sum(value2, collection2)
    assert has_sum(value3, collection3)
    assert has_sum(value4, collection4)
    assert has_sum(value5, collection5)
    
#   SUBSET PROBATZEKO KOMENTARIOAK KENDU
###############################################################
    assert subset(value0, collection0) == [None]
    assert subset(value1, collection1) in perm11 + perm12 
    assert subset(value2, collection2) in perm21
    assert subset(value3, collection3) in perm31 + perm32 + perm33
    assert subset(value4, collection4) in perm41 
    assert subset(value5, collection5) in perm51 
    
##  ALL_SUBSETS PROBATZEKO KOMENTARIOAK KENDU   
##############################################################

    assert all_subsets(value0, collection0) == [None]

    all_solutions1 = all_subsets(value1, collection1)
    assert len(all_solutions1) == 2
    assert all_solutions1[0] in perm11 + perm12
    assert all_solutions1[1] in perm11 + perm12
    
    all_solutions2 = all_subsets(value2, collection2)
    assert len(all_solutions2) == 1
    assert all_solutions2[0] in perm21
    
        
    all_solutions3 = all_subsets(value3, collection3)
    assert len(all_solutions3) == 3
    assert all_solutions3[0] in perm31 + perm32 + perm33
    assert all_solutions3[1] in perm31 + perm32 + perm33
    assert all_solutions3[2] in perm31 + perm32 + perm33
    
    
    all_solutions4 = all_subsets(value4, collection4)       
    assert len(all_solutions4) == 2
    assert all_solutions4[0] in perm41
    assert all_solutions4[1] in perm41 
    
### DENBORA NEURTZEKO VALUE BATZEN DUEN AZPIBILDUMARIK EZ DUEN 
### BILDUMA HAU ERABILTZEN DA
####################################################################    
    collection5 = list(range(1,25))
    value5 = 301
    assert subset(value5, collection5) == [None] 

    
start_time = time()
test()
elapsed_time = time() - start_time   
print("Elapsed time: %0.10f seconds." % elapsed_time)   