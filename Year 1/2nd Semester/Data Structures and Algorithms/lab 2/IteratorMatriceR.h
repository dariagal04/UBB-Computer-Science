#pragma once
#include "Matrice.h"

class Container;

class IteratorMatriceR
{
	friend class Container;

private:
	//iteratorul memoreaza o referinta catre container
	const Container& con;
	//aici alte atribute specifice: curent, etc

	IteratorMatriceR(const Container& c);

public:
	TElem element() const;
	bool valid() const;
	void urmator();
	void prim();
};

