#include <iostream>

using namespace std;


class Customer {
private:
	static int defaultCount;
};


int main() {


Customer::defaultCount = new int;
defaultCount = 10;

}