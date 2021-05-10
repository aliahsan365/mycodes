#include <iostream>
#include <stack>
using namespace std;


int main() {

    while (true) {
    	stack<int> original, temporal, reverse;
    	int num;
    	bool palindrom = true;
    	while (!getline(cin,endl)) {
    		cin >> num;
            original.push(num);
    		temporal.push(num);
    	}
    	while(!temporal.empty()) {
    		int t = temporal.top();
    		temporal.pop();
    		reverse.push(t);
    	}
    	while(palindrom and !reverse.empty()) {
    		int o,r;
    		o = original.top();
    		r = reverse.top();
    		original.pop();
    		reverse.pop();
    		if (o != r) {
    			palindrom = false;
    		}
    	}
    	if (palindrom) {
    		cout << "It is a palindrome." << endl;
    	}
    	else {
    		cout << "It is NOT a palindrome." << endl;
    	}


    }
	
}

