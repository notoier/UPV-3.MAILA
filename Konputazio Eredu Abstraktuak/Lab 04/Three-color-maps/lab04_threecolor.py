from fourcolor import graph_is_4colorable

#Funtzio honekin, emandako grafo bat 3-koloreztagarria den konprobatuko dugu, 4-koloreztagarria konprobatzen duen funtzio bat erabiliz. 
#Horretarako, hurrengo laburketa egin beharko da
def graph_is_3colorable(g):
      for row in g: #Jasotako matrizearen (grafoa, berez) ilara bakoitzari 1 den elementua gehituko diogu: row = [0,1,1,0] --> row = [0,1,1,0,1]
            row.append(1) #1 elementua gehitu
               
      new_row = [] #Ilara berria sortu
      for i in range(0,len(g)): #Grafo baten ilararen luzerarako:
            new_row.append(1) #Ilara berriko posizio guztietan 1 zenbakia jarri
      new_row.append(0) #Azken posizioan aldiz 0 izan, matrizearen diagonala 0 izan behar delako
      g.append(new_row) #Ilara berria, grafoan sartu
      
      return graph_is_4colorable(g) #Grafoa 4-koloreztagarria den konprobatu. Hala bada, orduan hasierako grafoa 3-koloreztagarria dela esan nahi du.    


def test():
      g1 = [[0, 1, 1, 0],
            [1, 0, 0, 1],
            [1, 0, 0, 1],
            [0, 1, 1, 0]]
      assert graph_is_3colorable(g1)

      g2 = [[0, 1, 1, 1],
            [1, 0, 0, 1],
            [1, 0, 0, 1],
            [1, 1, 1, 0]]
      assert graph_is_3colorable(g2)

      g3 = [[0, 1, 1, 1],
            [1, 0, 1, 1],
            [1, 1, 0, 1],
            [1, 1, 1, 0]]
      assert not graph_is_3colorable(g3)


test()
