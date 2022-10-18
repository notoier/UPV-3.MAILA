from itertools import permutations

# Funtzio honek, emandako grafo batean, zirkuitu hamiltoniar baten existentzia bilatzen du (NP Problema bat).
# Horretarako, lehenik eta behin, grafo horretan egon daitezkeen bide guztiak lortuko dira, permutations() funtzioa erabiliz. 
# Ondoren, for batekin bideen lista iteratuko dugu, bide bakoitza konprobatzeko. 
# Horretarako, bide bakoitzak dituen nodoak ikusiko ditugu, while horren barruan. Han, gure bidea zeharkatuko dugu, eta grafoaren matrizean konprobatuko dugu ea gure uneko nodoa,
# benetan, bidearen hurrengo nodora lotuta dagoen. Izan ere, permutations() egiterakoan, honek ez du kontuan hartzen benetan egin daitezkeen bideak, baizik eta konbinazio guztiak.
# Beraz, nodo guztietatik pasa ondoren, hamiltonian boolearra True izaten bada, orduan zirkuitu hamiltoniar bat aurkitu duela esan nahi du, beraz funtzioak True bueltatuko luke. 
# False izatekotan, beste bide bat konprobatuko dugu. baten bat True bueltatu arte edo bide guztiak konprobatuta egon arte.
 
def graph_has_Hamiltonian_circuit(g):
      hamiltonian = False
      perms = list(permutations(range(0, len(g)))    )
      for path in perms: 
            i = 0
            while i < len(path):
                  if i + 1 < len(path):
                        if g[path[i]][path[i+1]] != 1:
                              hamiltonian = False
                              break
                        else: 
                              hamiltonian = True
                  else: 
                        if g[path[i]][path[0]] != 1: 
                              hamiltonian = False
                              break
                        else: 
                              hamiltonian = True
                  i += 1
            if hamiltonian is True: 
                  break
      return hamiltonian

def test():
      g1 = [[0, 1, 1, 0, 0],
            [1, 0, 1, 1, 1],
            [1, 1, 0, 1, 1],
            [0, 1, 1, 0, 1],
            [0, 1, 1, 1, 0]]
      assert graph_has_Hamiltonian_circuit(g1)


      g2 = [[0, 1, 1, 0, 0, 0],
            [1, 0, 1, 1, 1, 0],
            [1, 1, 0, 1, 1, 0],
            [0, 1, 1, 0, 1, 1],
            [0, 1, 1, 1, 0, 1],
            [0, 0, 0, 1, 1, 0]]
    
      assert graph_has_Hamiltonian_circuit(g2)

      g3 = [[0, 1, 1, 0, 0, 0, 0, 0],
            [1, 0, 1, 1, 0, 1, 1, 1],
            [1, 1, 0, 0, 1, 1, 1, 1],
            [0, 1, 0, 0, 0, 1, 0, 0],
            [0, 0, 1, 0, 0, 0, 1, 0],
            [0, 1, 1, 1, 0, 0, 1, 1],
            [0, 1, 1, 0, 1, 1, 0, 1],
            [0, 1, 1, 0, 0, 1, 1, 0]]
    
      assert graph_has_Hamiltonian_circuit(g3)
    
      g4 = [[0, 1, 1, 0, 0, 0, 0, 0, 0, 0],
            [1, 0, 1, 1, 1, 1, 1, 0, 0, 0],
            [1, 1, 0, 0, 1, 1, 1, 0, 1, 0],
            [0, 1, 0, 0, 0, 1, 0, 0, 0, 0],
            [0, 1, 1, 0, 0, 1, 1, 0, 0, 0],
            [0, 1, 1, 1, 1, 0, 1, 1, 0, 0],
            [0, 1, 1, 0, 1, 1, 0, 1, 0, 1],
            [0, 0, 0, 0, 0, 1, 1, 0, 0, 0],
            [0, 0, 1, 0, 0, 0, 0, 0, 0, 1],
            [0, 0, 0, 0, 0, 0, 1, 0, 1, 0]]
    
      assert not graph_has_Hamiltonian_circuit(g4)
    
   
    

test()
