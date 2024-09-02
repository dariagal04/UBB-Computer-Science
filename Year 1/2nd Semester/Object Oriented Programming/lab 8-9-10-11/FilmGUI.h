#pragma once
#include <vector>
#include <string>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/qlistwidget.h>
#include <QStringList>
#include "service.h"

class FilmGUI : public QWidget {
private:

	FilmService& srv;

	std::unordered_map<string, int> rap = srv.raport();

	QLabel* lblTitlu = new QLabel{ "Titlu: " };
	QLabel* lblGen = new QLabel{ "Gen: " };
	QLabel* lblAn = new QLabel{ "An: " };
	QLabel* lblActor = new QLabel{ "Actor: " };

	QLineEdit* txtTitlu = new QLineEdit;
	QLineEdit* txtGen = new QLineEdit;
	QLineEdit* txtAn = new QLineEdit;
	QLineEdit* txtActor = new QLineEdit;

	QListWidget* lst = new QListWidget;

	QPushButton* bAdauga = new QPushButton("Adauga");
	QPushButton* bSterge = new QPushButton("Sterge");
	QPushButton* bModifica = new QPushButton("Modifica");
	QPushButton* bExit = new QPushButton{ "Exit" };

	QGroupBox* sortari = new QGroupBox(tr("Tip sortare"));

	QRadioButton* sortTitlu = new QRadioButton(QString::fromStdString("Titlu"));
	QRadioButton* sortActor = new QRadioButton(QString::fromStdString("Gen"));
	QRadioButton* sortAnGen = new QRadioButton(QString::fromStdString("An+Gen"));
	QPushButton* bsort = new QPushButton("Sortare");

	QLabel* lblFiltruAn = new QLabel{ "Anul dupa care se filtreaza:" };
	QLineEdit* txtFiltruAn = new QLineEdit;
	QPushButton* bFiltruAn = new QPushButton("Filtreaza dupa an");

	QLabel* lblFiltruTitlu = new QLabel{ "Titlul dupa care se filtreaza:" };
	QLineEdit* txtFiltruTitlu = new QLineEdit;
	QPushButton* bFiltruTitlu = new QPushButton("Filtreaza dupa titlu");

	QPushButton* bUndo = new QPushButton("Undo");

	QPushButton* bReincarcaFilme = new QPushButton("Reincarca filme");

	QTableWidget* tabelFilme;

	QPushButton* bCos = new QPushButton("Accesare cos");
	QPushButton* bAdaugaCos = new QPushButton("Adauga film in cos");
	QLineEdit* titluCos = new QLineEdit;
	QPushButton* bAdaugaRandomCos = new QPushButton("Adauga filme random in cos");
	QLineEdit* numar = new QLineEdit;
	QPushButton* bGolesteCos = new QPushButton("Goleste cos");
	QListWidget* listaCos = new QListWidget;

	QLineEdit* txtExport = new QLineEdit;
	QPushButton* bExportaCos = new QPushButton("Exporta cos");
	QLabel* lblRnd = new QLabel{ "Numar random:" };
	QLabel* lblExport = new QLabel{ "Nume fisier:" };

	QWidget* butoaneGenuriW = new QWidget;
	QVBoxLayout* butoaneGenuri = new QVBoxLayout;

	void initGUI();

	void loadDataList(vector<Film> filme);

	void loadDataCos(vector<Film> filme);

	void initConnect();

	void loadButoane();
public:
	FilmGUI(FilmService& srv) :srv{ srv } {
		initGUI();
		initConnect();
		try {
			loadDataList(srv.getAll());
		}
		catch (Exception& ex1) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(ex1.getMesaj()));
		}
	}

	void guiAdaugaFilm();
	void guiStergeFilm();
	void guiModificaFilm();
};

