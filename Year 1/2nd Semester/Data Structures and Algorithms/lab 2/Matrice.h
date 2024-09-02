#pragma once

#include <compare>
#include <iostream>
typedef int TElem;
typedef std::pair<std::pair<int, int>, TElem> TriData;


#define NULL_TELEMENT 0
#define NULL_TRIPLE      \
	{                      \
		{-1, -1}, NULL_TELEM \
	}

class Matrice {

private:
	/* aici e reprezentarea */

	int nrLin, nrCol;
	TriData* elems;
	int capacitate, size;
	//int capacitate, size;

public:
	//constructor
	//se arunca exceptie daca nrLinii<=0 sau nrColoane<=0
	Matrice(int nrLinii, int nrColoane);

	int mcapacitate() const;
	//destructor
	~Matrice();

	//returnare element de pe o linie si o coloana
	//se arunca exceptie daca (i,j) nu e pozitie valida in Matrice
	//indicii se considera incepand de la 0
	TElem element(int i, int j) const;


	// returnare numar linii
	int nrLinii() const;

	// returnare numar coloane
	int nrColoane() const;


	// modificare element de pe o linie si o coloana si returnarea vechii valori
	// se arunca exceptie daca (i,j) nu e o pozitie valida in Matrice
	TElem modifica(int i, int j, TElem);

	//adauga element
	void add_elem(TriData elem);

	//modifica capacitatea astfel incat sa existe suficient spatiu pentru a adauga noi elemente
	void resize();

	void delete_elem(TriData elem);

	void afis();

};







