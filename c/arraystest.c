#include <stdio.h>
#include <string.h>


void print_array(int *array, int len) {
	
	for (int i = 0; i < len; ++i) {
		printf("%d\n",*(array+i));
	}

}



int main(void) {
	int array[4] = {1,2,3,4};
	//esta forma no es seguroa para implementarlo en una funcion
	//mejor hacerlo con el sizof o puntero al array
	printf("impriminedo array tradicional c\n");
	for (int i = 0; i < 4; ++i) {
		printf("%d\n",array[i] );
	}

	//


	int n = sizeof(array)/sizeof(int);
	printf("imprimindo con sizeof\n");
	for (int i = 0; i < n; ++i) {
		printf("%d\n",array[i] );
	}

	int *p;
	p = &array[0];
	printf("imprimindo con puntero_ini\n");
	//funciona pk esta es por bytes en memoria.

	for (int i = 0; i < n; ++i) {
		printf("%d\n",*(p+i));
	}




	printf("imprimindo con puntero_ini_funcion\n");
	//n=(int)sizeof(array)/sizeof(int)
	print_array(&array[0],n);





}