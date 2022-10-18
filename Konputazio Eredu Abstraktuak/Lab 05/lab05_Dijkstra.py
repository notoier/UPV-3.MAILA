from time import time
from math import inf

# Dijkstra-ren algoritmoa
from time import sleep
def Dijkstra (graph, initial):
      
      sol = [graph[i][initial] if i != initial else 0 for i in range(len(graph))] #Hasierako grafotik distantziak lortu
      visited = [False if i != initial else True for i in range(len(graph))] #Bisitatutako nodoen lista False-ra hasieratu, hasierako nodoa izan ezik
      n = 0 #Index() funtzioak erabilitzeko erabili den hasiera puntua (Bi balio berdin daudenean aldatuko da, errorerik ez egoteko)
      v_ = 0 #Index() bueltatutakoa berdina den konprobatzeko aldagaia
      
      while visited.count(False) > 0: #False balioak baldin badaude orduan ez dugu amaitu
            
            #Funtzio honek <index()> balio minimoa dagoen posizio bueltatuko digu, 'n' bi balio berdin daudenean aldatuko dugu, 
            # modu honetan, index() funtzioa puntu horretatik bilatzen hasiko da, lehen aurkitutako balioa baztertuz
            v = sol.index(min([sol[i] if not visited[i] else inf for i in range(len(graph))]), n) 
            
            visited[v] = True #Visitatutako nodoa True ipini
            
            #Distantzia berria (r[v]) + nodo horren distantzia, 
            #dagoeneko distantzia baino txikiagoa bada, orduan distantzia berrira aldatu 
            sol = [sol[v] + graph[v][i] if sol[i] > sol[v] + graph[v][i] else sol[i] for i in range((len(graph)))] 
            
            if v_ == v: #Aurreko indizea oraingo indize bera bada, orduan bi distantzia berdin daudela esan nahi du
                  n = v + 1 #Beraz, index() funtzioa v+1-etik hasiko da begiratzen, lehenengo balio berdina bastertzeko
            v_ = v #Aurreko indizea, oraingo indizea bihurtu
            
      return sol #Soluzioa bueltatu

def test():
    
    g0 = [[0.0, 5.0, 1.0, inf],
          [5.0, 0.0, 1.0, 2.0],
          [1.0, 1.0, 0.0, 10.0],
          [inf, 2.0, 10.0, 0.0]]
    
    assert Dijkstra(g0, 3) == [4.0, 2.0, 3.0, 0.0]
    
    g1 =  [[0.0, 2.0],
           [2.0, 0.0]]
    
    assert Dijkstra(g1,0) == [0.0,2.0]
    
    g2 = [[0.0, 5.0, 3.0],
          [5.0, 0.0, inf],
          [3.0, inf, 0.0]]

    assert Dijkstra(g2, 1) == [5.0, 0.0, 8.0]
        
     
    g3 = [[0.0, 1.0, 2.0, 3.0, 4.0],
          [1.0, 0.0, inf, inf, 8.0],
          [2.0, inf, 0.0, 2.0, 2.0],
          [3.0, inf, 2.0, 0.0, 5.0],
          [4.0, 8.0, 2.0, 5.0, 0.0]]
    
    assert Dijkstra(g3, 3) == [3.0, 4.0, 2.0, 0.0, 4.0]
        
    g4 = [[0.0, 6.0, 2.0, 5.0],
          [6.0, 0.0, 4.0, inf],
          [2.0, 4.0, 0.0, 2.0],
          [5.0, inf, 2.0, 0.0]]
    
    assert Dijkstra(g4, 3) == [4.0, 6.0, 2.0, 0.0]
    
    g5 = [[0.0, 10.0, 1.0, inf, inf, inf],
          [10.0, 0.0, inf, 5.0, 4.0, inf],
          [1.0, inf, 0.0, 8.0, 2.0, 3.0],
          [inf, 5.0, 8.0, 0.0, inf, 2.0],
          [inf, 4.0, 2.0, inf, 0.0, inf],
          [inf, inf, 3.0, 2.0, inf, 0.0]]
    
    assert Dijkstra(g5, 0) == [0.0, 7.0, 1.0, 6.0, 3.0, 4.0]
    
    
    g6 = [[0.0, 3.0, 1.0, inf, inf, inf, inf],
          [3.0, 0.0, 8.0, 10.0, 5.0, inf, inf],
          [1.0, 8.0, 0.0, inf, inf, inf, inf],
          [inf, 10.0, inf, 0.0, 6.0, inf, 9.0],
          [inf, 5.0, inf, 6.0, 0.0, 1.0, 2.0],
          [inf, inf, inf, inf, 1.0, 0.0, 4.0],
          [inf,inf,inf, 9.0, 2.0, 4.0, 0.0]]
    
    assert Dijkstra(g6, 3)  == [13.0, 10.0, 14.0, 0.0, 6.0, 7.0, 8.0]

initial_time = time()
test()
elapsed_time = time() - initial_time   
print("Elapsed time: %0.10f seconds." % elapsed_time)       
