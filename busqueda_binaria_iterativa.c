# include <stdio.h> /* incluye biblioteca donde se define E/S */


int main() {
	
 
   //pre: vector esta ordenado
   //pos       0 1 2 3 4 5
   int N[6] = {1,2,3,4,5,9};
   int valor = 5;
   int n_elems = sizeof(N)/sizeof(int);
   
   int min,max;
   min = 0; 
   
   max = n_elems;
   
   int pos; // posicon del elemento
   char  flag = 'F';
   int mitad = (max+min)/2;

   while (min <= max && flag == 'F') {
	    
	    
	    int current_elem = N[mitad];
	    
	    if (current_elem  == valor) {
			pos = mitad;
			flag = 'V'; 
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
   if (flag == 'F') {
	   printf("no se ha encontrado el elemento en el array\n");
	   
	   }
   else  {
	   printf("se ha encontrado el valor en la pos %d \n",pos);
	   
	   }
   
  return 0; 
}



