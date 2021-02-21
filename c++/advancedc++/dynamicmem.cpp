#include <iostream>
using namespace std;


void print(int* a, int N) {
	for (int i = 0; i < N; ++i) {
		cout << a[i] << " ";
	}
	cout << endl;
}

void increment(int *a, int N) {
	for (int i = 0; i < N; ++i) {
		a[i] = ++a[i]; 
	}
}

// da error ejecucion,devolver la @ de c,el stack libera la memoria al salir de la funcion,
// y c ya no existe, asi que imprimir c en el main u otra funcion: da error en exec time.
/*
int* copy(int *a, int N) {

	int c[N];
	for (int i = 0; i < N; ++i) {
		c[i] = a[i];
	}
	return c;
}
*/


void copy_v2(int *a, int N, int* c) {
	for (int i = 0; i < N; ++i) {
		c[i] = a[i];
	}
}

int* copy_v3(int *a, int N) {
	// esta vez, alocatamos mem en heap(nosotros somoms responsables de eliminarla cuando ya no sea necesaria)
	// si nos olvidamos, en ciertos lenguajes se hace automatico, o en si , el S.O. al terminar el programa libera todas las memoria.
	int* c = new int[N];
	for (int i = 0; i < N; ++i) {
		c[i] = a[i];
	}
	return c;
}



int main() {
	int N = 5;
	

	//declaramos array a de N, y alocatamos con 5xzeros (enteros).
	int a[N] = {0,0,0,0,0};
    int c[N]; //solamente declaramos , no alocatamos.
	cout << a << endl; // imprime la @ de inicio de a en stack

	print(a,N);
	increment(a,N);
	print(a,N);
	
	//int* c = copy(a,N);
	//print(c,N);

	copy_v2(a,N,c);
	increment(c,N);
	print(c,N);
	
	int* d = copy_v3(c,N);
	increment(d,N);
	print(d,N);
	
}

