#include "MyList.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

int addParticipant(MyList* le, char* surname, char* name, int scor)
{
	Participant* p = createParticipant(surname, name, scor);
	int valid = validateParticipant(p);
	if (valid != 0)
	{
		destroyParticipant(p);
		return valid;
	}
	add(le, p);
	return 0;
}

int findPart(MyList* l, char* surname, char* name)
{
		for (int i = 0; i < size(l); i++)
		{
			if (strcmp(get(l, i)->surname, surname) == 0 && strcmp(get(l, i)->name, name) == 0) //&& (get(l, i)->scor - scor < 0.0000001))
			{
				return i;
			}
		}
	return -1;
}

int updatePart(MyList* l, char* surname, char* name, int scor, int poz)
{
	if (poz>=0&&poz<size(l))
	{
			Participant* up = createParticipant(surname, name, scor);
			update(l, poz, up);
			return 0;
	}
	return -1;
}



MyList* filter(MyList* l,int filter) {
	if (filter == 10)
	{
		return copyList(l);
	}
	MyList* filtered = createEmpty();
	for (int i = 0; i < size(l); ++i) {
		Participant* p = get(l, i);
		if (p->scor <= filter)
		{
			add(filtered, createParticipant(p->surname, p->name, p->scor));
		}
	}
	return filtered;
}

MyList* sortP(MyList* list) {
	// Sort participants in descending order based on score using selection sort
	
	for (int i = 0; i < size(list) - 1; i++) {
		int maxIndex = i;
		for (int j = i + 1; j < size(list); j++) {
			if (list->elem[j]->scor > list->elem[maxIndex]->scor) {
				maxIndex = j;
			}
		}
		if (maxIndex != i) {
			// Swap participants at position i and maxIndex
			Participant* temp = list->elem[i];
			list->elem[i] = list->elem[maxIndex];
			list->elem[maxIndex] = temp;
		}
	}
	for (int i = 0; i < size(list) - 1; ++i) {
		for (int j = 0; j < size(list) - i - 1; ++j) {
			if (strcmp(list->elem[j]->name, list->elem[j + 1]->name) > 0) {
				Participant* temp = list->elem[j];
				list->elem[j] = list->elem[j + 1];
				list->elem[j + 1] = temp;
			}
		}
	}
	return list;
}

/*
MyList* sortPn(MyList* list) {
	for (int i = 0; i < size(list) - 1; ++i) {
		for (int j = 0; j < size(list) - i - 1; ++j) {
			if (strcmp(list->elem[j]->name, list->elem[j + 1]->name) > 0) {
				Participant* temp = list->elem[j];
				list->elem[j] = list->elem[j + 1];
				list->elem[j + 1] = temp;
			}
		}
	}
	return list;
}
*/

int delParticipant(MyList* le, int poz)
{
	/*
	if (le->len <= poz)
		return 1;
	del(le, poz);
	return 0;
	*/
	if (poz < le->len && poz>=0)
	{
		Participant* del_p = get(le, poz);
		del(le, poz);
		destroyParticipant(del_p);
		return 0;}
	else return 1;
}

void testAddPDelP()
{
	MyList* l = createEmpty();
	assert(addParticipant(l, "gal", "daria", 10) == 0);
	assert(addParticipant(l, "", "daria", 10) == 1);
	assert(addParticipant(l, "gal", "", 10) == 2);
	assert(addParticipant(l, "gal", "daria", -10) == 3);
	add(l, createParticipant("Gal", "Daria", 10));
	assert(delParticipant(l, 0) == 0);
	assert(delParticipant(l, 13) == 1);
	destroy(l);
}

void testfindPart()
{
	MyList* le = createEmpty();
	add(le, createParticipant("gal", "daria", 10));
	assert(findPart(le, "gal", "daria") == 0);
	assert(findPart(le, "gall", "daria") == -1);
	assert(findPart(le, "", "daria") == -1);
	destroy(le);
}

void testUpdateP()
{
	//Participant* p = createParticipant("gal", "daria", 10);
	MyList* le = createEmpty(); 
	add(le, createParticipant("gal", "daria", 10));
	updatePart(le, "keresztesi", "daria", 10, 0);
	Participant* p1 = get(le, 0);
	assert(strcmp(p1->surname, "keresztesi") == 0);
	assert(strcmp(p1->name, "daria") == 0);
	assert(p1->scor == 10);
	assert(updatePart(le, "-1", "-1", -1, -1)==-1);
	/*Participant* p2 = get(le, 0);
	assert(strcmp(p2->surname, "keresztesi") == 0); 
	assert(strcmp(p2->name, "daria") == 0); 
	assert(get(le, 0)->scor == 10); */
	/*int v = updatePart(le, "", "-1", -1, 0);
	assert(v == 1);*/
	destroy(le);


}

void testfilter()
{
	MyList* l = createEmpty();
	add(l, createParticipant("g", "d", 5));
	add(l, createParticipant("d", "g", 10));
	MyList* filtered = filter(l, 7), * filtered2 = filter(l, 10);
	assert(size(filtered) == 1);
	assert(size(filtered2) == 2);
	destroy(l);
	destroy(filtered);
	destroy(filtered2);

}

void testsorted()
{
	MyList* l = createEmpty(); 
	add(l, createParticipant("g", "d", 5)); 
	add(l, createParticipant("d", "g", 10));
	MyList* sorted = sortP(l);
	assert(get(sorted, 0)->scor == 5);
	assert(get(sorted, 1)->scor == 10);
	destroy(l);  
}

/*
void testsorted2()
{
	MyList* l = createEmpty(); 
	add(l, createParticipant("b", "b", 5));
	add(l, createParticipant("a", "a", 10));
	MyList* sorted = sortPn(l); 
	assert(strcmp(get(sorted, 0)->name, "a") == 0);
	assert(strcmp(get(sorted, 1)->name, "b") == 0);
	destroy(l); 
	destroy(sorted); 
}*/