#pragma once
#include "domain.h"
#include "VectorDinamic.h"
#include<utility>
#include<string>

using std::string;
/*
* Clasa de exceptii
*/
class RepoExceptions
{
	string msg;

public:
	RepoExceptions(string m) :msg{ m } {

	}
	string getMesaj() {
		return msg;
	}
};

/*
* Clasa repo
*/
class LocatarRepo
{
private:
	VectorDinamic<Locatar> bloc;

public:
	/*

	* Constructorul de copie
	*/
	//LocatarRepo(const LocatarRepo& ot) = delete;

	/*
	* Constructorul de vector de locatari
	*/
	LocatarRepo() = default;


	void adaugalocatar(const Locatar& f);


	int cautalocatar(int apartament, string proprietar, int suprafata, string tip);


	void stergelocatar(int p);


	void modificalocatar(int apartament, string proprietar, int suprafata, string tip, int poz);


	VectorDinamic<Locatar> filtraresuprafata(int suprafata);


	VectorDinamic<Locatar> filtraretip(string tip);


	void sortare();


	const VectorDinamic<Locatar>& getAll();
};
