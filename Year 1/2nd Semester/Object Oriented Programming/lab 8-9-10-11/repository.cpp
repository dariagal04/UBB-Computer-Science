#include "repository.h"
#include "domain.h"

#include<string>
#include<fstream>

using std::string;


void FilmRepo::adaugaFilm(const Film& f) {
	for (const auto& f1 : filme)
	{
		if (f.getTitlu() == f1.getTitlu() && f.getGen() == f1.getGen() && f.getAn() == f1.getAn() && f.getActor() == f1.getActor())
			throw RepoExceptions("Film existent!\n\n");
	}
	filme.push_back(f);
}

const Film& FilmRepo::cautaTitlu(string titlu)
{
	auto f = std::find_if(this->filme.begin(), this->filme.end(), [=](const Film& f) {
		return (f.getTitlu() == titlu);
		});
	if (f != this->filme.end())
		return (*f);
	else
		throw RepoExceptions("Filmul nu exista!\n");
}

void FilmRepo::modificaFilm(Film f, Film nou)
{
	for (auto& f1 : filme)
	{
		if (f.getTitlu() == f1.getTitlu() && f.getGen() == f1.getGen() && f.getAn() == f1.getAn() && f.getActor() == f1.getActor())
		{
			f1.setTitlu(nou.getTitlu());
			f1.setGen(nou.getGen());
			f1.setAn(nou.getAn());
			f1.setActor(nou.getActor());
			return;
		}
	}
}

void FilmRepo::stergeFilm(const Film& f)
{
	int i = 0;
	for (const auto& f1 : filme)
	{
		if (f1.getTitlu() == f.getTitlu() && f1.getGen() == f.getGen() && f1.getAn() == f.getAn() && f1.getActor() == f.getActor())
		{
			filme.erase(filme.begin() + i);
			return;
		}
		i++;
	}
}

vector<Film> FilmRepo::getAll() {
	return filme;
}

void FilmRepoFile::loadFromFile() {
	std::ifstream in(fileName);
	if (!in.is_open())
		throw RepoExceptions("Eroare la deschiderea fisierului!\n\n");
	string titlu, gen, actor;
	int an;
	while (std::getline(in, titlu) && std::getline(in, gen) && in >> an && std::getline(in >> std::ws, actor))
	{
		Film f{ titlu,gen,an,actor };
		FilmRepo::adaugaFilm(f);
	}
	in.close();
}

void FilmRepoFile::writeToFile()
{
	std::ofstream out(fileName);
	//if (!out.is_open())
		//throw RepoExceptions("Eroare la deschiderea fisierului!\n\n");
	for (auto& f : FilmRepo::getAll())
	{
		out << f.getTitlu() << '\n';
		out << f.getGen() << '\n';
		out << f.getAn() << '\n';
		out << f.getActor() << '\n';
	}
	out.close();
}

