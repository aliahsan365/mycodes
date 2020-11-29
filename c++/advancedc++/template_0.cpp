#include <iostream>
#include <string>
#include <functional>
#include <algorithm>
using namespace std;



//another way of polymorphism : templates as functions
template<typename t> 
t Min(t a, t b) {
	if (a < b) {
		return a;
	}
	return b;
}



int main() {
	int a,b;
	a = 1; b = 2;
	double c,d;
	c = 1.0; d = 2.0;
	cout << Min(a,b) << endl;
	cout << Min(c,d) << endl;
}
