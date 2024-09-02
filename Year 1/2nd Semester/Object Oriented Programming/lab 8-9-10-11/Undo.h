#pragma once
#include "domain.h"
#include "repository.h"

class ActiuneUndo {
public:
	virtual void doUndo() = 0;

	virtual ~ActiuneUndo() {};
};

class UndoAdauga :public ActiuneUndo {
	RepoAbstract& rep;
	Film f;
public:
	UndoAdauga(RepoAbstract& rep, const Film& f) :rep{ rep }, f{ f } {}

	void doUndo() override {
		rep.stergeFilm(f);
	}
};

class UndoModifica : public ActiuneUndo {
	Film fvechi;
	Film fnou;
	RepoAbstract& rep;
public:
	UndoModifica(RepoAbstract& rep, const Film& fvechi, const Film& fnou) :rep{ rep }, fvechi{ fvechi }, fnou{ fnou } {}

	void doUndo() override {
		rep.modificaFilm(fnou, fvechi);
	}
};

class UndoSterge : public ActiuneUndo {
	Film fsters;
	RepoAbstract& rep;
public:
	UndoSterge(RepoAbstract& rep, const Film& fsters) :rep{ rep }, fsters{ fsters } {}

	void doUndo() override {
		rep.adaugaFilm(fsters);
	}
};