#include "IteratorMDO.h"
#include "MDO.h"

#include <iostream>
#include <vector>

#include <exception>
using namespace std;

MDO::MDO(Relatie r) {
	prim = nullptr;
	rel = r;
	size = 0;

}


void MDO::adauga(TCheie c, TValoare v) {
	/*
	* Complexitate:
	*		Best Case: teta(1)
	*		Worst Case: teta(n*m), n=numar chei, m=numar valori in cheie
	*		Total: O(n*m)
	*		Spatiu: teta(1)
	*/
	NodCheie* curent = prim;
	NodCheie* ant = nullptr;

	if (prim == nullptr)
	{
		NodCheie* nou = new NodCheie;
		nou->cheie = c;
		nou->lista = new NodValoare;
		nou->lista->val = v;
		nou->lista->urm = nullptr;
		nou->urm = nullptr;
		prim = nou;
	}
	else
	{
		bool existaCheie = false;
		while (curent != nullptr && rel(curent->cheie, c))
		{
			if (curent->cheie == c)
			{
				bool existaVal = false;
				NodValoare* valori = curent->lista;
				while (valori->urm != nullptr)
				{
					if (valori->val == v)
					{
						existaVal = true;
						break;
					}
					valori = valori->urm;
				}
				if (!existaVal)
				{
					NodValoare* valNoua = new NodValoare;
					valNoua->val = v;
					valNoua->urm = nullptr;
					valori->urm = valNoua;
					existaCheie = true;
				}
			}
			ant = curent;
			curent = curent->urm;
		}
		if (!existaCheie)
		{
			if (curent == nullptr && rel(ant->cheie, c))
			{
				NodCheie* nou = new NodCheie;
				nou->cheie = c;
				nou->lista = new NodValoare;
				nou->lista->val = v;
				nou->lista->urm = nullptr;
				nou->urm = nullptr;
				ant->urm = nou;
			}
			else
			{
				NodCheie* nou = new NodCheie;
				nou->cheie = c;
				nou->lista = new NodValoare;
				nou->lista->val = v;
				nou->lista->urm = nullptr;
				nou->urm = curent;
				if (ant == nullptr)
					prim = nou;
				else
					ant = nou;
			}
		}
	}
	size++;
}

vector<TValoare> MDO::cauta(TCheie c) const {
	/*
	* Complexitate:
	*		Best Case: teta(1)
	*		Worst Case: teta(n*m), n=numar chei, m=numar valori in cheie
	*		Total: O(n*m)
	*		Spatiu: teta(1)
	*/
	vector<TValoare> valori;
	NodCheie* curent = prim;
	if (prim == nullptr)
		return valori;
	while (curent->cheie != c && curent->urm != nullptr)
		curent = curent->urm;
	if (curent->cheie == c)
	{
		NodValoare* valoare = curent->lista;
		while (valoare != nullptr)
		{
			valori.push_back(valoare->val);
			valoare = valoare->urm;
		}
	}
	return valori;
}

bool MDO::sterge(TCheie c, TValoare v) {
	/*
	* Complexitate:
	*		Best Case: teta(1)
	*		Worst Case: teta(n*m), n=numar chei, m=numar valori in cheie
	*		Total: O(n*m)
	*		Spatiu: teta(1)
	*/
	NodCheie* curent = prim;
	NodCheie* ant = nullptr;
	while (curent != nullptr)
	{
		if (curent->cheie == c)
		{
			NodValoare* valoare = curent->lista;
			NodValoare* valant = nullptr;
			bool valGasita = false;
			while (valoare != nullptr)
			{
				if (valoare->val == v)
				{
					valGasita = true;
					break;
				}
				valant = valoare;
				valoare = valoare->urm;
			}
			if (valGasita)
			{
				if (valant == nullptr)
				{
					if (curent->lista->urm == nullptr)
					{
						delete valoare;
						if (ant == nullptr)
							prim = prim->urm;
						else
							ant->urm = curent->urm;
						delete curent;
						size--;
						return true;
					}
					else
					{
						curent->lista = valoare->urm;
						delete valoare;
						size--;
						return true;
					}
				}
				else
				{
					if (valoare->urm != nullptr)
					{
						valant->urm = valoare->urm;
						delete valoare;
						size--;
						return true;
					}
					else
					{
						delete valoare;
						size--;
						return true;
					}
				}
			}
		}
		ant = curent;
		curent = curent->urm;
	}
	return false;
}

int MDO::dim() const {
	/*
	* Complexitate:
	*		Best Case: teta(1)
	*		Worst Case: teta(1)
	*		Total: O(1)
	*		Spatiu: teta(1)
	*/
	return size;
}

bool MDO::vid() const {
	/*
	* Complexitate:
	*		Best Case: teta(1)
	*		Worst Case: teta(1)
	*		Total: O(1)
	*		Spatiu: teta(1)
	*/
	return (prim == nullptr);
}

IteratorMDO MDO::iterator() const {
	/*
	* Complexitate:
	*		Best Case: teta(1)
	*		Worst Case: teta(1)
	*		Total: O(1)
	*		Spatiu: teta(1)
	*/
	return IteratorMDO(*this);
}


void MDO::goleste() {
	/*
	* Complexitate:
	*		Worst Case: teta(n*m), n=numar chei, m=numar maxim valori intr-o cheie
	*		Total: O(n*m)
	*		Spatiu: teta(1)
	*/
	if (vid())
		throw exception("mdo e gol");
	NodCheie* curent = prim;
	while (prim != nullptr)
	{
		NodValoare* valCurenta = prim->lista;
		NodValoare* val = prim->lista;
		prim = prim->urm;
		while (valCurenta != nullptr)
		{
			valCurenta = valCurenta->urm;
			val = valCurenta;
			size--;
		}
		curent = prim;
	}
}

/*
Algoritm golește()
	dacă vid() este adevărat atunci
		@arunca exceptie
		sf daca
	curent <- prim
	cât timp prim != nullptr executa
		valCurenta <- [prim].lista
		val <- [prim].lista
		prim <- [prim].urm
		cât timp valCurenta != nullptr executa
			valCurenta = [valCurenta].urm
			val <- valCurenta
			size-- 
			sf cat timp
		curent <- prim
		sf cat timp
sf goleste
	*/


MDO::~MDO() {
	/*
	* Complexitate:
	*		Best Case: teta(1)
	*		Worst Case: teta(n*m), n=numar chei, m=numar maxim valori intr-o cheie
	*		Total: O(n*m)
	*		Spatiu: teta(1)
	*/
	NodCheie* curent = prim;
	while (prim != nullptr)
	{
		NodValoare* val1 = prim->lista;
		NodValoare* val2 = prim->lista;
		prim = prim->urm;
		while (val1 != nullptr)
		{
			val1 = val1->urm;
			delete val2;
			val2 = val1;
		}
		delete curent;
		curent = prim;
	}
	size = 0;
}

