#include <bits/stdc++.h>
using namespace std;

ifstream fin("nfa.in");

// NFA -> DFA

vector<int> NFA[100][100];       // Tabel tranzitii NFA
int DFA[100][100];               // Tabel tranzitii DFA
vector<int> StDFA[100];          // Starile DFA-ului (Nr. ordine si vector al starilor originale din care e compus)
int NrSt;
queue<int> q;
int n,m;
set<int>StFin;

bool AmGasitNULL = 0;            // In cazul in care atunci cand transformam din NFA in DFA, o stare nu merge
                                 // in toate literele din limbaj

// Minimizare

int DFA2FIN[100];                // Stocam starile finale noi (Dupa transformare)
vector<vector<int>> Prev;        // Cream 2 vectori de vectori pentru a putea compara
vector<vector<int>> Curr;        // clasa de echivalenta curenta cu cea din urma


void AfisareDFA() {

        cout<<endl<<"Afisare DFA Transformat din NFA"<<endl<<endl;

		for (int i=0; i<NrSt;i++)
        {
            cout<<"------------------------"<<endl<<endl;
            cout<<"Starea: ";
            int ok = 0;
            for (int k=0;k<StDFA[i].size();k++)
            {
                cout<<StDFA[i][k];
                if (StFin.find(StDFA[i][k]) != StFin.end())
                    ok = 1;
            }
            cout<<" ("<<i<<")"<<endl<<endl;
            for (int j=0;j<m;j++)
            {
                cout<<"Litera: "<<j<<" Destinatie: ";
                for (int k=0; k<StDFA[DFA[i][j]].size(); k++)
                    cout<<StDFA[DFA[i][j]][k];
                cout<<endl;
            }
            cout<<endl;
            if (ok == 1)
            {
                cout<<"Starea curenta este si finala"<<endl<<endl;
                DFA2FIN[i] = 1;                                     // Am integrat in afisarea DFA-ului dupa transformare
                                                                    // si marcarea Starilor finale ale acestuia,
                                                                    // pt a folosi la minimizare
            }

        }
        cout<<"--------------------------"<<endl;
}

int SetCrt(int x)  // Caut in care set de stari se afla x si returnez indexul acelui set
{
    for (int i=0;i<Prev.size();i++) // Iterare pe set
        for (int j=0;j<Prev[i].size();j++) // Iterare pe element din set
            if (Prev[i][j] == x)
                return i;
}

bool Afisat[100];

void AfisareDFA_Minimizat()
{

    cout<<endl<<" Afisare DFA Minimizat "<<endl<<endl;
    cout<<"--------------------------"<<endl;

    for (int i=0;i<n;i++)
    {
        if (Afisat[i] == 0)
        {
            cout<<"Starea: ";
            int index = SetCrt(i);
            for(int k=0; k<Prev[index].size(); k++)
            {
                cout << Prev[index][k];
                Afisat[Prev[index][k]] = 1; // Initial gresit
            }
            cout<<endl<<endl;

            for (int j=0;j<m;j++)
            {
                cout<<"Litera: "<<j<<" Destinatia: ";
                int index = SetCrt(DFA[i][j]);
                for (int k=0;k<Prev[index].size();k++)
                    cout<<Prev[index][k];

                cout<<endl<<endl;
            }


            cout<<endl;
            cout<<"--------------------------"<<endl;
        }
    }

}

int main()
{
    int nrtrn,StCrt,NrStFin,StareFinala;

    fin>>n>>m;  // Nr stari n si nr litere ale limbajului m

    for (int i=0;i<n;i++)
        for (int j=0;j<m;j++)
            {
                fin>>nrtrn;
                NFA[i][j].resize(nrtrn);  // Ii modific marimea lui NFA[i][j] pentru a fi egal
                                          // cu nr de tranzitii ce pleaca din starea i cu simbolul j
            }

    for (int i=0;i<n;i++)
        for (int j=0;j<m;j++)
            for(int k=0;k<NFA[i][j].size();k++)
                fin>>NFA[i][j][k];  // Citesc propriu zis tranzitiile (De la i la k cu simbolul j)

    fin>>NrStFin;
    for (int i=0;i<NrStFin;i++)
    {
        fin>>StareFinala;
        StFin.insert(StareFinala);
    }

    // NFA -> DFA

    q.push(0);  // Similar cu tema anterioara, adaugam starea initiala in coada
    vector<int> v; v.push_back(0);
    StDFA[NrSt] = v; // La inceput prima stare din DFA va fi vectorul format din starea initiala
    NrSt++;

    while (!q.empty())
    {
        StCrt = q.front();
        q.pop();

        for (int j=0;j<m;j++)
        {
            vector<int> ConstrSt; // Construiesc starea curenta

            for (int i=0;i<StDFA[StCrt].size();i++)
                for (int k=0;k<NFA[StDFA[StCrt][i]][j].size();k++)
                    ConstrSt.push_back(NFA[StDFA[StCrt][i]][j][k]);  // Pt fiecare litera din limbaj, ma uit ce tranzitii
                                                                     // pornesc din Starile ce alcatuiesc vectorul curent
                                                                     // (NFA[StDFA[StCrt]) si apoi adaug destinatiile la
                                                                     // vectorul pe care-l construiesc

            sort(ConstrSt.begin(),ConstrSt.end()); // Rearanjez noul vector
            ConstrSt.resize(unique(ConstrSt.begin(),ConstrSt.end())-ConstrSt.begin()); // Scoatem dublurile de stari iar apoi
                                                                                       // modificam  sa scapam de spatiile
                                                                                       // in plus lasate de Unique
            int ok = -1;
            for (int i=0;i<NrSt;i++)  // Verificam daca aceasta stare compusa am mai intalnit-o
                if (StDFA[i] == ConstrSt)
                {
                    ok = i;
                    break;
                }

            if (ok == -1)  // Daca nu, o adaugam atat in vectorul de stari al noului dfa cat si in coada
                                                 // Obs: in coada se adauga cea mai noua stare, nu starea compusa
            {
                if (ConstrSt.size() == 0)
                    AmGasitNULL = 1;

                StDFA[NrSt] = ConstrSt;
                q.push(NrSt);
                DFA[StCrt][j] = NrSt;
                NrSt++;
            }
            else
            {
                DFA[StCrt][j] = ok;  // Daca deja exista, doar o adaug la tabelul DFA-ului
            }

        }
    }

    if (AmGasitNULL) // Caz netratat original -> duce la situatii
                     // unde este pusa o linie in plus cu o stare ce nu exista
    {
        NrSt--;
    }

    AfisareDFA();

    //Minimizarea DFA

    n = NrSt;

    vector<int> Cls[2];  // Facem clasa 1 de echivalenta in care plasam in Cls[0] starile nefinale si in Cls[1] pe cele finale

    for (int i=0;i<n;i++)
        Cls[DFA2FIN[i]].push_back(i);

    Curr.push_back(Cls[0]);
    Curr.push_back(Cls[1]);

    while (Curr != Prev)
    {
        Prev = Curr;
        for (int i=0;i<Curr.size();i++) // Iterare set
        {
            for (int j=1;j<Curr[i].size();j++) // Iterare element din set
            {
                int Aranjat = 0;
                for (int k=0;k<j;k++) // Vad daca elementele din setul i, dinaintea lui j
                                      // se vor afla in noua clasa de echivalenta in
                                      // acelasi set cu acesta
                {
                    int InAcelasiSet = 1;

                    for (int l=0;l<m;l++)  // Verific daca tranzitiile din j vor ajunge in acelasi
                                           // seturi de stari cu tranzitiile din k
                        if (SetCrt(DFA[Curr[i][j]][l]) != SetCrt(DFA[Curr[i][k]][l]))
                        {
                            InAcelasiSet = 0;
                            break;
                        }

                    if (InAcelasiSet == 1)  // Daca toate literele erau in aceleasi seturi,
                                           // atunci starea nu trebuie mutata in alt set
                    {
                        Aranjat = 1;
                        break;
                    }

                }

                if (Aranjat == 1) // Daca am terminat cu starea aceasta, trec mai departe
                    continue;

                for (int k=Prev.size();k<Curr.size();k++)  // Daca nu s-a putut pastra in acelasi set,
                                                           // se compara cu elemente din celelalte seturi nou create
                    for (int l=0;l<Curr[k].size();k++)
                    {
                        int InAcelasiSet = 1;

                        for (int p=0;p<m;p++)
                            if (SetCrt(DFA[Curr[i][j]][p]) != SetCrt(DFA[Curr[k][l]][p])) // Compar elementul din setul i cu element din setul k
                            {
                                InAcelasiSet = 0;
                                break;
                            }

                        if (InAcelasiSet == 1) // Daca toate comparatiile au iesit egale
                                               // atunci il mutam in setul k si il stergem din i
                        {
                            Curr[k].push_back(Curr[i][j]);
                            Curr[i].erase(Curr[i].begin()+j);
                            Aranjat = 1;
                            break;
                        }


                    }

                    if (Aranjat == 1)  // Daca am terminat de mutat, trec la urmatoarea stare
                        continue;

                    // Ultimul caz este cel in care elementul nu poate ramane in setul curent
                    // dar nu poate fi nici mutat in vreunul din cele create deja

                    // In acest caz, creez un nou set format doar din el si il sterg din setul vechi

                    vector<int> v2;
                    v2.push_back(Curr[i][j]);

                    Curr.push_back(v2);
                    Curr[i].erase(Curr[i].begin()+j);
            }

        }

        // Dupa ce am plasat toate elementele, sortez vectorii
        // ca atunci cand revine la conditia initiala Prev != Curr
        // sa se opreasca in momentul in care 2 clase de echivalenta
        // consecutive sunt egale

        for (int i=0;i<Prev.size();i++)
            sort(Prev[i].begin(),Prev[i].end());

        for (int i=0;i<Curr.size();i++)
            sort(Curr[i].begin(),Curr[i].end());

        sort (Prev.begin(),Prev.end());
        sort (Curr.begin(),Curr.end());
    }

    AfisareDFA_Minimizat();

    fin.close();
    return 0;
}

