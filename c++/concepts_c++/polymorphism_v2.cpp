#include <iostream>
using namespace std;


//polimorfismo: virtual vs virtual = 0, version 2.

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

	A* a1 = new B();
	A* a2 = new C();
	a1-> f(); // para a1 (B) , usara la def de B, fb.
	a2-> f(); // para a2 (C) , usara la def de A, fa.
	//D d = new D(); //esto no se puede hacer pk D() es clase abstracata
	D* d1 = new E(); // esto si pk instanciamos E que no es abstracta
	d1->fd();
	D* d2 = new F(); 
	d2->fd();
	//nota: Declarado como hijo, no puede instanciar padre, al reves si.
	//B b1 = new A(); 
	





}