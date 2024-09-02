#include "service.h"
#include "VectorDinamic.h"

using std::string;
//using std::vector;

void LocatarService::adauga(int apartament, string proprietar, int suprafata, string tip)
{
	if (apartament < 0 || proprietar == "" || tip == "" || suprafata < 0)
		throw RepoExceptions("Date invalide!\n\n");
	Locatar f(apartament, proprietar, suprafata, tip);
	rep.adaugalocatar(f);
}


int LocatarService::cauta(int apartament, string proprietar, int suprafata, string tip) const
{
	if (apartament < 0 || proprietar == "" || tip == "" || suprafata < 0)
		throw RepoExceptions("Date invalide!\n\n");
	return rep.cautalocatar(apartament, proprietar, suprafata, tip);
}

int LocatarService::sterge(int apartament, string proprietar, int suprafata, string tip)
{
	if (apartament < 0 || proprietar == "" || tip == "" || suprafata < 0)
		throw RepoExceptions("Date invalide!\n\n");
	const auto& poz = rep.cautalocatar(apartament, proprietar, suprafata, tip);
	if (poz == -1)
		throw RepoExceptions("Locatarul nu exista!\n\n");
	rep.stergelocatar(poz);
}

void LocatarService::modifica(int apartament, string proprietar, int suprafata, string tip, int poz)
{
	if (apartament < 0 || proprietar == "" || suprafata < 0 || tip == "")
		throw RepoExceptions("Date invalide!\n\n");
	rep.modificalocatar(apartament, proprietar, suprafata, tip, poz);
}

VectorDinamic<Locatar> LocatarService::filtraretip(string tip) const
{
	if (tip == "")
		throw RepoExceptions("tip invalid!\n\n");
	return rep.filtraretip(tip);
}

VectorDinamic<Locatar> LocatarService::filtraresuprafata(int suprafata) const
{

	if (suprafata < 0)
		throw RepoExceptions("suprafata invalida!\n\n");
	return rep.filtraresuprafata(suprafata);
}

void LocatarService::sortare()
{
	rep.sortare();
}

const VectorDinamic<Locatar>& LocatarService::getAll() {
	return rep.getAll();
}
