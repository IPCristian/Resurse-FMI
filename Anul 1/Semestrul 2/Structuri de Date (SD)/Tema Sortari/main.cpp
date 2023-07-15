#include <iostream>
#include <fstream>
#include <cstdlib>
#include <time.h>
#include <windows.h>
#include <algorithm>
using namespace std;
ifstream fin("test.txt");



// Portiune bubblesort

void BubbleSort(int v[],int nrelem)
{
    int i,k;
    do{
        k = 0;
        for (i=0;i<=nrelem-1;i++)
            if (v[i] > v[i+1])
                {
                    swap(v[i],v[i+1]);
                    k = 1;
                }

    }while(k == 1);
}

// Portiune countsort

void CountSort(int v[],int nrelem,int maxim)
{
    int mn,mx,range,i,corect[nrelem];
    mn = mx = v[0];
    for (i=1;i<nrelem;i++)
    {
        if (mn>v[i])
            mn = v[i];
        if (mx<v[i])
            mx = v[i];
    }
    range = mx-mn+1;
    int vecfrec[range] = {0};
    for (i=0;i<nrelem;i++)
        vecfrec[v[i]-mn]++;
    for (i = 1;i<range;i++)
        vecfrec[i] += vecfrec[i-1];
    for (i=nrelem-1;i>=0;i--)
    {
        corect[vecfrec[v[i]-mn]-1] = v[i];
        vecfrec[v[i]-mn]--;
    }
    for (i=0;i<nrelem;i++)
        v[i] = corect[i];
}

// Portiune merge sort

int tmp[10001];
void MergeSort(int v[], int st, int dr)
{
	if(st < dr)
	{
		int m = (st + dr) / 2;
		MergeSort(v, st , m);
		MergeSort(v, m + 1 , dr);
		int i = st, j = m + 1, k = 0;
		while( i <= m && j <= dr )
			if( v[i] < v[j])
				tmp[++k] = v[i++];
			else
				tmp[++k] = v[j++];
		while(i <= m)
			tmp[++k] = v[i++];
		while(j <= dr)
			tmp[++k] = v[j++];
		for(i = st , j = 1 ; i <= dr ; i ++ , j ++)
			v[i] = tmp[j];
	}
}

// Portiune radix sort

int Maxim(int v[],int nrelem)
{
    int maxim = v[0];
    for (int i=1;i<nrelem;i++)
        if (v[i] > maxim)
            maxim = v[i];
    return maxim;
}

void CountSortRadix(int v[],int nrelem, int exp)
{
    int corect[nrelem],i,count[10] = {0};
    for (i=0;i<nrelem;i++)
        count[(v[i]/exp)%10]++;
    for (i=1;i<10;i++)
        count[i] += count[i-1];
    for (i=nrelem-1;i>=0;i--)
    {
        corect[count[(v[i]/exp)%10] -1] = v[i];
        count[(v[i]/exp)%10]--;
    }
    for (i=0;i<nrelem;i++)
        v[i] = corect[i];
}

void RadixSort(int v[],int nrelem)
{
    int mx = Maxim(v,nrelem);
    for (int exp=1;mx/exp>0;exp*=10)
        CountSortRadix(v,nrelem,exp);
}

// Portiune quick sort

int Partitie(int v[],int st,int dr)
{
    int pivot = v[dr];
    int i = st-1;
    for (int j=st;j<dr;j++)
        if (v[j]<=pivot)
    {
        i++;
        swap(v[i],v[j]);
    }
    swap(v[i+1],v[dr]);
    return(i+1);
}

int Partitie_Piv(int v[],int st,int dr)
{
    int r = st + rand() % (dr-st);
    swap(v[r],v[dr]);
    return Partitie(v,st,dr);

}

void QuickSort(int v[],int st,int dr)
{
    if (st<dr)
    {
        int pi = Partitie_Piv(v,st,dr);
        QuickSort(v,st,pi-1);
        QuickSort(v,pi+1,dr);
    }
}

// Setare ceas pt. timp executie

double PCFreq = 0.0;
__int64 CounterStart = 0;

void StartCounter()
{
    LARGE_INTEGER li;
    if(!QueryPerformanceFrequency(&li))
    cout << "QueryPerformanceFrequency failed!\n";

    PCFreq = double(li.QuadPart)/1000.0;

    QueryPerformanceCounter(&li);
    CounterStart = li.QuadPart;
}
double GetCounter()
{
    LARGE_INTEGER li;
    QueryPerformanceCounter(&li);
    return double(li.QuadPart-CounterStart)/PCFreq;
}

// Portiune verificare corectitudine sortare

int Testare(int v[],int nrelem)
{
    int anterior = v[0];
    for (int i=1;i<nrelem;i++)
    {
        if (v[i]<anterior)
            return 0;
        anterior = v[i];
    }
    return 1;
}

int main()
{
    srand(time(NULL));
    int x,i,j,nr,maxim,v[5][10000],v2[5][10000],sor;
    double temp;
    fin>>x;
    for (i=0;i<x;i++)
    {
        cout<<"Testul nr. "<<i+1<<" :"<<endl;
        fin>>nr>>maxim;
        for (j=0;j<nr;j++)
        {
            v[i][j] = rand() % maxim;
            v2[i][j] = v[i][j];
        }
        for (sor=0;sor<=5;sor++)
        {
            if (sor == 0)
            {
                StartCounter();
                BubbleSort(v[i],nr);
                temp = GetCounter();
                cout<<"BubbleSort : "<<temp;
                if (Testare(v[i],nr) == 1)
                    cout<<" Sortare reusita";
                else cout<<" Greseala Sortare";
            }
            if (sor == 1)
            {
                StartCounter();
                CountSort(v[i],nr,maxim);
                temp = GetCounter();
                cout<<"CountSort : "<<temp;
                if (Testare(v[i],nr) == 1)
                    cout<<" Sortare reusita";
                else cout<<" Greseala Sortare";
            }
            if (sor == 2)
            {
                StartCounter();
                MergeSort(v[i],0,nr-1);
                temp = GetCounter();
                cout<<"MergeSort : "<<temp;
                if (Testare(v[i],nr) == 1)
                    cout<<" Sortare reusita";
                else cout<<" Greseala Sortare";
            }
            if (sor == 3)
            {
                StartCounter();
                QuickSort(v[i],0,nr-1);
                temp = GetCounter();
                cout<<"QuickSort : "<<temp;
                if (Testare(v[i],nr) == 1)
                    cout<<" Sortare reusita";
                else cout<<" Greseala Sortare";
            }
            if (sor == 4)
            {
                StartCounter();
                RadixSort(v[i],nr);
                temp = GetCounter();
                cout<<"RadixSort : "<<temp;
                if (Testare(v[i],nr) == 1)
                    cout<<" Sortare reusita";
                else cout<<" Greseala Sortare";
            }
            if (sor == 5)
            {
                StartCounter();
                std::sort(v[i],v[i]+nr);
                temp = GetCounter();
                cout<<"SortDefault : "<<temp;
                if (Testare(v[i],nr)== 1)
                    cout<<" Sortare reusita";
                else cout<<" Greseala Sortare";
            }
            for (j=0;j<nr;j++)
                v[i][j] = v2[i][j];
            cout<<endl;
        }
        cout<<endl;

    }
    return 0;
}
