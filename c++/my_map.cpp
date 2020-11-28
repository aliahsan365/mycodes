#include <iostream>
#include <map>
#include <string>
#include <functional>
#include <vector>
#include <iterator>
using namespace std;


int main() {

	map<char,int> my_map; 
	my_map['a'] = 1;
	my_map['b'] = 2;
	my_map['c'] = 3;

	
	map<char,int>::iterator it;
	for (it = my_map.begin(); it!=my_map.end(); ++it) {
		cout << (*it).first << " => " << (*it).second << endl;
	}

	auto my_map_copy(my_map);
	auto it2 = my_map_copy.end(); // itr is of type std::map<char,int>::iterator
	char key;
	int value;



}