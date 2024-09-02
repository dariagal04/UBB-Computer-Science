#pragma once
#include <string>
#include <iostream>
using std::string;
//using std::cout;
/*
* Clasa entitatii
* titlu - string
* gen - string
* an - int
* actor - string
*/
class Film
{
private:

	string titlu;
	string gen;
	int an;
	string actor;

public:

	/*
	* Seteaza titlul unui film
	*/
	void setTitlu(string t);

	/*
	* Seteaza genul unui film
	*/
	void setGen(string g);

	/*
	* Seteaza anul unui film
	*/
	void setAn(int a);

	/*
	* Seteaza actorul unui film
	*/
	void setActor(string a);

	/*
	* De tip string, returneaza titlul unui film
	*/
	string getTitlu() const;

	/*
	* De tip string, returneaza genul unui film
	*/
	string getGen() const;

	/*
	* De tip int, returneaza anul aparitiei al unui film
	*/
	int getAn() const;

	/*
	* De tip string, returneaza actorul principal unui film
	*/
	string getActor() const;

	/*
	* Constructorul default
	*/
	Film() = default;

	/*
	* Constructorul filmului
	*/
	Film(string titlu, string gen, int an, string actor) :titlu{ titlu }, gen{ gen }, an{ an }, actor{ actor } {

	}
	/*
	* Constructorul de copie
	*/
	Film(const Film& ot) :titlu{ ot.titlu }, gen{ ot.gen }, an{ ot.an }, actor{ ot.actor } {
	}
};

bool cmpTitlu(const Film& f1, const Film& f2);

bool cmpAnGen(const Film& f1, const Film& f2);

bool cmpActor(const Film& f1, const Film& f2);