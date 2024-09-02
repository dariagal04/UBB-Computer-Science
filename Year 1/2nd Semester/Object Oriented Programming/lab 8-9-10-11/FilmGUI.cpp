#include "FilmGUI.h"

#include<stdio.h>
#include<stdlib.h>
#include<string.h>


void FilmGUI::initGUI() {
	QHBoxLayout* lyMain = new QHBoxLayout;
	setLayout(lyMain);

	//lyMain->addWidget(lst);

	QWidget* stg = new QWidget;
	QVBoxLayout* stgLy = new QVBoxLayout;
	stg->setLayout(stgLy);

	QWidget* dr = new QWidget;
	QVBoxLayout* drLy = new QVBoxLayout;
	dr->setLayout(drLy);

	QWidget* form = new QWidget;
	QFormLayout* formLy = new QFormLayout;
	form->setLayout(formLy);
	formLy->addRow(lblTitlu, txtTitlu);
	formLy->addRow(lblGen, txtGen);
	formLy->addRow(lblAn, txtAn);
	formLy->addRow(lblActor, txtActor);

	formLy->addWidget(bAdauga);
	formLy->addWidget(bSterge);
	formLy->addWidget(bModifica);

	drLy->addWidget(form);

	QVBoxLayout* sortLy = new QVBoxLayout;
	sortari->setLayout(sortLy);
	sortLy->addWidget(sortTitlu);
	sortLy->addWidget(sortActor);
	sortLy->addWidget(sortAnGen);
	sortLy->addWidget(bsort);

	drLy->addWidget(sortari);

	QWidget* formFiltru = new QWidget;
	QFormLayout* filtruLy = new QFormLayout;
	formFiltru->setLayout(filtruLy);

	filtruLy->addRow(lblFiltruAn, txtFiltruAn);
	filtruLy->addWidget(bFiltruAn);

	filtruLy->addRow(lblFiltruTitlu, txtFiltruTitlu);
	filtruLy->addWidget(bFiltruTitlu);

	drLy->addWidget(formFiltru);

	stgLy->addWidget(bReincarcaFilme);

	drLy->addWidget(bUndo);

	int nLin = 10;
	int nCol = 4;
	tabelFilme = new QTableWidget{ nLin,nCol };

	QStringList tblHeaderList;
	tblHeaderList << "Titlu" << "Gen" << "An" << "Actor";
	tabelFilme->setHorizontalHeaderLabels(tblHeaderList);

	//tabelFilme->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

	stgLy->addWidget(tabelFilme);

	stgLy->addWidget(lst);

	butoaneGenuriW->setLayout(butoaneGenuri);

	for (const auto& pair : rap) {
		QPushButton* buton = new QPushButton(QString::fromStdString(pair.first));
		butoaneGenuri->addWidget(buton);

		connect(buton, &QPushButton::clicked, [=]() {
			QMessageBox::information(this, "Info", QString::fromStdString("Filme de tip %1: %2").arg(QString::fromStdString(pair.first)).arg(pair.second));
			});
	}

	stgLy->addWidget(butoaneGenuriW);

	drLy->addWidget(bCos);

	drLy->addWidget(bExit);

	lyMain->addWidget(stg);
	lyMain->addWidget(dr);
}

void FilmGUI::loadButoane() {
	QLayoutItem* aux;
	while ((aux = butoaneGenuri->takeAt(0)) != nullptr) {
		if (QWidget* widget = aux->widget()) {
			delete widget;
		}
		delete aux;
	}

	rap = srv.raport();

	for (const auto& pair : rap) {
		QPushButton* buton = new QPushButton(QString::fromStdString(pair.first));
		butoaneGenuri->addWidget(buton);

		connect(buton, &QPushButton::clicked, [=]() {
			QMessageBox::information(this, "Info", QString::fromStdString("Filme de tip %1: %2").arg(QString::fromStdString(pair.first)).arg(pair.second));
			});
	}
}

void FilmGUI::initConnect() {
	QObject::connect(bAdauga, &QPushButton::clicked, this, &FilmGUI::guiAdaugaFilm);
	QObject::connect(bModifica, &QPushButton::clicked, this, &FilmGUI::guiModificaFilm);
	QObject::connect(bSterge, &QPushButton::clicked, this, &FilmGUI::guiStergeFilm);

	QObject::connect(bExit, &QPushButton::clicked, [&]() {
		QMessageBox::information(this, "Info", "Iesire din aplicatie!");
		close();
		});

	QObject::connect(bUndo, &QPushButton::clicked, [&]() {
		try {
			try {
				this->srv.undo();
				this->loadDataList(srv.getAll());
				loadButoane();

				QMessageBox::information(this, "Info", QString::fromStdString("Undo efectuat!"));
			}
			catch (RepoExceptions& ex) {
				QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMesaj()));
			}
		}
		catch (Exception& ex1) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(ex1.getMesaj()));
		}
		});

	QObject::connect(bsort, &QPushButton::clicked, [&]() {
		if (sortTitlu->isChecked())
			loadDataList(srv.sortare_titlu());
		else if (sortActor->isChecked())
			loadDataList(srv.sortare_actor());
		else if (sortAnGen->isChecked())
			loadDataList(srv.sortare_an_gen());
		});

	QObject::connect(bFiltruAn, &QPushButton::clicked, [&]() {
		try {
			try {
				string filtru = txtFiltruAn->text().toStdString();
				loadDataList(srv.filtrareAn(std::stoi(filtru)));
				txtFiltruAn->clear();
			}
			catch (RepoExceptions& ex) {
				QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMesaj()));
			}
		}
		catch (Exception& ex1) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(ex1.getMesaj()));
		}
		});

	QObject::connect(bFiltruTitlu, &QPushButton::clicked, [&]() {
		try {
			try {
				string filtru = txtFiltruTitlu->text().toStdString();
				loadDataList(srv.filtrareTitlu(filtru));
				txtFiltruTitlu->clear();
			}
			catch (RepoExceptions& ex) {
				string filtru = txtFiltruAn->text().toStdString();
				loadDataList(srv.filtrareAn(std::stoi(filtru)));
				txtFiltruAn->clear();
			}
		}
		catch (Exception& ex1) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(ex1.getMesaj()));
		}
		});

	QObject::connect(bReincarcaFilme, &QPushButton::clicked, [&]() {
		loadDataList(srv.getAll());
		});

	QObject::connect(bCos, &QPushButton::clicked, [&]() {
		QWidget* meniuCos = new QWidget;
		QFormLayout* cosLy = new QFormLayout;
		meniuCos->setLayout(cosLy);
		cosLy->addRow("Titlu film: ", titluCos);
		cosLy->addWidget(bAdaugaCos);
		cosLy->addRow(lblRnd, numar);
		cosLy->addWidget(bAdaugaRandomCos);
		cosLy->addWidget(bGolesteCos);
		cosLy->addRow(lblExport, txtExport);
		cosLy->addWidget(bExportaCos);
		cosLy->addWidget(listaCos);
		meniuCos->show();
		});

	QObject::connect(bAdaugaCos, &QPushButton::clicked, [&]() {
		try {
			try {
				string titlu = titluCos->text().toStdString();
				titluCos->clear();
				srv.cosAdauga(titlu);
				loadDataCos(srv.getAllCos());
			}
			catch (RepoExceptions& ex) {
				QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMesaj()));
			}
		}
		catch (Exception& ex1) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(ex1.getMesaj()));
		}
		});

	QObject::connect(bAdaugaRandomCos, &QPushButton::clicked, [&]() {
		try {
			try {
				int nr = numar->text().toInt();
				numar->clear();
				srv.cosAdaugaRandom(nr);
				loadDataCos(srv.getAllCos());
			}
			catch (RepoExceptions& ex) {
				QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMesaj()));
			}
		}
		catch (Exception& ex1) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(ex1.getMesaj()));
		}
		});

	QObject::connect(bGolesteCos, &QPushButton::clicked, [&]() {
		srv.cosSterge();
		loadDataCos(srv.getAllCos());
		});

	QObject::connect(bExportaCos, &QPushButton::clicked, [&]() {
		try {
			string fis = txtExport->text().toStdString();
			txtExport->clear();
			srv.cosExport(fis);
			//listaCos->clear();
			//srv.cosSterge();
			loadDataCos(srv.getAllCos());

			QMessageBox::information(this, "Info", QString::fromStdString("Cos exportat!"));
		}
		catch (RepoExceptions& ex) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMesaj()));
		}
		});

}

void FilmGUI::loadDataList(vector<Film> filme) {
	tabelFilme->clearContents();
	tabelFilme->setRowCount(filme.size());

	int i = 0;
	for (auto& film : filme) {
		tabelFilme->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(film.getTitlu())));
		tabelFilme->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(film.getGen())));
		tabelFilme->setItem(i, 2, new QTableWidgetItem(QString::number(film.getAn())));
		tabelFilme->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(film.getActor())));
		i++;
	}

	lst->clear();
	for (const auto& film : filme) {
		auto f = new QListWidgetItem(QString::fromStdString(film.getTitlu() + " " + film.getGen() + " " + std::to_string(film.getAn()) + " " + film.getActor()));
		lst->addItem(f);
	}

}

void FilmGUI::loadDataCos(vector<Film> filme) {
	listaCos->clear();
	for (const auto& film : filme) {
		auto f = new QListWidgetItem(QString::fromStdString(film.getTitlu() + " " + film.getGen() + " " + std::to_string(film.getAn()) + " " + film.getActor()));
		listaCos->addItem(f);
	}
}

void FilmGUI::guiAdaugaFilm() {
	try {
		try {
			string titlu = txtTitlu->text().toStdString();
			string gen = txtGen->text().toStdString();
			int an = txtAn->text().toInt();
			string actor = txtActor->text().toStdString();

			txtTitlu->clear();
			txtGen->clear();
			txtAn->clear();
			txtActor->clear();

			srv.adauga(titlu, gen, an, actor);
			loadDataList(srv.getAll());
			loadButoane();

			QMessageBox::information(this, "Info", QString::fromStdString("Film adaugat!"));
		}
		catch (RepoExceptions& ex) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMesaj()));
		}
	}
	catch (Exception& ex1) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex1.getMesaj()));
	}
}

void FilmGUI::guiModificaFilm()
{
	try {
		try {
			string titlu = txtTitlu->text().toStdString();
			const auto& f = srv.cauta(titlu);

			//txtTitlu->clear();

			//string titlu1 = txtTitlu->text().toStdString();
			string gen = txtGen->text().toStdString();
			int an = txtAn->text().toInt();
			string actor = txtActor->text().toStdString();

			txtTitlu->clear();
			txtGen->clear();
			txtAn->clear();
			txtActor->clear();

			srv.modifica(titlu, gen, an, actor, f);
			loadDataList(srv.getAll());
			loadButoane();

			QMessageBox::information(this, "Info", QString::fromStdString("Film modificat!"));
		}
		catch (RepoExceptions& ex) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMesaj()));
		}
	}
	catch (Exception& ex1) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex1.getMesaj()));
	}
}

void FilmGUI::guiStergeFilm() {
	try {
		try {
			string titlu = txtTitlu->text().toStdString();
			txtTitlu->clear();

			const auto& f = srv.cauta(titlu);
			srv.sterge(f);
			loadDataList(srv.getAll());
			loadButoane();

			QMessageBox::information(this, "Info", QString::fromStdString("Film sters!"));
		}
		catch (RepoExceptions& ex) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMesaj()));
		}
	}
	catch (Exception& ex1) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex1.getMesaj()));
	}
}

