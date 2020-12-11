#include <iostream>
#include "Arbre.hpp"

int main() {

	int ra,rb,rc;
	std::cin >> rb >> rc;
	
	Arbre b = Arbre(rb);
	Arbre c = Arbre(rc);
	
	std::cin >> ra;
	
	Arbre a = Arbre(ra,&b,&c);
	a.print_preordre();
	std::cout << std::endl; 
	
	Arbre d = Arbre(4,&a,NULL);
	d.print_preordre();
	std::cout << std::endl; 
	
	Arbre e = Arbre(5,NULL,NULL);
	e.print_preordre();
	std::cout << std::endl; 

	d.plantar(&a,&e);
	d.print_preordre();
	std::cout << std::endl; 
}