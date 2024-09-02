#include "IteratorMDO.h"
#include "MDO.h"
#include <iostream>
#include <vector>
#include <exception>
#include <unordered_map>
#include <map>

using namespace std;

// Constructorul implicit al MultiDictionarului Ordonat
// Complexitate: O(1)
MDO::MDO(Relatie r) : radacina(nullptr), rel(r), dimensiune(0) {}

// Adauga o pereche (cheie, valoare) in MDO
// Complexitate: O(h), unde h este inaltimea arborelui
void MDO::adauga(TCheie c, TValoare v) {
    radacina = adauga_rec(radacina, c, v);
    dimensiune++;
}

// Functie recursiva pentru adaugare
// Complexitate: O(h)
MDO::Nod* MDO::adauga_rec(Nod* nod, TCheie c, TValoare v) {
    if (nod == nullptr) {
        return new Nod(make_pair(c, v));
    }
    if (rel(c, nod->elem.first)) {
        nod->stanga = adauga_rec(nod->stanga, c, v);
    }
    else {
        nod->dreapta = adauga_rec(nod->dreapta, c, v);
    }
    return nod;
}

// Cauta o cheie si returneaza vectorul de valori asociate
// Complexitate: O(h)
vector<TValoare> MDO::cauta(TCheie c) const {
    return cauta_rec(radacina, c);
}

// Functie recursiva pentru cautare
// Complexitate: O(h + k), unde k este numarul de valori asociate cu cheia
vector<TValoare> MDO::cauta_rec(Nod* nod, TCheie c) const {
    if (nod == nullptr) {
        return {};
    }
    if (nod->elem.first == c) {
        vector<TValoare> rezultat = { nod->elem.second };
        vector<TValoare> stanga = cauta_rec(nod->stanga, c);
        vector<TValoare> dreapta = cauta_rec(nod->dreapta, c);
        rezultat.insert(rezultat.end(), stanga.begin(), stanga.end());
        rezultat.insert(rezultat.end(), dreapta.begin(), dreapta.end());
        return rezultat;
    }
    else if (rel(c, nod->elem.first)) {
        return cauta_rec(nod->stanga, c);
    }
    else {
        return cauta_rec(nod->dreapta, c);
    }
}

// Sterge o cheie si o valoare
// Complexitate: O(h)
bool MDO::sterge(TCheie c, TValoare v) {
    bool gasit = false;
    radacina = sterge_rec(radacina, c, v, gasit);
    if (gasit) dimensiune--;
    return gasit;
}

// Functie recursiva pentru stergere
// Complexitate: O(h)
MDO::Nod* MDO::sterge_rec(Nod* nod, TCheie c, TValoare v, bool& gasit) {
    if (nod == nullptr) return nod;

    if (c == nod->elem.first && v == nod->elem.second) {
        gasit = true;
        if (nod->stanga == nullptr) {
            Nod* temp = nod->dreapta;
            delete nod;
            return temp;
        }
        else if (nod->dreapta == nullptr) {
            Nod* temp = nod->stanga;
            delete nod;
            return temp;
        }
        Nod* temp = minValueNode(nod->dreapta);
        nod->elem = temp->elem;
        nod->dreapta = sterge_rec(nod->dreapta, temp->elem.first, temp->elem.second, gasit);
    }
    else if (rel(c, nod->elem.first)) {
        nod->stanga = sterge_rec(nod->stanga, c, v, gasit);
    }
    else {
        nod->dreapta = sterge_rec(nod->dreapta, c, v, gasit);
    }
    return nod;
}

// Gaseste nodul cu valoarea minima
// Complexitate: O(h)
MDO::Nod* MDO::minValueNode(Nod* node) {
    Nod* current = node;
    while (current && current->stanga != nullptr)
        current = current->stanga;
    return current;
}

// Returneaza numarul de perechi (cheie, valoare) din MDO 
// Complexitate: O(1)
int MDO::dim() const {
    return dimensiune;
}

// Verifica daca MultiDictionarul Ordonat e vid
// Complexitate: O(1)
bool MDO::vid() const {
    return dimensiune == 0;
}

// Returneaza iterator pe MDO
// Complexitate: O(1)
IteratorMDO MDO::iterator() const {
    return IteratorMDO(*this);
}

// Destructorul
// Complexitate: O(n), unde n este numărul de noduri
MDO::~MDO() {
    distruge(radacina);
}

// Distruge recursiv toate nodurile
// Complexitate: O(n)
void MDO::distruge(Nod* nod) {
    if (nod == nullptr) return;
    distruge(nod->stanga);
    distruge(nod->dreapta);
    delete nod;
}

// Returneaza cea mai frecventa cheie din MDO
// Complexitate: O(n)
TCheie MDO::ceaMaiFreqCheie() {
    std::map < TCheie, int > frecvente;
    ceaMaiFreqCheieRec(radacina, frecvente);
    int maxFreq = 0;
    TCheie cheieMaxFreq = -1;
    for (const auto& pereche : frecvente) {
        if (pereche.second > maxFreq) {
            maxFreq = pereche.second;
            cheieMaxFreq = pereche.first;
        }
    }
    return cheieMaxFreq;
}

// Functie recursiva pentru ceaMaiFreqCheie
// Complexitate: O(n)
void MDO::ceaMaiFreqCheieRec(Nod* nod, std::map<TCheie, int>& frecvente) const {
    if (nod == nullptr) return;
    frecvente[nod->elem.first]++;
    ceaMaiFreqCheieRec(nod->stanga, frecvente);
    ceaMaiFreqCheieRec(nod->dreapta, frecvente);
}
