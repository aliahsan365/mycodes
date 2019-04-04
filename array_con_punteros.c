# include <stdio.h> /* incluye biblioteca donde se define E/S */


int main() {
	
 
    
   int N[6] = {1,2,3,4,5,6};
   int *p;
   p = N; // p contiene la direccion al primer elemento de N. N[0].
 
 
   printf("normal\n");
   for (int i = 0; i < 6; ++i) {
	   int num = N[i];
	   printf("%d\n",num);
	   }
   printf("con punteros\n");
   int n = sizeof(N)/sizeof(int);
   for (int i = 0; i < n; ++i) {
	   int *aux;
	   aux = p + i;
	   printf("%d\n",*aux);
	   }	   
	   
	   
	   
	   
   
	

}



