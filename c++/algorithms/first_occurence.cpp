#include <iostream>
#include <vector>
using namespace std;


//P84219


//https://jutge.org/problems/P84219_en

int first_occurrence(double x, const vector<double>& v) {

	int left,right;
	left  = 0;
	right = v.size();

	while (left < right or right >= 0) {

		int m =  (left + right) / 2;

		if (v[m] == x) return m;
		
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

	vector<double> v = {1,2,3,4,5,6,8,8,8,8,9};

	double x = 8;

	cout << first_occurrence(x,v) << endl;


}