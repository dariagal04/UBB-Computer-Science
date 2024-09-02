#pragma once
#include <string>
#include "domain.h"
#include "repository.h"
#include "VectorDinamic.h"
using std::string;
//using std::vector;

/*
* Clasa de service
*/
class LocatarService
{
	LocatarRepo& rep;
public:
	/*
	* Constructor
	*/
	LocatarService(LocatarRepo& rep) :rep{ rep } {

	}
	/*
	Constructor de copie
	*/
	LocatarService(const LocatarRepo& ot) = delete;

	//LocatarService() = default;
	LocatarService() = delete;


	void adauga(int apartament, string proprietar, int suprafata, string tip);


	int cauta(int apartament, string proprietar, int suprafata, string tip) const;


	int sterge(int apartament, string proprietar, int suprafata, string tip);


	void modifica(int apartament, string proprietar, int suprafata, string tip, int poz);


	VectorDinamic<Locatar> filtraretip(string tip) const;


	VectorDinamic<Locatar> filtraresuprafata(int suprafata) const;


	void sortare();


	const VectorDinamic<Locatar>& getAll();

};
