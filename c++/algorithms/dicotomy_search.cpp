#include <iostream>
#include <vector>
using namespace std;






int position(double x, const vector<double>& v, int left, int right) {
	int p = right + left / 2;
	int n = v.size();
	if (n >= 1) {
		if (v[p] > x) {
			return position(x,v,0,p-1);
		}
		else if (v[p] < x) {
			return position(x,v,p+1,n-1);
		}
		else if (v[p] == x) {
			return p;
		}
	}
	return -1;
}



int main() {

	vector<double> v = {0.0,1.0,2.0,3.0,4.0,5.0,7.0};
	double x = 7.0;
	int n = v.size();
	int p = position(x,v,0,n-1);
	cout << "position: " << p << endl;



}