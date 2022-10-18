from solve_vc import solve_vc

#Multisolver bat, zeinek 'VERTEX COVER', 'INDEPENDENT SET' eta 'CLIQUE' problementzat emaitza bueltatuko duen, batetik besterako laburketak eginez.
def multisolve(graph, problem):    
    if problem ==   "VERTEX COVER": #'VERTEX COVER' motako problema bada orduan jadanik eginda dagoen solve_vc funtzio erabiliko dugu emaitza lortzeko
        return solve_vc(graph) #solve_vc funtzioa jasotako grafoarekin erabili
    
    elif problem == "INDEPENDENT SET": #'INDEPENDENT SET' motako problema bada, orduan hurrengo soluzioa emango dugu
        vc = solve_vc(graph) #Grafo baten 'VERTEX COVER' soluzioa jaso
        return [0 if vc[i] == 1 else 1 for i in range(0, len(vc))] #Jasotako soluzioari buelta eman, List Conprehension erabiliz, izan ere, 'INDEPENDENT SET', 
                                                                   #'VERTEX COVER'-en soluzioaren osagarria da. vc=[0,1,1,0] --> I.S = [1,0,0,1]        
    else:
        # Grafo batean 'INDEPENDENT SET' soluzio bat badago, orduan, grafo horren osagarrian, 'CLIQUE' soluzio bat edukiko dugu.
        iss = multisolve(graph, 'INDEPENDENT SET') #'INDEPENDENT SET' soluzioaren emaitza jasoko dugu 'CLIQUE' problemaren soluzioarako
        graph_comp = [[1 if graph[i][j] == 0 and j != i else 0 for i in range(0, len(graph))] for j in range(len(graph[0]))] #Emandako grafoaren osagarria lortu
        for i in range(0 , len(iss)): #'INDEPENDENT SET' emaitzan 1 den elementua bilatu
            if iss[i] == 1: #Behin aurkituta grafo osagarriko i ilara (Lehen 1 zenbakia aurkitu dugun puntua) eta 'INDEPENDENT SET' emaitzak konparatuko ditugu
                clique = [1 if graph_comp[i][j] == iss[j] and iss[j] == 0 else 0 for j in range(0, len(iss))] #Bietan posizio berean 0 bat badago, orduan 1 jarri
                break #Hasierako for-tik atera
        clique[i] = 1 #Azkenik, lehen 1 aurkitu dugun puntuan, clique emaitzan, puntu berean 1 jarriko dugu
        return clique #'CLIQUE' problemarako soluzioa bueltatu 
                    

def test():
   graph = [[0, 0, 1, 0], [0, 0, 0, 1], [1, 0, 0, 1], [0, 1, 1, 0]]
   sol_vertex = multisolve(graph, "VERTEX COVER")
   sol_clique = multisolve(graph, "CLIQUE")
   sol_independent_set =  multisolve(graph, "INDEPENDENT SET")
   
   assert sol_vertex in [[0,0,1,1], [1,0,0,1], [0,1,1,0]]
   assert sol_independent_set in [[1,0,0,1],[1,1,0,0],[0,1,1,0]]
   assert sol_clique in [[1,0,1,0],[0,0,1,1],[0,1,0,1]]

test()
