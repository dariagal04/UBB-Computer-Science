#pragma once

#include "MyListAgentie.h"

typedef struct service {
    MyListAgentie* undolist;
    MyListAgentie* lista;
}Service;

Service createService();

void destroyService(Service* l);
/*
* Add an offer to the agency
*/
int addOffer(Service* l, char* type, double surface, char* address, double price);

/*
* Find thhe position of a given offer in the agency
*/
int findOffer(Service* l, char* type, double surface, char* address, double price, int* invalid);

/*
* Delete an offer from the agency
*/
int deleteOffer(Service* l, int poz);

/*
* Update an offer from the agency
*/
int updateOffer(Service* l, char* type, double surface, char* address, double price, int poz);

/*
* Compares the type of two offers
*/
int cmpType(Offer* o1, Offer* o2);

/*
* Compares te price of two offers
*/
int cmpPrice(Offer* o1, Offer* o2);

/*
* Returns the ascendent sorted list
*/
MyListAgentie* sortedAscOffers(MyListAgentie* l);//, char cmpType, double cmpPrice);

/*
* Returns the descendent sorted list
*/
MyListAgentie* sortedDescOffers(MyListAgentie* l);//, char cmpType, double cmpPrice);

/*
* Filter offers in the agency
* typeSubstring - cstring
* return all offers where typeSubstring is a substring of the type
*/
MyListAgentie* filterType(Service* l, char* typeSubstring);


/*
* Filter offers by price in the agency
* nr - integer
* return all offers where the price equals nr
*/
MyListAgentie* filterPrice(Service* l, double nr);

/*
* Filter offers by surface in the agency
* nr - double
* return all offers where surface is nr
*/
MyListAgentie* filterSurface(Service* l, double nr);

int service_undo(Service* service);

void testAddOffer();

void testFindOffer();

void testDeleteOffer();

void testUpdateOffer();

void testfilterType();

void testfilterPrice();

void testfilterSurface();

void testcmpType();

void testcmpPrice();

void testsortedAscOffers();

void testsortedDescOffers();

void testUndo();