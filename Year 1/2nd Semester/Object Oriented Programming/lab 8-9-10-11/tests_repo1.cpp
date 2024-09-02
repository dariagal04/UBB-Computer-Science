#include "tests_repo1.h"
#include "repository.h"
#include <assert.h>
#include<fstream>
#include<iostream>
#include <unordered_map>

void testProb() {
    Repo1 repo;
    repo.setProbabilitate(0.000000000001);
    try {
        repo.prob();
        assert(false);
    }
    catch (Exception& ex) {
        assert(ex.getMesaj() == "Nu se poate executa functia!\n\n");
        assert(true);
    }
}

void testAdaugaFilm_repo1() {
    Repo1 repo;
    repo.setProbabilitate(1000000);
    Film film("Titlu", "Gen", 2022, "Actor");
    repo.setProbabilitate(1000000);
    repo.adaugaFilm(film);
    try {
        repo.adaugaFilm(film);
        assert(false);
    }
    catch (RepoExceptions& ex) {
        assert(ex.getMesaj() == "Film existent!\n\n");
        assert(true);
    }

    assert(repo.getAll().size() == 1);
    assert(repo.getAll().at(0).getTitlu() == "Titlu");

    repo.setProbabilitate(0.0000000001);
    try {
        repo.adaugaFilm(film);
        assert(false);
    }
    catch (Exception& ex1) {
        assert(ex1.getMesaj() == "Nu se poate executa functia!\n\n");
        assert(true);
    }

}

void testCautaTitlu_repo1() {
    Repo1 repo;
    repo.setProbabilitate(1000000);
    Film film("Titlu", "Gen", 2022, "Actor");
    repo.adaugaFilm(film);
    const Film& filmGasit = repo.cautaTitlu("Titlu");

    assert(filmGasit.getTitlu() == "Titlu");

    try {
        repo.cautaTitlu("titlu");
        assert(false);
    }
    catch (RepoExceptions& ex) {
        assert(ex.getMesaj() == "Filmul nu exista!\n");
        assert(true);
    }

    repo.setProbabilitate(0.0000000001);
    try {
        repo.cautaTitlu("Titlu");
        assert(false);
    }
    catch (Exception& ex1) {
        assert(ex1.getMesaj() == "Nu se poate executa functia!\n\n");
        assert(true);
    }
}

void testModificaFilm_repo1() {
    Repo1 repo;
    repo.setProbabilitate(1000000);
    Film film("Titlu", "Gen", 2022, "Actor");
    repo.adaugaFilm(film);
    Film filmNou("Titlu Nou", "Gen Nou", 2023, "Actor Nou");
    repo.modificaFilm(film, filmNou);

    const Film& filmModificat = repo.cautaTitlu("Titlu Nou");
    assert(filmModificat.getTitlu() == "Titlu Nou");
    assert(filmModificat.getGen() == "Gen Nou");
    assert(filmModificat.getAn() == 2023);
    assert(filmModificat.getActor() == "Actor Nou");

    repo.setProbabilitate(0.0000000001);
    try {
        repo.modificaFilm(filmNou, film);
        assert(false);
    }
    catch (Exception& ex1) {
        assert(ex1.getMesaj() == "Nu se poate executa functia!\n\n");
        assert(true);
    }

}

void testStergeFilm_repo1() {
    Repo1 repo;
    repo.setProbabilitate(1000000);
    Film film("Titlu", "Gen", 2022, "Actor");
    repo.adaugaFilm(film);

    Film film1("Titlu1", "Gen1", 2023, "Actor1");
    repo.adaugaFilm(film1);

    Film film2("Titlu2", "Gen2", 2024, "Actor2");
    repo.adaugaFilm(film2);

    repo.stergeFilm(film1);

    assert(repo.getAll().size() == 2);

    try {
        repo.stergeFilm(film1);
        assert(false);
    }
    catch (RepoExceptions& ex)
    {
        assert(ex.getMesaj() == "Filmul nu exista!\n");
        assert(true);
    }

    repo.setProbabilitate(0.000000001);
    try {
        repo.stergeFilm(film1);
        assert(false);
    }
    catch (Exception& ex1) {
        assert(ex1.getMesaj() == "Nu se poate executa functia!\n\n");
        assert(true);
    }

    try {
        vector<Film> FILME = repo.getAll();
        assert(false);
    }
    catch (Exception& ex1) {
        assert(ex1.getMesaj() == "Nu se poate executa functia!\n\n");
        assert(true);
    }

}