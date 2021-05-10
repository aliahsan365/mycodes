#include <iostream>
#include <vector>
using namespace std;


struct A {

    void m1 () {
        cout << "A::m1" << endl;
    }

    virtual void m2 () {
        cout << "A::m2" << endl;
    }

};


struct B : A {

    void m1 () {
        cout << "B::m1" << endl;
    }

    virtual void m2 () {
        cout << "B::m2" << endl;
    }

};


void f1 (A x) {
    x.m1();
    x.m2();
}


void f2 (A& x) {
    x.m1();
    x.m2();
}


void f3 (B& x) {
    x.m1();
    x.m2();
}


int main() {
    A a;
    a.m1();
    a.m2();

    B b;
    b.m1();
    b.m2();

    cout << endl;

    f1(a);
    f1(b);

    cout << endl;

    f2(a);
    f2(b);

    cout << endl;

    // f3(a);   no pot compilar perquè espera una B, no una A.
    f3(b);

    cout << endl;

    vector<A> v1 = {a, b};
    for (auto x : v1) {
        x.m1();
        x.m2();
    }

    cout << endl;

    vector<A*> v2 = {&a, &b};
    for (auto x : v2) {
        x->m1();
        x->m2();
    }

}
