/*  SDIZO IS1 223B LAB06
Pawe³ Rutkowski
prutkowski@wi.zut.edu.pl */
#include "stdafx.h"
#include <stdio.h>
#include <tchar.h>
#include <cstdlib>
#include <iostream>
#include <time.h>
#include <fstream>
#include <math.h>

using namespace std;

struct slowo{
	slowo *node_left;
	int key;
	slowo *node_right;
};

int flag, nodenumber = 0;

slowo* initiate()
{
	slowo* head;
	head = new slowo;
	head->node_left = NULL;
	head->key = NULL;                           // INICJALIZACJA POWODUJE WSTAWIENIE WPISU O KLUCZU NULL
	head->node_right = NULL;
	nodenumber++;
	return head;
}

void minimax(slowo *head){
	if (head){
		cout << "Min: " << head->node_left->key << endl;
		cout << "Max: " << head->node_right->key << endl;
	}
	else
		cout << "Kopiec jest pusty" << endl;
}

void first15nodes(slowo *word, int i){
	if (word && i < 4){
		first15nodes(word->node_right, i + 1);
		for (int j = 0; j <= i; j++)
			cout << "\t";
		cout << word->key << endl;
		first15nodes(word->node_left, i + 1);
	}
	else if (i < 4)
		cout << endl;
}

int tree_height(slowo *word){
	int left = 0, right = 0;
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

int tree_nodes(slowo* word){
	if (!word)
		return 0;
	return tree_nodes(word->node_left) + 1 + tree_nodes(word->node_right);
}

bool pathtonewmin(slowo* headmin, slowo* nowa, bool changeflag, int wys, int nodes){
	slowo *kid = headmin;
	if (kid == nowa){
		return true;
	}
	int i = pow(2, wys - 2);
	if (i > nodes){
		kid = kid->node_left;
	}
	else{
		kid = kid->node_right;
		nodes = nodes - i;
	}
	changeflag = pathtonewmin(kid, nowa, changeflag, wys - 1, nodes);
	if (changeflag){
		int tmp;
		if (kid->key < headmin->key){
			tmp = kid->key;
			kid->key = headmin->key;
			headmin->key = tmp;
			return true;
		}
		return false;
	}
	return changeflag;
}

bool pathtonewmax(slowo* headmax, slowo* nowa, bool changeflag, int wys, int nodes){
	slowo *kid = headmax;
	if (kid == nowa){
		return true;
	}
	int i = pow(2, wys - 2);
	if (i > nodes){
		kid = kid->node_left;
	}
	else{
		kid = kid->node_right;
		nodes = nodes - i;
	}
	changeflag = pathtonewmax(kid, nowa, changeflag, wys - 1, nodes);
	if (changeflag){
		int tmp;
		if (kid->key > headmax->key){
			tmp = kid->key;
			kid->key = headmax->key;
			headmax->key = tmp;
			return true;
		}
		return false;
	}
	return changeflag;
}

bool scan_inorder(slowo *word, int keyg, bool flags)
{
	if (word && flags){
		flags = scan_inorder(word->node_left, keyg, flags);
		if (word->key == keyg){
			flags = false;
			return flags;
		}
		flags = scan_inorder(word->node_right, keyg, flags);
		return flags;
	}
	else
		return flags;
}

void insert(slowo* head, int keyg)
{
	slowo  *pr, *prv, *nowa;
	pr = NULL;
	nowa = new slowo;
	if (nowa == NULL)
	{
		cout << "Brak miejsca w pamieci" << endl;
		flag = -2;
		return;
	}
	nowa->node_left = NULL;
	nowa->key = keyg;
	nowa->node_right = NULL;
	prv = head;
	if (prv == NULL){
		cout << "Lista nie zostala zainicjalizowana" << endl;
		flag = -2;
		return;
	}
	if (!scan_inorder(head, keyg, true)){						//powtarzanie sie elementu
		flag = -1;
		return;
	}

	int wys, nodes, i, nodestopath, wystopath;
	wys = ceil(log2(nodenumber+1));
	nodes = nodenumber - pow(2, wys - 1)+1;
	nodestopath = nodes;
	wystopath = wys;
	
	slowo* kuzyn = head;
	bool kuzynflag = true, treeflag=false;						//FALSE=MIN TRUE=MAX

	if (nodes == pow(2, wys-1)){
		nodestopath = 0;
		wystopath++;
		while (prv!=NULL){
			pr = prv;
			prv = prv->node_left;
		}
		kuzyn = kuzyn->node_right;
		if (kuzyn == NULL){
			kuzynflag = false;
		}
		while (kuzynflag){
			if (kuzyn->node_left)
				kuzyn = kuzyn->node_left;
			else
				kuzynflag = false;
		}
	}
	else{
		pr = prv;
		i = pow(2, wys - 2);
		if (i > nodes){
			prv = prv->node_left;
			kuzyn = kuzyn->node_right;
		}
		else{
			treeflag = true;
			prv = prv->node_right;
			kuzyn = kuzyn->node_left;
			nodes = nodes - i;
		}
		wys--;
	}

	while (prv!=NULL)
	{
		pr = prv;
		i = pow(2, wys - 2);
		if (i > nodes){
			prv = prv->node_left;
			if (kuzyn->node_left && kuzynflag)
				kuzyn = kuzyn->node_left;
			else
				kuzynflag = false;
		}
		else{
			prv = prv->node_right;
			if (kuzyn->node_right && kuzynflag)
				kuzyn = kuzyn->node_right;
			else
				kuzynflag = false;
			nodes = nodes - i;
		}
		wys--;
	}							//koniec fazy 1

	if (kuzyn == NULL){
		head->node_left = nowa;
		nodenumber++;
		return;
	}
	else if (pr->node_left==NULL){
		pr->node_left = nowa;
	}
	else{
		pr->node_right = nowa;
	}

	int tmp;
	if (treeflag && nowa->key < kuzyn->key){
		treeflag = false;
		tmp = nowa->key;
		nowa->key = kuzyn->key;
		kuzyn->key = tmp;
		nowa = kuzyn;
		nodestopath = nodestopath - pow(2, wystopath - 2);
	}
	else if (!treeflag && nowa->key > kuzyn->key){
		treeflag = true;
		tmp = nowa->key;
		nowa->key = kuzyn->key;
		kuzyn->key = tmp;
		nowa = kuzyn;
		nodestopath = nodestopath / 2 + pow(2,wystopath-3);
		wystopath--;
	}						//koniec fazy 2

	if (treeflag)
		pathtonewmax(head->node_right, nowa, true, wystopath - 1, nodestopath - pow(2, wystopath - 2));
	else
		pathtonewmin(head->node_left, nowa, true, wystopath - 1, nodestopath);


	flag = 0;                     // Wstawilo koniec fazy 3
	nodenumber++;
	return;
}

void losins(slowo* head, int X)
{
	int i, keyg, *tab,j=0;
	tab = new int[X];
	srand(time(NULL));
	for (i = 0; i<X; i++)
	{
		flag = -1;
		while (flag == -1)
		{
			keyg = (rand()*rand()) % 1000001 + 10;
			insert(head, keyg);
		} 
		if (flag == -2)
			i = X;
	}
	return;
}

void delslowomin(slowo* head)
{
	if (!head){
		cout << "Drzewo nie zostalo zainicjowane" << endl;
		return;
	}

	if (!head->node_right){
		delete(head->node_left);
		head->node_left = NULL;
		cout << "Usunieto ostatni element kopca" << endl;
		nodenumber--;
		return;
	}

	slowo *pr = NULL, *prv = head, *grandpr = NULL;
	
	int wys, nodes, i, wystopath;
	wys = ceil(log2(nodenumber + 1));
	nodes = nodenumber - pow(2, wys - 1);
	wystopath = wys;

	if (nodes == pow(2, wys)){
		while (prv != NULL){
			grandpr = pr;
			pr = prv;
			prv = prv->node_right;
			wystopath--;
		}
	}

	while (prv != NULL)
	{
		grandpr = pr;
		pr = prv;
		i = pow(2, wys - 2);
		if (i > nodes)
			prv = prv->node_left;
		else{
			prv = prv->node_right;
			nodes = nodes - i;
		}
		wys--;
	}

	head->node_left->key = pr->key;			//min<=>last leaf
	
	if (grandpr->node_left == pr)
		grandpr->node_left = NULL;
	else
		grandpr->node_right = NULL;

	delete(pr);

	bool changeflag = true;
	int tmp, wyswhile = 2;
	slowo *cousine=head->node_right;
	prv = head->node_left;

	while (changeflag){
		if (prv->node_right && prv->node_right){
			if (prv->node_left->key < prv->node_right->key && prv->node_left->key < prv->key){
				tmp = prv->key;
				prv->key = prv->node_left->key;
				prv->node_left->key = tmp;
				prv = prv->node_left;
				wyswhile++;
				if (cousine->node_left)
					cousine = cousine->node_left;
			}
			else if (prv->node_right->key < prv->key){
				tmp = prv->key;
				prv->key = prv->node_right->key;
				prv->node_right->key = tmp;
				prv = prv->node_right;
				wyswhile++;
				if (cousine->node_right)
					cousine = cousine->node_right;
			}
			else
				changeflag = false;
		}
		else if (prv->node_right){
			if (prv->key > prv->node_right->key){
				tmp = prv->key;
				prv->key = prv->node_right->key;
				prv->node_right->key = tmp;
				prv = prv->node_right;
				wyswhile++;
				if (cousine->node_right)
					cousine = cousine->node_right;
			}
			else
				changeflag = false;
		}
		else if (prv->node_left){
			if (prv->key > prv->node_left->key){
				tmp = prv->key;
				prv->key = prv->node_left->key;
				prv->node_left->key = tmp;
				prv = prv->node_left;
				wyswhile++;
				if (cousine->node_left)
					cousine = cousine->node_left;
			}
			else
				changeflag = false;
		}
		else
			changeflag = false;
	}
	
	if (cousine){
		if (cousine->key < prv->key){
			tmp = prv->key;
			prv->key = cousine->key;
			cousine->key = tmp;
		}
	}

	nodenumber--;
	return;
}

void delslowomax(slowo* head)
{
	if (!head){
		cout << "Drzewo nie zostalo zainicjowane" << endl;
		return;
	}

	if (!head->node_right){
		cout << "Nie istnieje juz zaden element poddrzewa max (prawego)" << endl;
		return;
	}

	slowo *pr = NULL, *prv = head, *grandpr = NULL;

	int wys, nodes, i, wystopath;
	wys = ceil(log2(nodenumber+1));
	nodes = nodenumber - pow(2, wys - 1);
	wystopath = wys;

	if (nodes == pow(2, wys)){
		while (prv != NULL){
			grandpr = pr;
			pr = prv;
			prv = prv->node_right;
			wystopath--;
		}
	}

	while (prv != NULL)
	{
		grandpr = pr;
		pr = prv;
		i = pow(2, wys - 2);
		if (i > nodes)
			prv = prv->node_left;
		else{
			prv = prv->node_right;
			nodes = nodes - i;
		}
		wys--;
	}

	head->node_right->key = pr->key;			//max<=>last leaf koniec fazy 1

	if (grandpr->node_left == pr)
		grandpr->node_left = NULL;
	else
		grandpr->node_right = NULL;

	delete(pr);

	bool changeflag = true;
	int tmp, wyswhile = 2;
	slowo *cousine = head->node_left;
	prv = head->node_right;

	while (changeflag){
		if (prv->node_right && prv->node_right){
			if (prv->node_left->key > prv->node_right->key && prv->node_left->key > prv->key){
				tmp = prv->key;
				prv->key = prv->node_left->key;
				prv->node_left->key = tmp;
				prv = prv->node_left;
				wyswhile++;
				if (cousine->node_left)
					cousine = cousine->node_left;
			}
			else if (prv->node_right->key > prv->key){
				tmp = prv->key;
				prv->key = prv->node_right->key;
				prv->node_right->key = tmp;
				prv = prv->node_right;
				wyswhile++;
				if (cousine->node_right)
					cousine = cousine->node_right;
			}
			else
				changeflag = false;
		}
		else if (prv->node_right){
			if (prv->key < prv->node_right->key){
				tmp = prv->key;
				prv->key = prv->node_right->key;
				prv->node_right->key = tmp;
				prv = prv->node_right;
				wyswhile++;
				if (cousine->node_right)
					cousine = cousine->node_right;
			}
			else
				changeflag = false;
		}
		else if (prv->node_left){
			if (prv->key < prv->node_left->key){
				tmp = prv->key;
				prv->key = prv->node_left->key;
				prv->node_left->key = tmp;
				prv = prv->node_left;
				wyswhile++;
				if (cousine->node_left)
					cousine = cousine->node_left;
			}
			else
				changeflag = false;
		}
		else
			changeflag = false;
	}											//koniec fazy 2

	if (cousine){
		if (cousine->key > prv->key){
			tmp = prv->key;
			prv->key = cousine->key;
			cousine->key = tmp;
		}
	}											//koniec fazy 3

	nodenumber--;
	return;
}

slowo* delall(slowo *head){
	while (head->node_left)
		delslowomin(head);
	delete(head);
	nodenumber = 0;
	return NULL;
}



int _tmain(int argc, _TCHAR* argv[])
{
	clock_t begin, end;
	double time_spent;
	begin = clock();

	int X1, X2, k1, k2;
	ifstream wczyt;

	wczyt.open("inlab06.txt");
	if (wczyt.good())
	{
		slowo* head = NULL;						//dodawanie elementow dziala, poprawic wyswietlanie, dodac usuwanie
		head = initiate();
		wczyt >> X1 >> X2 >> k1 >> k2;
		losins(head, X1);
		insert(head, k1);
		insert(head, k2);
		delslowomin(head);
		delslowomax(head);
		first15nodes(head,0);
		head = delall(head);
		head = initiate();
		losins(head, X2);
		delslowomin(head);
		delslowomax(head);
		insert(head, k1);
		insert(head, k2);
		minimax(head);
		head = delall(head);
		minimax(head);
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

