#include <bits/stdc++.h>

using namespace std;


ifstream fin("abce.in");
ofstream fout("abce.out");

int NrNod; // Nr noduri in Lista 0 (cea de jos)
int height=0; // Nr liste curent

struct Nod
{
    int Val;
    Nod* Dr; // Elementul din dreapta pe lista  curenta
    Nod* Jos; // Pozitia elementului curent in lista urmatoare
};

vector<Nod*> Roots; // Toate root-urile
Nod* Temp = NULL; // Pt legaturile dintre liste

int Random() // Dam cu banul pana ce pica pajura (0) ca sa
              // alegem pe cate liste punem elementul
{
    float flip = 1, height_return = 0;
    while (flip && height_return <= height)
    {
        flip = (float) rand()/RAND_MAX;
        flip = int(flip*10);
        if (flip >= 5)
        {
            flip = 1;
            if (height_return < height)
                height_return++;
        }
        else flip = 0;
    }
    return height_return;
}

int Random2() // Acelasi lucru dar doar cand creeam o noua lista
{
    float flip = (float) rand()/RAND_MAX;
    flip = int(flip*10);
    if (flip >= 5)
        return 1;
    else return 0;
}

void Inserare(int Valoare,Nod* Root,int Nivel) // Valoarea pe care dorim sa o adaugam, Nodul curent la care ne uitam, Nivelul la care dorim sa adaugam valoarea
{
    if (Nivel >= 0)
    {

        if (Root->Dr != NULL && Root->Dr->Val < Valoare)
            return Inserare(Valoare,Root->Dr,Nivel);

        else if (Nivel == 0)
        {
            Nod* Nou;
            Nou = new Nod;
            Nou->Val = Valoare;
            Nou->Jos = NULL;

            if (Temp != NULL)
                Temp->Jos = Nou;

            if (Root->Dr == NULL)
            {
                Root->Dr = Nou;
                Nou->Dr = NULL;
            }
            else
            {
                Nou->Dr = Root->Dr;
                Root->Dr = Nou;
            }
        }
        else
        {
            Nod* Nou;
            Nou = new Nod;
            Nou->Val = Valoare;
            if (Temp != NULL)
                    Temp->Jos = Nou;
            Temp = Nou;

            if (Root->Dr == NULL)
            {
                Root->Dr = Nou;
                Nou->Dr = NULL;

                Inserare(Valoare,Roots[Nivel-1],Nivel-1);

            }
            else
            {
                Nou->Dr = Root->Dr;
                Root->Dr = Nou;

                Inserare(Valoare,Roots[Nivel-1],Nivel-1);
            }


        }

    }

    Temp = NULL;

}

void Stergere(int Valoare,Nod* Root)
{
    if (Root->Jos != NULL)
        Stergere(Valoare,Root->Jos);

    while (Root->Dr !=NULL && Root->Dr->Val < Valoare)
        Root = Root->Dr;

    if (Root->Dr != NULL && Root->Dr->Val == Valoare)
    {
        if (Root->Dr->Dr != NULL)
            Root->Dr = Root->Dr->Dr;
        else
            Root->Dr = NULL;
    }
}

bool Cautare(int Valoare,Nod* Root)
{
    while (Root->Dr !=NULL && Root->Dr->Val < Valoare)
        Root = Root->Dr;

    if (Root->Dr != NULL && Root->Dr->Val == Valoare)
        return 1;

    if (Root->Jos == NULL)
        return 0;

    Cautare(Valoare,Root->Jos);
}

Nod* Cautare2(int Valoare,Nod* Root)
{
    while (Root->Dr !=NULL && Root->Dr->Val < Valoare)
        Root = Root->Dr;

    if (Root->Dr != NULL && Root->Dr->Val == Valoare && Root->Jos == NULL)
        return Root;

    if (Root->Jos != NULL)
        return Cautare2(Valoare,Root->Jos);

    return NULL;
}

int Predecesor(int Valoare,Nod* Root)
{
    //cout<<"\nCaut predecesorul lui: "<<Valoare;
    Nod* Caut;

    if (Cautare(Valoare,Roots[height]) == 0)
    {
        Inserare(Valoare,Roots[height],height);
        Caut = Cautare2(Valoare,Root);
        Stergere(Valoare,Root);
    }
    else
    {
        Caut = Cautare2(Valoare,Root);
        return Caut->Dr->Val;
    }
    return Caut->Val;
}

int Succesor(int Valoare,Nod* Root)
{
    //cout<<"\nCaut succesorul lui: "<<Valore;
    Nod* Caut;
    if (Cautare(Valoare,Roots[height]) == 0)
    {
        Inserare(Valoare,Roots[height],height);
        Caut = Cautare2(Valoare,Root);
        Stergere(Valoare,Root);
    }
    else
    {
        Caut = Cautare2(Valoare,Root);
        return Caut->Dr->Val;
    }

    if (Caut->Dr != NULL)
        return Caut->Dr->Val;
    else return -1;
}

void Afisare(int x,int y,Nod* Root)
{
    Nod* Prim;

    if (Cautare(x,Roots[height]) == 0)
    {
        Inserare(x,Roots[height],height);
        Prim = Cautare2(x,Root);
        Stergere(x,Root);
    }
    else
        Prim = Cautare2(x,Root);

    while (Prim->Dr != NULL && Prim->Dr->Val <= y)
    {
        fout<<Prim->Dr->Val<<' ';
        Prim = Prim->Dr;
    }
}

void Afisare2(int x,int y,Nod* Root)
{
    Nod* Prim;

    if (Cautare(x,Roots[height]) == 0)
    {
        Inserare(x,Roots[height],height);
        Prim = Cautare2(x,Root);
        Stergere(x,Root);
    }
    else
        Prim = Cautare2(x,Root);

    while (Prim->Dr != NULL && Prim->Dr->Val <= y)
    {
        cout<<Prim->Dr->Val<<' ';
        Prim = Prim->Dr;
    }
}

void Update()
{
    if (int(sqrt(NrNod)) > height+1)
    {
        Nod* RootNou;
        RootNou = new Nod;
        RootNou->Val = 0;
        RootNou->Dr = NULL;
        RootNou->Jos = Roots[height];
        Roots.push_back(RootNou);
        height++;

        Nod* RootPrec;
        RootPrec = Roots[height-1];

        int ban;
        srand(time(NULL));
        while (RootPrec->Dr != NULL)
        {
            ban = Random2();

            if (ban == 1)
            {
                Inserare(RootPrec->Dr->Val,Roots[height],height);
                Stergere(RootPrec->Dr->Val,Roots[height-1]);
            }

            RootPrec = RootPrec->Dr;
        }
    }
}

void Fisier()
    {
            int n;
    fin>>n;
    for (int i=0;i<n;i++)
    {
        int Raspuns,x,y;
        fin>>Raspuns;
        Update();

        /*for (int i=Roots.size()-1;i>=0;i--)
        {
            cout<<endl;
            Nod* Root;
            Root = Roots[i];

            while (Root->Dr != NULL)
            {
                cout<<Root->Dr->Val<<' ';
                Root = Root->Dr;
            }

        }

    cout<<"\n\n";*/

        switch(Raspuns)
        {

            case 1:
            {
                NrNod++;
                fin>>x;
                int H = Random();
                Inserare(x,Roots[H],H);
                break;

            }

            case 2:
            {
                NrNod--;
                fin>>x;
                Stergere(x,Roots[height]);
                break;

            }

            case 3:
            {
                fin>>x;
                fout<<Cautare(x,Roots[height])<<"\n";
                break;
            }

            case 4:
            {
                fin>>x;
                fout<<Predecesor(x,Roots[height])<<"\n";
                break;
            }

            case 5:
            {
                fin>>x;
                fout<<Succesor(x,Roots[height])<<"\n";
                break;
            }

            case 6:
            {
                fin>>x>>y;
                Afisare(x,y,Roots[height]);
                fout<<"\n";
                break;
            }

        }
    }

    }

void Tastatura()
{
    while (1>0)
    {

        system("CLS");
        jump2:
        Update();
        cout<<"  ____________________\n";
        cout<<" |   Meniu SkipList  |\n";
        cout<<" |-------------------|\n";
        cout<<" |  (1) Afisare      |\n";
        cout<<" |-------------------|\n";
        cout<<" |  (2) Adaugare     |\n";
        cout<<" |-------------------|\n";
        cout<<" |  (3) Stergere     |\n";
        cout<<" |-------------------|\n";
        cout<<" |  (4) Predecesor   |\n";
        cout<<" |-------------------|\n";
        cout<<" |   (5) Succesor    |\n";
        cout<<" |-------------------|\n";
        cout<<" |   (6) Interval    |\n";
        cout<<" |-------------------|\n";
        cout<<" |    (7) Iesire     |\n";
        cout<<" |___________________|\n";

        int Raspuns;
        cout<<"\n> Comanda: ";cin>>Raspuns;

        switch(Raspuns)
        {
            case 1:
                {

                    for (int i=Roots.size()-1;i>=0;i--)
                    {
                        cout<<endl;
                        Nod* Root;
                        Root = Roots[i];

                        while (Root->Dr != NULL)
                        {
                            cout<<Root->Dr->Val<<' ';
                            Root = Root->Dr;
                        }
                        cout<<endl;

                    }
                    goto jump2;

                }
            case 2:
                {
                    NrNod++;
                    int x;
                    cout<<"\n> Nr. de adaugat: ";cin>>x;
                    int H = Random();
                    Inserare(x,Roots[H],H);
                    cout<<"\n> "<<x<<" a fost adaugat cu succes\n";
                    goto jump2;
                }
            case 3:
                {
                    NrNod--;
                    int x;
                    cout<<"\n> Nr. de sters: ";cin>>x;
                    Stergere(x,Roots[height]);
                    cout<<"\n "<<x<<" a fost sters cu succes\n";
                    goto jump2;
                }
            case 4:
                {
                    int x;
                    cout<<"\n> Nr. caruia ii cautam predecesorul: ";cin>>x;
                    cout<<"\n> Predecesorul cautat este: "<<Predecesor(x,Roots[height])<<"\n";
                    goto jump2;
                }
            case 5:
                {
                    int x;
                    cout<<"\n> Nr. caruia ii cautam succesorul: ";cin>>x;
                    cout<<"\n> Succesorul cautat este: "<<Succesor(x,Roots[height])<<"\n";
                    goto jump2;
                }
            case 6:
                {
                    int x,y;
                    cout<<"\n> Limita inferioara: ";cin>>x;
                    cout<<"\n> Limita superioara: ";cin>>y;
                    cout<<"\n> Interval cerut: ";Afisare2(x,y,Roots[height]);
                    cout<<"\n";
                    goto jump2;
                }
            case 7:
             goto jump;
        }
    }
    jump:
        return;
}

int main()
{

    Nod* Root;
    Root = new Nod;
    Root->Val = 0;
    Root->Dr = NULL;
    Root->Jos = NULL;
    Roots.push_back(Root);

    bool Tip;
    cout<<"> Afisare din fisier: 1";
    cout<<"\n> Afisare de la tastatura: 0";
    cout<<"\n\n> Comanda: ";cin>>Tip;

    if (Tip == 1)
        Fisier();
    else Tastatura();

    fin.close();
    fout.close();
    return 0;
}
