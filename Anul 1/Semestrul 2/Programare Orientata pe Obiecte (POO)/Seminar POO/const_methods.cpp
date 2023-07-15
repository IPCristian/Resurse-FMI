#include <iostream>

class A {
    const int i = 3;
    float f;
public:
    A (int a, float b = 3.0) : i(a) {
        f = b;
        std::cout << i;
        // i = (int) f - a; // eroare de compilare
    }

    void foo () const { // metoda const
        int j = i + 22;
        // f = 33;          //eroare de compilare
    }

    void bar () {
        // f = 25;         // metoda nu e constanta, putem modifica
    }
};


int main () {
    const A a(4);
    // a.bar();  // eroare de compilare
    a.foo();   // functioneaza
}