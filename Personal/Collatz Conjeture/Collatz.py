import random

def Collatz(N):
    if N == 1:
        return True
    if N % 2 == 0:
        N = N/2
    else:
        N = N*3 +1
    return Collatz(N)
    
def main():
    for N in range(500,10000000000):
        result = Collatz(N)
        if result:
            print("Conjeture solved for " + str(N))
            
        else:
            print("Conjeture not solved for " + str(N))
        
if __name__ == "__main__":
    main()