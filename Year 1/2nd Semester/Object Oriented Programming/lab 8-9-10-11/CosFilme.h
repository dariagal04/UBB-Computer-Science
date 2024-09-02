#pragma once
#include "domain.h"
#include <vector>
#include <random>

using std::vector;

class CosFilme {
private:
	vector<Film> cosFilme;

public:
	/*
	* Constructorul cosului
	*/
	CosFilme() = default;

	/*
	* Adauga un film in cos
	*/
	void adaugaFilmCos(const Film& f);

	/*
	* Adauga un numar de filme in cos
	*/
	void adaugaFilmRandomCos(vector<Film> filme, int nr);

	/*
	* Returneaza un vector cu toate filmele din cos
	*/
	const vector<Film>& getAllCos();

	/*
	* Sterge toate filmele din cos
	*/
	void stergeCos();

	bool cauta(string titlu);
};