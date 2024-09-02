#include "MyList.h"
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

MyList* createEmpty()
{
	MyList* le = (MyList*)malloc(sizeof(MyList)); // Allocate memory for MyList
	
	if (le != NULL) {
		le->capacitate = 1;
		le->elem = (ElemType*)malloc(sizeof(Participant) * le->capacitate);
		le->len = 0;
		
	}
	return le;
	
}

/*
void displayList(MyList* le)
{
	printf("Lista de participanti:\n");
	for (int i = 0; i < le->len; i++) {
		ElemType participant = le->elem[i];
		printf("Participant %d:\n", i + 1);
		printf("Nume: %s ", participant->surname); 
		printf("Prenume: %s ", participant->name);
		printf("Scor: %d ", participant->scor);
		printf("\n");
	}
}*/
void destroy(MyList* le)
{
	for (int i = 0; i < le->len; i++)
	{
		Participant* p = get(le, i);
		destroyParticipant(p); 
	}
	le->len = 0;
	free(le->elem);
	free(le);
}

ElemType get(MyList* le, int poz) {
	/*
	if (poz < 0 || poz >= le->len) {
		//printf("Index out of bounds!\n");
		//exit(EXIT_FAILURE);
		exit(1);
	}
	*/
	return le->elem[poz];
}

/*
MyList copyList(MyList* l)
{
	MyList le = createEmpty();
	for (int i = 0; i < size(l); i++)
	{
		ElemType p = get(l, i);
		Participant p2 = createParticipant(p->surname, p->name, p->scor);
		add(&le, &p2);
	}
	return le;
}
*/

MyList* copyList(MyList* le)
{
	MyList* newList = createEmpty();
	for (int i = 0; i < le->len; i++)
	{
		ElemType el = le->elem[i];
		add(newList, createParticipant(el->surname, el->name, el->scor));
	}
	return newList;
}


/*
ElemType get(MyList* le, int poz)
{
	return le->elem[poz];
}
*/
void add(MyList* le, ElemType el)
{
	if (le->capacitate == le->len)
	{
		//alocam spatiu mai mare
		int newCapacity = le->capacitate * 2;
		ElemType* aux = (ElemType*)malloc(sizeof(ElemType) * newCapacity);
		if (aux != NULL) 
		{
			for (int i = 0; i < le->len; i++)
				aux[i] = le->elem[i];
		}
		free(le->elem);
		le->elem = aux;
		le->capacitate = newCapacity;
	}
	if (le->elem != NULL)
	{
		le->elem[le->len] = el;
		le->len++;
	}
	//free(le->elem);
}

int size(MyList* le)
{
	return le->len;
}

void del(MyList* le, int poz)
{
	for (int i = poz; i < le->len-1; i++)
		le->elem[i] = le->elem[i + 1];
	le->len--;
}

void update(MyList* le, int poz, ElemType el)
{
	Participant* copy_p = le->elem[poz];
	le->elem[poz] = el;
	destroyParticipant(copy_p);
}


void testcreateEmptyDestroy()
{
	MyList* l = createEmpty();
	assert(size(l) == 0);
	destroy(l);
	//assert(size(l) == 0);
	Participant* p = createParticipant("gal", "daria", 10);// * p2 = createParticipant("gall", "darria", 9), * p3 = createParticipant("gl", "daia", 8);
	MyList* le = createEmpty();
	add(le, p);
	assert(size(le) == 1);
	//add(le, p2);
	//add(le, p3);
	destroy(le); // Eliberează memoria alocată pentru lista și toți participanții din listă


	// Eliberarea memoriei pentru participanții care nu au fost adăugați la listă
	//destroyParticipant(p);
	//destroyParticipant(p2);
	//destroyParticipant(p3);
}
/*
void testcreateEmptyDestroy()
{
	MyList* l = createEmpty();
	assert(size(l) == 0);
	Participant* p = createParticipant("gal", "daria", 10), * p2 = createParticipant("gall", "darria", 9), * p3 = createParticipant("gl", "daia", 8);
	add(l,p);
	assert(size(l) == 1);
	add(l, p2);
	add(l, p3);
	destroy(l);
	destroyParticipant(p); destroyParticipant(p2); destroyParticipant(p3);
	assert(size(l) == 0);
	Participant* p4 = createParticipant("gal", "daria", 10);
	add(l, p4);
	del(l, 0);
	assert(size(l) == 0);
	destroyParticipant(p4);
	//destroy(l);


}*/


void testcopyList()
{
	MyList* l = createEmpty();
	add(l, createParticipant("a", "b", 10));
	add(l, createParticipant("a2", "b2", 20)); 
	MyList* l2 = copyList(l);
	assert(size(l2) == 2);
	assert(strcmp(get(l2, 0)->surname, "a") == 0);
	destroy(l);
	destroy(l2);
	//destroyParticipant(ptr_p);
}



void testUpdate()
{
	MyList* l = createEmpty();
	//Participant* p = createParticipant("Gal", "Daria", 10);
	add(l, createParticipant("Gal", "Daria", 10));
	assert(size(l) == 1);
    Participant* o = createParticipant("Keresztesi", "Daria", 10);
	update(l, 0, o);
	Participant* el = get(l, 0);
	assert(strcmp(o->surname, el->surname) == 0);
	assert(strcmp(o->name, el->name) == 0);
	assert(o->scor == el->scor);
	destroy(l);
}