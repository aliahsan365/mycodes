#include <iostream>
using namespace std;





class A {
	public:
		A() {
		cout << "a" << endl;
	}
	void say_hello() {

		cout << "holaaa como estas" << endl;

	}
};






namespace funciones {

	void f(A a) {
		a.say_hello();
	}
};