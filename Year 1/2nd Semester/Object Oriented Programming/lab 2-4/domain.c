#include "domain.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>



char* get_nume(Participant* participant) {
	return participant->surname;
}

char* get_prenume(Participant* participant) {
	return participant->name;
}

int get_scor(Participant* participant) {
	return participant->scor;
}

Participant* createParticipant(char* surname, char* name, int scor)
{
	Participant* p = (Participant*)malloc(sizeof(Participant));
	//memset(p, 0, sizeof(Participant));
	if (p != NULL)
	{
		size_t nrc = strlen(surname) + 1;
		p->surname = malloc(nrc * sizeof(char));
		if (p->surname != NULL)
			strcpy_s(p->surname, nrc, surname);
		size_t nrc2 = strlen(name) + 1;
		p->name = malloc(nrc2 * sizeof(char));
		if (p->name != NULL)
			strcpy_s(p->name, nrc2, name);
		p->scor = scor;
	}
	return p;

}

void destroyParticipant(Participant* p)
{
	free(p->surname);
	free(p->name);
	p->scor = -1;
	//free(p->scor);
	free(p); 
	//p->surname[0] = '\0';
	//p->name[0] = '\0';
}

int validateParticipant(Participant* p)
{
	if (strlen(p->surname) == 0)
		return 1;
	if (strlen(p->name) == 0)
		return 2;
	if (p->scor < 0)
		return 3;
	return 0;
}
void testValidate()
{
	Participant* p = createParticipant("", "daria", 10);
	assert(validateParticipant(p) == 1);
	destroyParticipant(p);
	p = createParticipant("gal", "", 10);
	assert(validateParticipant(p) == 2);
	destroyParticipant(p);
	p = createParticipant("gal", "daria", -10);
	assert(validateParticipant(p) == 3);
	destroyParticipant(p);
	p = createParticipant("gal", "daria", 10);
	assert(validateParticipant(p) == 0);
	destroyParticipant(p);
}

void testCreateDestroy()
{
	Participant* p = createParticipant("gal", "daria", 10);
	assert(strcmp(p->surname, "gal") == 0);
	assert(strcmp(p->name, "daria") == 0);
	assert(p->scor == 10);
	destroyParticipant(p);
}

void testgetnumeprenscor()
{
	Participant* p = createParticipant("gal", "daria", 10);
	assert(strcmp(get_nume(p), "gal") == 0);
	assert(strcmp(get_prenume(p), "daria") == 0);
	assert(get_scor(p) == 10);
	destroyParticipant(p);
}