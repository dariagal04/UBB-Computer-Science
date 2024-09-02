#include "domain.h"
#include <string>
using std::string;

void Film::setTitlu(string t)
{
	titlu = t;
}

void Film::setGen(string g)
{
	gen = g;
}

void Film::setAn(int a)
{
	an = a;
}

void Film::setActor(string a)
{
	actor = a;
}

string Film::getTitlu() const
{
	return titlu;
}

string Film::getGen() const
{
	return gen;
}

int Film::getAn() const
{
	return an;
}

string Film::getActor() const
{
	return actor;
}

bool cmpTitlu(const Film& f1, const Film& f2)
{
	return f1.getTitlu() < f2.getTitlu();
}

bool cmpAnGen(const Film& f1, const Film& f2)
{
	if (f1.getAn() == f2.getAn())
		return f1.getGen() < f2.getGen();
	else
		return f1.getAn() < f2.getAn();
}

bool cmpActor(const Film& f1, const Film& f2)
{
	return f1.getActor() < f2.getActor();
}