#include <stdlib.h>
#include <stdio.h>



void f(int a[]) {
    int a_size = sizeof(a)/sizeof(int);
    printf("%d\n", a_size);


}



int main() {
   
    int a[5] = {1,2,3,4,5};
    int b[] = {1,2,3,4,5,6};

    f(a);
    f(b);



}