#include <iostream>
#include <string.h>
#include <vector>
#include <fstream>

using namespace std;

ofstream fout("date.out");

class Vaccin{

private:

    float pret;
    int temp_dep;
    string substante;

public:

    Vaccin(){

        this->pret = 0;
        this->temp_dep = 0;
        this->substante = "Anonim";

    }

    Vaccin(float pret,int temp,string subst)
    {
        this->pret = pret;
        this->temp_dep = temp;
        this->substante = subst;
    }

    ~Vaccin(){}

    friend istream& operator>>(istream& in,Vaccin& v);
    friend ostream& operator<<(ostream& out,const Vaccin& v);

    virtual void afisareSchemaVaccinare() = 0;

};

istream& operator>>(istream& in,Vaccin& v)
{
    cout<<"\nPret Vaccin: ";
    in>>v.pret;
    cout<<"\nTemperatura de depozitare: ";
    in>>v.temp_dep;
    cout<<"\nSubstantele continute: ";
    in>>v.substante;

    return in;
}

ostream& operator<<(ostream& out,const Vaccin& v)
{
    out<<"\nPret Vaccin: "<<v.pret;
    out<<"\nTemperatura de depozitare: "<<v.temp_dep;
    out<<"\nSubstantele continute: "<<v.substante;

    return out;
}

class VaccinAntigripal:public Vaccin{

private:

    string tulpini;
    bool recomandari;

public:

    VaccinAntigripal():Vaccin(){

        this->tulpini = "Anonim";
        this->recomandari = false;

    }

    VaccinAntigripal(float pret, int temp, string subst,string tulpini,bool recomandari):Vaccin(pret,temp,subst)
    {
        this->tulpini = tulpini;
        this->recomandari = recomandari;
    }

    ~VaccinAntigripal(){}

    friend istream& operator>>(istream& in,VaccinAntigripal& v);
    friend ostream& operator<<(ostream& out,const VaccinAntigripal& v);

    void afisareSchemaVaccinare()
    {
        cout<<"\n\nLa adulti se administreaza o doza de 0.5 ml, iar la copii si adolescenti o doza de 0.3 ml, repetandu-se din 2 in 2 ani";
    }


};

istream& operator>>(istream& in,VaccinAntigripal& v)
{
    in>>(Vaccin&) v;
    cout<<"\nAsupra caror tulpini actioneaza: ";
    in>>v.tulpini;
    cout<<"\nRespecta recomandarile Organizatiei Mondiale a Sanatatii? (0/1): ";
    in>>v.recomandari;

    return in;
}
ostream& operator<<(ostream& out,const VaccinAntigripal& v)
{
    out<<(Vaccin&) v;
    out<<"\nAsupra caror tulpini actioneaza: "<<v.tulpini;
    out<<"\nRespecta recomandarile Organizatiei Mondiale a Sanatatii? (0/1): "<<v.recomandari;
    out<<"\n";
    return out;
}

class VaccinAntihepatic:public Vaccin{

private:

    char tip;
    string mod_vac;

public:

    VaccinAntihepatic():Vaccin(){

        this->tip = '0';
        this->mod_vac = "Anonim";

    }

    VaccinAntihepatic(float pret, int temp, string subst,char tip, string mod_vac):Vaccin(pret,temp,subst)
    {
        this->tip = tip;
        this->mod_vac = mod_vac;
    }

    ~VaccinAntihepatic(){}

    friend istream& operator>>(istream& in,VaccinAntihepatic& v);
    friend ostream& operator<<(ostream& out,const VaccinAntihepatic& v);

    void afisareSchemaVaccinare()
    {
        if (this->tip == 'C')
        {
            cout<<"\n\nDoar la recomandarea doctorului";
        }

        else
            cout<<"\n\nLa copii cu varsta mai mica de 1 an se administreaza 2 injectari la un interval de o luna, a treia injectare dupa 6 luni de la prima administrare, la adulti conform schemei de imunizare recomandata de medic";
    }


};

istream& operator>>(istream& in,VaccinAntihepatic& v)
{
    in>>(Vaccin&) v;
    cout<<"\nTip Hepatita: ";
    in>>v.tip;
    cout<<"\nModul de vaccinare: ";
    in>>v.mod_vac;

    return in;
}
ostream& operator<<(ostream& out,const VaccinAntihepatic& v)
{
    out<<(Vaccin&) v;
    out<<"\nTip Hepatita: "<<v.tip;
    out<<"\nModul de vaccinare: "<<v.mod_vac;
    out<<"\n";
    return out;
}

class VaccinAntiSarsCov2:public Vaccin{

private:

    string reac_adv;
    float efic;
    string med_contraind;

public:

    VaccinAntiSarsCov2():Vaccin()
    {
        this->reac_adv = "Anonim";
        this->efic = 0;
        this->med_contraind = "Anonim";
    }

    VaccinAntiSarsCov2(float pret, int temp, string subst,string reac,float efic,string med):Vaccin(pret,temp,subst)
    {
        this->reac_adv = reac;
        this->efic = efic;
        this->med_contraind = med;
    }

    ~VaccinAntiSarsCov2(){}

    friend istream& operator>>(istream& in,VaccinAntiSarsCov2& v);
    friend ostream& operator<<(ostream& out,const VaccinAntiSarsCov2& v);

    void afisareSchemaVaccinare()
    {
        cout<<"\n\nSe administreaza persoanelor cu varsta de peste 16 ani, 2 doze la o perioada de 21 zile";
    }

};

istream& operator>>(istream& in,VaccinAntiSarsCov2& v)
{
    in>>(Vaccin&) v;
    cout<<"\nReactii adverse administrarii: ";
    in>>v.reac_adv;
    cout<<"\nEficienta: ";
    in>>v.efic;
    cout<<"\nMedicamente contraindicate: ";
    in>>v.med_contraind;

    return in;
}
ostream& operator<<(ostream& out,const VaccinAntiSarsCov2& v)
{
    out<<(Vaccin&) v;
    out<<"\nReactii adverse administrarii: "<<v.reac_adv;
    out<<"\nEficienta: "<<v.efic;
    out<<"\nMedicamente contraindicate: "<<v.med_contraind;
    out<<"\n";
    return out;
}

class Comanda{

private:

    const int id_comanda;
    string data;
    string nume;
    string vaccin;
    int cant;

public:

    static int contor;

    Comanda():id_comanda(contor++)
    {
        this->data = "00-00-0000";
        this->nume = "Anonim";
        this->vaccin = "Anonim";
        this->cant = 0;
    }

    Comanda(string data,string nume,string vaccin,int cant):id_comanda(contor++)
    {
        this->data = data;
        this->nume = nume;
        this->vaccin = vaccin;
        this->cant = cant;
    }

    ~Comanda(){}

    Comanda& operator=(const Comanda& c)
    {
        if (this != &c)
        {
            this->data = c.data;
            this->nume = c.nume;
            this->vaccin = c.vaccin;
            this->cant = c.cant;
        }
    }

    friend istream& operator>>(istream& in,Comanda& c);
    friend ostream& operator<<(ostream& out,const Comanda& c);

};

istream& operator>>(istream& in,Comanda& c)
{
    cout<<"\nData comanda: ";
    in>>c.data;
    cout<<"\nDenumire client: ";
    in>>c.nume;
    cout<<"\nTip Vaccin: ";
    in>>c.vaccin;
    cout<<"\nCantitate: ";
    in>>c.cant;

    return in;
}
ostream& operator<<(ostream& out,const Comanda& c)
{
    out<<"\nData comanda: "<<c.data;
    out<<"\nDenumire client: "<<c.nume;
    out<<"\nTip Vaccin: "<<c.vaccin;
    out<<"\nCantitate: "<<c.cant;

    return out;
}

class ListaComenzi{

private:

    vector<Comanda> Vec;

public:

    ListaComenzi(){}

    ~ListaComenzi(){

    if (!this->Vec.empty())
        this->Vec.clear();
    }

    ListaComenzi& operator=(const ListaComenzi& l)
    {

        if (this != &l)
        {
            this->Vec = l.Vec;
        }

        return *this;
    }

    ListaComenzi& operator+(const Comanda& c)
    {
        this->Vec.push_back(c);

        return *this;
    }

    Comanda& operator[](int index)
    {
        return this->Vec[index];
    }

 /*   void Afis()
    {
        for (auto i=this->Vec.begin();i!=this->Vec.end();i++)
            cout<<this->Vec[i]<<"\n";
    } */

};


int Comanda::contor = 100;

int main()
{
    /*VaccinAntigripal a;
    VaccinAntihepatic b;
    VaccinAntiSarsCov2 c;

    cin>>a>>b>>c;
    cout<<a<<b<<c;

    Vaccin *list[3];

    list[0] = new VaccinAntigripal();
    list[1] = new VaccinAntihepatic();
    list[2] = new VaccinAntiSarsCov2();

    for (int i=0;i<3;i++)
        list[i]->afisareSchemaVaccinare();

    Comanda com1("20-11-2020","SpitalX","AntiSarsCov2",20);

    ListaComenzi lista;

    lista = lista + com1;

    cout<<lista[0];*/

    vector<Vaccin*> list;
    ListaComenzi lista;

    while (1>0)
    {
        cout<<"\n1.Adaugare vaccin nou\n2.Afisare tuturor vaccinelor pe care le detine\n3.Numele producatorilor pentru toate vaccinurile\n4.Adaugarea unei comenzi\n5.Afisarea tuturor comenzilor\n6.Valorea comenzilor dintr-o anumita zi\n7.Afisarea schemei de vaccinare pentru un anumit tip de vaccin\n8.Iesire\n\n";
        int k;
        cin>>k;
        if (k == 1)
        {
            string vac;

            cout<<"\nTip vaccin: ";
            cin>>vac;
            if (vac.compare("Antigripal") == 0)
                {VaccinAntigripal vac2; cin>>vac2;list.push_back(&vac2);}
            else if (vac.compare("Antihepatic") == 0)
                {VaccinAntihepatic vac2; cin>>vac2;list.push_back(&vac2);}

            else {VaccinAntiSarsCov2 vac2; cin>>vac2;list.push_back(&vac2);}

            k = -1;
        }
 /*       else if (k == 2)
        {
            for (auto i=list.begin();i != list.end(); i++)
                cout<<list[i]<<"\n";
        } */

        else if (k == 4)
        {
            Comanda com;
            cin>>com;
            lista = lista + com;
        }
/*        else if (k == 5)
        {
            lista.Afis();
        }

        else if (k == 6)
        {

        }
*/
        else if (k == 7)
        {
            string vac;

            cout<<"\nTip vaccin: ";
            cin>>vac;
            if (vac.compare("Antigripal") == 0)
                {VaccinAntigripal vac2; vac2.afisareSchemaVaccinare();}
            else if (vac.compare("Antihepatic") == 0)
                {VaccinAntihepatic vac2; vac2.afisareSchemaVaccinare();}

            else {VaccinAntiSarsCov2 vac2; vac2.afisareSchemaVaccinare();}
        }

        else if (k == 8)
            break;
    }

    fout.close();
    return 0;
}
