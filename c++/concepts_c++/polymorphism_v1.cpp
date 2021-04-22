#include <iostream>
using namespace std;


//polimorfismo: virtual vs virtual = 0.

class A {

public:
	virtual void f () {
		cout << "fa" << endl;
	}


};

class B : public A {
public:
	void f () {
		cout << "fb" << endl;
	}

};

class C : public A {



};


class D {

public:
	virtual void fd() = 0;

};


class E : public D{
public:
	void fd() {
		cout << "fd e" << endl;
	}
}; 


class F : public D {
public:
	void fd() {
		cout << "fd f" << endl;
	}


};

int main() {

	A a;
	a.f();
	B b;
	b.f();
	//virtual sin forzar (virtual != 0) implica que da una definion para c des de clase Base
	C c;
	c.f();
	//D d; // D no se puede instanciar al ser abstracta, puramente abstracta en este caso
	//d.fd(); // consecuencia logica de D d.
	E e;
	e.fd();
	F f;
	f.fd();
	


}