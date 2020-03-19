#include <stdio.h> /* incluye biblioteca donde se define E/S */


struct elemento {
	int valor;
	int *next;
	int *prev; 
	
	} elemento;

struct lista {
	int n_elementos;
	
	int *first;
	};

//ACABARLA

int main() {
	
    struct elemento e; 
    
    e.valor = 2;
    e.next = NULL;
    e.prev = NULL;
    
    printf("valor es %d\n",e.valor);

  


   return 0; 
}
