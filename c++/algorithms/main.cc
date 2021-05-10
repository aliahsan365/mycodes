#include <iostream>
#include <vector>
using namespace std;


int position(double x, const vector<double>& v, int left, int right) {
    int p = right + left / 2;
    if (p > 1) {
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
    int n;
    while (cin >> n) {
        vector<double> V(n);
        for (int i = 0; i < n; ++i) cin >> V[i];
        int t;
        cin >> t;
        while (t--) {
            double x;
            int left, right;
            cin >> x >> left >> right;
            cout << position(x, V, left, right) << endl;
        }
    }
}
