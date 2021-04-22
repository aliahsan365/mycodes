#include <iostream>
using namespace std;


class A {
	public:
		
		//virtual void implementme() = 0;
		
		void impelmentme_no_mandatory() {
			cout << "des de a " << endl;


		};
		


};

class B : public A {
public:
		
		void impelmentme_no_mandatory() {
			cout << "des de b " << endl;


		};

};



int main() {
	//CASE 1 : 
	
	//B b;
	//b.impelmentme_no_mandatory();
	A a;
	a.impelmentme_no_mandatory();
	B b; 
	b.impelmentme_no_mandatory();
	//a.impelmentme_no_mandatory();
	//a.impelmentme_no_mandatory();
	//b.impelmentme_no_mandatory();

}