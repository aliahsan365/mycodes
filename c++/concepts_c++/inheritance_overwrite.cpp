#include <iostream>
using namespace std;

//herencia v1

class A {

public:
	void f () {
		cout << "fa" << endl;
	}


};

class B : public A {
public:
	void f () {
		cout << "fb" << endl;
	}

};

int main() {
	A a;
	a.f();
	B b;
	b.f();



}