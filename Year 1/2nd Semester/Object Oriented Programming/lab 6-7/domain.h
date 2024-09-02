#pragma once
#include <string>
//#include <iostream>
using std::string;
//using std::cout;
/*
* Clasa entitatii
* apartament - int
* proprietar - string
* suprafata - int
* tip - string
*/
class Locatar
{
private:

	int apartament;
	string proprietar;
	int suprafata;
	string tip;

public:

	string getProprietar() const;


	string getTip() const;


	int getApartament() const;


	int getSuprafata() const;

	Locatar() = default;

	Locatar(int apartament, string proprietar, int suprafata, string tip) :apartament{ apartament }, proprietar{ proprietar }, suprafata{ suprafata }, tip{ tip } {

	}

	Locatar(const Locatar& l) :apartament{ l.apartament }, proprietar{ l.proprietar }, suprafata{ l.suprafata }, tip{ l.tip } {
		//cout << "*";
	}





	//Locatar(const Locatar&) = default;


};