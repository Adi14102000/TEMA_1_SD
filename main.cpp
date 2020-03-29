#include<iostream>
#include<fstream>
#include<cstdlib>
#include<chrono>
#include<bits/stdc++.h>
#include<climits>
using namespace std;
int n, maxim, v[10000], t;
float timp[5][100];
bool verificare(int n, int v[])
{
    int i;
    bool ok=true;
    for(i=0; i<n-1; i++)
        if(v[i]>v[i+1])
            ok=false;
               return ok;
}
void generare(int n, int v[])
{
    for(int i=0; i<n; i++)
        v[i]=rand()%maxim+1;
}
void bubblesort(int n, int v[])
{
    int auxiliar, i, j;
    bool ok;
    ok=true;
    while(ok)
    {
        ok=false;
        for(i=0; i<n-1; i++)
            for(j=i+1; j<n; j++)
                if(v[i]>v[j])
                {
                    auxiliar=v[i];
                    v[i]=v[j];
                    v[j]=auxiliar;
                    ok=true;
                }
    }
}
void countsort(int n, int v[])
{
    int i, k=0, aux[10000]= {0};
    for(i=0; i<n; i++)
    {
        aux[v[i]]++;
    }
    for(i=0; i<=maxim; i++)
    {
        if(aux[i]!=0)
        {
            v[k]=i;
            aux[i]--;
            i--;
            k++;
        }
    }
}
void sortare_cifra(int n, int v[], int x)
{
    int aux[10000], c[10]= {0}, i;
    for(i=0; i<n; i++)
    {
        c[(v[i]/x)%10]++;
    }
    for(i=1; i<10; i++)
    {
        c[i]+=c[i-1];
    }
    for(i=n-1; i>=0; i--)
    {
        aux[c[(v[i]/x)%10]-1]=v[i];
        c[(v[i]/x)%10]--;
    }
    for(i=0; i<n; i++)
        v[i]=aux[i];
}
void radixsort(int n, int v[])
{
    int i;
    i=1;
    while(maxim/i>0)
    {
        sortare_cifra(n, v, i);
        i*=10;
    }
}
void intercls(int n, int v[], int st, int dr, int mij)
{
    int aux[10000], i, j, k;
    i=st, j=mij+1, k=0;
    while(i<=mij && j<=dr)
    {
        if(v[i]<v[j])
        {
            aux[k]=v[i];
            i++;
            k++;
        }
        else
        {
            aux[k]=v[j];
            k++;
            j++;
        }
    }
    for(; i<=mij; i++)
    {
        aux[k]=v[i];
        k++;
    }
    for(; j<=dr; j++)
    {
        aux[k]=v[j];
        k++;
    }
    k=0;
    for(i=st; i<=dr; i++)
    {
        v[i]=aux[k];
        k++;
    }
}
void mergesort(int n, int v[], int st, int dr)
{
    if(st<dr)
    {
        int mij=(st+dr)/2;
        mergesort(n, v, st, mij);
        mergesort(n, v, mij+1, dr);
        intercls(n, v, st, dr, mij);
    }
}
int pivot(int n, int v[], int st, int dr)
{
    int i=st, j=dr, di=0, dj=-1, aux;
    while(i<j)
    {
        if(v[i]>=v[j])
        {
            aux=v[i];
            v[i]=v[j];
            v[j]=aux;
            aux=di;
            di=-dj;
            dj=-aux;
        }
        i=i+di;
        j=j+dj;
    }
    return i;
}
void qsort(int n, int v[], int st, int dr)
{
    int p;
    if(st<dr)
    {
        p=pivot(n, v, st, dr);
        qsort(n, v, st, p-1);
        qsort(n, v, p+1, dr);
    }
}
void afisare(int n, int v[])
{
    int i;
    for(i=0; i<n; i++)
        cout<<v[i]<<" ";
    cout<<endl;
}
int main()
{
    ifstream f("date.txt");
    f>>t;
    int i;
    int k=0, tmin;
    for(i=0; i<t; i++)
    {
        f>>n>>maxim;
        generare(n, v);
        afisare(n, v);
        cout<<endl;
        if(n<=10000)
        {
            auto start=chrono::high_resolution_clock::now();
            ios_base::sync_with_stdio(false);
            bubblesort(n, v);
            auto end=chrono::high_resolution_clock::now();
            double time_taken=chrono::duration_cast<chrono::nanoseconds>(end-start).count();
            time_taken*=1e-9;
            timp[k][0]=time_taken;
            cout<<"DURATA:"<<time_taken<<setprecision(9);
            cout<<"sec"<<endl;
            if(verificare(n, v)==false)
                cout<<"EROARE"<<endl;
            else
            {
                afisare(n, v);
                cout<<endl;
            }
        }
        else
        {
            cout<<"BUBBLESORT NU ESTE EFICIENT!";
            timp[k][0]=INT_MAX;
        }
        if(maxim<=1000000)
        {
            auto start=chrono::high_resolution_clock::now();
            ios_base::sync_with_stdio(false);
            countsort(n, v);
            auto end=chrono::high_resolution_clock::now();
            double time_taken=chrono::duration_cast<chrono::nanoseconds>(end-start).count();
            time_taken*=1e-9;
            timp[1][k]=time_taken;
            cout<<"DURATA:"<<time_taken<<setprecision(9);
            cout<<"sec"<<endl;
            if(verificare(n, v)==false)
                cout<<"EROARE"<<endl;
            else
            {

                afisare(n, v);
                cout<<endl;
            }
        }
        else
        {
            cout<<"COUNTSORT NU ESTE EFICIENT";
            t[1][k]=INT_MAX;
        }
        auto start=chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        radixsort(n, v);
        auto end=chrono::high_resolution_clock::now();
        double time_taken=chrono::duration_cast<chrono::nanoseconds>(end-start).count();
        time_taken*=1e-9;
        timp[2][k]=time_taken;
        cout<<"DURATA:"<<time_taken<<setprecision(9);
        cout<<"sec"<<endl;
        if(verificare(n, v)==false)
            cout<<"EROARE"<<endl;
        else
        {
            afisare(n, v);
            cout<<endl;
        }
        auto start=chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        mergesort(n, v, 0, n-1);
        auto end=chrono::high_resolution_clock::now();
        double time_taken=chrono::duration_cast<chrono::nanoseconds>(end-start).count();
        time_taken*=1e-9;
        t[3][k]=time_taken;
        cout<<"DURATA:"<<time_taken<<setprecision(9);
        cout<<"sec"<<endl;
        if(verificare(n, v)==false)
            cout<<"EROARE"<<endl;
        else
        {
            afisare(n, v);
            cout<<endl;
        }
        auto start=chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        qsort(n, v, 0, n-1);
        auto end=chrono::high_resolution_clock::now();
        double time_taken=chrono::duration_cast<chrono::nanoseconds>(end-start).count();
        time_taken*=1e-9;
        timp[4][k]=time_taken;
        cout<<"DURATA:"<<time_taken<<setprecision(9);
        cout<<"sec"<<endl;
        if(verificare(n, v)==false)
            cout<<"EROARE"<<endl;
        else
        {
            afisare(n, v);
            cout<<endl;
        }
        tmin=INT_MAX;
        for(int j=0; j<5; j++)
            if(timp[j][k]<tmin)
                tmin=timp[j][k];
        cout>>"Timpul minim pentru testul "<<k+1<<"a fost obtinut de ";
        if(t[0][k]==tmin)
            cout<<"bubblesort"<<endl;
        if(t[1][k]==tmin)
            cout<<"countsort"<<end;
        if(t[2][k]==tmin)
            cout<<"radixsort"<<endl;
        if(t[3][k]==tmin)
            cout<<"mergesort"<<endl;
        if(t[4][k]==tmin)
            cout<<"quicksort"<<endl;
        k++;
    }
    cout<<"Timpul minim pentru bubblesort a fost in timpul testului: ";
    tmin=INT_MAX;
    for(i=0; i<k; i++)
        if(t[0][i]<tmin)
            tmin=t[0][i];
    for(i=0; i<k; i++)
        if(t[0][i]==tmin)
        {
            cout<<i+1<<endl;
            break;
        }
    cout<<"Timpul minim pentru countsort a fost in timpul testului: ";
    tmin=INT_MAX;
    for(i=0; i<k; i++)
        if(t[1][i]<tmin)
            tmin=t[1][i];
    for(i=0; i<k; i++)
        if(t[1][i]==tmin)
        {
            cout<<i+1<<endl;
            break;
        }
    cout<<"Timpul minim pentru radixsort a fost in timpul testului: ";
    tmin=INT_MAX;
    for(i=0; i<k; i++)
        if(t[2][i]<tmin)
            tmin=t[2][i];
    for(i=0; i<k; i++)
        if(t[2][i]==tmin)
        {
            cout<<i+1<<endl;
            break;
        }
    cout<<"Timpul minim pentru mergesort a fost in timpul testului: ";
    tmin=INT_MAX;
    for(i=0; i<k; i++)
        if(t[3][i]<tmin)
            tmin=t[3][i];
    for(i=0; i<k; i++)
        if(t[3][i]==tmin)
        {
            cout<<i+1<<endl;
            break;
        }
    cout<<"Timpul minim pentru quicksort a fost in timpul testului: ";
    tmin=INT_MAX;
    for(i=0; i<k; i++)
        if(t[4][i]<tmin)
            tmin=t[4][i];
    for(i=0; i<k; i++)
        if(t[4][i]==tmin)
        {
            cout<<i+1<<endl;
            break;
        }
    return 0;
}
