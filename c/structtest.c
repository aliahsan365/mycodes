#include <stdio.h>
#include <string.h>

struct coche
{
	int mat;
	struct coche *next;
};


int main(void) {
    struct coche c1 = {1,NULL};
    struct coche c2 = {2,NULL};
    struct coche c3 = {3,NULL};
    struct coche c4 = {4,NULL};
    c1.next = &c2;
    c2.next = &c3;
    c3.next = &c4;
    struct coche *pcoche;
    pcoche = &c1;
    while ( pcoche != NULL) {
        printf("%d\n",pcoche->mat);
        pcoche = pcoche->next;
      }
    return 0;
  }