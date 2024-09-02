#pragma warning(disable : 4996)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include "domain.h"
#include "MyList.h"
#include "service.h"
#include "UI.h"

#include<stdio.h>
#include<stdlib.h>
#include<string.h>


void testAll()  
{
	testValidate();
	testCreateDestroy();
	testcreateEmptyDestroy(); 
	testAddPDelP();
	testcopyList();
	testUpdate();
	testgetnumeprenscor();
	testfindPart();
	testUpdateP();
	testfilter();
	testsorted();
}

void run()
{
	MyList* part = createEmpty();
	int ruleaza = 1;
	while (ruleaza)
	{
		printf("1. Add\n2. Delete\n3. Update\n4. Filter scor\n5. Sort name/scor\n0. Exit\nCommand: ");
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
		/*
		else if (cmd == 6)
		{
			MyList* sortedL = sortPn(part);
			displayList(sortedL); 
			destroy(sortedL); 
		}
		*/
		else if (cmd == 0)
		{
			printf("programul s a incheiat!!");
			ruleaza = 0;
		}
		else
			printf("Comanda invalida!");
	}
	destroy(part);
}

int main()
{
	testAll();
	run();  
	_CrtDumpMemoryLeaks();
	return 0;
}
