#include <iostream>
#include <vector>
using namespace std;


//P69348

typedef vector<vector<int>> Matrix;






void print_sols(Matrix& sols) {

	int n = sols.size();
	int m = sols[0].size();

	for (int i  = 0; i < n; ++i) {
		cout << "(";
		for (int j = 0; j < m; ++j) {
			cout << sols[i][j] << ",";
		}
		cout << ")";
	}

}






void all_combinations(int step, int limit, vector<int>& sol, Matrix& sols) {

	if (n > 1) {
		for (int i = 1; i <= limit; ++i) {
			
			all_combinations(step+1,limit,sol,sols);
		}
	}
	else {


	}




}









int main() {

	int n;
	cin >> n;
	Matrix sols = vector<vector<int>> (n,vector<int>(n));
	vector<int> sol(n);
	all_combinations(n,sol,sols);
	print_sols(sols);
}