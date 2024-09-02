#pragma once

typedef struct {
	char* type;
	double surface;
	char* address;
	double price;
}Offer;

/*
* Create a new offer
*/
Offer* createOffer(char* type, double surface, char* address, double price); 

/*
* Create a copy of an offer
*/
Offer* copyOffer(Offer* o);

/*
* Dealocate memory occupied by offer
*/

void destroyOffer(Offer* o);

void testCreateDestroy();

/*
* Validate an offer
*/
int valideaza(Offer* o);

void test_valideaza();

void testCopyOffer();

