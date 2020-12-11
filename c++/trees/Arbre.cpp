#include "Arbre.hpp"

Arbre::Arbre(int root) {
	r = root;
	iz = NULL;
	dr = NULL;
}


Arbre::Arbre(int root, Arbre* i, Arbre* d) {
	r = root;
	iz = i;
	dr = d;
}


int Arbre::root() {
	return r;
}

bool Arbre::is_empty() {
	return this == NULL;
}


void Arbre::plantar(Arbre* a, Arbre* b) {
      iz = a;
      dr = b;
}


void Arbre::print_preordre() {
	if ( iz != NULL) {
		(*iz).print_preordre();
	   }
    std::cout << (*this).root() << " ";
    if(dr != NULL) {
    	(*dr).print_preordre();
    }
}

