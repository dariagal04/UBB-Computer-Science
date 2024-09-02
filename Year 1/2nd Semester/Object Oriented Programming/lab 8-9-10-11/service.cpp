#include "service.h"
#include <vector>
#include <fstream>
#include<exception>
#include<unordered_map>
#include "Undo.h"

using std::vector;
using std::string;
//using std::vector;

void FilmService::adauga(string titlu, string gen, int an, string actor)
{
	if (titlu == "" || gen == "" || actor == "" || an < 0)
		throw RepoExceptions("Date invalide!\n\n");
	Film f{ titlu, gen, an, actor };
	rep.adaugaFilm(f);
	undoAct.push_back(std::make_unique<UndoAdauga>(rep, f));
}

const Film& FilmService::cauta(string titlu) const
{
	if (titlu == "")
		throw RepoExceptions("Date invalide!\n\n");
	return rep.cautaTitlu(titlu);
}

void FilmService::sterge(Film f)
{
	rep.stergeFilm(f);
	undoAct.push_back(std::make_unique<UndoSterge>(rep, f));
}

void FilmService::modifica(string titlu1, string gen1, int an1, string actor1, Film f)
{
	if (titlu1 == "" || gen1 == "" || actor1 == "" || (an1 < 0 && an1 != -1))
		throw RepoExceptions("Date invalide!\n\n");
	if (titlu1 == "-1")
		titlu1 = f.getTitlu();
	if (gen1 == "-1")
		gen1 = f.getGen();
	if (an1 == -1)
		an1 = f.getAn();
	if (actor1 == "-1")
		actor1 = f.getActor();
	Film nou{ titlu1,gen1,an1,actor1 };
	rep.modificaFilm(f, nou);
	undoAct.push_back(std::make_unique<UndoModifica>(rep, f, nou));
}

vector<Film> FilmService::filtrareAn(int an) const
{
	if (an < 0)
		throw RepoExceptions("An invalid!\n\n");
	const vector<Film>& filme = getAll();
	vector<Film> filmeF;
	std::copy_if(filme.begin(), filme.end(), back_inserter(filmeF), [an](const Film& f) {
		return f.getAn() == an;
		});
	return filmeF;
}

vector<Film> FilmService::filtrareTitlu(string titlu) const
{
	if (titlu == "")
		throw RepoExceptions("Titlu invalid!\n\n");
	const vector<Film>& filme = getAll();
	vector<Film> filmeF;
	std::copy_if(filme.begin(), filme.end(), back_inserter(filmeF), [titlu](const Film& f) {
		return f.getTitlu() == titlu;
		});
	return filmeF;
}

vector<Film> FilmService::sortare_titlu()
{
	vector<Film> sortat{ rep.getAll() };
	sort(sortat.begin(), sortat.end(), cmpTitlu);
	return sortat;
}

vector<Film> FilmService::sortare_actor()
{
	vector<Film> sortat{ rep.getAll() };
	sort(sortat.begin(), sortat.end(), cmpActor);
	return sortat;
}

vector<Film> FilmService::sortare_an_gen()
{
	vector<Film> sortat{ rep.getAll() };
	sort(sortat.begin(), sortat.end(), cmpAnGen);
	return sortat;
}

vector<Film> FilmService::getAll() const {
	return rep.getAll();
}

void FilmService::cosAdauga(string titlu)
{
	const auto& film = rep.cautaTitlu(titlu);
	if (cosCurent.cauta(titlu))
		throw RepoExceptions("Filmul se afla deja in cos!\n\n");
	cosCurent.adaugaFilmCos(film);
}

int FilmService::cosAdaugaRandom(int nr)
{
	cosCurent.adaugaFilmRandomCos(this->getAll(), nr);
	return (int)(cosCurent.getAllCos().size());
}

const vector<Film>& FilmService::getAllCos()
{
	return cosCurent.getAllCos();
}

void FilmService::cosSterge()
{
	cosCurent.stergeCos();
}

//void FilmService::cosExport(string filename)
//{
//	if (filename.find(".csv") == std::string::npos && filename.find(".html") == std::string::npos)
//	{
//		throw RepoExceptions("Fisierul nu este valid!\n");
//	}
//	else
//	{
//		std::ofstream fout(filename);
//		if (filename.find("html") != std::string::npos)
//		{
//			fout << "<html>";
//			fout << "<style> table, th, td {border:1px solid black} body{background-color: #E6E6FA;} </style>";
//			fout << "<body>";
//			fout << "<h1> COS </h1>";
//			fout << "<table><tr><th>Titlu</th> <th>Gen</th> <th>An</th> <th>Actor </th></tr>";
//			for (auto& f : getAllCos()) {
//				fout << "<tr><td>" << f.getTitlu() << "<td>" << f.getGen() << "</td><td>" << f.getAn()
//					<< "</td><td>" << f.getActor() << "</td></tr>";
//			}
//			fout << "</table></body>";
//			fout << "<html>";
//		}
//		else
//		{
//			for (auto& f : getAllCos())
//			{
//				fout << f.getTitlu() << ";" << f.getGen() << ";" << f.getAn() << ";" << f.getActor() << '\n';
//			}
//		}
//		fout.close();
//	}
//
//}

void FilmService::cosExport(string filename)
{
	// Verifică dacă fișierul are extensia corectă .csv
	if (filename.find(".csv") == std::string::npos)
	{
		throw RepoExceptions("Fisierul nu este valid!\n");
	}

	// Deschide fișierul pentru scriere
	std::ofstream fout(filename);

	// Scrie datele în format CSV
	for (const auto& f : getAllCos())
	{
		fout << f.getTitlu() << ";" << f.getGen() << ";" << f.getAn() << ";" << f.getActor() << '\n';
	}

	// Închide fișierul
	fout.close();
}

std::unordered_map<string, int> FilmService::raport()
{
	std::unordered_map<string, int> rap;
	for (const Film& f : rep.getAll())
		rap[f.getGen()]++;
	return rap;
}

void FilmService::undo()
{
	if (undoAct.empty())
		throw RepoExceptions("Nu se mai poate face undo!\n\n");
	undoAct.back()->doUndo();
	undoAct.pop_back();
}