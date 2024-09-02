#pragma once

#include "MDO.h"

class IteratorLP;

class IteratorMDO {
	friend class MDO;
	friend class IteratorLP;
private:

	//constructorul primeste o referinta catre Container
	//iteratorul va referi primul element din container
	IteratorMDO(const MDO& dictionar);

	//contine o referinta catre containerul pe care il itereaza
	const MDO& dict;

	NodCheie* cheie_curent;
	NodValoare* valoare_curenta;

public:

	//reseteaza pozitia iteratorului la inceputul containerului
	void prim();

	void prim_c();

	//muta iteratorul in container
	// arunca exceptie daca iteratorul nu e valid
	void urmator();

	void urmator_c();

	//verifica daca iteratorul e valid (indica un element al containerului)
	bool valid() const;

	bool valid_c() const;

	//returneaza valoarea elementului din container referit de iterator
	//arunca exceptie daca iteratorul nu e valid
	TElem element() const;

	TCheie element_c() const;
};

