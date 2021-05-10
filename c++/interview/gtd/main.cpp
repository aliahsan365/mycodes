#include <iostream>

using namespace std;


struct Foo {};
struct Bar {};



int main() {
	Foo* f = new Foo;

	Bar* b1 = f;
	Bar* b2 = static_cast<Bar*> (f);
	Bar* b3 = dynamic_cast<Bar*> (f);
	Bar* b4 = reinterpret_cast<Bar*>(f);
	Bar* b5 = const_cast<Bar*> (f);

	return 0;

}
