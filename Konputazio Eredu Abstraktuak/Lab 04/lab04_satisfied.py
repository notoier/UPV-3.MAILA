def is_satisfied(num_variables, clauses, assignment): #num_variables erabili daiteke, baina soluzio honekin ez da behar
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
            return False  #Klausula oso bat False bada, orduan guztia False izango da, beraz False bueltatu          
                    
    return True #Jasotako klausula guztiak True badira, orduan True bueltatu

def test():
    num_variables = 4
    clauses = [[1,2,-3],[2,-4],[-1,3,4]]
    assignment = [0,1,1,1,1]
    assert is_satisfied(num_variables, clauses, assignment)

    assignment = [0,1,0,1,1]
    assert not is_satisfied(num_variables, clauses, assignment)
    
    clauses = [[-3, -1], [2, -3, -4, -1], [-1, -4], [-3], [-1, -2], [-3, 4, -2], [-1, -4, 2]]
    assignment = [0,0,0,1,0]
    assert not is_satisfied(num_variables, clauses, assignment)
    
    num_variables = 5
    clauses = [[1, -5, 4], [-1, 5, 3, 4], [-3, -4]]
    assignment = [0,0,0,1,0,1]
    assert not is_satisfied(num_variables, clauses, assignment)
test()    

