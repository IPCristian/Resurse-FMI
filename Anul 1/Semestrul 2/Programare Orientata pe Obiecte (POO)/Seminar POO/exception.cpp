#include <iostream>
using namespace std;

class B {

};

class D: public B {

};


int main () {

    try {
        throw dec();
    } catch (B b) {

    } catch (D d) {

    }


    cout << endl;

    return 0;
}