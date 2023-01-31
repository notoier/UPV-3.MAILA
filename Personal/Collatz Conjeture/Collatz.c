
int collatz(int N)
{
    int M;
    for (int n = 0; n <= 10; n++){
        for(int m = 0; m <= 10; m++){
                M = ((N * (1/2)^n *3)+1)^m;
                if (M == N){
                    return 1;
                }
        }
    }
}

void main(){
    for (int i = 0; i <= 100000; i++){
        int N = random();
        if (collatz(N)){
            println("Collatz Conjeture Solved, loop created with" + str(N));
        } else {
            println("Loop not created for" + str(N));
        }
    }
    return 0;
}