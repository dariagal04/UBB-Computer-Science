#include "MyListAgentie.h"

#include<string.h>
#include<assert.h>
#include<stdlib.h>

/*
* Create an empty list
*/
MyListAgentie* createEmpty()
{
	MyListAgentie* rez = (MyListAgentie*)malloc(sizeof(MyListAgentie));;
	if (rez != NULL) {
		rez->cp = 1;
		rez->elems = (ElemType*)malloc(sizeof(Offer) * rez->cp);
		rez->lg = 0;

	}
	return rez;
}

/*
* Destroy list
*/
void destroy(MyListAgentie* l)
{
	for (int i = 0; i < l->lg; i++)
	{
		ElemType o = l->elems[i];
		destroyOffer(o);
	}
	free(l->elems);
	free(l);

}

/*
* Get an element from the list
* poz - position of the element, needs to be valid
* return the element on the given position
*/
ElemType get(MyListAgentie* l, int poz)
{
	return l->elems[poz];
}

/*
* Return number of elements of the list
*/
int size(MyListAgentie* l)
{
	return l->lg;
}

/*
* Add element into the list
* post: element is added at the end of the list
*/
void add(MyListAgentie* l, ElemType el)
{
	if (l->cp == l->lg)
	{
		int cpNoua = l->cp * 2;
		ElemType* arrnou = (ElemType*)malloc(sizeof(ElemType) * cpNoua);
		for (int i = 0; i < l->lg; i++)
			if (arrnou != NULL)
				arrnou[i] = l->elems[i];
		free(l->elems);

		l->elems = arrnou;
		l->cp = cpNoua;
	}
	if (l->elems != NULL)
	{
		l->elems[l->lg] = el;
		l->lg++;
	}
}

/*
* Delete an element from the list
*/
ElemType delete(MyListAgentie* l, int poz)
{
	ElemType el = l->elems[poz];
	//destroyOffer(l->elems[poz]);
	for (int i = poz; i < (l->lg) - 1; i++)
		l->elems[i] = l->elems[i + 1];
	l->lg--;
	return el;
}

void distrugeListaDeListe(MyListAgentie* lista)
{
	for (int i = 0; i < lista->lg; i++)
		destroy(lista->elems[i]);
	free(lista->elems);
	free(lista);
}

/*
* Update an element from the list
*/
void update(MyListAgentie* l, int poz, ElemType el)
{
	destroyOffer(l->elems[poz]);
	l->elems[poz] = el;
}

/*
* Make a shallow copy of the list
* return MyListAgentie containing the same elements as l
*/
MyListAgentie* copyList(MyListAgentie* l)
{
	MyListAgentie* rez = createEmpty();
	for (int i = 0; i < size(l); i++)
	{
		add(rez, copyOffer(l->elems[i]));
	}
	return rez;
}

/*
* Interchanges two offers from the agency
*/
void exchange(MyListAgentie* l, int i, int j)
{
	ElemType eli = get(l, i), elj = get(l, j);
	l->elems[i] = elj;
	l->elems[j] = eli;
}

ElemType removeLast(MyListAgentie* lista) {
	ElemType rez = lista->elems[lista->lg - 1];
	lista->lg--;

	return rez;
}

void testCreateList()
{
	MyListAgentie* l = createEmpty();
	assert(size(l) == 0);
	destroy(l);
}

void testIterateList()
{
	MyListAgentie* l = createEmpty();
	add(l, createOffer("casa", 1234, "Cluj-Napoca", 150000));
	add(l, createOffer("teren", 125, "Arad", 12300));
	assert(size(l) == 2);

	Offer* o = get(l, 0);
	assert(strcmp(o->type, "casa") == 0);
	assert(o->surface == 1234.0);
	o = get(l, 1);
	assert(strcmp(o->address, "Arad") == 0);
	assert(o->price == 12300.0);
	destroy(l);
	//assert(size(l) == 0);
}

void testCopyList()
{
	MyListAgentie* l = createEmpty();
	add(l, createOffer("casa", 1234, "Cluj-Napoca", 150000));
	add(l, createOffer("teren", 125, "Arad", 12300));
	MyListAgentie* l1 = copyList(l);
	assert(size(l1) == 2);
	Offer* o = get(l1, 1);
	assert(strcmp(o->address, "Arad") == 0);

	destroy(l);
	destroy(l1);
}

void testGet()
{
	MyListAgentie* l = createEmpty();
	add(l, createOffer("casa", 1234, "Cluj-Napoca", 150000));
	add(l, createOffer("teren", 125, "Arad", 12300));
	Offer* o = get(l, 0);
	assert(strcmp(o->type, "casa") == 0);
	assert(o->surface == 1234);
	assert(strcmp(o->address, "Cluj-Napoca") == 0);
	assert(o->price == 150000);

	destroy(l);
}
void testSize()
{
	MyListAgentie* l = createEmpty();
	add(l, createOffer("casa", 1234, "Cluj-Napoca", 150000));
	add(l, createOffer("teren", 125, "Arad", 12300));
	assert(size(l) == 2);

	destroy(l);
}

void testAdd()
{

	MyListAgentie* l = createEmpty();
	add(l, createOffer("casa", 1234, "Cluj-Napoca", 150000));
	assert(size(l) == 1);

	Offer* o = get(l, 0);
	assert(strcmp(o->type, "casa") == 0);
	assert(o->surface == 1234);
	assert(strcmp(o->address, "Cluj-Napoca") == 0);
	assert(o->price == 150000);

	destroy(l);
}

void testDelete()
{

	MyListAgentie* l = createEmpty();
	add(l, createOffer("casa", 1234, "Cluj-Napoca", 150000));
	assert(size(l) == 1);

	add(l, createOffer("teren", 125, "Arad", 12300));
	assert(size(l) == 2);

	//Offer* el = get(l, 1);

	ElemType ln = delete(l, 0);
	destroyOffer(ln);
	assert(size(l) == 1);

	//Offer* el1 = get(l, 0);

	assert(strcmp(((Offer*)get(l, 0))->type, ((Offer*)get(l, 1))->type) == 0);
	assert(((Offer*)get(l, 0))->surface == ((Offer*)get(l, 1))->surface);
	assert(strcmp(((Offer*)get(l, 0))->address, ((Offer*)get(l, 1))->address) == 0);
	assert(((Offer*)get(l, 0))->price == ((Offer*)get(l, 1))->price);
	 

	destroy(l);
}
void testUpdate()
{
	MyListAgentie* l = createEmpty();
	add(l, createOffer("casa", 1234, "Cluj-Napoca", 150000));
	assert(size(l) == 1);

	Offer* o = createOffer("teren", 10100, "arad", 123);
	update(l, 0, o);

	Offer* el = get(l, 0);
	assert(strcmp(o->type, el->type) == 0);
	assert(o->surface == el->surface);
	assert(strcmp(o->address, el->address) == 0);
	assert(o->price == el->price);

	destroy(l);
}

void testExchange()
{

	MyListAgentie* l = createEmpty();
	add(l, createOffer("casa", 1234, "Cluj-Napoca", 150000));
	assert(size(l) == 1);

	add(l, createOffer("teren", 125, "Arad", 12300));
	assert(size(l) == 2);

	exchange(l, 0, 1);

	Offer* o1 = get(l, 0);
	Offer* o2 = get(l, 1);

	assert(strcmp(o1->type, "teren") == 0);
	assert(strcmp(o2->type, "casa") == 0);

	destroy(l);
}

void testRemove()
{
	MyListAgentie* l = createEmpty();
	add(l, createOffer("casa", 1234, "Cluj-Napoca", 150000));
	add(l, createOffer("cas", 1234, "Cluj-Napoca", 150000));
	ElemType ln = removeLast(l);
	destroyOffer(ln);
	assert(size(l) == 1);
	destroy(l);

}