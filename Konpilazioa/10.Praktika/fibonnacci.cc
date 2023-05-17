#include <iostream>
using namespace std;

int fib (int x) {
	if (x == 1 || x == 0) 
		return x;
	else 
		return fib(x-1)+fib(x-2);
}

int main() {
	int x,i=0;
	
	cout << "Sartu seriearen elementu kopurua: ";
	cin >> x;
	if (x < 0)
		cerr << "Errorea: zenbaki negatiboekin ezin da seriea eratu." << endl;
	else {
		cout << "Fibonacci-ren seriea: ";
		while(i < x) {
			cout << " " << fib(i);
			i++;
		}
		cout << endl;
	}
	return 0;
}