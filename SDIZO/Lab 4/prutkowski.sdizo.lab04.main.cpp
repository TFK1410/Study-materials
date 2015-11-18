/*  SDIZO IS1 223B LAB04
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
	if (!head)
	{
		cout << "Drzewo nie zostalo zainicjowane" << endl;
		return head;
	}
	if (!s->key)
	{
		cout << "Drzewo jest puste" << endl;
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
	
	if (!s->node_left && !s->node_right && !s_par)		//usuwany jest jedyny element drzewa -> head
		head = NULL;
	else if (!s->node_left && !s->node_right){		//usuwany jest lisc
		if (s_par->node_left == s)
			s_par->node_left = NULL;
		else
			s_par->node_right = NULL;
	}
	else if (!s->node_left && !s_par){				//jezeli nie ma zadnego poprzednika to wstawiany jako head jest nastepnik (brak lewego poddrzewa)	
		head = s->node_right;
	}
	else if (!s->node_left){				//przeskakiwany jest usuwany element
		if (s_par->node_left == s)
			s_par->node_left = s->node_right;
		else
			s_par->node_right = s->node_right;
	}
	else if (!s->node_right && s_par){				//przeskakiwany jest usuwany element (usuwany element nie jest headem)	
		if (s_par->node_left == s)
			s_par->node_left = s->node_left;
		else
			s_par->node_right = s->node_left;
	}
	else{									//wstawiany w miejsce usuwanego jest node poprzedni z inorder (bedzie on lisciem)
		slowo *preinorder = s->node_left;
		slowo *parpreinorder = s;
		while (preinorder->node_right){
			parpreinorder = preinorder;
			preinorder = preinorder->node_right;
		}
		s->key = preinorder->key;			//zastepujemy klucz: ten z liscia => usuwanego klucza (by nie meczyc sie z polaczeniami)
		if (parpreinorder->node_left == preinorder){	// usuwamy ten lisc
			if (s->node_left->node_left)
				parpreinorder->node_left = s->node_left->node_left;
			else
				parpreinorder->node_left = NULL;
		}
		else
			parpreinorder->node_right = NULL;
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



//////////////////////////////////////////////////// LAB4


slowo* delall(slowo *word){ //pierwszy argument to head
	if (word->node_left)
		delall(word->node_left);
	if (word->node_right)
		delall(word->node_right);
	delete(word);
	if (word)
		word = NULL;
	return NULL;
}

int tree_height(slowo *word){
	int left=0, right=0;
	if (!word)
	{
		cout << "Drzewo nie zostalo zainicjowane" << endl;
		return 0;
	}
	if (word->node_left)
		left = tree_height(word->node_left);
	if (word->node_right)
		right = tree_height(word->node_right);
	if (left > right)
		return left + 1;
	else
		return right + 1;
}

int tree_nodes(slowo *word){
	if (!word)
		return 0;
	return tree_nodes(word->node_left) + 1 + tree_nodes(word->node_right);
}


slowo* rotate_right(slowo* head, slowo* s_grdpar, slowo* s_par, slowo* s){
	slowo* temp;
	if (s_grdpar){
		if (s_grdpar->node_right == s_par){
			s_grdpar->node_right = s;
		}
		else{
			s_grdpar->node_left = s;
		}
	}
	else
		head = s;

	if (s_par->node_left == s){
		temp = s->node_right;
		s->node_right = s_par;
		s_par->node_left = temp;
	}
	else{
		temp = s->node_right;
		s->node_left = s_par;
		s_par->node_right = temp;
	}

	return head;
}

slowo* rotate_left(slowo* head, slowo* s_grdpar, slowo* s_par, slowo* s){
	slowo* temp;
	if (s_grdpar){
		if (s_grdpar->node_right == s_par){
			s_grdpar->node_right = s;
		}
		else{
			s_grdpar->node_left = s;
		}
	}
	else
		head = s;

	if (s_par->node_right == s){
		temp = s->node_left;
		s->node_left = s_par;
		s_par->node_right = temp;
	}
	else{
		temp = s->node_left;
		s->node_right = s_par;
		s_par->node_left = temp;
	}

	return head;
}


slowo* DSW_algorithm(slowo* head, int N){
	slowo *s, *s_child, *s_par;
	
	s_par = NULL;				//FAZA I - ulozenie w "liste"
	s = head;
	while (s){ 
		if (s->node_left){
			s_child = s->node_left;
			head = rotate_right(head, s_par, s, s_child);
			s = s_child;
		}
		else{
			s_par = s;
			s = s->node_right;
		}
	}

	int i, m;					//FAZA II - ulozenie w optymalne drzewo
	s_par = NULL;
	s = head;

	m = 1;
	while (m <= N)
		m = 2 * m + 1;
	m = m / 2;

	for (i = 0; i < (N - m); i++){
		if (s->node_right){
			s_child = s->node_right;
			head = rotate_left(head, s_par, s, s_child);
			s_par = s_child;
			s = s_child->node_right;
		}
	}

	while (m > 1){
		m = m / 2;
		s_par = NULL;
		s = head;
		for (i = 0; i < m; i++){
			if (s->node_right){
				s_child = s->node_right;
				head = rotate_left(head, s_par, s, s_child);
				s_par = s_child;
				s = s_child->node_right;
			}
		}
	}
	return head;
}


int _tmain(int argc, _TCHAR* argv[])
{
	clock_t begin, end;
	double time_spent;
	begin = clock();

	int X1, X2;
	ifstream wczyt;

	wczyt.open("inlab04.txt");
	if (wczyt.good())
	{
		slowo* head = NULL;
		head = initiate();
		wczyt >> X1 >> X2;
		head = losins(head, X1);
		cout << "Drzewo ma wysokosc: " << tree_height(head) << endl;
		head = DSW_algorithm(head, tree_nodes(head));
		cout << "Drzewo ma wysokosc: " << tree_height(head) << endl;
		head = delall(head);
		head = initiate();
		head = losins(head, X2);
		cout << "Drzewo ma wysokosc: " << tree_height(head) << endl;
		head = DSW_algorithm(head, tree_nodes(head));
		cout << "Drzewo ma wysokosc: " << tree_height(head) << endl;
		head = delall(head);
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

