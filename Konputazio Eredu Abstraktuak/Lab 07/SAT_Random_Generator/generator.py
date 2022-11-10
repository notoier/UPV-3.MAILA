import sat_generator
import preSAT

import sys

def main(argv):

    variables = int(sys.argv[1])
    clauses = int(sys.argv[2])
    sats = [sat_generator.generate(variables, clauses) for i in range(1)]
    #print "Eliminados los posibles repetidos:"
    #sats = [[list(set(x)) for x in elem] for elem in sats]
    
    #sats = [list(dict.fromkeys(elem)) for elem in sats]
    #sats = list(set(sats))
    
    p1 = set(tuple(x) for x in sats[0])
    
    print("Ausaz sortutako SAT formula:\n" + str(sats[0]))
    
    """
    for clause in sats:
        preSAT.sat_preprocessing(variables, clause)
    """
    preprocessed = preSAT.sat_preprocessing(variables, sats[0])
    print("Aurreprozesatutako SAT formula:\n" + str(preprocessed))
    
if __name__ == "__main__":
    if (len(sys.argv) != 3):
        print('generator.py <number_of_variables> <number_of_clauses>')
        sys.exit(-1)
    main(sys.argv[1:])
