/*  SDIZO IS1 223B LAB01
Pawe³ Rutkowski
prutkowski@wi.zut.edu.pl */
#include <cstdlib>
#include <iostream>
#include <time.h>
#include <fstream>

using namespace std;

struct s
{
       int los;
       char znk;
       double zero;
};

s ** losowanie(int N)
{
    int i;
    srand(time(NULL));
    s **tab1=new s*[N];
    for(i=0;i<N;i++)
    {
                     tab1[i]=new s;
                     tab1[i]->los=(rand()*rand())%1000001;
                     tab1[i]->znk=char(rand()%26+65);
                     tab1[i]->zero=0;                
    }
    cout<<"Adres tablicy struktur to: "<<tab1<<endl;
    return tab1;
}

void usuwanie(s **tab1, int N)
{
    int i;
    for(i=0;i<N;i++)
    {
                     delete tab1[N-i];
    }
    delete *tab1;
}

void sortowanie(s **tab1, int N)
{
    s *tmp;
    int i,j;
    for(i=0;i<N;i++)
    {
                    for(j=0;j<N-i-1;j++)
                    {
                                        if(tab1[j]->los>tab1[j+1]->los)
                                        {
                                                            tmp=tab1[j];
                                                            tab1[j]=tab1[j+1];
                                                            tab1[j+1]=tmp;
                                        }
                    }
    } 
}

int count_znk(s **tab1, int N, char X)
{
    int liczba=0,i;
    for(i=0;i<N;i++)
    {
                    if(tab1[i]->znk==X)
                    liczba++;
    }
    return liczba;
}

int main(int argc, char *argv[])
{
    clock_t begin, end;
    double time_spent;
    begin = clock();
    int N;
    char X;
    s **tab;
    ifstream wczyt;
    wczyt.open("inlab01.txt");
    if(wczyt.good())
    {
                    wczyt>>N>>X;
                    tab=losowanie(N);
                    sortowanie(tab,N);
                    cout<<"Ilosc znakow "<<X<<" to: "<<count_znk(tab,N,X)<<endl;
                    usuwanie(tab,N);
    }
    else
    {
                    cout<<"Blad otwierania pliku\n"<<endl;
    }
    end = clock();
    time_spent = (double)(end-begin) / CLOCKS_PER_SEC;
    cout<<"Czas wykonania w sekundach to: "<<time_spent<<endl;
    system("PAUSE");
    return EXIT_SUCCESS;
}
