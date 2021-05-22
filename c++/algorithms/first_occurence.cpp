#include <iostream>
#include <vector>
using namespace std;


//P84219


//https://jutge.org/problems/P84219_en

int first_occurrence(double x, const vector<double>& v) {

	int left,right;
	left  = 0;
	right = v.size();
	while (left < right) {
		if (right < 0) {
			return -1;
		}

		int m =  (left + right) / 2;
		
		if (v[m] == x) {
			
			while (m >= 0) {
				if (m == 0) {
					return m;
				}
				if (v[m] == x) {
					--m;
				}
				else {
					return m+1;
				}

			}
			
		}
		
		else if (v[m] > x) {
			right = m - 1;
		}
		
		else if (v[m] < x) {
			left = m + 1;		
		}
	}
	return -1;

}



int main() {

	vector<double> v = {1,2,3,4,5,6,7,8,8,8,8};

	double x = 1;

	cout << first_occurrence(x,v) + 1  << endl;


}