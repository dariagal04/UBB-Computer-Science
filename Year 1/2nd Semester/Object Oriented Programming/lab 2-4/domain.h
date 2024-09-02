#pragma once
#include <string.h>
//#include "domain.c"
typedef struct {
	char *surname;
	char *name;
	int scor;
}Participant;

/// <summary>
/// functie care creeaza participant
/// </summary>
/// <param name="surname"></param>
/// <param name="name"></param>
/// <param name="scor"></param>
/// <returns></returns>
Participant* createParticipant(char* surname, char* name, int scor);

/// <summary>
/// functie care distruge participant
/// </summary>
/// <param name="p"></param>
void destroyParticipant(Participant* p);

/// <summary>
/// functie care valideaza participant
/// </summary>
/// <param name="surname"></param>
/// <param name="name"></param>
/// <param name="scor"></param>
/// <returns></returns>
int validateParticipant(Participant*);

/// <summary>
/// functie care testeaza validarea participantului
/// </summary>
/// <param name="surname"></param>
/// <param name="name"></param>
/// <param name="scor"></param>
/// <returns></returns>
void testValidate();

/// <summary>
/// functie care testeaza creearea si dstrugerea participantului
/// </summary>
/// <param name="surname"></param>
/// <param name="name"></param>
/// <param name="scor"></param>
/// <returns></returns>
void testCreateDestroy();

void testgetnumeprenscor();