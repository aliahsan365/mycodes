#include <iostream>

class Arbre {
public:
	Arbre(int);
	Arbre(int,Arbre*,Arbre*);
	void print_preordre();
	int root();
	bool is_empty();
    void plantar(Arbre*, Arbre*);
private:
	int r;
	Arbre* iz;
	Arbre* dr;
};