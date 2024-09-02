#pragma once

#include "domain.h"
typedef Participant* ElemType;
typedef struct
{
	ElemType* elem;
	int len;
	int capacitate;
}MyList;


/// <summary>
/// functie care distruge participant
/// </summary>
/// <param name="surname"></param>
/// <param name="name"></param>
/// <param name="scor"></param>
/// <returns></returns>
MyList* createEmpty();


void testUpdate();

/// <summary>
/// functie care schimba un participant
/// </summary>
/// <param name="surname"></param>
/// <param name="name"></param>
/// <param name="scor"></param>
/// <returns></returns>
void update(MyList* le, int poz, ElemType el);

MyList* copyList(MyList* le);


/// <summary>
/// functie care distruge participant din lista
/// </summary>
/// <param name="surname"></param>
/// <param name="name"></param>
/// <param name="scor"></param>
/// <returns></returns>
void destroy(MyList* le);

ElemType get(MyList* le, int poz);


/// <summary>
/// functie care returneaza numarul participantilor
/// </summary>
/// <param name="surname"></param>
/// <param name="name"></param>
/// <param name="scor"></param>
/// <returns></returns>
int size(MyList* le);


/// <summary>
/// functie care adauga participant
/// </summary>
/// <param name="surname"></param>
/// <param name="name"></param>
/// <param name="scor"></param>
/// <returns></returns>
void add(MyList* le, ElemType el);

/// <summary>
/// functie care sterge participant
/// </summary>
/// <param name="surname"></param>
/// <param name="name"></param>
/// <param name="scor"></param>
/// <returns></returns>
void del(MyList* le, int poz);


/// <summary>
/// functie care testeaza creearea unei liste goale, distrugerea, adaugarea si stergerea
/// </summary>
/// <param name="surname"></param>
/// <param name="name"></param>
/// <param name="scor"></param>
/// <returns></returns>
void testcreateEmptyDestroy();

void testcopyList();

