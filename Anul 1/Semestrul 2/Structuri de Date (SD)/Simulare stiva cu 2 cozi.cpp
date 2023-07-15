#include <bits/stdc++.h>
using namespace std;

// Idee generala : Cand dorim adaugarea unui element, pur si simplu il punem in Q1. Cand dorim eliminarea unui element,
// mutam toate celelalte elemente din fata sa din Q1 in Q2, ii dam pop si apoi dam swap intre Q1 si Q2. (Q3 utilizat ca si copie a lui Q1 pt afisarea stivei)

void AdaugareElement(queue<int>& Q1,int x)
{
    Q1.push(x);
}

void StergereElement(queue<int>& Q1,queue<int>& Q2)
{
    while (Q1.size()>1)
    {
        Q2.push(Q1.front());
        Q1.pop();
    }
    Q1.pop();
    swap(Q1,Q2);
}

int main()
{
    queue<int>Q1,Q2,Q3;
    int a,x,k=1;
    while (1>0)
    {
        system("cls");
        if (k == 1)
        {
            cout<<"Stiva goala - Nu se pot sterge elemente\n";
            k=0;
        }
        cout<<"Meniu:\n1.Adaugare Element Stiva\n2.Stergere Element Stiva\n3.Terminare program\nStiva actuala : ";
        Q3=Q1;
        while (Q3.size()>0)
                {
                    cout<<Q3.front()<<' ';
                    Q3.pop();
                }
        cout<<endl;
        cin>>a;
        if (a==1)
        {
            cout<<endl<<"Element de adaugat : ";
            cin>>x;
            AdaugareElement(Q1,x);
        }
        else if (a==2)
                {
                    if (Q1.size()>0)
                        StergereElement(Q1,Q2);
                    else
                        k = 1;
                }
        else if (a==3)
            break;

    }
    return 0;
}
