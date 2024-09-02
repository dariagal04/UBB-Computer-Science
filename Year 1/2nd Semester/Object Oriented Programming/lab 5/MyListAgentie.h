#pragma once

#include "Agentie.h"

typedef void* ElemType;

typedef struct {
	ElemType* elems;
	int lg;
	int cp;
}MyListAgentie;

/*
* Create an empty list
*/
MyListAgentie* createEmpty();

/*
* Destroy list
*/
void destroy(MyListAgentie* l);

/*
* Get an element from the list
* poz - position of the element, needs to be valid
* return element on the given position
*/
ElemType get(MyListAgentie* l, int poz);

/*
* Return number of elements in the list
*/
int size(MyListAgentie* l);

/*
* Add element to the list
* post: element is added to the end of the list
*/
void add(MyListAgentie* l, ElemType el);

/*
* Delete an element from the list
*/
ElemType delete(MyListAgentie* l, int poz);

/*
* Update an element from the list
*/
void update(MyListAgentie* l, int poz, ElemType el);

/*
* Make a shallow copy of the list
* return MyListAgentie containing the same elementa as l
*/
MyListAgentie* copyList(MyListAgentie* l);

/*
* Interchanges two offers from the agency
*/
void exchange(MyListAgentie* l, int i, int j);


ElemType removeLast(MyListAgentie* lista);
void distrugeListaDeListe(MyListAgentie* l);
void testCreateList();
void testIterateList();
void testCopyList();
void testGet();
void testSize();
void testAdd();
void testDelete();
void testUpdate();
void testExchange();
void testRemove();