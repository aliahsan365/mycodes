#include <iostream>

using namespace std;


void cambia_valor(int &a, int &b) {
	++a;
	++b;
	
	}

void cambia_valor_punteros(int *pa, int *pb)  {
	++(*pa);
	++(*pb);  
	
	}

int main() {
	
	cout << "empiezo" << endl;
	cout << "referencia normal" << endl;
	int a = 2;
	int b = 3;
	cout << "normal: a:" << a << " " << "b:" << b << endl;
	cambia_valor(a,b);
    cout << "referencia: a:" << a << " " << "b:" << b << endl;

	
	cout << "con punteros c,c++" << endl;
	
	int *pa;
	int *pb;
	pa = &a;
	pb = &b;
	cambia_valor_punteros(pa,pb);
	cout << "punteros: a:" << a << " " << "b:" << b << endl;

	cout << "con punteros estilo c tipicamente" << endl;
	cambia_valor_punteros(&a,&b);
    cout << "punteros_C: a:" << a << " " << "b:" << b << endl;

	

}
