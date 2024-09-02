#pragma once
#include "MyList.h"

/// <summary>
/// functie care adauga participant in lista
/// </summary>
/// <param name="surname"></param>
/// <param name="name"></param>
/// <param name="scor"></param>
/// <returns></returns>
int addParticipant(MyList* le, char* surname, char* name, int scor);

/// <summary>
/// functie care sterge participant din lista
/// </summary>
/// <param name="surname"></param>
/// <param name="name"></param>
/// <param name="scor"></param>
/// <returns></returns>
int delParticipant(MyList* le, int poz);

/// <summary>
/// functie care testeaza adaugarea participantului in lista
/// </summary>
/// <param name="surname"></param>
/// <param name="name"></param>
/// <param name="scor"></param>
/// <returns></returns>
void testAddPDelP();


/// <summary>
/// functie care cauta un participant
/// </summary>
/// <param name="surname"></param>
/// <param name="name"></param>
/// <param name="scor"></param>
/// <returns></returns>
int findPart(MyList* l, char* surname, char* name, int scor, int* invalid);


/// <summary>
/// functie care schimba un participant
/// </summary>
/// <param name="surname"></param>
/// <param name="name"></param>
/// <param name="scor"></param>
/// <returns></returns>
int updatePart(MyList* l, char* surname, char* name, int scor, int poz);

void testfindPart();

void testUpdateP();

MyList* filter(MyList* l, int filter);

void testfilter();

MyList* sortP(MyList* l);

void testsorted();

MyList* sortPn(MyList* l);

void testsorted2();