#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"





struct my_clock_list* lc = NULL; 


int main() {
    
    int a,b;
    
    a = 8888;
    b = 3;

    int m = my_max(a,b);

    printf("%d\n",m);

    struct my_clock c;


	return 0;
}


