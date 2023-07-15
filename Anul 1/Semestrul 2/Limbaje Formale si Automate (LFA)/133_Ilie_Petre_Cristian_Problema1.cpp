#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

ifstream fin("date.in");
ofstream fout("date.out");

struct tranzitie
{
    int destinatie;
    char litera;
};

vector<tranzitie>L[1000];
vector<int>StFin;

int main()
{
    tranzitie trn;
    int N,st,M,x,S,nrF,StF,NrCuv,litcrt=0,StCrt,ver,ver2;
    string CuvCrt;


    fin>>N;
    for (int i=0;i<N;i++)
        fin>>st;

    // Scapam de denumirea starilor deoarece nu o utilizam

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
    for (int i=0;i<NrCuv;i++)
    {
        fin>>CuvCrt;
        ver = 0;
        litcrt = 0;        // La fiecare cuvant initializam verificarea intregului cuvant cu 0, litera curenta la 0 si starea curenta la S (din date.in)
        StCrt = S;


        while (litcrt < CuvCrt.size())
        {
            ver2 = 0;
            for (int j=0;j<L[StCrt].size();j++)
            {
                if (L[StCrt][j].litera == CuvCrt[litcrt])             // Cautam o tranzitie care incepe din StCrt si pleaca cu litcrt a sirului CuvCrt
                    {
                        ver2 = 1;
                        StCrt = L[StCrt][j].destinatie;               // Daca o gasim, ver2 devine 1 pentru a putea trece la urmatoarea litera iar starea curenta devine destinatia tranzitiei utilizate
                    }
            }
            if (ver2 == 1)
            {
                if (litcrt == CuvCrt.size()-1)                        // Daca litcrt a ajuns la finalul cuvantului si var2 este tot 1 inseamna ca am parcurs intreg cuvantul si verificam daca starea curenta este finala. In caz afirmativ ver devine 1
                {
                    for (int k=0;k<StFin.size();k++)
                        if (StCrt == StFin[k])
                            ver = 1;
                }

                litcrt++;
            }
            else
                break;
        }


        if (ver == 1)                                                 // Daca la final ver este 1 inseamna ca am parcurs intreg cuvantul si a fost acceptat de catre DFA
            fout<<"DA\n";
        else
            fout<<"NU\n";

 }
    fin.close();
    fout.close();

    return 0;
}
