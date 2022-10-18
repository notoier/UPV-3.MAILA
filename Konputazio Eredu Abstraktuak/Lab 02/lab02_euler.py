
# Funtzio honek, jasotako grafo batean zirkuitu Eleriar bat dagoen ala ez esango digu (P motako problema). Horretarako, grafoari dagokion matrizea iteratuko du, eta errenkadean dagoen 
# 1 kopurua ( nodoa beste nodoari lotuta badago 1 izango da, bestela 0) zenbatuko du. Zenbaketa egin ostean, 1-eko kopurua bakoitia bada, orduan grafo 
# horretan zirkuitu eulerriarik ez dagoela esan nahi du. Bestalde, zenbaketa guztiak bikoitiak badira, orduan grafo horrek zirkuitu eulerriar bat du. 
def graph_has_Eulerian_circuit(g):
      for elem in g:
          if elem.count(1) % 2 != 0: 
                return False
      return True
          


def test():
      g1 = [[0, 1, 1, 0, 0],
          [1, 0, 1, 1, 1],
          [1, 1, 0, 1, 1],
          [0, 1, 1, 0, 1],
          [0, 1, 1, 1, 0]]
      assert not graph_has_Eulerian_circuit(g1)


      g2 = [[0, 1, 1, 0, 0, 0],
          [1, 0, 1, 1, 1, 0],
          [1, 1, 0, 1, 1, 0],
          [0, 1, 1, 0, 1, 1],
          [0, 1, 1, 1, 0, 1],
          [0, 0, 0, 1, 1, 0]]
    
      assert graph_has_Eulerian_circuit(g2)

      g3 = [[0, 1, 1, 0, 0, 0, 0, 0],
          [1, 0, 1, 1, 0, 1, 1, 1],
          [1, 1, 0, 0, 1, 1, 1, 1],
          [0, 1, 0, 0, 0, 1, 0, 0],
          [0, 0, 1, 0, 0, 0, 1, 0],
          [0, 1, 1, 1, 0, 0, 1, 1],
          [0, 1, 1, 0, 1, 1, 0, 1],
          [0, 1, 1, 0, 0, 1, 1, 0]]
    
      assert not graph_has_Eulerian_circuit(g3)
    
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
    
      assert graph_has_Eulerian_circuit(g4)
    

test()

