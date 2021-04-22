#include <iostream>
using namespace std;


class A {
public:
	void fa() {
		cout << "fa des de a" << endl;
	}
protected:
	void p_fa() {
		cout << "protected p_faaa" << endl;
	}
private:
	void priv_fa() {
		cout << "priv_f" << endl;
	}
};

/* CASE 1 : PRIVATE
class B : private A {
	public:
		void fb () {
			cout << "fb des de b" << endl;
			//p_fa(); se puede, es privado de B ahora		
		}
};

*/
/*CASE 2 : PROTECTED
class B : protected A {
	public:
		void fb () {
			cout << "fb des de b" << endl;
			//p_fa(); se puede, es privado de B ahora		
		}
};

class C : public B {
public:
	void fc() {
		cout << "fc des de c" << endl;
		fa();
		p_fa();
	}


};
*/
//CASE 3 : PUBLIC
class B : public A {
public:
	void fb () {
		cout << "fb des de b" << endl;
	}
};


int main() {

    cout << "CASE 1, PRIVATE" << endl;
	//A ----> B 
	//PRIVATE -> PRIVATE
	//PROTECTED -> PRIVATE
	//PUBLIC -> PRIVATE
	B b;
	b.fb();
    //b.fa(); // no se podria en variante herencia privada
    cout << "CASE 2, PROTECTED" << endl;
    //A ----> B 
	//PRIVATE -> PRIVATE
	//PROTECTED -> PROTECTED
	//PUBLIC -> PROTECTED
    //C c;
    //c.fc();
    //c.fb();
    //c.fa();
    //c.p_fa(); // puedes usar todos
	cout << "CASE 3, PUBLIC" << endl;
	//A ----> B 
	//PRIVATE -> PRIVATE
	//PROTECTED -> PROTECTED
	//PUBLIC -> PRIVATE
	b.fa();
	//b.p_fa(); // no podrias al ser protected de B, pero si des de B.

	



}