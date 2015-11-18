/*  SDIZO IS1 223B LAB03
Pawe³ Rutkowski
prutkowski@wi.zut.edu.pl */
#include "stdafx.h"
#include <stdio.h>
#include <tchar.h>
#include <cstdlib>
#include <iostream>
#include <time.h>
#include <fstream>

using namespace std;

struct slowo{
	slowo *node_left;
	int key;
	slowo *node_right;
};

int flag;

slowo* initiate()
{
	slowo* head;
	head = new slowo;
	head->node_left = NULL;
	head->key = NULL;                           // INICJALIZACJA POWODUJE WSTAWIENIE WPISU O KLUCZU NULL
	head->node_right = NULL;
	return head;
}

slowo* insert(slowo* head, int keyg)
{
	slowo  *pr, *prv, *nowa;
	pr = NULL;
	nowa = new slowo;
	if (nowa == NULL)
	{
		cout << "Brak miejsca w pamieci" << endl;
		flag = -2;
		return head;
	}
	nowa->node_left = NULL;
	nowa->key = keyg;
	nowa->node_right = NULL;
	prv = head;
	if (prv == NULL)
	{
		cout << "Lista nie zostala zainicjalizowana" << endl;
		flag = -2;
		return head;
	}
	if (!head->key)                              // TUTAJ ZOSTAJE NADPISANY
	{
		head = nowa;
		flag = 0;
		return head;
	}
	while (prv)
	{
		if (prv->key == keyg)
		{
			flag = -1;        // Powtorzyl sie klucz
			return head;
		}
		pr = prv;
		if (prv->key < keyg)
			prv = prv->node_right;
		else
			prv = prv->node_left;
	}
	if (pr->key > keyg)
		pr->node_left = nowa;
	else
		pr->node_right = nowa;
	flag = 0;                     // Wstawilo
	return head;
}

slowo* losins(slowo* head, int X)
{
	int i, keyg;
	srand(time(NULL));
	for (i = 0; i<X; i++)
	{
		flag = -1;
		while (flag == -1)
		{
			keyg = (rand()*rand()) % 1000001 + 10;
			head = insert(head, keyg);
		}
		if (flag == -2)
			i = X;
	}
	return head;
}

void search(slowo* head, int keyf)
{
	slowo* s;
	s = head;
	while (s)
	{
		if (s->key == keyf)
		{
			cout << "Element o tym kluczu znajduje sie w drzewie" << endl;
			return;
		}
		else if (s->key < keyf)
			s = s->node_right;
		else
			s = s->node_left;
	}
	cout << "Nie udalo sie znalezc podanego klucza" << endl;
	return;
}

slowo* delslowo(slowo* head, int keyg)
{
	slowo *s, *s_par;
	s = head;
	s_par = NULL;
	if (!s->key)
	{
		cout << "Lista jest pusta" << endl;
		return head;
	}
	while (s && s->key != keyg)
	{
		s_par = s;
		if (s->key < keyg)
			s = s->node_right;
		else
			s = s->node_left;
	}
	if (!s)
	{
		cout << "Brak slowa o takim kluczu" << endl;
		return head;
	}
	
	if (!s->node_left&&!s->node_right){		//usuwany jest lisc
		if (s_par->node_left == s)
			s_par->node_left = NULL;
		else
			s_par->node_right = NULL;
	}
	else if (!s->node_left){				//przeskakiwany jest usuwany element
		if (s_par->node_left == s)
			s_par->node_left = s->node_right;
		else
			s_par->node_right = s->node_right;
	}
	else if (!s->node_right){				//przeskakiwany jest usuwany element	
		if (s_par->node_left == s)
			s_par->node_left = s->node_left;
		else
			s_par->node_right = s->node_left;
	}
	else{									//wstawiany w miejsce usuwanego jest node poprzedni z inorder
		slowo *preinorder=s->node_left;
		while (preinorder->node_right)
			preinorder = preinorder->node_right;
		s->key = preinorder->key;
		s = preinorder;
	}

	delete(s);
	cout << "Slowo zostalo poprawnie usuniete" << endl;
	return head;
}

void scan_inorder(slowo *word)
{
	if (word){
		scan_inorder(word->node_left);
		cout << word->key << " \n";
		scan_inorder(word->node_right);
	}
}



int _tmain(int argc, _TCHAR* argv[])
{
	clock_t begin, end;
	double time_spent;
	begin = clock();

	int X, k1, k2, k3, k4;
	ifstream wczyt;

	wczyt.open("inlab03.txt");
	if (wczyt.good())
	{
		slowo* head = NULL;
		head = initiate();
		wczyt >> X >> k1 >> k2 >> k3 >> k4;
		head = delslowo(head, k1);
		head = losins(head, X);
		head = insert(head, k1);
		head = insert(head, k2);
		head = insert(head, k3);
		head = insert(head, k4);
		head = delslowo(head, k1);
		search(head, k1);
		head = delslowo(head, k2);
		head = delslowo(head, k3);
		head = delslowo(head, k4);
		//scan_inorder(head);
	}
	else
	{
		cout << "Blad otwierania pliku\n" << endl;
	}
	wczyt.close();

	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	cout << "Czas wykonania w sekundach to: " << time_spent << endl;
	system("Pause");
	return 0;
}

