#include <iostream>
#include "Arbre.hpp"
using namespace std;


int main() {

	Arbre a = Arbre(5);
	if (a.is_empty()) {
		cout << "arbol vacio" << endl;
	}
	else {
		cout << "arbol no vacio" << endl;
	}
}