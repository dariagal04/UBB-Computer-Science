#pragma warning(disable : 4996)

#include "UI.h"
#include "service.h"
//#include "domain.h"
//#include "MyList.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <assert.h>


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
}

void add_Part(MyList* le)
{
	printf("surname: ");
	char surname[15];
	scanf_s("%s", surname, 15);
	printf("name: ");
	char name[15];
	scanf_s("%s", name, 15);
	printf("scor: ");
	int scor;
	scanf_s("%d", &scor);
	int error = addParticipant(le,surname, name, scor);
	if (error != 0)
		printf("Invalid p!\n");
	else
		printf("p added!\n");
}

void del_Part(MyList* le)
{
	/*
	printf("position: ");
	int poz = scanf_s("%d", &poz);
	int error = delParticipant(le, poz);
	if (error == 0)
		printf("p deleted\n");
	else
		printf("p not deleted!\n");*/

	printf("surname: ");  
	char surname[15]; 
	scanf_s("%s", surname, 15); 
	printf("name: "); 
	char name[15]; 
	scanf_s("%s", name, 15);  
	printf("scor: "); 
	int scor; 
	scanf_s("%d", &scor);

	int invalid = 0;
	int ok = findPart(le, surname, name, scor, &invalid);

	if (invalid == 1)
		printf("Invalid participant!\n");
	else
	{
		if (ok == -1)
			printf("The participant does not exist!\n");
		else
		{
			delParticipant(le, ok);
			printf("Participant deleted!\n");
		}
	}
}

void update_Part(MyList* l)
{
	printf("surname: ");
	char surname[15];
	scanf_s("%s", surname, 15);
	printf("name: ");
	char name[15];
	scanf_s("%s", name, 15);
	printf("scor: ");
	int scor;
	scanf_s("%d", &scor);

	int invalid = 0;
	int ok = findPart(l,surname, name, scor, &invalid);

	if (invalid == 1)
		printf("Invalid participant!\n");
	else
	{
		if (ok == -1)
			printf("The participant does not exist!\n");
		else
		{
			printf("Participant found. Enter the modifications or -1 if you do not wish to modify the requested argument.\n");
			printf("New surname: ");
			scanf_s("%s", surname, 15);
			printf("New name: ");
			scanf_s("%s", name, 15);
			printf("New scor: ");
			scanf_s("%d", &scor);

			int error = updatePart(l, surname, name, scor, ok);
			if (error != 0)
				printf("Invalid participant!\n");
			else
				printf("Participant updated!\n");
		}
	}
}
/*
void run()
{
	MyList* part = createEmpty();
	int ruleaza = 1;
	while (ruleaza)
	{
		printf("1. Add\n2. Delete\n3. Update\n4. Filter scor\n5. Sort\n0. Exit\nCommand: ");
		int cmd = 0;
		scanf_s("%d", &cmd);
		if (cmd == 1)
		{
			add_Part(part);
			displayList(part);
		}
		else if (cmd == 2)
		{
			del_Part(part);
			displayList(part);
		}
		else if (cmd == 3)
		{
			update_Part(part);
			displayList(part);
		}
		else if (cmd == 4)
		{
			printf("score: ");
			int filtered;
			scanf_s("%d", &filtered);
			MyList* filteredL = filter(part, filtered);
			displayList(filteredL);
			destroy(filteredL);
		}
		else if (cmd == 5)
		{
			MyList* sortedL = sortP(part);
			displayList(sortedL);
			destroy(sortedL);
		}
		else if (cmd == 0)
		{
			printf("programul s a incheiat!!");
			ruleaza = 0;
		}
		else
			printf("Comanda invalida!");
	}
}
*/