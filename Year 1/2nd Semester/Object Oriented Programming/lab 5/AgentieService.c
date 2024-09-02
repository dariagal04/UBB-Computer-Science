#include "AgentieService.h"

#include<string.h>
#include<assert.h>
#include<stdlib.h>



Service createService() {
	Service service;
	service.undolist = createEmpty();
	service.lista = createEmpty();
	return service;
}
/*
 * distruge service-ul
 */
void destroyService(Service* service) {
	destroy(service->lista);
	distrugeListaDeListe(service->undolist);
}

/*
* Add an offer to the agency
*/
int addOffer(Service* l, char* type, double surface, char* address, double price)
{
	Offer* o = createOffer(type, surface, address, price);
	
	int valid = valideaza(o);
	if (valid != 0)
	{
		destroyOffer(o);
		return valid;
	}
	MyListAgentie* toUndo = copyList(l->lista);
	add(l->lista, o);
	add(l->undolist, toUndo);
	return 0;
}

/*
* Find the position of a specified offer
*/
int findOffer(Service* l, char* type, double surface, char* address, double price, int* invalid)
{
	Offer* o = createOffer(type, surface, address, price);
	int valid = valideaza(o);
	//if (valid != 0)
		//*invalid = 1;
	//else
	//{
		for (int i = 0; i < size(l->lista); i++)
		{
			Offer* el = get(l->lista, i);
			if (strcmp(el->type, type) == 0 && (el->surface - surface < 0.0000001) && strcmp(el->address, address) == 0 && (el->price - price < 0.0000001))
			{
				destroyOffer(o);
				return i;
			}
		}
	//}
	destroyOffer(o);
	return -1;
}

/*
* Delete an offer from the agency
*/
//int deleteOffer(Service* l, int poz)
//{
//	MyListAgentie* toUndo = copyList( copyList(l->lista));
//	delete(l->lista, poz);
//	add(l->undolist, toUndo);
//	return 0;
//}

int deleteOffer(Service* l, int poz) {
	//MyListAgentie* lung = l->lista;
	if (poz < 0 || poz >= size(l->lista))
		return 1;
	MyListAgentie* toUndo = copyList(l->lista);
	add(l->undolist, toUndo);
	Offer* t = delete(l->lista, poz);
	destroyOffer(t);
	return 0;
}

/*
* Update an offer from the agency
*/
int updateOffer(Service* l, char* type, double surface, char* address, double price, int poz)
{
	//Offer* o = get(l->lista, poz);

	/*if (strcmp(type, "-1") == 0)
		type = o->type;
	if (surface == -1)
		surface = o->surface;
	if (strcmp(address, "-1") == 0)
		address = o->address;
	if (price == -1)
		price = o->price;*/
	if (poz < 0 || poz >= size(l->lista))
		return -1;
	Offer* new_o = createOffer(type, surface, address, price);
	int valid = valideaza(new_o);
	if (valid)
	{
		destroyOffer(new_o);
		return valid;
	}
	MyListAgentie* toUndo = copyList(l->lista);
	add(l->undolist, toUndo);
	update(l->lista, poz, new_o);
	return 0;
}

/*
* Compares the type of two offers
*/
int cmpType(Offer* o1, Offer* o2)
{
	return strcmp(o1->type, o2->type);
}

/*
* Compares te price of two offers
*/
int cmpPrice(Offer* o1, Offer* o2)
{
	if (o1->price > o2->price)
		return 1;
	else if (o1->price == o2->price)
		return 0;
	return -1;
}

/*
* Returns the ascendent sorted list
*/
MyListAgentie* sortedAscOffers(MyListAgentie* l)//, FctCmp cmpType, FctCmp cmpPrice)
{
	MyListAgentie* l_sorted = copyList(l);
	for (int i = 0; i < size(l_sorted) - 1; i++)
		for (int j = i + 1; j < size(l_sorted); j++)
			if (cmpPrice(l_sorted->elems[i], l_sorted->elems[j]) == 1)
				exchange(l_sorted, i, j);
			else if (cmpPrice(l_sorted->elems[i], l_sorted->elems[j]) == 0)
			{
				if (cmpType(l_sorted->elems[i], l_sorted->elems[j]) > 0)
					exchange(l_sorted, i, j);
			}
	return l_sorted;
}

/*
* Returns the descendent sorted list
*/
MyListAgentie* sortedDescOffers(MyListAgentie* l)//, FctCmp cmpType, FctCmp cmpPrice)
{
	MyListAgentie* l_sorted = copyList(l);
	for (int i = 0; i < size(l_sorted) - 1; i++)
		for (int j = i + 1; j < size(l_sorted); j++)
			if (cmpPrice(l_sorted->elems[i], l_sorted->elems[j]) == -1)
				exchange(l_sorted, i, j);
			else if (cmpPrice(l_sorted->elems[i], l_sorted->elems[j]) == 0)
			{
				if (cmpType(l_sorted->elems[i], l_sorted->elems[j]) < 0)
					exchange(l_sorted, i, j);
			}

	return l_sorted;
}


/*
* Filter offers by type in the agency
* typeSubstring - cstring
* return all offers where typeSubstring is a substring of the type
*/
MyListAgentie* filterType(Service* l, char* typeSubstring)
{
	//if (typeSubstring == NULL || strlen(typeSubstring) == 0) 
		//return copyList(l->lista); 
	MyListAgentie* rez = createEmpty();
	for (int i = 0; i < size(l->lista); i++)
	{
		Offer* o = get(l->lista, i);
		if (strstr(o->type, typeSubstring) != NULL)
			add(rez, copyOffer(o));
	}
	return rez;
}


/*
* Filter offers by price in the agency
* nr - integer
* return all offers where the price equals nr
*/
MyListAgentie* filterPrice(Service* l, double nr)
{
	MyListAgentie* rez = createEmpty();
	for (int i = 0; i < size(l->lista); i++)
	{
		Offer* o = get(l->lista, i);
		if (o->price == nr)
			add(rez, copyOffer(o));
	}
	return rez;
}

/*
* Filter offers by surface in the agency
* nr - double
* return all offers where surface equals nr
*/
MyListAgentie* filterSurface(Service* l, double nr)
{
	MyListAgentie* rez = createEmpty();
	for (int i = 0; i < size(l->lista); i++)
	{
		Offer* o = get(l->lista, i);
		if (o->surface == nr)
			add(rez, copyOffer(o));
	}
	return rez;
}

int service_undo(Service* store)
{
	if (store->undolist->lg == 0)
		return 0;
	MyListAgentie* l = delete(store->undolist, store->undolist->lg - 1);
	destroy(store->lista);
	store->lista = l;
	return 1;
}


void testAddOffer() {
	Service service = createService();
	assert(addOffer(&service, "house", 100.0, "Main Street", 500000) == 0);
	assert(size(service.lista) == 1);
	assert(size(service.undolist) == 1);
	destroyService(&service);
}

void testFindOffer() {
	Service service = createService();
	int invalid = 0;
	addOffer(&service, "house", 100.0, "Main Street", 500000);
	int position = findOffer(&service, "house", 100.0, "Main Street", 500000, &invalid);
	assert(position == 0);
	assert(invalid == 0);
	position = findOffer(&service, "apartment", 50.0, "Second Street", 200000, &invalid);
	assert(position == -1);
	assert(invalid == 0);
	destroyService(&service);
}

void testDeleteOffer() {
	Service service = createService();
	int err = deleteOffer(&service, -1);
	assert(err == 1);
	addOffer(&service, "house", 100.0, "Main Street", 500000);
	assert(deleteOffer(&service, 0) == 0);
	assert(size(service.lista) == 0);
	//assert(size(service.undolist) == 1);
	destroyService(&service);
}

void testUpdateOffer() {
	Service service = createService();
	assert(updateOffer(&service, "apartment", 50.0, "Second Street", 250000, 0) == -1);
	addOffer(&service, "house", 100.0, "Main Street", 500000);
	assert(updateOffer(&service, "apartment", 50.0, "Second Street", 250000, 0) == 0);
	//Offer* updatedOffer = get(service.lista, 0);
	assert(strcmp(((Offer*)get(service.lista, 0))->type, "apartment") == 0);
	assert(((Offer*)get(service.lista, 0))->surface == 50.0);
	assert(strcmp(((Offer*)get(service.lista, 0))->address, "Second Street") == 0);
	assert(((Offer*)get(service.lista, 0))->price == 250000);
	destroyService(&service);
}

void testUndo() {
	Service service = createService();
	int err = service_undo(&service);
	assert(err == 0);
	addOffer(&service, "house", 100.0, "Main Street", 500000);
	service_undo(&service);
	assert(size(service.lista) == 0);
	assert(size(service.undolist) == 0);
	destroyService(&service);
}


void testfilterType() {
	Service service = createService();
	addOffer(&service, "house", 100.0, "Main Street", 500000);
	addOffer(&service, "apartment", 50.0, "Second Street", 200000);
	addOffer(&service, "house", 150.0, "Third Street", 600000);

	MyListAgentie* filteredList = filterType(&service, "house");
	assert(size(filteredList) == 2);
	destroy(filteredList);

	filteredList = filterType(&service, "apartment");
	assert(size(filteredList) == 1);
	destroy(filteredList);

	filteredList = filterType(&service, "villa");
	assert(size(filteredList) == 0);
	destroy(filteredList);

	destroyService(&service);
}

void testfilterPrice() {
	Service service = createService();
	addOffer(&service, "house", 100.0, "Main Street", 500000);
	addOffer(&service, "apartment", 50.0, "Second Street", 200000);
	addOffer(&service, "house", 150.0, "Third Street", 600000);

	MyListAgentie* filteredList = filterPrice(&service, 500000);
	assert(size(filteredList) == 1);
	destroy(filteredList);

	filteredList = filterPrice(&service, 200000);
	assert(size(filteredList) == 1);
	destroy(filteredList);

	filteredList = filterPrice(&service, 700000);
	assert(size(filteredList) == 0);
	destroy(filteredList);

	destroyService(&service);
}

void testfilterSurface() {
	Service service = createService();
	addOffer(&service, "house", 100.0, "Main Street", 500000);
	addOffer(&service, "apartment", 50.0, "Second Street", 200000);
	addOffer(&service, "house", 150.0, "Third Street", 600000);

	MyListAgentie* filteredList = filterSurface(&service, 100.0);
	assert(size(filteredList) == 1);
	destroy(filteredList);

	filteredList = filterSurface(&service, 50.0);
	assert(size(filteredList) == 1);
	destroy(filteredList);

	filteredList = filterSurface(&service, 200.0);
	assert(size(filteredList) == 0);
	destroy(filteredList);

	destroyService(&service);
}

void testcmpType() {
	Offer* o1 = createOffer("house", 100.0, "Main Street", 500000);
	Offer* o2 = createOffer("apartment", 50.0, "Second Street", 200000);

	assert(cmpType(o1, o2) > 0);
	assert(cmpType(o2, o1) < 0);
	assert(cmpType(o1, o1) == 0);

	destroyOffer(o1);
	destroyOffer(o2);
}

void testcmpPrice() {
	Offer* o1 = createOffer("house", 100.0, "Main Street", 500000);
	Offer* o2 = createOffer("apartment", 50.0, "Second Street", 200000);

	assert(cmpPrice(o1, o2) > 0);
	assert(cmpPrice(o2, o1) < 0);
	assert(cmpPrice(o1, o1) == 0);

	destroyOffer(o1);
	destroyOffer(o2);
}


void testsortedAscOffers()
{
	MyListAgentie* l = createEmpty();

	add(l, createOffer("b", 122, "oradea", 123455));
	//assert(error == 0);

	add(l, createOffer("b", 15, "arad", 11));
	//assert(error == 0);

	add(l, createOffer("a", 12, "cluj", 11));

	MyListAgentie* sorted_l = sortedAscOffers(l);//, cmptype, cmpprice);

	Offer* o1 = get(sorted_l, 0);
	Offer* o2 = get(sorted_l, 1);
	Offer* o3 = get(sorted_l, 2);

	assert(strcmp(o1->type, "a") == 0);
	assert(strcmp(o2->type, "b") == 0);
	assert(strcmp(o3->type, "b") == 0);

	assert(o1->price == 11);
	assert(o2->price == 11);
	assert(o3->price == 123455);

	destroy(l);
	destroy(sorted_l);

}


void testsortedDescOffers()
{
	MyListAgentie* l = createEmpty();

	add(l, createOffer("b", 122, "oradea", 123455));
	//assert(error == 0);

	add(l, createOffer("b", 15, "arad", 11));
	//assert(error == 0);

	add(l, createOffer("a", 12, "cluj", 11));

	MyListAgentie* sorted_l = sortedDescOffers(l);//, cmptype, cmpprice);

	Offer* o1 = get(sorted_l, 0);
	Offer* o2 = get(sorted_l, 1);
	Offer* o3 = get(sorted_l, 2);

	assert(strcmp(o1->type, "b") == 0);
	assert(strcmp(o2->type, "b") == 0);
	assert(strcmp(o3->type, "a") == 0);

	assert(o1->price == 123455);
	assert(o2->price == 11);
	assert(o3->price == 11);

	destroy(l);
	destroy(sorted_l);

}
