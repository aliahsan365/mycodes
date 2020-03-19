#include <iostream>
#include <vector>
#include <map>
#include <functional>
using namespace std;


int main() {
	string s("Marta");
transform(s.begin(), s.end(), s.begin(), [](char c) { return toupper(c); });
}
