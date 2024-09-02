#include "domain.h"
#include "tests.h"
#include "service.h"
#include "repository.h"
#include "CosFilme.h"
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <QtWidgets/qapplication.h>
#include<QtWidgets/qlabel.h>
#include"FilmGUI.h"


void testall()
{
	testRepo();
	testGetTitlu();
	testGetGen();
	testGetAn();
	testGetActor();
	testAdd();
	testCauta();
	testModifica();
	testSterge();
	testFiltrareAn();
	testFiltrareTitlu();
	testSortare();
	testCosAdauga();
	testCosAdaugaRandom();
	testCosSterge();
	testCosExport();
	testRaport();
	testCautaTitlu();
	testFisier();
	testUndo();
}


int main(int argc, char* argv[])
{
	testall();

	string filename = "D:/dari/an1sem2/OOP/filme.txt";

	QApplication a(argc, argv);
	FilmRepoFile rep{ filename };
	CosFilme cos;
	FilmService srv{ rep,cos };
	FilmGUI gui{ srv };
	gui.show();
	return a.exec();

}