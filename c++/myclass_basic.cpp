
#include <iostream>
#include <vector>
#include <string>
using namespace std;


class Enemy {       
  public:
  	string name;
  	void set_name(string name) {
  		(*this).name = name;
  	}
  	string get_name()  {
  		return (*this).name;
  	}

};


class Player{
    public:
		string name;
		void set_name(string name) {
			(*this).name = name;
		}
		string get_name() {
			return (*this).name;
		}

};

//compilation : g++ -std=c++17 -o myclass_basic myclass_basic.cpp 


int main() {

	Enemy e = Enemy();
	Player p = Player();
	p.set_name("ali");
	cout << p.get_name() << endl;

}
