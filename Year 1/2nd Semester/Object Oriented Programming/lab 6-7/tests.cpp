#include "tests.h"
#include <assert.h>
#include "VectorDinamic.h"

void testRepo()
{
	LocatarRepo rep;
	Locatar f{ 1,"a",50,"garsoniera" };
	rep.adaugalocatar(f);
	const auto& filme = rep.getAll();
	assert(filme.size() == 1);
	rep.adaugalocatar({ 1,"a",50,"garsoniera" });
	rep.adaugalocatar({ 2,"b",50,"garsoniera" });
	rep.adaugalocatar({ 3,"c",50,"garsoniera" });
	rep.adaugalocatar({ 4,"d",50,"garsoniera" });
	assert(filme.size() == 5);
}

void testGetapartament()
{
	Locatar f{ 1,"a",50,"garsoniera" };
	assert(f.getApartament() == 1);

}

void testGetproprietar()
{
	Locatar f{ 1,"a",50,"garsoniera" };
	assert(f.getProprietar() == "a");

}

void testGetsuprafata()
{
	Locatar f{ 1,"a",50,"garsoniera" };
	assert(f.getSuprafata() == 50);
}

void testGettip()
{
	Locatar f{ 1,"a",50,"garsoniera" };
	assert(f.getTip() == "garsoniera");

}

void testAdd()
{
	LocatarRepo rep;
	LocatarService srv{ rep };
	srv.adauga(1, "a", 50, "garsoniera");
	const auto& bloc = srv.getAll();
	assert(bloc.size() == 1);

	try {
		srv.adauga(1, "", 50, "garsoniera");
		assert(false);
	}
	catch (RepoExceptions& ex) {
		assert(ex.getMesaj() == "Date invalide!\n\n");
		assert(true); // ma astept sa arunce exceptie
	}
	assert(bloc.size() == 1);
}

void testCauta()
{
	LocatarRepo rep;
	LocatarService srv{ rep };
	srv.adauga(1, "a", 50, "garsoniera");
	srv.adauga(2, "b", 50, "garsoniera");
	srv.adauga(3, "c", 50, "garsoniera");
	srv.adauga(4, "d", 50, "garsoniera");
	const auto& bloc = srv.getAll();
	assert(bloc.size() == 4);

	assert(srv.cauta(1, "a", 50, "garsoniera") == 0);

	try {
		srv.cauta(1, "", 50, "garsoniera");
		//assert(false);
	}
	catch (RepoExceptions& ex) {
		assert(ex.getMesaj() == "Date invalide!\n\n");
		assert(true); // ma astept sa arunce exceptie
	}
}

//void testSterge()
//{
//	LocatarRepo rep;
//	LocatarService srv{ rep };
//	srv.adauga(1, "a", 50, "garsoniera");
//	srv.adauga(2, "b", 50, "garsoniera");
//	srv.adauga(3, "c", 50, "garsoniera");
//	srv.adauga(4, "d", 50, "garsoniera");
//	const auto& bloc = srv.getAll();
//	assert(bloc.size() == 4);
//	assert(srv.sterge(2, "b", 50, "garsoniera") == 0);
//	srv.sterge(2, "b", 50, "garsoniera");
//	const auto& bloc1 = srv.getAll();
//	assert(bloc1.size() == 3);
//	//assert(srv.sterge(2, "b", 50, "garsoniera") == 1);
//
//	try {
//		srv.sterge(2, "", 50, "garsoniera");
//		assert(false);
//	}
//	catch (RepoExceptions& ex) {
//		assert(ex.getMesaj() == "Date invalide!\n\n");
//		assert(true); // ma astept sa arunce exceptie
//	}
//}

void testSterge()
{
	LocatarRepo rep;
	LocatarService srv{ rep };
	srv.adauga(1, "a", 50, "garsoniera");
	srv.adauga(2, "b", 50, "garsoniera");
	srv.adauga(3, "c", 50, "garsoniera");
	srv.adauga(4, "d", 50, "garsoniera");
	const auto& bloc = srv.getAll();
	assert(bloc.size() == 4);
	srv.sterge(2, "b", 50, "garsoniera");
	const auto& bloc1 = srv.getAll();
	assert(bloc1.size() == 3);
	try {
		srv.sterge(2, "b", 50, "garsoniera");
		assert(false);
	}
	catch (RepoExceptions& ex) {
		assert(ex.getMesaj() == "Locatarul nu exista!\n\n");
		assert(true);
	}
	try {
		srv.sterge(2, "", 50, "garsoniera");
		assert(false);
	}
	catch (RepoExceptions& ex) {
		assert(ex.getMesaj() == "Date invalide!\n\n");
		assert(true); // ma astept sa arunce exceptie
	}

	rep.stergelocatar(-2);
	assert(rep.getAll().size() == 3);
	//rep.stergelocatar(1);
	//rep.stergelocatar(3);
	//rep.stergelocatar(4);
}

void testModifica()
{
	LocatarRepo rep;
	LocatarService srv{ rep };
	srv.adauga(1, "a", 50, "garsoniera");
	srv.adauga(2, "b", 50, "garsoniera");
	srv.adauga(3, "c", 50, "garsoniera");
	srv.adauga(4, "d", 50, "garsoniera");
	const auto& poz = srv.cauta(2, "b", 50, "garsoniera");
	srv.modifica(2, "bb", 50, "garsoniera", poz);
	const auto& bloc = srv.getAll();
	assert(bloc.get(1).getApartament() == 2);
	assert(bloc.get(1).getProprietar() == "bb");
	assert(bloc.get(1).getSuprafata() == 50);
	assert(bloc.get(1).getTip() == "garsoniera");
	srv.modifica(1, "b", 50, "garsoniera", 0);
	const auto& bl1 = srv.getAll();
	assert(bl1.get(0).getApartament() == 1);
	assert(bl1.get(0).getProprietar() == "b");
	assert(bl1.get(0).getSuprafata() == 50);
	assert(bl1.get(0).getTip() == "garsoniera");
	try {
		srv.modifica(1, "", 50, "garsoniera", 0);
		assert(false);
	}
	catch (RepoExceptions& ex) {
		assert(ex.getMesaj() == "Date invalide!\n\n");
		assert(true); // ma astept sa arunce exceptie
	}
}

void testFiltraresuprafata()
{
	LocatarRepo rep;
	LocatarService srv{ rep };
	srv.adauga(1, "a", 30, "garsoniera");
	srv.adauga(2, "b", 50, "ap cu 2 camere");
	srv.adauga(3, "c", 50, "ap cu 3 camere");
	srv.adauga(4, "d", 30, "garsoniera");
	const auto& bsup = srv.filtraresuprafata(50);
	assert(bsup.size() == 2);
	assert(bsup.get(0).getSuprafata() == 50);
	assert(bsup.get(1).getSuprafata() == 50);
	try {
		srv.filtraresuprafata(-12);
		assert(false);
	}
	catch (RepoExceptions& ex) {
		assert(ex.getMesaj() == "suprafata invalida!\n\n");
		assert(true); // ma astept sa arunce exceptie
	}
}

void testFiltrareTip()
{
	LocatarRepo rep;
	LocatarService srv{ rep };
	srv.adauga(1, "a", 30, "garsoniera");
	srv.adauga(2, "b", 50, "ap cu 2 camere");
	srv.adauga(3, "c", 50, "ap cu 3 camere");
	srv.adauga(4, "d", 30, "garsoniera");
	const auto& btip = srv.filtraretip("garsoniera");
	assert(btip.size() == 2);
	assert(btip.get(0).getTip() == "garsoniera");
	assert(btip.get(1).getTip() == "garsoniera");
	try {
		srv.filtraretip("");
		assert(false);
	}
	catch (RepoExceptions& ex) {
		assert(ex.getMesaj() == "tip invalid!\n\n");
		assert(true); // ma astept sa arunce exceptie
	}
}

void testSortare()
{
	LocatarRepo rep;
	LocatarService srv{ rep };
	srv.adauga(1, "a", 50, "garsoniera"); //  3 1 2 5 4
	srv.adauga(4, "c", 60, "ap cu 2 camere");
	srv.adauga(3, "a", 50, "ap cu 3 camere");
	srv.adauga(5, "c", 30, "garsoniera");
	srv.adauga(2, "c", 30, "garsoniera");
	srv.sortare();
	const auto& loc = srv.getAll();
	assert(loc.size() == 5);
	assert(loc.get(0).getApartament() == 3);
	assert(loc.get(1).getApartament() == 1);
	assert(loc.get(2).getApartament() == 2);
	assert(loc.get(3).getApartament() == 5);
	assert(loc.get(4).getApartament() == 4);
	assert(loc.get(0).getProprietar() == "a");
	assert(loc.get(1).getProprietar() == "a");
	assert(loc.get(2).getProprietar() == "c");
	assert(loc.get(3).getProprietar() == "c");
	assert(loc.get(4).getProprietar() == "c");
	assert(loc.get(0).getSuprafata() == 50);
	assert(loc.get(1).getSuprafata() == 50);
	assert(loc.get(2).getSuprafata() == 30);
	assert(loc.get(3).getSuprafata() == 30);
	assert(loc.get(4).getSuprafata() == 60);
	assert(loc.get(1).getTip() == "garsoniera");
	assert(loc.get(0).getTip() == "ap cu 3 camere");
	assert(loc.get(3).getTip() == "garsoniera");
	assert(loc.get(2).getTip() == "garsoniera");
	assert(loc.get(4).getTip() == "ap cu 2 camere");

}

void test_vector()
{
	VectorDinamic<int> original;
	original.push_back(1);

	VectorDinamic<int> copied(original);

	assert(copied.size() == 1);
	assert(original.get(0) == copied.get(0));
}
