def sat_preprocessing(num_variables, clauses):
    assignment = [None for i in num_variables]
    i = 0
    jarraitu = True
    while jarraitu:
        jarraitu = False
        if R1_aplikagarria(clauses):
            jarraitu = True
            R1_aplikatu(assignment, clauses)
            
        if R2_aplikagarria():
            jarraitu = True
            
        R3_aplikatu(assignment, clauses)
        
def R1_aplikagarria(clauses): # Clausularen luzera 1 izatea
    return [len(clause) for clause in clauses].count(1) >= 1

def R1_aplikatu(assignment, clauses):
    for clause in clauses:
        if len(clause) == 1:
            literal = clause[0]
            if literal < 0:
                assignment[abs(literal)] = False
            else:
                assignment[literal] = True
 
def R2_aplikagarria(assignment, clauses, num_variables): # Clausula aldi batean agertzea, ala bada, eta balio bat asignaturik ez badu, balio bat aplikatu
    aurkituta = False
    for clause in clauses:
        for literal in clause:
            appearences = []
            appearences[num_variables + abs(literal)] += 1 # Counts the number of appearences of a clause.
    for i in range(num_variables):
        if len(appearences[i]) == 1 and appearences[num_variables + i] == 1 and assignment[i] != None:
            aurkituta = True
            if i <= num_variables:
                assignment[i] = 1
            else:
                assignment[i] = 0
    return aurkituta

def R3_aplikatu(assignment, clauses):
     for clause in clauses: #Jasotako klausula bakoitza konprobatu
        maxFalse = len(clause) #Klausula batean egon daitekeen False kopurua
        
        for literal in clause: #Klausula bateko literalak konprobatu
        
            if literal < 0: #Literala negatiboa bada, orduan aurrean not bat duela esan nahi du:  x1 == 1 eta ¬x1 == -1
        
                if assignment[abs(literal)] == 1: #1 == True; 0 == False
                    maxFalse -= 1 #False kopuru maximoari 1 kendu
                else:
                    break #True bada, orduan hurrengo klausulara pasatu
            
            else:
                if assignment[abs(literal)] == 0: #1 == False; 0 == True
                    maxFalse -= 1 #False kopuru maximoari 1 kendu
                else:
                    break #True bada, orduan hurrengo klausulara pasatu
                
        if maxFalse == 0: #MaxFalse 0-ra heltzen bada, orduan klausula oso bat False dela esan nahi du
           continue
        else: 
            clauses.pop(clause)      
                    


"""
    def test():
        assert [] == sat_preprocessing(1, [[1]])
        assert [[1],[-1]] == sat_preprocessing(1, [[1], [-1]])
        assert [] == sat_preprocessing(4, [[4], [-3, -1], [3, -4, 2, 1], [1, -3, 4],
                                            [-1, -3, -4, 2], [4, 3, 1, 2], [4, 3],
                                            [1, 3, -4], [3, -4, 1], [-1]])
        
        assert [[1],[-1]] == sat_preprocessing(5, [[4, -2], [-1, -2], [1], [-4],
                                            [5, 1, 4, -2, 3], [-1, 2, 3, 5],
                                            [-3, -1], [-4], [4, -1, 2]])
        
        ans = [[5, 6, 2, 4], [3, 5, 2, 4], [-5, 2, 3], [-3, 2, -5, 6, -4]]
        assert ans == sat_preprocessing(6, [[-5, 3, 2, 6, 1], [5, 6, 2, 4],
                                            [3, 5, 2, -1, 4], [1], [2, 1, 4, 3, 6],
                                            [-1, -5, 2, 3], [-3, 2, -5, 6, -4]])
        # Espreski 2. erregela frogatzeko
        assert [] == sat_preprocessing(7, [[-5, 3, 2, 6, 1], [5, 6, 2, 4],
                                            [3, 5, 2, -1, 4], [1], [2, 1, 4, 3, 6],
                                            [-1, -5, 2, 3], [-3, 2, -5, 6, -4, 7]])
test()
"""     