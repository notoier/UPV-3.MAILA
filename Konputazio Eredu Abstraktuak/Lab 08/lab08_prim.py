
  
from matplotlib.colors import get_named_colors_mapping


def prim_algorithm(graph):
      visited = [0]
      sec_graph = [[float("inf") for r in range(len(graph[0]))] for c in range(len(graph[0]))]
      while len(visited) < len(graph[0]):
            min_distance = float("inf")
            _node = None
            for node in visited:
#                 print("NODO ACTUAL: " + str(node))
                  for _node in range(len(graph[node])):
                        if graph[node][_node] < min_distance and _node not in visited:
                              j = node
                              i = _node
                              min_distance = graph[node][_node]
#           print("DISTANCIA MINIMA: " + str(min_distance))
#           print("NODO AÑADIDO: " + str(i))
            if i:
                  sec_graph[j][i] = min_distance
                  sec_graph[i][j] = min_distance
#                 print("GRAPH: " + str(sec_graph))
                  visited.append(i)     
#                 print("NODO VISITADO: " + str(visited))   
      return sec_graph 
 

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
