#include "ui.h"
#include "domain.h"
#include "VectorDinamic.h"
#include <iostream>
using std::cin;
using std::cout;
void UI::startUI()
{
	while (true) {
		cout << "1. Adauga\n2. Sterge\n3. Modifica\n4. Afisare\n5. Cautare\n6. Filtrare\n7. Sortare\n0. Exit\n Command: ";
		int cmd = 0;
		cin >> cmd;
		if (cmd == 0)
			break;
		if (cmd == 1)
		{
			int apartament;
			string proprietar;
			int suprafata;
			string tip;
			cout << "apartament: ";
			cin >> apartament;
			cout << "proprietar: ";
			std::cin.ignore();
			std::getline(std::cin, proprietar);
			cout << "suprafata: ";
			cin >> suprafata;
			cout << "tip: ";
			std::cin.ignore();
			std::getline(std::cin, tip);

			try {
				srv.adauga(apartament, proprietar, suprafata, tip);
				cout << "Locatar adaugat!\n\n";
			}
			catch (RepoExceptions ex) {
				cout << ex.getMesaj();
			}
		}
		if (cmd == 2)
		{
			int apartament;
			string proprietar;
			int suprafata;
			string tip;
			cout << "apartament: ";
			cin >> apartament;
			cout << "proprietar: ";
			std::cin.ignore();
			std::getline(std::cin, proprietar);
			cout << "suprafata: ";
			cin >> suprafata;
			cout << "tip: ";
			std::cin.ignore();
			std::getline(std::cin, tip);
			try {
				if (srv.sterge(apartament, proprietar, suprafata, tip) == 1)
					cout << "Locatarul nu exista!\n\n";
				else
					cout << "Locatar sters!\n\n";
			}
			catch (RepoExceptions ex) {
				cout << ex.getMesaj();
			}
		}
		if (cmd == 3)
		{
			int apartament;
			string proprietar;
			int suprafata;
			string tip;
			cout << "apartament: ";
			cin >> apartament;
			cout << "proprietar: ";
			std::cin.ignore();
			std::getline(std::cin, proprietar);
			cout << "suprafata: ";
			cin >> suprafata;
			cout << "tip: ";
			std::cin.ignore();
			std::getline(std::cin, tip);
			try {
				const auto& ok = srv.cauta(apartament, proprietar, suprafata, tip);
				if (ok == -1)
					cout << "Locatarul nu exista!\n\n";
				else
				{
					int apartament1;
					string proprietar1;
					int suprafata1;
					string tip1;
					cout << "apartament nou: ";
					cin >> apartament1;
					cout << "proprietar nou: ";
					std::cin.ignore();
					std::getline(std::cin, proprietar1);
					cout << "suprafata noua: ";
					cin >> suprafata1;
					cout << "tip nou: ";
					std::cin.ignore();
					std::getline(std::cin, tip1);
					try {
						srv.modifica(apartament1, proprietar1, suprafata1, tip1, ok);
						cout << "Locatar modificat!\n\n";
					}
					catch (RepoExceptions ex) {
						cout << ex.getMesaj();
					}
				}
			}
			catch (RepoExceptions ex) {
				cout << ex.getMesaj();
			}
		}
		if (cmd == 4)
		{
			VectorDinamic<Locatar> bloc{ srv.getAll() };
			if (bloc.size() == 0)
				cout << "Nu exista locatari in lista!\n\n";
			else
			{
				cout << "locatari:\n";
				for (auto const& f : bloc)
					cout << "apartament: " << f.getApartament() << " | proprietar: " << f.getProprietar() << " | suprafata: " << f.getSuprafata() << " | tip: " << f.getTip() << '\n';
				cout << '\n';
			}
		}
		if (cmd == 5)
		{
			int apartament;
			string proprietar;
			int suprafata;
			string tip;
			cout << "apartament: ";
			cin >> apartament;
			cout << "proprietar: ";
			std::cin.ignore();
			std::getline(std::cin, proprietar);
			cout << "suprafata: ";
			cin >> suprafata;
			cout << "tip: ";
			std::cin.ignore();
			std::getline(std::cin, tip);
			try {
				const auto& ok = srv.cauta(apartament, proprietar, suprafata, tip);
				if (ok == -1)
					cout << "Locatarul nu exista!\n\n";
				else
					cout << "Locatarul e pe pozitia " << ok << ".\n\n";
			}
			catch (RepoExceptions ex) {
				cout << ex.getMesaj();
			}

		}
		if (cmd == 6)
		{
			cout << "Introduceti numele campului dupa care doriti sa fie facuta filtrarea(tip, suprafata): ";
			string filtru;
			cin >> filtru;
			if (filtru == "tip")
			{
				string tip;
				cout << "Introduceti tip: ";
				std::cin.ignore();
				std::getline(std::cin, tip);
				try {
					auto loc = srv.filtraretip(tip);
					if (loc.size() == 0)
						cout << "Nu exista filme corespunzatoare filtrului!\n\n";
					for (const auto& f : loc)
						cout << "apartament: " << f.getApartament() << " | proprietar: " << f.getProprietar() << " | suprafata: " << f.getSuprafata() << " | tip: " << f.getTip() << '\n';
					cout << '\n';
				}
				catch (RepoExceptions ex) {
					cout << ex.getMesaj();
				}
			}
			else if (filtru == "suprafata")
			{
				int suprafata;
				cout << "Introduceti suprafata: ";
				cin >> suprafata;
				try {
					auto loc = srv.filtraresuprafata(suprafata);
					if (loc.size() == 0)
						cout << "Nu exista locatari corespunzatoari filtrului!\n\n";
					for (const auto& f : loc)
						cout << "apartament: " << f.getApartament() << " | proprietar: " << f.getProprietar() << " | suprafata: " << f.getSuprafata() << " | tip: " << f.getTip() << '\n';
					cout << '\n';
				}
				catch (RepoExceptions ex) {
					cout << ex.getMesaj();
				}
			}
			else
				cout << "Camp invalid!\n\n";
		}
		if (cmd == 7)
		{
			srv.sortare();
			VectorDinamic<Locatar> bloc{ srv.getAll() };
			if (bloc.size() == 0)
				cout << "Nu exista filme in lista!\n\n";
			else
			{
				cout << "Locatari:\n";
				for (auto const& f : bloc)
					cout << "apartament: " << f.getApartament() << " | proprietar: " << f.getProprietar() << " | suprafata: " << f.getSuprafata() << " | tip: " << f.getTip() << '\n';
				cout << '\n';
			}
		}
	}
}