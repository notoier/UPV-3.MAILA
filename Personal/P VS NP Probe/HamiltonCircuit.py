from itertools import permutations
from math import factorial
from unittest import skipIf
from random import randint

def PequalsNPforHamiltonianCircuit(g, hamiltonian = False):
    perms = list(permutations(range(0, len(g)))    )
    skipAmount = 0
    j=0
    while j < len(perms):
        path = perms[j]
        i = 0
        j = j + skipAmount
        skipAmount = 0
        while i < len(path):
            if i + 1 < len(path):
                if g[path[i]][path[i+1]] != 1:
                    hamiltonian = False
                    skipAmount = skipablePaths(g, i+1)
                    break
                else: 
                    hamiltonian = True
            else: 
                if g[path[i]][path[0]] != 1: 
                    skipAmount = skipablePaths(g, i+1)
                    hamiltonian = False
                    break
                else: 
                    hamiltonian = True
                    i += 1
            if hamiltonian is True: 
                break
        j += 1
    return hamiltonian

def skipablePaths(g, i):
    skipablePathAmount = factorial(len(g)-i)
    return skipablePathAmount

def createRandomGraph():
    nodes = int(input('Enter the number of nodes to create a random graph from: '))
    graph = [[randint(0,1) for i in range(0, nodes)] for j in range(0, nodes)]
    return graph
    
def main():
    graph = createRandomGraph()
    print(graph)
    print(PequalsNPforHamiltonianCircuit(graph))

if __name__ == '__main__':
    main()
    