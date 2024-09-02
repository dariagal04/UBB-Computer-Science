#include "CosFilme.h"
#include <random>

using std::shuffle;

void CosFilme::adaugaFilmCos(const Film& f)
{
	this->cosFilme.push_back(f);
}

void CosFilme::adaugaFilmRandomCos(vector<Film> filme, int nr)
{
	shuffle(filme.begin(), filme.end(), std::default_random_engine(std::random_device{}()));
	while (int(cosFilme.size()) < nr && !filme.empty())
	{
		if (!cauta(filme.back().getTitlu()))
		{
			cosFilme.push_back(filme.back());
		}
		filme.pop_back();
	}
}

const vector<Film>& CosFilme::getAllCos()
{
	return this->cosFilme;
}

void CosFilme::stergeCos()
{
	this->cosFilme.clear();
}

bool CosFilme::cauta(string titlu)
{
	auto f = std::find_if(this->cosFilme.begin(), this->cosFilme.end(), [=](const Film& f) {
		return (f.getTitlu() == titlu);
		});
	if (f != this->cosFilme.end())
		return true;
	return false;
}