from time import time

# cover 0, 1 eta None elementuez osatutako zerrenda bat da

# i-ren posizioan 1ekoa badago, i. nodoa cover-ean dago
# i-ren posizioan 0koa badago, i. nodoa ez dago cover-ean 
# i-ren posizioan None badago, ez dakigu i. nodoa cover-ean dagoen ala ez
#
# partial_validity_check-ek, cover posible eta grafo bat emanda, frogatzen du
# cover-aren nodoek grafoaren ertz guztiak estal ditzazketen ala ez

def partial_validity_check(cover, graph):
      for i in range(0, len(cover)-1):
            if cover[i] == 0:
                  for node in graph[i]:
                        if node == 1 and cover[node] == 0:
                              print(node)
                              print(cover[node])
                              print(graph)
                              return False
                        continue
      return True

# vertex_cover_tree-k bilaketa zuhaitza hasieratu eta recursive_vertex_cover-i deitzen dio
def vertex_cover_tree(graph):
    n = len(graph)
    cover = [None]*n
    return recursive_vertex_cover(graph, cover)




# recursive_vertex_cover-ek bilaketa zuhaitza errekurtsiboki eraikitzen du
def recursive_vertex_cover(graph, cover):

    ############
    # TODO: Funtzioaren zati hau programatu
    #
    # Baliozko cover bat eraikitzea dagoela frogatu
    # Posible ez bada, [1]*len(cover) bueltatu
    # bestela, 
    # cover-a osoa bada, bueltatu
    # cover-a osoa ez bada, cover-ean ez dagoen v nodo bat topatu
    
    
    # Zure kodearen amaiera
    # Hurrengoak bilaketa zuhaitzaren bi adarrak irekitzen ditu
    # Ez ezer ikutu
    ##############
        copy_cover = list(cover)
        cover[v] = 0
        c0 = recursive_vertex_cover(graph, cover)
        cover = list(copy_cover)
        cover[v] = 1
        c1 = recursive_vertex_cover(graph, cover)
        return c0 if c0.count(1) < c1.count(1) else c1

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

    
   
    
#    partial_validity_check funtzioa probatzeko iruzkinak kendu
#    assert not partial_validity_check([0,0], g1)
#    assert not partial_validity_check([0,0,1], g2)
#    assert partial_validity_check([1,None,None], g2) 
    assert partial_validity_check([0,None,None], g2) 
    assert partial_validity_check([1,0,0], g2) 
    assert partial_validity_check([1,1,0], g2) 
    assert partial_validity_check([0,1,None], g2)
    assert not partial_validity_check([0,None,0], g2) 
    assert not partial_validity_check([0, 1, 1, 0, 1, 0], g5)
    assert partial_validity_check([0, 1, 1, 1, 0, 0], g5) 
    assert partial_validity_check([1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1], g6)
    
###################################################################  
    
 
##    recursive_vertex_cover funtzioa probatzeko iruzkinak kendu
#    assert vertex_cover_tree(g1) in [[1,0],[0,1]]
#    assert vertex_cover_tree(g2)  == [1,0,0]
#    assert vertex_cover_tree(g3) in [[1, 0, 1, 0, 1], 
#                                     [1, 0, 0, 1, 1]]
#    assert vertex_cover_tree(g4)  == [1, 0, 1, 0]
#    assert vertex_cover_tree(g5)  in  [[0, 1, 1, 1, 0, 0], 
#                                       [0, 1, 1, 0, 0, 1]]
#    
#    
#    assert vertex_cover_tree(g6) in [[1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1],
#                                     [1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1],
#                                     [1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1],
#                                     [1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1],
#                                     [1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1],
#                                     [1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1],
#                                     [1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0],
#                                     [1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1],
#                                     [1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0],
#                                     [1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1],
#                                     [1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 1],
#                                     [1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1],
#                                     [1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0],
#                                     [1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1],
#                                     [1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0],
#                                     [1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1],
#                                     [1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1],
#                                     [1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0],
#                                     [1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1],
#                                     [1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1],
#                                     [1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 1],
#                                     [1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0],
#                                     [1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1],
#                                     [1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0],
#                                     [1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1],
#                                     [1, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1],
#                                     [1, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0],
#                                     [1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1],
#                                     [1, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1],
#                                     [1, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1],
#                                     [1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1]]
    
start_time = time()
test()
elapsed_time = time() - start_time   
print("Elapsed time: %0.10f seconds." % elapsed_time)      

test()
elapsed_time = time() - start_time   
print("Elapsed time: %0.10f seconds." % elapsed_time)      
