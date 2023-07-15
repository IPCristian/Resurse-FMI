#include <iostream>
#include <string.h>
#include <vector>
using namespace std;

class Decoratiune {

private:

    string nume;
    string culoare;
    bool reciclabila;
    float pretul;

public:

    Decoratiune()
    {
        this->nume = "Anonim";
        this->culoare = "Anonim";
        this->reciclabila = 0;
        this->pretul = 0;
    }

    Decoratiune(string nume,string culoare,bool reciclabila,float pretul)
    {
        this->nume = nume;
        this->culoare = culoare;
        this->reciclabila = reciclabila;
        this->pretul = pretul;
    }

    ~Decoratiune(){}

    Decoratiune& operator = (const Decoratiune& dec)
    {
        this->nume = dec.nume;
        this->culoare = dec.culoare;
        this->reciclabila = dec.reciclabila;
        this->pretul = dec.pretul;
    }

    string getNume()
    {
        return this->nume;
    }

    float pret()
    {
        return this->pretul;
    }

    void reciclabil() // "Sa afle oricand daca o decoratiune este reciclabila"
    {
        if (this->reciclabila == true)
            cout<<"Da";
        else
            cout<<"Nu";
    }

    friend istream& operator>>(istream& in,Decoratiune& dec);
    friend ostream& operator<<(ostream& out,const Decoratiune& dec);
};

istream& operator>>(istream& in,Decoratiune& dec)
{
    cout<<"Denumire: ";
    in>>dec.nume;
    cout<<"Culoare: ";
    in>>dec.culoare;
    cout<<"Reciclabila ? (0/1) : ";
    in>>dec.reciclabila;
    cout<<"Pret : ";
    in>>dec.pretul;
    cout<<endl;

    return in;
}

ostream& operator<<(ostream& out,const Decoratiune& dec)
{
    out<<"Denumire : "<<dec.nume<<endl;
    out<<"Culoare : "<<dec.culoare<<endl;
    out<<"Reciclabila  : ";
    if (dec.reciclabila == true)
        out<<"Da"<<endl;
    else
        out<<"Nu"<<endl;
    out<<"Pret : "<<dec.pretul<<endl;
    out<<endl;

    return out;
}


class ListaProduse {

private:

    vector<Decoratiune> produse;

public:


    ListaProduse(){

        vector <Decoratiune> produse;

    }

    ~ListaProduse()
    {
        if (this->produse.size() != 0)
            this->produse.clear();
    }

    ListaProduse& operator=(const ListaProduse& prod)
    {
        if (this != &prod)
        {
            this->produse = prod.produse;
        }
    }

    ListaProduse operator+(Decoratiune prod)
    {
        ListaProduse aux;
        aux.produse = this->produse;
        aux.produse.push_back(prod);
        return aux;

    }

    Decoratiune& operator[](int index)
    {

        if (0<=index && index<sizeof(this->produse))
        {
            index = index -1; // Ca Produse[1] sa returneze primul element
            return this->produse[index];
        }
    }

    void remove(int index)
    {
        index = index - 1; // Ca remove(1) sa stearga primul element
        this->produse.erase(this->produse.begin() + index - 1);
    }

    float pret()
    {
        float prettotal = 0;
        for (int i=0;i<this->produse.size();i++)
            prettotal += this->produse[i].pret();
        return prettotal;
    }

    void numedecoratiuni()
    {
        for (int i=0;i<sizeof(this->produse);i++)
            cout<<this->produse[i].getNume()<<' ';
    }

};



int main()
{
    Decoratiune a,c;
    ListaProduse b;
    cin>>a>>c;
    cout<<a.pret()<<endl;
    b = b + a;
    b = b + c;
    cout<<b[1]<<endl;
    cout<<b[2].pret()<<endl;
    cout<<b.pret()<<endl;
    b.remove(2);
    cout<<b.pret();
    return 0;
}
