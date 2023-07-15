#include <iostream>
#include <cmath>
using namespace std;
class Point {
    int x, y;
    public:
    Point (const int& a = 0, const int& b = 0) : x(a), y(b) { }
    // supraincarcarea operatorului - pentru a
    // determina distanta dintre doua puncte
    double operator-(const Point&) const;
    // supraincarcarea operatorului * pentru produsul
    // scalar a doua puncte/doi vectori
    int operator*(const Point&) const;
    // supraincarcarea operatorului de atribuire
    Point& operator=(const Point&);
    void operator() (int = 2);
    int operator[] (int = 3);
    // supraincarcarea operatorului + pentru
    // tranlatarea unui punct
    friend Point operator* (const int&, const Point&);
    // supraincarcarea operatorului << pentru afisarea unui punct
    friend ostream& operator<<(ostream&, const Point&);
    // supraincarcarea operatorului >> pentru citirea unui punct
    friend istream& operator>>(istream&, Point&);
};

double Point::operator- (const Point& p) const {
    double dx = x - p.x, dy = y - p.y;
    double px = dx*dx, py = dy*dy;
    return sqrt(px+py);
}

int Point::operator* (const Point& p ) const {
    return x * p.x + y *p.y;
};
// p1 + p2 <=> p1.operator+(p2);
// 5 * p1 <=> operator*(5, p1);
// p = p;
Point& Point::operator= (const Point& p) {
    if (this == &p) {
        return *this;
    }
    this->x = p.x;
    this->y = p.y;
    return *this;
}

Point operator* (const int& x, const Point& p) {
    Point o;
    o.x = x * p.x;
    o.y = x * p.y;
    return o;
}

ostream& operator<<(ostream& out, const Point& p) {
    out << "(" << p.x << "," << p.y << ")";
    return out;
}


istream& operator>>(istream& in, Point& p) {
    in >> p.x >> p.y;
    return in;
}

int main () {
    Point m(1, 6), n(12, 5);
    // Point operator()(int i = 0);
    cout << "Distanta dintre " << m << " si " << n << " este " << m - n << endl;
    // Distanta dintre (1,6) si (12,5) este 11.0454
    cout << "Translatam " << m << " cu 3 " << 3 * m << endl;
    // Translatam (1,6) cu 3 (3,18)
    cout << "Produsul scalar " << m * n << endl;
    // Produsul scalar 42
    return 0;
}


/*
C<int> a;
C<string> b;
*/