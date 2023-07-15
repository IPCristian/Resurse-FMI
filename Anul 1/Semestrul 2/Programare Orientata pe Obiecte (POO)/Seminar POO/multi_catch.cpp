#include <iostream>

using namespace std;

int main () {
    try {
        throw "expection";
        throw 2;
        throw 2.5;
    } catch (int x) {
        cout << "am prins expectia " << x;
    } catch (const char* s) {
        cout << "am prins exceptia " << s;
    } catch (...) {
        cout << "Exceptie :(" << endl;
    }
    return 0;
}
