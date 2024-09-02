#pragma once
//#include<vector>

#include<iostream>
using std::cout;
template <typename Element>
class IteratorVector1;


template <typename Element>
class VectorDinamic {
private:
	int cp;
	int lg;
	Element* elems;
public:

	VectorDinamic();

	VectorDinamic(const VectorDinamic& other);

	~VectorDinamic();

	VectorDinamic& operator=(const VectorDinamic& other);

	VectorDinamic(VectorDinamic&& other);

	VectorDinamic& operator=(VectorDinamic&& other);

	void push_back(const Element& f);

	int size() const noexcept;

	Element& get(int pozitie) const;

	void erase(int poz);

	friend class IteratorVector1<Element>;

	IteratorVector1<Element> begin();

	IteratorVector1<Element> end();

};


template <typename Element>
VectorDinamic<Element>::VectorDinamic() : elems{ new Element[2] }, lg{ 0 }, cp{ 2 } {
}

template <typename Element>
VectorDinamic<Element>::VectorDinamic(const VectorDinamic& other) {
	elems = new Element[other.cp];
	for (int i = 0; i < other.lg; i++)
		elems[i] = other.elems[i];
	lg = other.lg;
	cp = other.cp;
}

template <typename Element>
VectorDinamic<Element>::~VectorDinamic() {
	delete[] elems;
}

template <typename Element>
VectorDinamic<Element>& VectorDinamic<Element>::operator=(const VectorDinamic& other) {
	if (this == &other)
		return *this;
	delete[] elems;
	elems = new Element[other.cp];
	for (int i = 0; i < other.lg; i++)
		elems[i] = other.elems[i];
	lg = other.lg;
	cp = other.cp;
	return *this;
}

template <typename Element>
VectorDinamic<Element>::VectorDinamic(VectorDinamic&& other) {
	elems = other.elems;
	lg = other.lg;
	cp = other.cp;

	other.elems = nullptr;
	other.lg = 0;
	other.cp = 0;
}

template <typename Element>
VectorDinamic<Element>& VectorDinamic<Element>::operator=(VectorDinamic&& other) {
	if (this == &other)
		return *this;
	delete[] elems;

	elems = other.elems;
	lg = other.lg;
	cp = other.cp;

	other.elems = nullptr;
	other.lg = 0;
	other.cp = 0;
	return *this;
}

template <typename Element>
void VectorDinamic<Element>::push_back(const Element& f)
{
	if (cp == lg)
	{
		Element* aux = new Element[cp * 2];
		for (int i = 0; i < lg; i++)
			aux[i] = elems[i];
		delete[] elems;
		elems = aux;
		cp *= 2;
	}
	elems[lg++] = f;
}

template <typename Element>
Element& VectorDinamic<Element>::get(int pozitie) const
{
	return elems[pozitie];
}

template <typename Element>
int VectorDinamic<Element>::size() const noexcept
{
	return lg;
}

template <typename Element>
void VectorDinamic<Element>::erase(int poz)
{
	if (poz < 0 || poz >= lg)
		return;
	for (int i = poz; i < lg - 1; i++)
		elems[i] = elems[i + 1];
	lg--;
}

template <typename Element>
IteratorVector1<Element> VectorDinamic<Element>::end()
{
	return IteratorVector1<Element>(*this, lg);
}

template <typename Element>
IteratorVector1<Element> VectorDinamic<Element>::begin()
{
	return IteratorVector1<Element>(*this);
}




template <typename Element>
class IteratorVector1 {


private:

	const VectorDinamic<Element>& vector;

	int poz = 0;

public:

	IteratorVector1(const VectorDinamic<Element>& vector) noexcept;

	IteratorVector1(const VectorDinamic<Element>& vector, int poz) noexcept;

	Element& element() const noexcept;

	void urmator() noexcept;

	Element& operator*();

	IteratorVector1& operator++();

	bool operator==(const IteratorVector1& it) noexcept;

	bool operator!=(const IteratorVector1& it) noexcept;

};


template <typename Element>
IteratorVector1<Element>::IteratorVector1(const VectorDinamic<Element>& vector) noexcept : vector{ vector } {}

template <typename Element>
IteratorVector1<Element>::IteratorVector1(const VectorDinamic<Element>& vector, int poz) noexcept : vector{ vector }, poz{ poz } {}

template <typename Element>
Element& IteratorVector1<Element>::element() const noexcept {
	return vector.elems[poz];
}

template <typename Element>
void IteratorVector1<Element>::urmator() noexcept {
	poz++;
}

template <typename Element>
Element& IteratorVector1<Element>::operator*() {
	return element();
}

template <typename Element>
IteratorVector1<Element>& IteratorVector1<Element>::operator++() {
	urmator();
	return *this;
}

template <typename Element>
bool IteratorVector1<Element>::operator==(const IteratorVector1& it) noexcept {
	return poz == it.poz;
}

template <typename Element >
bool IteratorVector1<Element>::operator!=(const IteratorVector1& it) noexcept {
	return !(*this == it);
}