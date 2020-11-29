
#include <iostream>
#include <vector>
using namespace std;



class Test {       
  public:             
    int type;        
    Test() {
    	cout << "test is created" << endl;
    } 

};


class Integration : Test {

	public:
		Integration ()  {
            //it calls parent constructor 
			cout << "Integration test is created" << endl;
		}
};


class Unit : Test {

	public:
		Unit ()  {
            //it calls parent constructor 
			cout << "Unit test is created" << endl;
		}
};




//compilation : 

int main() {

	Test t = Test();
	Integration i = Integration();
	Unit u = Unit();








}