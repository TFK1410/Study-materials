/*  SDIZO IS1 223B LAB02
Pawe³ Rutkowski
prutkowski@wi.zut.edu.pl */
#include <cstdlib>
#include <iostream>
#include <time.h>
#include <fstream>

using namespace std;

struct slowo{
       slowo *previous;
       int key;
       slowo *next;
};

int flag;

slowo* initiate()
{
     slowo* head;
     head=new slowo;
     head->previous=NULL;
     head->key=NULL;                           // INICJALIZACJA POWODUJE WSTAWIENIE WPISU O KLUCZU 0
     head->next=NULL;
     return head;
}

slowo* insert(slowo* head, int keyg)
{
     slowo  *pr,*prv,*nowa;
     pr=NULL;
     nowa=new slowo;
     if(nowa==NULL)
     {
              cout<<"Brak miejsca w pamieci"<<endl;
              flag=-2;
              return head;
     }
     nowa->next=NULL;
     nowa->key=keyg;
     nowa->previous=NULL;
     prv=head;
     if(prv==NULL)
     {
             cout<<"Lista nie zostala zainicjalizowana"<<endl;
             flag=-2;
             return head;
     }
     if(!head->key)                              // TUTAJ ZOSTAJE NADPISANY
     {
              head=nowa;
              flag=0;
              return head;                   
     }                   
     while(prv)
     {
               if(prv->key==keyg)
               {
                                 flag=-1;        // Powtorzyl sie klucz
                                 return head;
               }
               if(prv->key<keyg)
               {
                                 pr=prv;
                                 prv=prv->next;                
               }
               else
               {
                                 if(!pr)
                                        head=nowa;
                                 else
                                 {
                                        pr->next=nowa;
                                        nowa->previous=pr;
                                 }
                                 nowa->next=prv;
                                 prv->previous=nowa;
                                 flag=0;            // Wstawilo do srodka lub heada
                                 return head;
               }
     }
     pr->next=nowa;
     nowa->previous=pr;
     flag=0;                     // Wstawilo na koniec
     return head;
}
     
slowo* losins(slowo* head, int X)
{
     int i,keyg;
     srand(time(NULL));
     for(i=0;i<X;i++)
     {
                     flag=-1;
                     while(flag==-1)
                     {
                                    keyg=(rand()*rand())%99991+10;
                                    head=insert(head,keyg);
                     }
                     if(flag==-2)
                                 i=X;
     }
     return head;
}

int search(slowo* head, int keyf)
{
    slowo* s;
    int i=1;
    s=head;
    while(s)
    {
            if(s->key==keyf)
            {
                            cout<<"Element o tym kluczu znajduje sie na miejscu: "<<i<<endl;
                            return 0;
            }
            s=s->next;
            i++;
    }
    cout<<"Nie udalo sie znalezc podanego klucza"<<endl;
}
                         
slowo* delslowo(slowo* head, int keyg)
{
    slowo *s,*s_prv;
    s=head;
    if(!s->key)
    {
            cout<<"Lista jest pusta"<<endl;
            return head;
    }
    while(s->key!=keyg && s)
    {
            s_prv=s;
            s=s->next;
    }
    if(!s)
    {
            cout<<"Brak slowa o takim kluczu"<<endl;
            return head;
    }
    if(s==head)
    {
            head=s->next;
            head->previous=NULL;
            delete s;
    }
    else 
    {
            s_prv->next=s->next;
            if(s->next)
                       s->next->previous=s_prv;
            delete s;
    }
    cout<<"Slowo zostalo poprawnie usuniete"<<endl;
    return head;  
}                 

void showfifo(slowo* head)
{
    slowo* s;
    s=head;
    while(s)
    {
            cout<<s->key<<endl;
            s=s->next;
    }
    cout<<endl;
}

void showlifo(slowo* head)
{
    slowo* s;
    s=head;
    while(s->next)
    {
            s=s->next;
    }
    if(s)
         cout<<s->key<<endl;
    while(s->previous)
    {
            s=s->previous;
            cout<<s->key<<endl;
    }
    cout<<endl;
}

slowo* delall(slowo* head)
{
    slowo *s,*s_prv;
    s=head;
    while(s)
    {
            s_prv=s;
            s=s->next;
            delete s_prv;
    }
    cout<<"Cala lista zostala usunieta"<<endl;
    return NULL;
}

int main(int argc, char *argv[])
{
    clock_t begin, end;
    double time_spent;
    begin = clock();
    
    int X,k1,k2,k3,k4;
    ifstream wczyt;
    
    wczyt.open("inlab02.txt");
    if(wczyt.good())
    {
                    slowo* head=NULL;
                    head=initiate();
                    wczyt>>X>>k1>>k2>>k3>>k4;
                    head=delslowo(head,k1);
                    head=losins(head,X);
                    head=insert(head,k2);
                    head=delslowo(head,k2);
                    search(head,k3);
                    head=insert(head,k4);
                    head=delslowo(head,k4);
                    showfifo(head);
                    showlifo(head);
                    head=delall(head);
    }
    else
    {
                    cout<<"Blad otwierania pliku\n"<<endl;
    }
    wczyt.close();
    
    end = clock();
    time_spent = (double)(end-begin) / CLOCKS_PER_SEC;
    cout<<"Czas wykonania w sekundach to: "<<time_spent<<endl;
    system("PAUSE");
    return EXIT_SUCCESS;
}
