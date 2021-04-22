#include <iostream>
using namespace std;


class A {
	public:
		A() {
			cout << "a" << endl; 
		}
		A (int v) {
			cout << "v es: " << v << endl;
		}
        void say_hello() {
        	cout << "hello" << endl;
        }



};

/*
class B : public A {
public:
	virtual void impelmentme_no_mandatory() {
		cout << "des de b" << endl;

	}



};

*/



// A a; implica instanciar tambien, contrario que JAVA.

int main() {
	//CASE 1 : 
	A a;
	a.say_hello();


}
