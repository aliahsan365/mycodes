#include <iostream>
#include <string>
#include <functional>
using namespace std;

auto y = [] (int first, int second)
{
    return first + second;
};



void _sum(void *f) {
	cout << y(66,3) << endl;
}


 


int main() {
	_sum(&y);
	//cout << y(2,3) << endl;
}
