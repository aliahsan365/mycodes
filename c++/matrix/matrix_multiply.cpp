#include <iostream>
#include <vector>

using namespace std;

typedef vector<vector<int>> Matrix;


void read_matrix(Matrix& m) {
	for (int i = 0; i < m.size(); ++i) {
		for (int j = 0; j < m[i].size(); ++j) {
			cin >> m[i][j];
		}
	}
}

void write_matrix(Matrix& m) {
	for (int i = 0; i < m.size(); ++i) {
		for (int j = 0; j < m[i].size(); ++j) {
			cout << m[i][j] << " ";
		}
		cout << endl;
	}
}

Matrix multiply_matrix(Matrix& a, Matrix& b) {

	int M = a.size();
	int N = b[0].size();
	Matrix res = vector<vector<int>> (M,vector<int> (N));
	for (int i = 0; i < M; ++i) {
		for(int j = 0; j < N; ++j) {
			int suma = 0;
			for (int k = 0; k < N; ++k) {
				suma += a[i][k] * b[k][j];
			}
			res[i][j] = suma;
		}
	}
	return res;

}



int main() {

	//input 1 : 
	//2 3 3 2
    //1 2 3 4 5 6
    //1 2 3 4 5 6

    //input 2 :
    //2 2 2 2
    //1 2 3 4
    //1 2 3 4

    //input 3:
    //4 3 3 1
    //1 2 3 4
    //1 2 3 4
    //1 2 3 4
    //4
    //5
    //6

	
    
	int F1,C1,F2,C2; // filas, columnas
	
	cin >> F1 >> C1 >> F2 >> C2;
    if (C1 != F2) {
    	return 1;
    }
	Matrix a = vector<vector<int>> (F1,vector<int> (C1));
	Matrix b = vector<vector<int>> (F2,vector<int> (C2));
	read_matrix(a);
	read_matrix(b);
	//res size will be : F1 x C2
	Matrix res = multiply_matrix(a,b);
	write_matrix(res);
	return 0;
}