#include <stdio.h>
#include <string.h>

void suma_por_dos(int *n1,int *n2) {
    printf("dentro de la funcion\n");
    printf("%d\n",(*n1));
    printf("%d\n",(*n2));
    //multiplico el condtenido por 2"
    *n1 = (*n1)*2;
    *n2 = (*n2)*2;
    printf("salgo de la funcion\n");
}


void suma_moficando_valores(int n1,int n2) {
    printf("dentro de moficando valores");
    printf("sin modificar\n");
    printf("%d\n",n1);
    printf("%d\n",n2);
    //multiplico el condtenido por 2"
    printf("con modificar\n");
    int* n1p = &n1;
    int* n2p = &n2;
    *n1p = n1*2;
    *n2p = n2*2;
    printf("%d\n",n1);
    printf("%d\n",n2);
    printf("salgo de la funcion suma_modificando_valores hacia el main\n");
}

