#include "Matrice.h"

#include <exception>
#include <iostream>

using namespace std;

// Best case: Theta(1)
//  Worst case: Theta(1)
// Average case: Theta(1)
Matrice::Matrice(int m, int n) {
	/* de adaugat */

	nrLin = m;
	nrCol = n;
	capacitate = m*n;
	elems = new TriData[capacitate];
	size = 0;

}

Matrice::~Matrice() {
	delete[] elems;
}




// Best case: Theta(1)
//  Worst case: Theta(1)
// Average case: Theta(1)
int Matrice::nrLinii() const {
	return nrLin;
}


// Best case: Theta(1)
//  Worst case: Theta(1)
//  Average case: Theta(1)
int Matrice::nrColoane() const {
	return nrCol;
}


int Matrice::mcapacitate() const {
	return capacitate;
}


// Best case: O(1)
//  Worst case: O(size)
// Average case: O(size)
TElem Matrice::element(int i, int j) const {
	if (i < 0 || i >= nrLin || j < 0 || j >= nrCol)
		throw exception();

	pair <int, int> p = { i, j };

	for (int i = 0; i < size; i++)
	{
		if (p == elems[i].first)
			return elems[i].second;
	}

	return NULL_TELEMENT;
}


// Best case: O(1)
//  Worst case: O(size)
// Average case: O(size)
void Matrice::resize()
{
	nrLin = nrLin * 2;
	nrCol = nrCol * 2;
	capacitate = nrLin*nrCol;
	TriData* aux = new TriData[capacitate];

	for (int i = 0; i < size; i++)
		aux[i] = elems[i];

	delete[] elems;
	elems = aux;

	
}


/*
 algoritm resize(Matrice)

    capacitate<- Matrice.capacitate *2
	creeaza(aux[capacitate])
	pentru i= 0,size executa
		aux[i]<- Matrice.elems[i]
		sf pentru
	delete(Matrice.elems)
	elems <-aux
sf algoritm
*/


// Best case: O(1)
//  Worst case: O(size)
//  Average case: O(size)
void Matrice::add_elem(TriData elem)
{
	if (size >= capacitate)
		resize();

	int line = elem.first.first;
	int col = elem.first.second;

	int position = size;

	for (int i = 0; i < size; i++)
	{
		if (elems[i].first.first == line)
		{
			if (elems[i].first.second > col)
			{
				position = i;
				break;
			}
		}
	}

	for (int j = size; j > position; j--)
		elems[j] = elems[j - 1];

	elems[position] = elem;
	size++;


}


void Matrice::afis()
{
	for (int i = 0; i < size; i++)
		cout << "i: " << elems[i].first.first << ", j: " << elems[i].first.second << ", val: " << elems[i].second << '\n';
}


// Best case: O(1)
//  Worst case: O(size)
//  Average case: O(size)
void Matrice::delete_elem(TriData elem)
{


	pair <int, int> p = { elem.first.first, elem.first.second };


	int position = 0;

	for (int i = 0; i < size; i++)
	{
		if (p == elems[i].first)
		{
			position = i;
			break;
		}
	}

	for (int i = position; i < size - 1; i++)
		elems[i] = elems[i + 1];

	size--;
}


// Best case: Theta(1)
//  Worst case: Theta(size)
//  Total: O(size)
TElem Matrice::modifica(int i, int j, TElem e) {
	if (i < 0 || i >= nrLin || j < 0 || j >= nrCol)
		throw exception();


	TElem toRet = NULL_TELEMENT;
	for (int k = 0; k < size; k++)
	{
		TriData P = elems[k];
		int x = P.first.first;
		int y = P.first.second;

		if (x == i && y == j)
		{
			toRet = P.second;
			elems[k].second = e;
			if (e == NULL_TELEMENT)
				delete_elem(elems[k]);
		}
	}

	if (toRet == NULL_TELEMENT && e != NULL_TELEMENT)
	{
		TriData P = make_pair(make_pair(i, j), e);
		add_elem(P);
	}



	return toRet;
}



