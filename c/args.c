#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[]) {

	printf("%d\n",argc);

	if (argc > 1) {
		int i;

		for (i = 1; i < argc; ++i) {
			printf("el argumento %d es %s\n",i,argv[i]);
		}
	}
}