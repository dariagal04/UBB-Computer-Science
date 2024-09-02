#include "IteratorMDO.h"
#include "MDO.h"
#include <iostream>
#include <vector>
#include <list>
#include <exception>
#include <map>

using namespace std;

MDO::MDO(Relatie r) {
    this->rel = r;
    this->m = 101; // capacitate initiala a tabelei de dispersie
    this->dimensiune = 0;
    this->tabela = vector<list<pair<TCheie, vector<TValoare>>>>(m);
}

int MDO::dispersie(TCheie c) const {
    return abs(c) % m;
}

void MDO::adauga(TCheie c, TValoare v) {
    int poz = dispersie(c);
    for (auto& p : tabela[poz]) {
        if (p.first == c) {
            p.second.push_back(v);
            dimensiune++;
            return;
        }
    }
    vector<TValoare> valori = { v };
    tabela[poz].emplace_back(c, valori);
    dimensiune++;
}

vector<TValoare> MDO::cauta(TCheie c) const {
    int poz = dispersie(c);
    for (const auto& p : tabela[poz]) {
        if (p.first == c) {
            return p.second;
        }
    }
    return vector<TValoare>();
}

bool MDO::sterge(TCheie c, TValoare v) {
    int poz = dispersie(c);
    for (auto it = tabela[poz].begin(); it != tabela[poz].end(); ++it) {
        if (it->first == c) {
            auto& valori = it->second;
            for (auto vit = valori.begin(); vit != valori.end(); ++vit) {
                if (*vit == v) {
                    valori.erase(vit);
                    dimensiune--;
                    if (valori.empty()) {
                        tabela[poz].erase(it);
                    }
                    return true;
                }
            }
        }
    }
    return false;
}

int MDO::dim() const {
    return dimensiune;
}

bool MDO::vid() const {
    return dimensiune == 0;
}

IteratorMDO MDO::iterator() const {
    return IteratorMDO(*this);
}

TCheie MDO::ceaMaiFreqCheie() {
    if (vid()) {
        throw exception();
    }

    TCheie frecventa_cheie;
    int max_frecventa = 0;
    std::map<TCheie, int> frecvente;

    for (const auto& lista : tabela) {
        for (const auto& p : lista) {
            frecvente[p.first] += p.second.size();
            if (frecvente[p.first] > max_frecventa) {
                max_frecventa = frecvente[p.first];
                frecventa_cheie = p.first;
            }
        }
    }

    return frecventa_cheie;
}

/*
Algoritm ceaMaiFreqCheie():
    daca vid() atunci
       @Arunca o exceptie
    sf daca

    TCheie frecventa_cheie
    int max_frecventa = 0
    map<TCheie, int> frecvente

    pentru fiecare lista in tabela:
        pentru fiecare pereche p in lista:
             frecvente[p.first] = frecvente[p.first] + p.second.size()
             daca frecvente[p.first] > max_frecventa atunci
                max_frecventa = frecvente[p.first]
                frecventa_cheie = p.first
             sf daca
        sf pentru
    sf pentru
    returneaza frecventa_cheie
sf ceaMaiFreqCheie

*/

MDO::~MDO() {
    // Destructor implicit folosit pentru vector si list
}
