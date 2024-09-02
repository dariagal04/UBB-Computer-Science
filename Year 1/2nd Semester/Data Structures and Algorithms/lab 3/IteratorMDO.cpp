#include "IteratorMDO.h"

#include "MDO.h"


IteratorMDO::IteratorMDO(const MDO& d) : dict(d) {
	/*
	* Complexitate:
	*		Best Case: teta(1)
	*		Worst Case: teta(1)
	*		Total: O(1)
	*		Spatiu: teta(1)
	*/
	cheie_curent = d.prim;
	if (cheie_curent != nullptr)
		valoare_curenta = d.prim->lista;
	else
		valoare_curenta = nullptr;

}

void IteratorMDO::prim() {
	/*
	* Complexitate:
	*		Best Case: teta(1)
	*		Worst Case: teta(1)
	*		Total: O(1)
	*		Spatiu: teta(1)
	*/
	cheie_curent = dict.prim;
	if (cheie_curent != nullptr)
		valoare_curenta = dict.prim->lista;
	else
		valoare_curenta = nullptr;
}

void IteratorMDO::prim_c() {
	/*
	* Complexitate:
	*		Best Case: teta(1)
	*		Worst Case: teta(1)
	*		Total: O(1)
	*		Spatiu: teta(1)
	*/
	cheie_curent = dict.prim;
}

void IteratorMDO::urmator() {
	/*
	* Complexitate:
	*		Best Case: teta(1)
	*		Worst Case: teta(1)
	*		Total: O(1)
	*		Spatiu: teta(1)
	*/
	if (this->valid())
	{
		if (valoare_curenta->urm != nullptr)
			valoare_curenta = valoare_curenta->urm;
		else
		{
			cheie_curent = cheie_curent->urm;
			if (valid())
				valoare_curenta = cheie_curent->lista;
		}
	}
	else
		throw std::exception();
}

void IteratorMDO::urmator_c()
/*
	* Complexitate:
	*		Best Case: teta(1)
	*		Worst Case: teta(1)
	*		Total: O(1)
	*		Spatiu: teta(1)
	*/
{
	if (valid_c())
		cheie_curent = cheie_curent->urm;
	else
		throw std::exception();
}

bool IteratorMDO::valid() const {
	/*
	* Complexitate:
	*		Best Case: teta(1)
	*		Worst Case: teta(1)
	*		Total: O(1)
	*		Spatiu: teta(1)
	*/
	if (cheie_curent != nullptr && valoare_curenta != nullptr)
		return true;
	return false;
}

bool IteratorMDO::valid_c() const
/*
	* Complexitate:
	*		Best Case: teta(1)
	*		Worst Case: teta(1)
	*		Total: O(1)
	*		Spatiu: teta(1)
	*/
{
	if (cheie_curent != nullptr)
		return true;
	return false;
}

TElem IteratorMDO::element() const {
	/*
	* Complexitate:
	*		Best Case: teta(1)
	*		Worst Case: teta(1)
	*		Total: O(1)
	*		Spatiu: teta(1)
	*/
	if (valid())
		return make_pair(cheie_curent->cheie, valoare_curenta->val);
	throw std::exception();
}

TCheie IteratorMDO::element_c() const {
	/*
	* Complexitate:
	*		Best Case: teta(1)
	*		Worst Case: teta(1)
	*		Total: O(1)
	*		Spatiu: teta(1)
	*/
	if (valid_c())
		return cheie_curent->cheie;
	throw std::exception();
}
