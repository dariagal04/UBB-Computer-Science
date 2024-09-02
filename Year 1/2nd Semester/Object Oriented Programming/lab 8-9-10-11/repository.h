#pragma once
#include "domain.h"
#include <unordered_map>
#include <random>
#include<utility>
#include<string>
#include<vector>

using std::string;
using std::vector;

/*
* Clasa de repo abstract
*/
class RepoAbstract {
public:
	/*

	* Constructorul de copie
	*/
	RepoAbstract() = default;

	/*
	* Constructorul de vector de filme
	*/
	RepoAbstract(const RepoAbstract& o) = delete;

	/*
	* Adauga un film in vector
	*/
	virtual void adaugaFilm(const Film& f) = 0;

	/*
	* Cauta un film dupa titlu
	*/
	virtual const Film& cautaTitlu(string titlu) = 0;

	/*
	* Modifica un film
	*/
	virtual void modificaFilm(Film f, Film nou) = 0;

	/*
	* Sterge un film din vector
	*/
	virtual void stergeFilm(const Film& f) = 0;

	/*
	* Returneaza intreaga lista de filme
	*/
	virtual vector<Film> getAll() = 0;

};

/*
* Clasa de exceptii
*/
class RepoExceptions
{
	string msg;

public:
	RepoExceptions(string m) :msg{ m } {

	}
	string getMesaj() const {
		return msg;
	}
};

class Exception {
	string msg;
public:
	Exception(string m) :msg{ m } {

	}
	string getMesaj() const {
		return msg;
	}
};

/*
* Clasa repo
* filme - vectorul in care se pastreaza filmele
*/
class FilmRepo : public RepoAbstract
{

	vector<Film> filme;

public:
	/*

	* Constructorul de copie
	*/
	FilmRepo(const FilmRepo& ot) = delete;

	/*
	* Constructorul de vector de filme
	*/
	FilmRepo() = default;

	/*
	* Adauga un film in vector
	*/
	void adaugaFilm(const Film& f) override;

	/*
	* Cauta un film dupa titlu
	*/
	const Film& cautaTitlu(string titlu) override;

	/*
	* Modifica un film
	*/
	void modificaFilm(Film f, Film nou) override;

	/*
	* Sterge un film din vector
	*/
	void stergeFilm(const Film& f) override;

	/*
	* Returneaza intreaga lista de filme
	*/
	vector<Film> getAll() override;

};

class FilmRepoFile : public FilmRepo {
private:
	string fileName;

	void loadFromFile();

	void writeToFile();

public:

	explicit FilmRepoFile(string fileName) : FilmRepo(), fileName{ fileName } {
		loadFromFile();
	}

	void adaugaFilm(const Film& f) override {
		FilmRepo::adaugaFilm(f);
		writeToFile();
	}

	void stergeFilm(const Film& f) override {
		FilmRepo::stergeFilm(f);
		writeToFile();
	}

	void modificaFilm(Film f, Film nou) override {
		FilmRepo::modificaFilm(f, nou);
		writeToFile();
	}
};