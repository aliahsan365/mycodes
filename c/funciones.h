#include <stdio.h>
#include <stdlib.h>


int my_max(int a, int b) {
	return a>b?a:b;
}


int my_min(int a, int b) {

	if (a > b) {
		return b;
	}
	return a;
}


struct my_clock {

	int h,m,s;

};


struct my_clock_node {

	int n_elementos;
	struct my_clock* prev,next;
	struct my_clock c;

};
