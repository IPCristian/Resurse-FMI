#include <iostream>
using namespace std;

class A {
public:
    A () {cout<<"A";}
    virtual ~A() = 0;
};
A::~A(){cout<<"~A";}

class B : public A {
public:
    B(){cout<<"B";}
    ~B(){cout<<"~B";}
};

class C: public B {
public:
    C () {cout << "C";}
    ~C () {cout << "~C";}
};

int main () {
    C c;
    B &pb = c;
    return 0;
}
