#include "Agentie.h"

#include<string.h>
#include<assert.h>
#include<stdlib.h>

/*
* Create a new offer
*/

Offer* createOffer(char* type, double surface, char* address, double price)
{
	Offer* rez = (Offer*)malloc(sizeof(Offer));
	if (rez != NULL) {
		size_t nrcType = strlen(type) + 1;
		rez->type = malloc(nrcType * sizeof(char));
		if (rez->type != NULL)
			strcpy_s(rez->type, nrcType, type);

		rez->surface = surface;

		size_t nrcAddress = strlen(address) + 1;
		rez->address = malloc(nrcAddress * sizeof(char));
		if (rez->address != NULL)
			strcpy_s(rez->address, nrcAddress, address);

		rez->price = price;
	}

	return rez;
}

/*
* Create a copy of an offer
*/
Offer* copyOffer(Offer* o)
{
	return createOffer(o->type, o->surface, o->address, o->price);
}

/*
* Dealocate memory occupied by offer
*/
void destroyOffer(Offer* o)
{
	free(o->type);
 	free(o->address);
	o->surface = o->price = -1;
	free(o);
}
/*
* Validate an offer
*/
int valideaza(Offer* o)
{
	if (strlen(o->type) == 0)
		return 1;
	if (o->surface < 0)
		return 2;
	if (strlen(o->address) == 0)
		return 3;
	if (o->price < 0)
		return 4;
	return 0;
}

void testCreateDestroy()
{
	Offer* o = createOffer("teren", 1234, "Oradea", 12000);
	assert(strcmp(o->type, "teren") == 0);
	assert(o->surface == 1234.0);
	assert(strcmp(o->address, "Oradea") == 0);
	assert(o->price == 12000.0);

	destroyOffer(o);
	//assert(o->surface == -1);
	//assert(o->price == -1);
}

void test_valideaza()
{
	Offer* o = createOffer("", 111, "Cluj", 12);
	assert(valideaza(o) == 1);
	destroyOffer(o);

	o = createOffer("casa", -2, "arad", 111);
	assert(valideaza(o) == 2);
	destroyOffer(o);

	o = createOffer("teren", 1111, "", 12);
	assert(valideaza(o) == 3);
	destroyOffer(o);

	o = createOffer("teren", 12, "Oradea", -6);
	assert(valideaza(o) == 4);
	destroyOffer(o);
}

void testCopyOffer()
{
	Offer* o = createOffer("casa", 111, "Cluj", 12);
	Offer* o1 = copyOffer(o);

	assert(strcmp(o1->type, "casa") == 0);
	assert(o1->surface == 111);
	assert(strcmp(o1->address, "Cluj") == 0);
	assert(o1->price == 12);

	destroyOffer(o);
	destroyOffer(o1);
}