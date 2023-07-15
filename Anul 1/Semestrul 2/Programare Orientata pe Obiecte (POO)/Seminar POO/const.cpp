#define x 30

int main () {
    int i = 6;
    int b = 3;
    const int * const p = &i;   // pointer catre o constanta de tip intreg
    //  *p = 2;              // eroare 
    p = &b;              // functioneaza
    int* const cp = &i;  // pointer constant
    *cp = 6;             // functioneaza
    //  cp = &b;             //eroare
    const int &r1 = i;   // referinta catre o constanta
    return 0;
}