#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include <stack>

using namespace std;

ifstream fin("date.in");
ofstream fout("date.out");

struct tranzitie
{
    int destinatie;
    char litera;
};


struct elcoada
{
    int stare;
    int indice;
    int adancime;
};

stack<int>Drum,Temp;                         // Am realizat cu ajutorul unui stack Drumul (in ordine inversa) pe parcursul programului
                                             // Si am utilizat Temp pentru a rasturna stackul pentru o afisare buna
vector<tranzitie>L[1000];
vector<int>StFin;
vector<int>V[1000];
queue<elcoada>Coada;

elcoada ElementCrt;
string BFS(int S,string Cuv)                // BFS realizat dupa modelul de pseudocod oferit in cadrul celui de-al doilea laborator (cu diferite modificari)
{
    elcoada a;
    a.stare = S;
    a.indice = 0;
    a.adancime = 1;

    while(!Coada.empty())
        Coada.pop();

    Coada.push(a);

    while (!Coada.empty())
    {
        ElementCrt = Coada.front();
        Coada.pop();
        Drum.push(ElementCrt.stare);

        while (ElementCrt.adancime < Drum.size())                 // Acest lucru se intampla in cazul in care am ajuns intr-un punct
                                                                  // in care totii vecinii unui nod nu au dus la verificarea intregului cuvant
                                                                  // iar atunci revenim la adancimea -1 celei curente si cautam
                                                                  // urmatorii vecini ai starii alese anterior, lucru ce necesita
								  // un rollback al stackului
        {
            Drum.pop();
        }

        for (int i=0;i<L[ElementCrt.stare].size();i++)
        {

            if (Cuv[ElementCrt.indice] == L[ElementCrt.stare][i].litera)
            {
                if (ElementCrt.indice == Cuv.size()-1)
                {
                    for (int k=0;k<StFin.size();k++)
                        if (L[ElementCrt.stare][i].destinatie == StFin[k])
                        {
                            Drum.push(StFin[k]);                      // Pentru ultima stare prin care trece
                            return "DA";
                        }
                }
                else
                {
                    elcoada b;
                    b.stare = L[ElementCrt.stare][i].destinatie;
                    b.indice = ElementCrt.indice + 1;
                    b.adancime = ElementCrt.adancime + 1;
                    Coada.push(b);

                }

            }

        }

    }
    return "NU";
}


int main()
{
    tranzitie trn;
    int N,st,M,x,S,nrF,StF,NrCuv,litcrt=0,StCrt,ver,ver2,o;
    string CuvCrt;


    fin>>N;
    for (int i=0;i<N;i++)
        fin>>st;


    fin>>M;
    for (int i=0;i<M;i++)
    {
        fin>>x>>trn.destinatie>>trn.litera;
        L[x].push_back(trn);
    }

    // Punem toate tranzitiile in vectorul L[x] unde x reprezinta Starea din care pleaca tranzitia

    fin>>S>>nrF;
    for (int i=0;i<nrF;i++)
    {
        fin>>StF;
        StFin.push_back(StF);
    }


    fin>>NrCuv;
    for (int r=0;r<NrCuv;r++)
    {
        fin>>CuvCrt;
        fout<<BFS(S,CuvCrt)<<endl;

        while(!Drum.empty())           // Pentru o afisare buna, trebuie inversat stackul
        {
            Temp.push(Drum.top());
            Drum.pop();
        }

        while(!Temp.empty())
        {
            cout<<Temp.top()<<' ';
            Temp.pop();
        }
        cout<<endl;
    }

    fin.close();
    fout.close();

    return 0;
}
