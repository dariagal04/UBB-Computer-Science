#include "domain.h"
#include <string>
using std::string;

int Locatar::getApartament() const
{
	return apartament;
}

string Locatar::getProprietar() const
{
	return proprietar;
}

int Locatar::getSuprafata() const
{
	return suprafata;
}

string Locatar::getTip() const
{
	return tip;
}
