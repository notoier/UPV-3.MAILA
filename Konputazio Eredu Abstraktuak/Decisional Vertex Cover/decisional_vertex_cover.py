from draw_graphs import draw_graphs

from pysat.solvers import Glucose4 as solv #Lingeling: High performance and is able to handle large problems

from timeit import default_timer as timer

from pysat.card import EncType, CardEnc

def reduce_VC_to_SAT(graph, k):
    cnf_formula = [] #Initialize our cnf_formula
    for i in range(len(graph)): #Iterate through the graph
        for j in range(i+1, len(graph[i])): #Iterate through every connection of the graph
            if graph[i][j] == 1: #If those nodes are connected (connection is 1)
                cnf_formula.append([i+1, j+1]) #We append a clause to the cnf_formula
    nodes = list(range(1, len(graph) + 1)) #Make a list of the nodes
    cnf_formula += CardEnc.atmost(nodes, k, EncType.cardnetwrk).clauses #Complete our cnf_formula using CardEnc from pysat library and we use the Cardinality encoding, as it works well with both small and large graphs
    return cnf_formula #Return the formula

def answer_sat(graph, k, allsolutions): 
    cnf_formula = reduce_VC_to_SAT(graph, k) #Get the cnf formula using the previous function
    sat_solver = solv() #Set the sat solver as the Lingeling solver, as it is a high performance solver, able to handle large problems
    sat_solver.append_formula(cnf_formula) #Introduce our cnf formula to the sat solver
    if sat_solver.solve(): #If the sat solver finds a solution
        if allsolutions: #Find all possible solutions for the given formula
            """
            solutions = [] #Initialize the solution list
            while sat_solver.solve(): #While the sat solver keeps finding solutions
                solution = sat_solver.get_model() #Get the solution 
                solutions.append(solution) #Introduce the solution to our list 
                cnf_formula.append([-v for v in solution]) #Introduce a new clause in our cnf formula, to negate the previous solution, so the sat_solver finds new solutions every time
                sat_solver.append_formula(cnf_formula) #Give the new cnf formula to the sat solver 
                """
            solutions = list(sat_solver.enum_models())
            return True, solutions #Return True, as we found at least one solution, and the list of solutions
        else:
            return True, sat_solver.get_model() #Return True, as we have found a solution, and the one solution, as we wanted
    return False, None #Return False and None because we didn't find a solution

def binary_search(graph, low, high, allsolutions):
    if low != high: #Check if we have reached the minimun posible 'k'
        k = (low + high) // 2 #If not, set the middle point between the low and high
        boolean, solution = answer_sat(graph, k, False) #Check if there's a solution with this new 'k'
        if boolean: #If there is
            return binary_search(graph, low, k, allsolutions) #Then, set the new 'k' as the highest posible 'k'
        else:             
            return binary_search(graph, k+1, high, allsolutions) #Else, set the new 'k' (+1) as the lowest posible 'k'     
    _, solution = answer_sat(graph, high, allsolutions) #If we have reached the minimun

    return low, solution #Then we return the minimun 'k' as well as the solution
    
def cover_2(graph):
    cover = [0 for _ in graph[0]] #Initialize the cover as 0 in every position
    for i in range(len(graph)): #Iterate through the graph
        for j in range(i + 1, len(graph)): #Iterate through the connection of the node
            if graph[i][j] == 1 and cover[i] == 0 and cover[j] == 0: #If neither of this connection's nodes are in the cover, and the connection is 1
                cover[i] = 1 #Then we set both nodes in the cover as 1
                cover[j] = 1
                if isCoverRight(graph, cover): #If we have found a cover that suits our graph
                    return cover #We return the cover
    return cover #Return the cover
 
def greedy(graph):
    #Initialize the Vertex Cover solution to be all positions filled with None
    cover = [0 for _ in graph[0]] #Initialize the cover with 0 in every position
    weight_list = [[sum(graph[i]), i] for i in range(len(graph))] #Make the a list of the weights of each node and said node [weight, node]; the more connections it has, higher the weight 
    while not isCoverRight(graph, cover): #while we haven't found a cover that fits our graph
        max_weight = 0 #we initialize the max_weight as 0
        for weight in weight_list: #We iterate through the weights
            if weight[0] > max_weight and cover[weight[1]] == 0: #If our weight is higher than the actual max weight and our node is not in the cover
                max_weight = weight[0] #Then we set the new weight as the max weight
                node = weight[1] #and we keep the node to be later introduced in the cover
        cover[node] = 1 #Set the node in the cover as 1, meaning that it will be part of it  
    return cover #Return the cover         

def isCoverRight(graph, cover):
    for i in range(len(graph)): #Iterate over all nodes
        for j in range(i+1, len(graph[i])): #Iterate over that node's connections
            if cover[i] <= 0 and cover[j] <= 0 and graph[i][j] == 1: #If the node is 1 but it's not in the cover, then, the given vertex cover is wrong
                return False #return False
    return True #return True
      
                    
def areCoversRight(graph, covers): #Checks if all given covers are correct
    for cover in covers: #Iterate through each cover
        if not isCoverRight(graph, cover): #If this cover is wrong
            return False #Then return False
    return True #Else, if we reach here, then it means that all given covers are right, so we return True
    
    
def test(filename, allsolutions):
    
    import pickle
    with open(filename, 'rb') as f:
        data = pickle.load(f)
        
    for graph in data:
    
        answer = binary_search(graph, 1, len(graph), allsolutions)
        if isCoverRight(graph, answer[1][0:len(graph)]):
            print("\nMinimum Vertex Cover has: " + str(answer[0]) + " nodes")
            print("SAT-solver's all possible answers are: " + str(answer[1][0:len(graph)]))
            draw_graphs(graph, answer[1])
       
            # for x in answer[1]:
            #     #+ str(answer[1][0:len(graph)]))
            #     print(x)
        else:
            print("SOLUTION INCORRECT!")
                

def test_approximation(filename, allsolutions):
    
    import pickle
    with open(filename, 'rb') as f:
        data = pickle.load(f)
        
    for graph in data:
        c1 = sum(cover_2(graph))
        c2 = sum(greedy(graph))

        low = max(c1, c2)//2
        high = min(c1, c2)  
                
        answer = binary_search(graph, low, high, allsolutions)
        
        if isCoverRight(graph, answer[1][0:len(graph)]):
            print("\nMinimum Vertex Cover has: " + str(answer[0]) + " nodes")
            print("SAT-solver's answer is: " + str(answer[1][0:len(graph)]))
            draw_graphs(graph, answer[1])
       
            
        else:
            print("SOLUTION INCORRECT!")
   
             
def test_all_solutions(filename, allsolutions):
    
    import pickle
    with open(filename, 'rb') as f:
        data = pickle.load(f)
        
    for graph in data:
    
        answer = binary_search(graph, 1, len(graph), allsolutions) 
        
        covers = [cover[0:len(graph)] for cover in answer[1]]
           
        if areCoversRight(graph, answer[1]):#, answer[1][0:len(graph)]):
            print("\nMinimum Vertex Cover has: " + str(answer[0]) + " nodes\n" + "SAT-solver's answer is:\n" + str(covers))
        else:
            print("SOLUTION INCORRECT!")
            
        draw_graphs(graph, answer) #Lerro hau komentatzea gomendagarria da, azken grafoa denbora asko behar du eta
              

if __name__ == "__main__":
    
    #Simple default cases, to check it works fine
    start = timer()
    print("DATA PACK 1: NOT ALL SOLUTIONS \n")
    test('mydata/data1.pkl', False)
    end = timer()
    print('Elapsed time: ' + str(end - start) + ' seconds \n')
    
    #More complex cases, to check efficiency
    start = timer()
    print("DATA PACK 2: NOT ALL SOLUTIONS \n")
    test('mydata/data2.pkl', False)
    end = timer()
    print('Elapsed time: ' + str(end - start) + ' seconds \n')
    
    #Cases to test APPROXIMATION algorithms
    start = timer()
    print("DATA PACK 2: NOT ALL SOLUTIONS + APPROXIMATION \n")
    test_approximation('mydata/data2.pkl', False)
    end = timer()
    print('Elapsed time: ' + str(end - start) + ' seconds \n')
    
    #Find ALL possible solutions
    start = timer()
    print("DATA PACK 1: ALL SOLUTIONS")
    test_all_solutions('mydata/data1.pkl', True)
    end = timer()
    print('Elapsed time: ' + str(end - start) + ' seconds')
    