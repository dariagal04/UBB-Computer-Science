#include "repository.h"
#include "VectorDinamic.h"
#include "domain.h"
//using std::vector;
#include<string>
using std::string;

void LocatarRepo::adaugalocatar(const Locatar& f) {

	bloc.push_back(f);
	/*if (cautalocatar(f.getApartament(), f.getProprietar(), f.getSuprafata(), f.getTip()) != -1)
		throw RepoExceptions("Film existent!\n\n");
	bloc.push_back(f);*/
}

int LocatarRepo::cautalocatar(int apartament, string proprietar, int suprafata, string tip) {
	int i = 0;
	for (const Locatar& f1 : bloc)
	{
		if (apartament == f1.getApartament() && proprietar == f1.getProprietar() && suprafata == f1.getSuprafata() && tip == f1.getTip())
			return i;
		i++;
	}
	return -1;
}

void LocatarRepo::stergelocatar(int p)
{
	bloc.erase(p);
}

void LocatarRepo::modificalocatar(int apartament, string proprietar, int suprafata, string tip, int poz)
{
	/**if (proprietar == "-1")
		proprietar = bloc[poz].getProprietar();
	if (tip == "-1")
		tip = bloc[poz].getTip();
	if (suprafata == -1)
		suprafata = bloc[poz].getSuprafata();
	if (apartament == -1)
		apartament = bloc[poz].getApartament();*/
	Locatar f(apartament, proprietar, suprafata, tip);
	bloc.get(poz) = f;
}

VectorDinamic<Locatar> LocatarRepo::filtraresuprafata(int suprafata)
{
	VectorDinamic<Locatar> loc;
	for (const auto& f : bloc)
	{
		if (f.getSuprafata() == suprafata)
			loc.push_back(f);
	}
	return loc;
}

VectorDinamic<Locatar> LocatarRepo::filtraretip(string tip)
{
	VectorDinamic<Locatar> loc;
	for (const auto& f : bloc)
	{
		if (f.getTip() == tip)
			loc.push_back(f);
	}
	return loc;
}

void LocatarRepo::sortare()
{
	const auto& l = bloc.size();
	for (int i = 0; i < l - 1; i++)
	{
		for (int j = i + 1; j < l; j++)
		{
			if (bloc.get(i).getProprietar() > bloc.get(j).getProprietar())
			{
				Locatar aux = bloc.get(i);
				bloc.get(i) = bloc.get(j);
				bloc.get(j) = aux;
			}
			else if (bloc.get(i).getProprietar() == bloc.get(j).getProprietar())
			{
				if (bloc.get(i).getSuprafata() > bloc.get(j).getSuprafata())
				{
					Locatar aux = bloc.get(i);
					bloc.get(i) = bloc.get(j);
					bloc.get(j) = aux;
				}
				else if (bloc.get(i).getSuprafata() == bloc.get(j).getSuprafata())
				{
					if (bloc.get(i).getTip() > bloc.get(j).getTip())
					{
						Locatar aux = bloc.get(i);
						bloc.get(i) = bloc.get(j);
						bloc.get(j) = aux;
					}
					else if (bloc.get(i).getTip() == bloc.get(j).getTip())
					{
						if (bloc.get(i).getApartament() > bloc.get(j).getApartament())
						{
							Locatar aux = bloc.get(i);
							bloc.get(i) = bloc.get(j);
							bloc.get(j) = aux;
						}
					}
				}
			}
		}
	}
}

const VectorDinamic<Locatar>& LocatarRepo::getAll() {
	return bloc;
}


