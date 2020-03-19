#include <stdio.h> /* incluye biblioteca donde se define E/S */





int findPos(int N[], int n_elementos, int valor) {
	
	int pos = -1;
	int min,max;
	min = 0; 
	max = n_elementos;
	int mitad = (max+min)/2;
	
	char c = 'F';
	
	while (min <= max && c == 'F') {
	    int current_elem = N[mitad];
	    
	    if (current_elem  == valor) {
			pos = mitad;
			c = 'V'; 
		}
	    else if (current_elem > valor) {
			max = mitad;
			mitad = (max+min)/2;
			
			}
	   else {
		   //valor > current_elem
		   min = mitad;
		   mitad = (max+min)/2;
		   }
		
		
		}
	

	return pos;

	
	}



int main() {
	
 
   //pre: vector esta ordenado
   //pos       0 1 2 3 4 5
   int N[6] = {1,2,3,4,5,9};
   int valor = 5;
   int n_elems = sizeof(N)/sizeof(int);
   int pos = findPos(N,n_elems,valor);
   if (pos > -1)  {
	  printf("pos del elemento buscado es: %d\n",pos); 
	  }
   else {
	  printf("el elemento buscado no esta en el array\n"); 
    }
   return 0; 
}



