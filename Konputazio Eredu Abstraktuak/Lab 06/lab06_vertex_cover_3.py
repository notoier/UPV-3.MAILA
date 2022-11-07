from time import time
from lab06_vertex_cover_2 import partial_validity_check, validity_check

#vertex_cover_tree-k bilaketa zuhaitza hasieratu eta recursive_vertex_cover-i deitzen dio
def vertex_cover_tree(graph):
    n = len(graph)
    cover = [None]*n
    return recursive_vertex_cover(graph, cover)

# recursive_vertex_cover-ek bilaketa zuhaitza errekurtsiboki eraikitzen du
def recursive_vertex_cover(graph, cover):
    # Baliozko cover bat eraikitzea dagoela frogatu
    # Posible ez bada, [1]*len(cover) bueltatu
    if not partial_validity_check(cover, graph):
        return [1] * len(cover)
    # # bestela,
    # # cover-a osoa bada, bueltatu
    if validity_check(cover, graph):
        #None edo  0 bada ordaun 0 jarri, bestela 1
        return [0 if cover[i] != 1 else 1 for i in range(len(cover))]
    # cover-a osoa ez bada, cover-ean ez dauden bi u eta v nodo topatu
    nodoak = [i for i in range(len(cover)) if cover[i] is None]
    # Nodo bakarra badago, cover-aren parte izan behar duen ala ez erabaki
    if len(nodoak) == 1:
        for node, index in enumerate(graph[nodoak[0]]):
            if node and cover[index]:
                #Nodoa cover-ean sartu
                cover[nodoak[0]] = 1
                break
    # eta behin eginda, cover osoa bueltatu
        return cover
                
    u = nodoak[0]
    v = nodoak[1]
    # Bestela, u eta v-rekin jarraitu
    copy_cover = list(cover)
    cover[u] = 1
    cover[v] = 0
    c10 = recursive_vertex_cover(graph, cover)
    cover = list(copy_cover)
    cover[u] = 0
    cover[v] = 1
    c01 = recursive_vertex_cover(graph, cover)
    cover = list(copy_cover)
    cover[u] = 1
    cover[v] = 1
    c11 = recursive_vertex_cover(graph, cover)
    if c10.count(1) <= min(c01.count(1), c11.count(1)):
        return c10
    elif c01.count(1) <= c11.count(1):
        return c01
    else:
        return c11

def test():
    
    g1 =  [[0, 1],
           [1, 0]]
       
    g2 = [[0, 1, 1],
          [1, 0, 0],
          [1, 0, 0]]
        
    
    g3 = [[0, 1, 1, 1, 1],
          [1, 0, 0, 0, 1],
          [1, 0, 0, 1, 1],
          [1, 0, 1, 0, 1],
          [1, 1, 1, 1, 0]]
    
        
    g4 = [[0, 1, 1, 1],
          [1, 0, 1, 0],
          [1, 1, 0, 1],
          [1, 0, 1, 0]]
    
       
    g5 = [[0, 1, 1, 0, 0, 0],
          [1, 0, 0, 1, 1, 0],
          [1, 0, 0, 1, 1, 1],
          [0, 1, 1, 0, 0, 1],
          [0, 1, 1, 0, 0, 0],
          [0, 0, 1, 1, 0, 0]]
    
    g6 = [[0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0],
          [1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0],
          [1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0],
          [0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0],
          [0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1],
          [0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0],
          [1, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0],
          [1, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0],
          [1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0],
          [1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0],
          [1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 1],
          [1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1],
          [0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1],
          [0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1],
          [0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0]]

    
   

 
#   recursive_vertex_cover funtzioa probatzeko iruzkinak kendu
    assert vertex_cover_tree(g1) in [[1,0],[0,1]]
    assert vertex_cover_tree(g2)  == [1,0,0]
    assert vertex_cover_tree(g3) in [[1, 0, 1, 0, 1], 
                                     [1, 0, 0, 1, 1]]
    assert vertex_cover_tree(g4)  == [1, 0, 1, 0]
    assert vertex_cover_tree(g5)  in  [[0, 1, 1, 1, 0, 0], 
                                       [0, 1, 1, 0, 0, 1]]
    
    
    assert vertex_cover_tree(g6) in [[1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1],
                                     [1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1],
                                     [1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1],
                                     [1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1],
                                     [1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1],
                                     [1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1],
                                     [1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0],
                                     [1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1],
                                     [1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0],
                                     [1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1],
                                     [1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 1],
                                     [1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1],
                                     [1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0],
                                     [1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1],
                                     [1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0],
                                     [1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1],
                                     [1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1],
                                     [1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0],
                                     [1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1],
                                     [1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1],
                                     [1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 1],
                                     [1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0],
                                     [1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1],
                                     [1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0],
                                     [1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1],
                                     [1, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1],
                                     [1, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0],
                                     [1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1],
                                     [1, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1],
                                     [1, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1],
                                     [1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1]]
    
start_time = time()
test()
elapsed_time = time() - start_time   
print("Elapsed time: %0.10f seconds." % elapsed_time)      
