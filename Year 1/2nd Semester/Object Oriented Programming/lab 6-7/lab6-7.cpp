#include "domain.h"
#include "tests.h"
#include "ui.h"
#include "service.h"
#include "repository.h"
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include "VectorDinamic.h"

void apel()
{
	LocatarRepo rep;
	LocatarService srv{ rep };
	UI ui{ srv };
	ui.startUI();
}

void testall()
{
	testRepo();
	testGetapartament();
	testGetproprietar();
	testGetsuprafata();
	testGettip();
	testAdd();
	testCauta();
	testModifica();
	testFiltrareTip();
	testFiltraresuprafata();
	testSortare();
	test_vector();
}

int main()
{
	testall();
	apel();
	_CrtDumpMemoryLeaks();

	return 0;
}

