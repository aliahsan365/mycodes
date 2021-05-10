#include <iostream>
#include <vector>
using namespace std;


//P81966


//https://jutge.org/problems/P81966_en


int position(double x, const vector<double>& v, int left, int right) {

	int m = (left + right) / 2;
	if (left > right) {
		return -1;
	}
	else if (right >= 0) {
		if (v[m] == x) return m;
		else if (v[m] > x) return position(x,v,left,m-1);
		else if (v[m] < x) return position(x,v,m+1,right); 
	}
	return -1;
}


/*
int position(double x, const vector<double>& v, int left, int right) {
	if (left > right) return -1;
	int mid = (left+right)/2;
	if (x < v[mid]) return position(x, v, left, mid-1);
	if (x > v[mid]) return position(x, v, mid+1, right);
	return mid;
}
*/
int main() {

	vector<double> v = {1,2,3,4,5,6,7,8};

	double x = 8;

	cout << position(x,v,0,7) << endl;


}