#include <iostream>

using namespace std;

class A {
    protected:
        int x;
    public:
        A() {cout << "A";}
        ~A () {cout<<"~A"<<endl;}
};

class B {
    protected:
        int x;
    public: 
        B() {cout<<"B" << endl;}
        ~B () {cout<<"~B"<<endl;}
};

class C: public A, public B {
    public:
        C () : B(), A() {
            A::x = 3;
        }
        friend void showC (C c);
};

void showC (C c) {
    cout << c.A::x << " ";
}

int main () {
    C c;
}