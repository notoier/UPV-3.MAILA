from draw_graphs import draw_graphs

from pysat.solvers import auskalosolver

from timeit import default_timer as timer

from pysat.card import EncType, CardEnc

import copy
import numpy

import networkx as nx



def reduce_VC_to_SAT(graph, k):
    SAT = [] #Declare estandar SAT
    for row in graph: #Iterate each row of the graph
        clause = [] #Declare the clause
        for i in range(len(row)): #Iterate each node of a row
            if row[i] == 1: #If node equals 1 then it means that there's a conection with at least one of the other nodes
                clause.append(i) #Itroduce the literal in the SAT clause
        SAT.append(clause) #After all iterations append the clause to our SAT 
    
    K_SAT = [] #Declare our K length SAT 
    for clause in SAT: #Iterate the clauses of our SAT
        new_clause = [clause[0]] #Declare the new clause, which will start with the first literal of the previous clause 
        for literal in clause: #Iterate each literal of the previous clause
            if literal != clause[0]: #If the literal is not the first one
                new_clause.append(literal) #Then, we append the literal to the new clause 
                if len(new_clause) == k: #If our new clause have reached a length that equals to k
                    K_SAT.append(new_clause) #Then we append the new clause to our K-SAT
                    new_clause = [clause[0]] #After that we reset our new clause
                    continue #And we continue to the next literal                           
    return K_SAT 


def answer_sat(graph, k, allsolutions): 
    return None

def binary_search(graph, low, high, allsolutions):
    return None
   
     
def cover_2(graph):     #TODO
    VC = [None for _ in graph[0]]
    max_count = 0
    for row in graph:
        for node in graph[row]:
            if not VC[node]:
                count = graph[row].count(1)
                if count > max_count:
                    max_count = count
                    vc_node = node
        VC[vc_node] = 1 
        max_count = 0   
    VC = [0 if VC[i] != 1 else 1 for i in range(len(VC))]        
                   
    return VC
     

def greedy(graph): #TODO
    VC = [None for _ in graph[0]]
    max_count = 0
    for row in graph:
        for node in graph[row]:
            if VC[node] != 1:
                count = graph[row].count(1)
                if count > max_count:
                    max_count = count
                    vc_node = node
        VC[vc_node] = 1 
        max_count = 0   
    VC = [0 if VC[i] != 1 else 1 for i in range(len(VC))]        
                   
    return VC
    

def isCoverRight(graph, length, cover):
    for i in range(length):
        for node in graph[i]:
            if cover[i] == 0 and cover[node] == 0 and graph[i][node] == 1:
                return False
    return True
      
                    
def areCoversRight(graph, length, covers):
    for cover in covers:
        if not isCoverRight(graph, length, cover):
            return False
    return True
    
    
def test(filename, allsolutions):
    
    import pickle
    with open(filename, 'rb') as f:
        data = pickle.load(f)
        
    for graph in data:
    
        answer = binary_search(graph, 1, len(graph), allsolutions)
        if isCoverRight(graph, answer[0], answer[1][0:len(graph)]):
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
        c1 = cover_2(graph)
        c2 = greedy(graph)
        
        i = max(c1, c2)//2
        j = min(c1, c2)        
            
        answer = binary_search(graph, i, j, allsolutions)
        
        if isCoverRight(graph, answer[0], answer[1][0:len(graph)]):
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
        
        if areCoversRight(graph, answer[0], answer[1]):#, answer[1][0:len(graph)]):
            print("\nMinimum Vertex Cover has: " + str(answer[0]) + " nodes\n" + "SAT-solver's answer is:\n" + str(answer[1][0:len(graph)]))
        else:
            print("SOLUTION INCORRECT!")
            
        draw_graphs(graph, answer)
              

if __name__ == "__main__":
    #Simple default cases, to check it works fine
    start = timer()
    test('mydata/data1.pkl', False)
    end = timer()
    print('Elapsed time: ' + str(end - start) + ' seconds')
    
    #More complex cases, to check efficiency
    start = timer()
    test('mydata/data2.pkl', False)
    end = timer()
    print('Elapsed time: ' + str(end - start) + ' seconds')
 
    #Cases to test APPROXIMATION algorithms
    start = timer()
    test_approximation('mydata/data2.pkl', False)
    end = timer()
    print('Elapsed time: ' + str(end - start) + ' seconds')
  
    #Find ALL possible solutions
    start = timer()
    test_all_solutions('mydata/data1.pkl', True)
    end = timer()
    print('Elapsed time: ' + str(end - start) + ' seconds')
