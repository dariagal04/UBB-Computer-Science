#pragma once
#include <string>
#include "domain.h"
#include "repository.h"
#include <unordered_map>

#include "Undo.h"
#include "CosFilme.h"
using std::string;


/*
* Clasa de service
*/
class FilmService
{
	RepoAbstract& rep;

	CosFilme& cosCurent;

	vector<std::unique_ptr<ActiuneUndo>> undoAct;

public:
	/*
	* Constructor
	*/
	FilmService(class RepoAbstract& rep, CosFilme& cos) :rep{ rep }, cosCurent{ cos } {
	}
	/*
	Constructor de copie
	*/
	FilmService(const FilmService& ot) = delete;

	FilmService() = delete;

	/*
	* Adauga un film in vector
	* Arunca exceptie daca datele introduse sunt invalide
	*/
	void adauga(string titlu, string gen, int an, string actor);

	/*
	* Cauta un film in vactor
	* Arunca exceptie daca datele introduse sunt invalide
	*/
	const Film& cauta(string titlu) const;

	/*
	* Sterge un film din vector
	* Arunca exceptie daca datele introduse sunt invalide
	*/
	void sterge(Film f);

	/*
	* Modifica un film din vector
	* Arunca exceptie daca datele introduse sunt invalide
	*/
	void modifica(string titlu1, string gen1, int an1, string actor1, Film f);

	/*
	* Filtreaza filmele aparute intr-un anumit an
	* Arunca exceptie daca anul introdus este invalid
	*/
	vector<Film> filtrareAn(int an) const;

	/*
	* Filtreaza filmele ce au un anumit titlu
	* Arunca exceptie daca titlul introdus este invalid
	*/
	vector<Film> filtrareTitlu(string titlu) const;

	/*
	* Sorteaza filmele dupa titlu
	*/
	vector<Film> sortare_titlu();

	/*
	* Sorteaza filmele dupa actor
	*/
	vector<Film> sortare_actor();

	/*
	* Sorteaza filmele dupa gen si an
	*/
	vector<Film> sortare_an_gen();

	/*
	* Returneaza intreaga lista de filme
	*/
	vector<Film> getAll() const;

	/*
	* Adauga un film cu titlul cautat in cos
	*/
	void cosAdauga(string titlu);

	/*
	* Adauga un numar de filme random in cos
	*/
	int cosAdaugaRandom(int nr);

	/*
	* Returneaaza toate filmele din cos
	*/
	const vector<Film>& getAllCos();

	/*
	* Goleste toate filmele din cos
	*/
	void cosSterge();

	/*
	* Exporta cosul in fisierul dat ca parmetru
	*/
	void cosExport(string filename);

	/*
	* Numar de filme pentru fiecare gen
	*/
	std::unordered_map<string, int> raport();

	/*
	* Efectueaza operatia de undo
	*/
	void undo();
};