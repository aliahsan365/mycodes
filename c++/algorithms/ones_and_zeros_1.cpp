#include <iostream>
#include <vector>
using namespace std;


void print_vector(vector<int> v) {
	int n = v.size();

	for (int i = 0; i < n; ++i) {

		cout << v[0] << " ";
	} 
	cout << endl;
}



void bt(int n, int step,  vector<int> v) {

	
    if (step > n-1) {
    	print_vector(v);
    }

    else {

    	for (int i = step; i < n; ++i) {
    		for (int j = 0; j < 2; ++j) {
    			v[i] = j;
    			bt(n,i,v);
    			
    		}
    	}
    }
}



int main() {
	
	int n;

	cin >> n;

	vector<int> v(n);


	
	
	bt(n,0,v);

	cout << endl;


}