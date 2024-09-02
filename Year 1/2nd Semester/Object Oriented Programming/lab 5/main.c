
#include "Agentie.h"
#include "MyListAgentie.h"
#include "AgentieService.h"
#include "UI.h"

#define _CRTDBG_MAP_ALLOC
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<crtdbg.h>

void test_all()
{
	testCreateDestroy();
	testCreateList();
	testIterateList();
	testCopyList();
	 testAddOffer();
	testFindOffer();
	testDeleteOffer();
	testUpdateOffer();
	testGet();
	testSize();
	testfilterType();
	testfilterPrice();
	testfilterSurface();
	testDelete();
	testAdd();
	testUpdate();
	test_valideaza();
	testExchange();
	testcmpPrice();
	testcmpType();
	testsortedDescOffers();
	testsortedAscOffers();
	testCopyOffer();
	testUndo();
	testRemove();
}

void run() 
{
	Service allOffers = createService();
	int ruleaza = 1;
	while (ruleaza)
	{
		printf("1. Add\n2. Filter\n3. All offers\n4. Delete\n5. Update\n6. Print ordered\n7. Exit\n8. Undo\n Command: ");
		int cmd = 0;
		int rez1 = scanf("%d", &cmd);
		if (rez1 != 1)
		{
			printf("Eroare la citire!\n\n");
			break;
		}
		if (cmd == 1)
			add_offer(&allOffers);
		else if (cmd == 2)
			filterOffers(&allOffers);
		else if (cmd == 3)
			printAllOffers(allOffers.lista);
		else if (cmd == 4)
			delete_offer(&allOffers);
		else if (cmd == 5)
			update_offer(&allOffers);
		else if (cmd == 6)
			print_ordered(allOffers.lista);
		else if (cmd == 7)
			ruleaza = 0;
		else if (cmd == 8)
			ui_undo(&allOffers);
		else
			printf("Comanda invalida!\n\n");
	}
	destroyService(&allOffers);
}

int main()
{
	test_all();
	run();
	_CrtDumpMemoryLeaks();
	return 0;
}