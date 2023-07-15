/*   Ilie Petre-Cristian - Grupa 133
        Eduard Gabriel Szmeteanca
    GNU GCC Compiler - Version 8.1.0 */


#include <bits/stdc++.h>

using namespace std;

struct data{

    int zi;
    int luna;
    int an;

};


class Malware{

private:

    float rat_imp;
    data data_inf;
    string nume;
    string met_inf;
    int nr_reg;
    vector<string> reg_mod;

public:

    Malware()  // Constructorul fara parametrii
    {
        this->rat_imp = 0;
        this->data_inf.an = 0;
        this->data_inf.luna = 0;
        this->data_inf.zi = 0;
        this->nume = "Anonim";
        this->met_inf = "unknown";
        this->nr_reg = 0;
    }

    ~Malware(){}  // Destructor

    Malware(const Malware& m) // Copy constructor
    {
        this->rat_imp = m.rat_imp;
        this->data_inf = m.data_inf;
        this->nume = m.nume;
        this->met_inf = m.met_inf;
        this->reg_mod = m.reg_mod;
        this->nr_reg = m.nr_reg;
    }

    Malware& operator=(const Malware& m) // Supraincarcare Operatorul =
    {
        if (this != &m)
        {
            this->rat_imp = m.rat_imp;
            this->data_inf = m.data_inf;
            this->nume = m.nume;
            this->met_inf = m.met_inf;
            this->reg_mod = m.reg_mod;
            this->nr_reg = m.nr_reg;
        }
        return *this;
    }

    void setImp(int l)
    {
        this->rat_imp += l;
    }

    int getImp()
    {
        return this->rat_imp;
    }

    virtual void CalcImp(); // Functie virtuala

    friend ostream& operator<<(ostream& out,const Malware& a); // Functii friend pentru operatorii >> si <<
    friend istream& operator>>(istream& in,Malware& a); // sunt declarati in exteriorul clasei

};

void Malware::CalcImp()
{
    int imp = 0;
    for (int i=0;i<this->nr_reg;i++)
        if (this->reg_mod[i] == "HKLM-run" || this->reg_mod[i] == "HKCU-run")
            imp+= 20;

    this->setImp(imp);
}

ostream& operator<<(ostream& out,const Malware& a) // Supraincarcare Operator <<
{
    out<<"\nRating impact: "<<a.rat_imp;
    out<<"\nData inf: "<<a.data_inf.zi<<"/"<<a.data_inf.luna<<"/"<<a.data_inf.an;
    out<<"\nNume: "<<a.nume;
    out<<"\nMetoda infectare: "<<a.met_inf;
    out<<"\nNr. registrii: "<<a.nr_reg;
    out<<"\nRegistrii: ";
    for (int i=0;i<a.reg_mod.size();i++)
        out<<a.reg_mod[i]<<' ';

    return out;
}
istream& operator>>(istream& in,Malware& a) // Supraincarcare Operator >>
{
    cout<<"Zi: ";in>>a.data_inf.zi;
    cout<<"Luna: ";in>>a.data_inf.luna;
    cout<<"An: ";in>>a.data_inf.an;
    cout<<"Nume: ";in>>a.nume;
    cout<<"Metoda inf: ";in>>a.met_inf;
    cout<<"Nr registrii: ";in>>a.nr_reg;
    for (int i=0;i<a.nr_reg;i++)
    {
        string reg;
        cout<<"Registru: ";in>>reg;
        a.reg_mod.push_back(reg);
    }

    a.CalcImp();

    return in;
}

class Rootkit : virtual public Malware // Mostenire
{
private:

    vector<string> list_imp;
    vector<string> str_semn;

public:

    Rootkit():Malware(){} // Constructor fara parametrii

    ~Rootkit(){} // Destructor

    friend ostream& operator<<(ostream& out,const Rootkit& c); // Functii friend pentru operatorii >> si <<
    friend istream& operator>>(istream& in,Rootkit& c);

    void CalcImp();

};

void Rootkit::CalcImp()
{
        Malware::CalcImp();
        int imp = 0;
        for (int i=0;i<this->str_semn.size();i++)
        {
            if (this->str_semn[i] == "System Service Descriptor Table")
                imp+= 100;
            if (this->str_semn[i] == "SSDT")
                imp+= 100;
            if (this->str_semn[i] == "NtCreateFile")
                imp+= 100;
        }
        for (int i=0;i<this->list_imp.size();i++)
            if (this->list_imp[i] == "ntoskrnl.exe")
                imp*=2;

        this->setImp(imp);
}

ostream& operator<<(ostream& out,const Rootkit& c) // Supraincarcare Operator <<
{
    out<<(Malware&)c;
    out<<"Importuri: ";
    for (int i=0;i<c.list_imp.size();i++)
        out<<c.list_imp[i]<<' ';
    out<<"\n";
    out<<"Stringuri semnificative: ";
    for (int i=0;i<c.str_semn.size();i++)
        out<<c.str_semn[i]<<' ';

    return out;
}

istream& operator>>(istream& in,Rootkit& c) // Supraincarcare Operator >>
{
    in>>(Malware&)c;
    int nr;
    cout<<"Nr importuri: ";in>>nr;
    cout<<"Importuri: ";
    for (int i=0;i<nr;i++)
    {
        string p;
        in>>p;
        c.list_imp.push_back(p);
    }
    cout<<"Nr. stringuri semnificative: ";
    in>>nr;
    cout<<"Stringuri semnificative: ";
    for (int i=0;i<nr;i++)
    {
        string p;
        in>>p;
        c.str_semn.push_back(p);
    }

    return in;
}

class Keylogger : virtual public Malware // Mostenire
{
    private:

    vector<string> fct_fol;
    vector<string> tas_spec;

    public:

    Keylogger():Malware(){}  // Constructor fara parametrii

    ~Keylogger(){} // Destructor

    void CalcImp();


    friend ostream& operator<<(ostream& out,const Keylogger& c); // Functii friend pentru operatorii << si >>
    friend istream& operator>>(istream& in,Keylogger& c);


};

void Keylogger::CalcImp()
{
    int imp = 0;

    Malware::CalcImp();
    for (int i=0;i<this->fct_fol.size();i++)
    {
        if (this->fct_fol[i]=="[Up]")
            imp+=10;
        if (this->fct_fol[i]=="[Num Lock]")
            imp+=10;
        if (this->fct_fol[i]=="[Down]")
            imp+=10;
        if (this->fct_fol[i]=="[Right]")
            imp+=10;
        if (this->fct_fol[i]=="[UP]")
            imp+=10;
        if (this->fct_fol[i]=="[Left]")
            imp+=10;
        if (this->fct_fol[i]=="[PageDown]")
            imp+=10;
    }
    for (int i=0;i<this->tas_spec.size();i++)
    {
        if (this->tas_spec[i]=="CreateFileW")
            imp+=30;
        if (this->tas_spec[i]=="OpenProcess")
            imp+=30;
        if (this->tas_spec[i]=="ReadFile")
            imp+=30;
        if (this->tas_spec[i]=="WriteFile")
            imp+=30;
        if (this->tas_spec[i]=="RegisterHotKey")
            imp+=30;
        if (this->tas_spec[i]=="SetWindowsHookEx")
            imp+=30;
    }

    this->setImp(imp);
}

ostream& operator<<(ostream& out,const Keylogger& c) // Supraincarcare Operator <<
{
    out<<(Malware&)c;
    out<<"\nFunctii folosite: ";
    for (int i=0;i<c.fct_fol.size();i++)
        out<<c.fct_fol[i]<<' ';
    out<<"\n\n\nTaste speciale: ";
    for (int i=0;i<c.tas_spec.size();i++)
        out<<c.tas_spec[i]<<' ';

    return out;
}


istream& operator>>(istream& in,Keylogger& c) // Supraincarcare Operator >>
{
    in>>(Malware&)c;
    int nr;
    cout<<"Nr. functii folosite: ";in>>nr;
    cout<<"Functiile: ";
    for (int i=0;i<nr;i++)
    {
        string r;
        in>>r;
        c.fct_fol.push_back(r);
    }
    cout<<"Nr. taste speciale: ";
    in>>nr;
    cout<<"Taste speciale: ";
    for (int i=0;i<nr;i++)
    {
        string r;
        in>>r;
        c.tas_spec.push_back(r);
    }

    return in;
}



class KernelKeylogger : public Keylogger, public Rootkit // Mostenire diamant, rezolvata cu virtual deasupra
{

private:

    bool asc_fis;
    bool asc_reg;

public:

    KernelKeylogger():Malware(),Keylogger(),Rootkit(){this->asc_fis = 0; this->asc_reg =0;} // Constructor fara parametrii

    ~KernelKeylogger(){} // Destructor

    void CalcImp();

    friend ostream& operator<<(ostream& out,const KernelKeylogger& c); // Functii friend pentru operatorii << si >>
    friend istream& operator>>(istream& in,KernelKeylogger& c);
};

void KernelKeylogger::CalcImp()
{
    Malware::CalcImp();
    int imp = 0;
    Rootkit::CalcImp();
    Keylogger::CalcImp();
    if (this->asc_fis)
        imp+=20;
    if (this->asc_reg)
        imp+=30;
    this->setImp(imp);
}

ostream& operator<<(ostream& out,const KernelKeylogger& c) // Supraincarcare Operator <<
{
    out<<(Keylogger&)c;
    out<<(Rootkit&)c;
    out<<"\nAscunde fisiere: "<<c.asc_fis;
    out<<"\nAscunde registrii: "<<c.asc_reg;

    return out;
}
istream& operator>>(istream& in,KernelKeylogger& c) // Supraincarcare Operator >>
{
    in>>(Keylogger&)c;
    in>>(Rootkit&)c;
    cout<<"\nAscunde fisiere? (1/0): ";in>>c.asc_fis;
    cout<<"\nAscunde registrii? (1/0): ";in>>c.asc_reg;

    return in;
}


class Ransomware : public Malware // Mostenire (IS-A)
{
    private:

        int rat_crip;
        float rat_obf;

    public:

    Ransomware():Malware(){this->rat_crip = 0; this->rat_obf = 0;}

    ~Ransomware(){}

    void CalcImp();

    friend ostream& operator<<(ostream& out,const Ransomware& c);
    friend istream& operator>>(istream& in,Ransomware& c);

};

void Ransomware::CalcImp()
{
    Malware::CalcImp();
    int imp =0;
    imp += this->rat_crip;
    imp += this->rat_obf;
    this->setImp(imp);
}

ostream& operator<<(ostream& out,const Ransomware& c) // Supraincarcare Operator <<
{
    out<<(Malware&)c;
    out<<"\nRating criptare: "<<c.rat_crip;
    out<<"\nRating obfuscare: "<<c.rat_obf;

    return out;
}

istream& operator>>(istream& in,Ransomware& c) // Supraincarcare Operator >>
{
    in>>(Malware&)c;
    cout<<"\nRating criptare: ";in>>c.rat_crip;
    cout<<"\nRating obfuscare: ";in>>c.rat_obf;

    return in;
}



class Computer
{
private:

    const int id_comp;
    int nr_mal;
    vector<Malware> lis_mal; // Vector ale altei clase (HAS-A)
    int rat_fin;

public:

    static int contor;

    Computer():id_comp(contor++) { // Constructor fara parametrii care actualizeaza si contorul pentru id

        nr_mal = 0;
        rat_fin = 0;

    }

    void CalcRatFin();

    int getrat()
    {
        return this->rat_fin;
    }

    void setrat(int l)
    {
        this->rat_fin = l;
    }

    ~Computer(){} // Destructor

    int getNr();


    friend ostream& operator<<(ostream& out,const Computer& c);
    friend istream& operator>>(istream& in,Computer& c);


};

int Computer::getNr()
{
    return this->nr_mal;
}

void Computer::CalcRatFin()
{
    this->rat_fin = 0;
    for (int i=0;i<nr_mal;i++)
        this->rat_fin += this->lis_mal[i].getImp();
    this->setrat(rat_fin);
}

ostream& operator<<(ostream& out,const Computer& c) // Supraincarcare Operatorul <<
{
    out<<"\nID: "<<c.id_comp;
    out<<"\nRating final: "<<c.rat_fin;
    out<<"\nNr. Malware-uri: "<<c.nr_mal;
    out<<"\nLista malware-uri: \n";
    for (int i=0;i<c.nr_mal;i++)
        out<<c.lis_mal[i]<<"\n\n";

    return out;
}

istream& operator>>(istream& in,Computer& c) // Supraincarcare Operator >>
{
    cout<<"Nr malware-uri: ";
    in>>c.nr_mal;
    for (int i=0;i<c.nr_mal;i++)
    {
        string k;
        cout<<"Tip malware: ";
        in>>k;
        if (k=="Rootkit")
        {
            Rootkit r;
            in>>r;
            c.lis_mal.push_back(r);

        }
        else if (k=="Keylogger")
        {
            Keylogger r;
            in>>r;
            c.lis_mal.push_back(r);

        }
        else if (k=="Ransomware")
        {
            Ransomware r;
            in>>r;
            c.lis_mal.push_back(r);
        }
        else if (k=="Kernel-Keylogger")
        {
            KernelKeylogger r;
            in>>r;
            c.lis_mal.push_back(r);
        }
        else {cout<<"Tip invalid\n"; i--;}
    }

    c.CalcRatFin();

    return in;
}

vector<Computer> Calc; // Vector de calculatoare din STL utilizat la memorarea, citirea si afisarea lor

class Meniu // Singleton, Cod preluat (si adaptat) dupa un exemplu dat de laborant in cadrul laboratorului.
            // Utilizat deoarece in program va exista un singur obiect de tipul clasei Meniu (utilizat pentru meniul interactiv)
{
    private:

        Meniu(){};
        static Meniu* Menu;

    public:

        Meniu(Meniu&) = delete;
        void operator=(const Meniu&) = delete;
        static Meniu* getInstance();
        void afis()
        {
            system("CLS");

            while(1>0)
            {
                cout<<"\n1.Afisare info calculatoare";
                cout<<"\n2.Afisare info calc dupa rating final";
                cout<<"\n3.Afisare primele k calc dupa rating final";
                cout<<"\n4.Afisare procent";
                cout<<"\n5.Citire calculator";
                cout<<"\n6.Iesire";
                int Raspuns;
                cout<<"\n> Comanda: ";
                cin>>Raspuns;

                switch(Raspuns)
                {
                case 1:
                    {for (int i=0;i<Calc.size();i++)
                        cout<<Calc[i]<<"\n\n";
                    break;}

                case 2:
                    break;

                case 3:
                    break;

                case 4:
                    {int k = 0;
                    int nr = Calc.size();
                    for (int i=0;i<Calc.size();i++)
                        if (Calc[i].getNr() > 0)
                            k++;
                    cout<<"Procent: "<<k*100/nr<<"%\n";
                    break;}

                case 5:
                    {Computer c;
                    cin>>c;
                    c.CalcRatFin();
                    Calc.push_back(c);
                    break;}

                case 6:
                    return;
                }

            }
        }
};

Meniu* Meniu::Menu = nullptr;
Meniu* Meniu::getInstance()
{
    if (!Menu)
        Menu = new Meniu();

    return Menu;
}

int Computer::contor = 1;


int main()
{
    Meniu* M = M->getInstance();

    M->afis();
    delete M;
    return 0;
}
