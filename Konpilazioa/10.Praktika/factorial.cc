#include <iostream>
using namespace std;

int fakt (int x) {
	if (x == 0)
		return 1;
	else
		return x * fakt(x - 1);
}

int main() {
	int x, f;
	
	cout << "Sartu zenbaki positibo bat: ";
	cin >> x;
	
	if (x < 0)
		cerr << "Errorea: zenbaki negatiboen faktoriala ezin da kalkulatu." << endl;
	else {
		f = fakt(x);
		cout <<  x << " zenbakiaren faktoriala " << f << " da" << endl;
	}
	return 0;
}
