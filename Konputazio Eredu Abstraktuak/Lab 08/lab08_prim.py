#Nodo guztiak lotzen dituen bide motzena lortzeko balio duen algoritmoa
def prim_algorithm(graph):
      visited = [0] #Visitatutako nodoak hasieratu
      sec_graph = [[float("inf") for r in range(len(graph[0]))] for c in range(len(graph[0]))] #Grafo sekundario bat hasieratu
      while len(visited) < len(graph[0]): #Nodo guztiak bisitatu ez ditugun bitartean
            min_distance = float("inf") #Distantzia minimoa infinitura hasieratu
            _node = None #Sartu beharreko nodoa hasieratu
            for node in visited: #Bisitatutako nodoak iteratu
#                 print("NODO ACTUAL: " + str(node))
                  for _node in range(len(graph[node])): #Grafoko lerroko nodoak iteratu
                        if graph[node][_node] < min_distance and _node not in visited: #Distantzia minimoa baino txikiagoa bada eta nodo hori ez badugu bisitatu
                              j = node #Gorde lehengo nodoa
                              i = _node #Gorde uneko nodoa
                              min_distance = graph[node][_node] #Gorde distantzia
#           print("DISTANCIA MINIMA: " + str(min_distance))
#           print("NODO AÑADIDO: " + str(i))
            if i: #Nodo berri bat sartu behar badugu
                  sec_graph[j][i] = min_distance #Distantziak nodo sekundarioan ipini
                  sec_graph[i][j] = min_distance #Bi posiziotan, grafo ez zuzendua delako, hau da, simetrikoa
#                 print("GRAPH: " + str(sec_graph))
                  visited.append(i) #Nodo berria sartu bisitatuen hartean
#                 print("NODO VISITADO: " + str(visited))   
      return sec_graph #Grafo sekundario bueltatu
 

def test():
    
    g1 =  [[float("inf"), 2.0],
           [2.0, float("inf")]]
    
    assert prim_algorithm(g1) == g1
    
    
       
    g2 = [[float("inf"), 5.0, 3.0],
          [5.0, float("inf"), float("inf")],
          [3.0, float("inf"), float("inf")]]
    
    assert prim_algorithm(g2) == g2
        
    
    
    g3 = [[float("inf"), 1.0, 2.0, 3.0, 4.0],
          [1.0, float("inf"), float("inf"), float("inf"), 8.0],
          [2.0, float("inf"), float("inf"), 2.0, 3.0],
          [3.0, float("inf"), 2.0, float("inf"), 5.0],
          [4.0, 8.0, 3.0, 5.0, float("inf")]]
    
    assert prim_algorithm(g3) == [[float("inf"), 1.0, 2.0, float("inf"), float("inf")], 
                                  [1.0, float("inf"), float("inf"), float("inf"), float("inf")], 
                                  [2.0, float("inf"), float("inf"), 2.0, 3.0], 
                                  [float("inf"), float("inf"), 2.0, float("inf"), float("inf")], 
                                  [float("inf"), float("inf"), 3.0, float("inf"), float("inf")]] 
    
    
        
    g4 = [[float("inf"), 6.0, 2.0, 5.0],
          [6.0, float("inf"), 4.0, float("inf")],
          [2.0, 4.0, float("inf"), 2.0],
          [5.0, float("inf"), 2.0, float("inf")]]
    
    assert prim_algorithm(g4) == [[float("inf"), float("inf"), 2.0, float("inf")], 
                                  [float("inf"), float("inf"), 4.0, float("inf")], 
                                  [2.0, 4.0, float("inf"), 2.0], 
                                  [float("inf"), float("inf"), 2.0, float("inf")]]
    
    
       
    g5 = [[float("inf"), 10.0, 1.0, float("inf"), float("inf"), float("inf")],
          [10.0, float("inf"), float("inf"), 5.0, 4.0, float("inf")],
          [1.0, float("inf"), float("inf"), 8.0, 2.0, 3.0],
          [float("inf"), 5.0, 8.0, float("inf"), float("inf"), 2.0],
          [float("inf"), 4.0, 2.0, float("inf"), float("inf"), float("inf")],
          [float("inf"), float("inf"), 3.0, 2.0, float("inf"), float("inf")]]
    
    assert prim_algorithm(g5) == [[float("inf"), float("inf"), 1.0, float("inf"), float("inf"), float("inf")], 
                                  [float("inf"), float("inf"),float("inf"), float("inf"), 4.0, float("inf")], 
                                  [1.0, float("inf"), float("inf"), float("inf"), 2.0, 3.0], 
                                  [float("inf"), float("inf"), float("inf"), float("inf"), float("inf"), 2.0], 
                                  [float("inf"), 4.0, 2.0, float("inf"), float("inf"), float("inf")], 
                                  [float("inf"), float("inf"), 3.0, 2.0, float("inf"), float("inf")]]
    
    
    
    g6 = [[float("inf"), 3.0, 1.0, float("inf"), float("inf"), float("inf"), float("inf")],
          [3.0, float("inf"), 8.0, 10.0, 5.0, float("inf"), float("inf")],
          [1.0, 8.0, float("inf"), float("inf"), float("inf"), float("inf"), float("inf")],
          [float("inf"), 10.0, float("inf"), float("inf"), 6.0, float("inf"), 9.0],
          [float("inf"), 5.0, float("inf"), 6.0, float("inf"), 1.0, 2.0],
          [float("inf"), float("inf"), float("inf"), float("inf"), 1.0, float("inf"), 4.0],
          [float("inf"),float("inf"),float("inf"), 9.0, 2.0, 4.0, float("inf")]]
    
    
    assert prim_algorithm(g6) == [[float("inf"), 3.0, 1.0, float("inf"), float("inf"), float("inf"), float("inf")], 
                                 [3.0, float("inf"), float("inf"), float("inf"), 5.0, float("inf"), float("inf")], 
                                 [1.0, float("inf"), float("inf"), float("inf"), float("inf"), float("inf"), float("inf")], 
                                 [float("inf"), float("inf"), float("inf"), float("inf"), 6.0, float("inf"), float("inf")], 
                                 [float("inf"), 5.0, float("inf"), 6.0, float("inf"), 1.0, 2.0], 
                                 [float("inf"), float("inf"), float("inf"), float("inf"), 1.0, float("inf"), float("inf")], 
                                 [float("inf"), float("inf"), float("inf"), float("inf"), 2.0, float("inf"), float("inf")]]

    

test()
