#  *** Problema honetan, literalen asignazioak True edo False bezala adierazi dira, 1 eta 0 izan beharrean
#   * True = 1 eta False = 0

def sat_preprocessing(num_variables, clauses):
    assignment = [False] + ([None] * num_variables) # X0 den klasularik ez dagoenez, hasierako posizioa False batekin hasieratuko dugu, aldiz, beste gustiak None izango dira

    jarraitu = True # Jarraitu hasieratu
    while jarraitu:
        jarraitu = False # Jarraitu ezin dugula adierazi
        if r1_konprobatu(clauses): # R1 betetzen den konprobatu
            r1_aplikatu(clauses, assignment) # R1 aplikatua
            jarraitu = True # Jarraitzear daukagu
        if r2_konprobatu(clauses, assignment): # R2 betetzen den konprobatu
            r2_aplikatu(clauses, assignment) # R2 aplikatu
            jarraitu = True # Jarraitzear daukagu
        r3_aplikatu(clauses, assignment) # R3 aplikatu
        if not r4_aplikatu(clauses, assignment): # R4 aplikatzean False bueltatzen badu
            return [[1], [-1]] # Orduan zerrenda hori bueltatuko dugu
    return clauses # Clausulak bueltatu


def r1_konprobatu(clauses):
    for clause in clauses: # Klausulak iteratu
        if len(clause) == 1: # 1-eko luzera duen klausula aurkitzen badugu
            return True #Orduan True bueltatu
    return False #Bestela, iterazioak amaitzean False bueltatu


def r1_aplikatu(clauses, assignment):
    clause = [clause for clause in clauses if len(clause) == 1][0] #  1-eko luzerako klausula bat hartu
    literala = clause[0] # Literala atera
    assignment[abs(literala)] = literala > 0 # Literal positiboa bada, orduan True, bestela False

def r2_konprobatu(clauses, assignment):
    bakarrak = [literal for clause in clauses for literal in clause] # Errepikatzen ez diren literak zerrenda batean sartu
    for i in range(1, len(assignment)): # Zerrenda errekorritu
        if (bakarrak.count(i) == 1 ^ bakarrak.count(-i) == 1) and assignment[i] is None: # Literal horren ezezkoa ez badago eta haietako bat agertzen bada (XOR egin) eta jadinik asignazio bat ez badu
            return True # Orduan True bueltatu
    return False # Bestela False


def r2_aplikatu(clauses, assignment):
    bakarrak = [literal for clause in clauses for literal in clause]  # Errepikatzen ez diren literak zerrenda batean sartu
    for i in range(1, len(assignment)): # Zerrenda errekorritu
        if (bakarrak.count(i) == 1 ^ bakarrak.count(-i) == 1) and assignment[i] is None:
            assignment[i] = bakarrak.count(i) == 1 # Literal horren ezezkoa ez badago eta haietako bat agertzen bada (XOR egin) eta jadinik asignazio bat ez badu
            return


def klausula_konprobatu(clause, assignment):
    for literal in clause: # Klausularen literalak iteratu
        if literal < 0: # Literala negatiboa bada 
            konprobaketa = assignment[abs(literal)] == 0 # Konprobatu literal horren asignazioa 0 dela
        else: # Bestela
            konprobaketa = assignment[abs(literal)] == 1 # Konprobatu literla horren asignazioa 1 dela
        if konprobaketa: # Konprobaketa ondo badago
            return True # Orduan True bueltatu
        
    return False # Bestela, for loop-a amaitzean, False bueltatu


def r3_aplikatu(clauses, assignment):
    i = 0 # i hasieratu
    while i < len(clauses): # i klasularen tamaina baino txikiagoa den bitartean
        if klausula_konprobatu(clauses[i], assignment): # Klausula betetzen bada
            clauses.pop(i) # Klausula hori kendu
        else: # Bestela
            i += 1 # i eguneratu


def r4_aplikatu(clauses, assignment):
    for clause in clauses: # Klausulak iteratu
        for literal in clause: # Klausularen literalk iteratu
            x = assignment[abs(literal)] # Literal horri dagokion asignazioa lortu
            if x is None: # Asignaziorik ez badago, hau da, None bada
                continue # Orduan hurrengo literalera pasatu

            if (literal > 0 and not x) or (literal < 0 and x): # Bestela, literal negatiboa bada eta haren asignazioa False bada edo kontrakoa
                clause.remove(literal) # Literala klausulatik kendu

            if not clause: # Klausula hutsik geratu bada, klausula hori betetzen ez dela esan dezakegu
                return False # Beraz, False bueltatu
    return True # Bestela, iterazio guztien ostean True bueltatu

#################
###TEST KASUAK###
#################

def test():
    assert [] == sat_preprocessing(1, [[1]])
    assert [[1], [-1]] == sat_preprocessing(1, [[1], [-1]])
    assert [] == sat_preprocessing(4, [[4], [-3, -1], [3, -4, 2, 1], [1, -3, 4],
                                       [-1, -3, -4, 2], [4, 3, 1, 2], [4, 3],
                                       [1, 3, -4], [3, -4, 1], [-1]])
    assert [[1], [-1]] == sat_preprocessing(5, [[4, -2], [-1, -2], [1], [-4],
                                                [5, 1, 4, -2, 3], [-1, 2, 3, 5],
                                                [-3, -1], [-4], [4, -1, 2]])

    ans = [[5, 6, 2, 4], [3, 5, 2, 4], [-5, 2, 3], [-3, 2, -5, 6, -4]]
    assert ans == sat_preprocessing(6, [[-5, 3, 2, 6, 1], [5, 6, 2, 4],
                                        [3, 5, 2, -1, 4], [1], [2, 1, 4, 3, 6],
                                        [-1, -5, 2, 3], [-3, 2, -5, 6, -4]])
    #  Espreski 2. erregela frogatzeko
    assert [] == sat_preprocessing(7, [[-5, 3, 2, 6, 1], [5, 6, 2, 4],
                                       [3, 5, 2, -1, 4], [1], [2, 1, 4, 3, 6],
                                       [-1, -5, 2, 3], [-3, 2, -5, 6, -4, 7]])


test()
