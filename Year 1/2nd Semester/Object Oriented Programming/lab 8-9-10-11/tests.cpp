#include "tests.h"
#include "repository.h"
#include <assert.h>
#include<fstream>
#include<iostream>
#include <unordered_map>

void testRepo()
{
	FilmRepo rep;
	Film f{ "a", "b", 12,"c" };
	rep.adaugaFilm(f);
	const auto& filme = rep.getAll();
	assert(filme.size() == 1);

	try {
		rep.adaugaFilm(f);
		assert(false);
	}
	catch (RepoExceptions& ex) {
		assert(ex.getMesaj() == "Film existent!\n\n");
		assert(true); // ma astept sa arunce exceptie
	}
	rep.adaugaFilm({ "b","c",19,"d" });
	rep.adaugaFilm({ "c","d",11,"e" });
	rep.adaugaFilm({ "d","e",124,"f" });
	rep.adaugaFilm({ "e","f",178,"g" });
	const auto& filme2 = rep.getAll();
	assert(filme2.size() == 5);
}

void testGetTitlu()
{
	Film f{ "a", "b", 12,"c" };
	assert(f.getTitlu() == "a");
	Film f1{ "dm","a",111,"w" };
	assert(f1.getTitlu() == "dm");
}

void testGetGen()
{
	Film f{ "a", "b", 12,"c" };
	assert(f.getGen() == "b");
	Film f1{ "dm","a",111,"w" };
	assert(f1.getGen() == "a");
}

void testGetAn()
{
	Film f{ "a", "b", 12,"c" };
	assert(f.getAn() == 12);
	Film f1{ "dm","a",111,"w" };
	assert(f1.getAn() == 111);
}

void testGetActor()
{
	Film f{ "a", "b", 12,"c" };
	assert(f.getActor() == "c");
	Film f1{ "dm","a",111,"w" };
	assert(f1.getActor() == "w");
}

void testAdd()
{
	FilmRepo rep;
	CosFilme cos;
	FilmService srv{ rep, cos };
	srv.adauga("a", "b", 123, "c");
	const auto& filme = srv.getAll();
	assert(filme.size() == 1);

	try {
		srv.adauga("", "b", 11, "ra");
		assert(false);
	}
	catch (RepoExceptions& ex) {
		assert(ex.getMesaj() == "Date invalide!\n\n");
		assert(true); // ma astept sa arunce exceptie
	}
	assert(filme.size() == 1);
}

void testCauta()
{
	FilmRepo rep;
	CosFilme cos;
	FilmService srv{ rep ,cos };
	srv.adauga("a", "b", 123, "c");
	srv.adauga("b", "c", 19, "d");
	srv.adauga("c", "d", 11, "e");
	srv.adauga("d", "e", 124, "f");
	const auto& filme = srv.getAll();
	assert(filme.size() == 4);

	const auto& f = srv.cauta("b");
	assert(f.getTitlu() == "b");
	assert(f.getGen() == "c");
	assert(f.getAn() == 19);
	assert(f.getActor() == "d");


	try {
		srv.cauta("");
		assert(false);
	}
	catch (RepoExceptions& ex) {
		assert(ex.getMesaj() == "Date invalide!\n\n");
		assert(true); // ma astept sa arunce exceptie
	}

	try {
		srv.cauta("titlu");
		assert(false);
	}
	catch (RepoExceptions& ex) {
		assert(ex.getMesaj() == "Filmul nu exista!\n");
		assert(true);
	}
}

void testSterge()
{
	FilmRepo rep;
	CosFilme cos;
	FilmService srv{ rep ,cos };
	srv.adauga("a", "b", 123, "c");
	srv.adauga("b", "c", 19, "d");
	srv.adauga("c", "d", 11, "e");
	srv.adauga("d", "e", 124, "f");
	const auto& filme = srv.getAll();
	assert(filme.size() == 4);
	Film f{ "b", "c", 19, "d" };
	srv.sterge(f);
	const auto& filme1 = srv.getAll();
	assert(filme1.size() == 3);
}

void testModifica()
{
	FilmRepo rep;
	CosFilme cos;
	FilmService srv{ rep ,cos };
	srv.adauga("a", "b", 123, "c");
	srv.adauga("b", "c", 19, "d");
	srv.adauga("c", "d", 11, "e");
	srv.adauga("d", "e", 124, "f");
	Film f = srv.getAll()[1];
	srv.modifica("-1", "am", 23, "-1", f);

	assert(srv.getAll()[1].getTitlu() == "b");
	assert(srv.getAll()[1].getGen() == "am");
	assert(srv.getAll()[1].getAn() == 23);
	assert(srv.getAll()[1].getActor() == "d");

	Film f1 = srv.getAll()[0];
	srv.modifica("ana", "-1", -1, "cc", f1);
	assert(srv.getAll()[0].getTitlu() == "ana");
	assert(srv.getAll()[0].getGen() == "b");
	assert(srv.getAll()[0].getAn() == 123);
	assert(srv.getAll()[0].getActor() == "cc");

	Film f2 = srv.getAll()[0];
	try {
		srv.modifica("", "b", 11, "ra", f2);
		assert(false);
	}
	catch (RepoExceptions& ex) {
		assert(ex.getMesaj() == "Date invalide!\n\n");
		assert(true); // ma astept sa arunce exceptie
	}
}

void testFiltrareAn()
{
	FilmRepo rep;
	CosFilme cos;
	FilmService srv{ rep ,cos };
	srv.adauga("a", "b", 123, "c");
	srv.adauga("b", "c", 19, "d");
	srv.adauga("c", "d", 11, "e");
	srv.adauga("d", "e", 123, "f");
	const auto& filmeAn = srv.filtrareAn(123);
	assert(filmeAn.size() == 2);
	assert(filmeAn[0].getGen() == "b");
	assert(filmeAn[1].getActor() == "f");
	try {
		srv.filtrareAn(-12);
		assert(false);
	}
	catch (RepoExceptions& ex) {
		assert(ex.getMesaj() == "An invalid!\n\n");
		assert(true); // ma astept sa arunce exceptie
	}
}

void testFiltrareTitlu()
{
	FilmRepo rep;
	CosFilme cos;
	FilmService srv{ rep ,cos };
	srv.adauga("a", "b", 123, "c");
	srv.adauga("b", "c", 19, "d");
	srv.adauga("a", "d", 11, "e");
	srv.adauga("d", "e", 123, "f");
	const auto& filmeTitlu = srv.filtrareTitlu("a");
	assert(filmeTitlu.size() == 2);
	assert(filmeTitlu[0].getGen() == "b");
	assert(filmeTitlu[1].getActor() == "e");
	try {
		srv.filtrareTitlu("");
		assert(false);
	}
	catch (RepoExceptions& ex) {
		assert(ex.getMesaj() == "Titlu invalid!\n\n");
		assert(true); // ma astept sa arunce exceptie
	}
}

void testSortare()
{
	FilmRepo rep;
	CosFilme cos;
	FilmService srv{ rep ,cos };
	srv.adauga("b", "r", 11, "c");
	srv.adauga("a", "c", 19, "d");
	const vector<Film>& sortat = srv.sortare_titlu();
	assert(sortat.size() == 2);
	assert(sortat[0].getTitlu() == "a");
	assert(sortat[1].getTitlu() == "b");
	assert(sortat[0].getGen() == "c");
	assert(sortat[1].getGen() == "r");
	assert(sortat[0].getAn() == 19);
	assert(sortat[1].getAn() == 11);
	assert(sortat[0].getActor() == "d");
	assert(sortat[1].getActor() == "c");

	const vector<Film>& sortat1 = srv.sortare_actor();
	assert(sortat1.size() == 2);
	assert(sortat1[0].getTitlu() == "b");
	assert(sortat1[1].getTitlu() == "a");
	assert(sortat1[0].getGen() == "r");
	assert(sortat1[1].getGen() == "c");
	assert(sortat1[0].getAn() == 11);
	assert(sortat1[1].getAn() == 19);
	assert(sortat1[0].getActor() == "c");
	assert(sortat1[1].getActor() == "d");

	srv.adauga("m", "a", 19, "d");
	const vector<Film>& sortat2 = srv.sortare_an_gen();
	assert(sortat2.size() == 3);
	assert(sortat2[0].getTitlu() == "b");
	assert(sortat2[0].getGen() == "r");
	assert(sortat2[0].getAn() == 11);
	assert(sortat2[0].getActor() == "c");

	assert(sortat2[1].getTitlu() == "m");
	assert(sortat2[1].getGen() == "a");
	assert(sortat2[1].getAn() == 19);
	assert(sortat2[1].getActor() == "d");

	assert(sortat2[2].getTitlu() == "a");
	assert(sortat2[2].getGen() == "c");
	assert(sortat2[2].getAn() == 19);
	assert(sortat2[2].getActor() == "d");
}

void testCosAdauga()
{
	FilmRepo rep;
	CosFilme cos;
	FilmService srv{ rep ,cos };
	srv.adauga("b", "r", 11, "c");
	srv.adauga("a", "c", 19, "d");
	srv.cosAdauga("a");
	assert(srv.getAllCos().size() == 1);
	try {
		srv.cosAdauga("a");
		assert(false);
	}
	catch (RepoExceptions& ex)
	{
		assert(ex.getMesaj() == "Filmul se afla deja in cos!\n\n");
		assert(true);
	}
}

void testCosAdaugaRandom()
{
	FilmRepo rep;
	CosFilme cos;
	FilmService srv{ rep ,cos };
	srv.adauga("a", "b", 123, "c");
	srv.adauga("b", "c", 19, "d");
	srv.adauga("c", "d", 11, "e");
	srv.adauga("d", "e", 124, "f");
	srv.cosAdaugaRandom(2);
	assert(srv.getAllCos().size() == 2);
}

void testCosSterge()
{
	FilmRepo rep;
	CosFilme cos;
	FilmService srv{ rep ,cos };
	srv.adauga("a", "b", 123, "c");
	srv.adauga("b", "c", 19, "d");
	srv.adauga("c", "d", 11, "e");
	srv.adauga("d", "e", 124, "f");
	srv.cosAdaugaRandom(2);
	assert(srv.getAllCos().size() == 2);
	srv.cosSterge();
	assert(srv.getAllCos().size() == 0);
}

void testCosExport()
{
	FilmRepo rep;
	CosFilme cos;
	FilmService srv{ rep ,cos };
	cos.adaugaFilmCos(Film{ "a","b",111,"c" });
	cos.adaugaFilmCos(Film{ "n","m",13,"p" });

	{
		string filename = "test.csv";
		srv.cosExport(filename);
		std::ifstream fin(filename);
		assert(fin.is_open());
		fin.close();
	}

	/*{
		string filename = "test.html";
		srv.cosExport(filename);
		std::ifstream fin(filename);
		assert(fin.is_open());
		fin.close();
	}*/

	{
		string filename = "test.txt";
		try {
			srv.cosExport(filename);
			assert(false);
		}
		catch (RepoExceptions& ex) {
			assert(ex.getMesaj() == "Fisierul nu este valid!\n");
			assert(true);
		}
	}
}

void testRaport()
{
	FilmRepo rep;
	CosFilme cos;
	FilmService srv{ rep ,cos };
	srv.adauga("a", "b", 123, "c");
	srv.adauga("b", "c", 19, "d");
	srv.adauga("c", "b", 11, "e");
	srv.adauga("d", "e", 124, "f");

	std::unordered_map<string, int> r = srv.raport();
	assert(r.size() == 3);
	assert(r["c"] == 1);
	assert(r["b"] == 2);
	assert(r["e"] == 1);
}

void testCautaTitlu()
{
	FilmRepo rep;
	Film f{ "a", "b", 12,"c" };
	rep.adaugaFilm(f);

	Film f1 = rep.cautaTitlu("a");
	assert(f1.getGen() == "b");

	try {
		rep.cautaTitlu("c");
		assert(false);
	}
	catch (RepoExceptions& ex)
	{
		assert(ex.getMesaj() == "Filmul nu exista!\n");
		assert(true);
	}
}

void testFisier()
{
	FilmRepoFile rep{ "D:/dari/an1sem2/OOP/test.txt" };
	CosFilme cos;
	FilmService srv{ rep,cos };
	assert(srv.getAll().size() == 3);
	srv.adauga("a", "b", 2023, "c");
	assert(srv.getAll().size() == 4);
	Film f{ "a", "b", 2023, "c" };
	srv.modifica("aa", "-1", -1, "cc", f);
	assert(srv.getAll()[3].getTitlu() == "aa");
	assert(srv.getAll()[3].getActor() == "cc");
	Film f1 = srv.getAll()[3];
	srv.sterge(f1);
	assert(srv.getAll().size() == 3);

	try {
		FilmRepoFile rep1{ "f123.txt" };
		assert(false);
	}
	catch (RepoExceptions& ex)
	{
		assert(ex.getMesaj() == "Eroare la deschiderea fisierului!\n\n");
		assert(true);
	}
}

void testUndo()
{
	FilmRepo rep;
	CosFilme cos;
	FilmService srv{ rep ,cos };
	srv.adauga("b", "c", 19, "d");
	srv.adauga("c", "d", 11, "e");
	srv.adauga("d", "e", 124, "f");
	assert(srv.getAll().size() == 3);
	Film f{ "d", "e", 124, "f" };
	srv.sterge(f);
	assert(srv.getAll().size() == 2);
	srv.undo();
	assert(srv.getAll().size() == 3);
	srv.adauga("aa", "bb", 111, "cc");
	assert(srv.getAll().size() == 4);
	srv.undo();
	assert(srv.getAll().size() == 3);
	Film f1{ "b", "c", 19, "d" };
	srv.modifica("bb", "cc", 1900, "dd", f1);
	assert(srv.getAll()[0].getTitlu() == "bb");
	assert(srv.getAll()[0].getGen() == "cc");
	assert(srv.getAll()[0].getAn() == 1900);
	assert(srv.getAll()[0].getActor() == "dd");
	srv.undo();
	assert(srv.getAll()[0].getTitlu() == "b");
	assert(srv.getAll()[0].getGen() == "c");
	assert(srv.getAll()[0].getAn() == 19);
	assert(srv.getAll()[0].getActor() == "d");

	FilmRepo rep1;
	CosFilme cos1;
	FilmService srv1{ rep1 ,cos1 };
	srv1.adauga("b", "c", 19, "d");
	assert(srv1.getAll().size() == 1);
	srv1.undo();
	assert(srv1.getAll().size() == 0);
	try {
		srv1.undo();
		assert(false);
	}
	catch (RepoExceptions& ex) {
		assert(ex.getMesaj() == "Nu se mai poate face undo!\n\n");
		assert(true);
	}
}