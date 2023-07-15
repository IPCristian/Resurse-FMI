#include <iostream>

int sum (int a, int b = 0, int c = 0) {
    return a + b;
}

int main () {
    // se apeleaza sum cu a = 4, b = 87 si c = 34
    std::cout << sum(4, 87, 34);
    
    // se apeleaza sum cu a = 10, b = 43 si c = 0 - valoare default
    std::cout << sum(10, 43);
    
// se apeleaza sum cu a = 5, b = 0 si c = 0 - b si c valori default
    std::cout << sum(5);         

    return 0;
}