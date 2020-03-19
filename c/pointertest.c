#include <stdio.h>
#include <string.h>
#include "/home/ali-bsc/Escritorio/ctutorials/misfunciones.h"

struct emp_account
{
    int systemid;
    char username[25];
    char password[25];
};

struct emp
{
    char name[25];
    char surname[25];
    int id;
    float salary;
    struct emp_account account;
    struct emp_account* paccount;
};

int main(void ) {
    printf("introduce primer numero\n");
    int n1;
    scanf("%d",&n1);
    printf("introduce segundo numero\n");
    int n2;
    scanf("%d",&n2);
    printf("%d\n",n1+n2);
    suma_por_dos(&n1,&n2);
    printf("vuelvo hacia main para imprimir\n");
    printf("%d\n",n1+n2);
    suma_por_dos(&n1,&n2);
    printf("vuelvo hacia 22222main para imprimir\n");
    printf("%d\n",n1+n2);
    suma_moficando_valores(n1,n2);
    int id;
    printf("dame el id del empleado\n");
    scanf("%d",&id);
    struct emp emp1;
    struct emp emp2;
    emp1.id = id;
    printf("el id del primer empleado es ");
    printf("%d\n",emp1.id);
    emp1.account.systemid = emp1.id*2;
    printf("%d\n", emp1.account.systemid);
    printf("ahora imprimimos usando punteros");
    struct emp_account* emppaccount;
    emppaccount = &emp1.account;
    int idfinal = emppaccount->systemid;
    printf ("idfinal con punteros\n");
    printf("%d\n", idfinal);
    //printf("%d\n", (emp1.paccount)->systemid);
    int misnumeros[10] = {0,1,2,3,4,5,6,7,8,9};
    for (int i = 0; i< (int)(sizeof(misnumeros)/sizeof(int)); ++i) {
      printf ("%d\n", misnumeros[i]);
    }
    struct emp_account lista_cuentas[2];
    lista_cuentas[0].systemid = 1;
    lista_cuentas[1].systemid = 2;
    for (int i =0; i < 2; ++i) {
      printf("%d\n", lista_cuentas[i].systemid);
    }
    return 0;

}
