#include <iostream>
#include <vector>
#include <string>
using namespace std;



void printsol(vector<int> &v) {
    for (int i = 0; i < int(v.size()); ++i) {
        cout << v[i] << " ";
        }
    cout << endl;
} 


void printboard(vector<int> &sol) {
    int n = int(sol.size());
    vector<vector<string>> board(n,vector<string> (n,"*"));
    for (int i = 0; i < n; ++i) {
        int f,c;
        f = i;
        c = sol[f];
        board[f][c] = "R";
        }
    for (int i = 0; i < int(board.size()); ++i) {
        for (int j = 0; j < int (board[i].size()); ++j) {
            cout << board[i][j] << " ";
            }
        cout << endl;
        }
    cout << endl;
    }    




void printsols(vector<vector<int>> &sols) {
	for (int i = 0; i < int(sols.size()); ++i) {
        for (int j = 0; j < int (sols[i].size()); ++j) {
            cout << sols[i][j] << " ";
            }
        cout << endl;
        printboard(sols[i]);
        }
    cout << endl;
    }   


bool checking(vector<int> &sol){ 
	int n = int(sol.size());
	for (int i = 0; i < n; i++){
		for (int j = i+1; j < n; j++){
			if (sol[i] == sol[j])
			 {
				 return false;
			 }
			 if (sol[i] - sol[j] == i - j or sol[i] - sol[j] == j - i)
			 {
				 return false;
			 }
			 
		}
	}
	return true;
}

	
void allsolutions(vector<int> &sol, int step, int limit, vector<vector<int>> &allsols) {
	//step = depth 
	if (step < limit) {	
		for (int i = 0; i < limit; ++i) {
			// sol[step], marcando la profuncidad
			sol[step] = i;
			allsolutions(sol,step+1,limit,allsols);
			}
		}
	else {
		//caso base : step >= limit.
		// solo aceptamos las solucion si cumple con las restriciones
		if (checking(sol)) {
			allsols.push_back(sol);
			}
	}
}


int main() {
    int n;
    cin >> n;
    vector<int> sol(n);
    vector<vector<int>> sols;
    allsolutions(sol,0,n,sols);
    printsols(sols);
    cout << "el numero de soluciones es " << int(sols.size()) << endl;
}
 

