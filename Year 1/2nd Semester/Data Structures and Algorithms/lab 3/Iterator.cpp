#include "Iterator.h"
#include "MDO.h"
#include <exception>
#include <utility>
using namespace std;
using std::make_pair;
using std::pair;

IteratorMDO::IteratorMDO(const MDO& dictionar)
    : dict(dictionar), nodCurent(dictionar.primulNod) {
    // Dacă nodul curent nu este nullptr, setăm iteratorul de valori la începutul listei de valori
    if (nodCurent != nullptr) {
        itValoareCurenta = nodCurent->valori.begin();
    }
}

void IteratorMDO::prim() {
    // Resetează poziția iteratorului la începutul MDO
    nodCurent = dict.primulNod;
    if (nodCurent != nullptr) {
        itValoareCurenta = nodCurent->valori.begin();
    }
}

void IteratorMDO::urmator() {
    // Verifică dacă iteratorul este valid înainte de a avansa
    if (!valid()) {
        throw exception("Iterator invalid!");
    }

    // Avansează la următoarea valoare din lista de valori din nodul curent
    ++itValoareCurenta;

    // Dacă am ajuns la finalul listei de valori din nodul curent,
    // avansează la următorul nod și resetează iteratorul de valori
    if (itValoareCurenta == nodCurent->valori.end()) {
        nodCurent = nodCurent->urmator;
        if (nodCurent != nullptr) {
            itValoareCurenta = nodCurent->valori.begin();
        }
    }
}

void IteratorMDO::precedent() {
    // Verifică dacă iteratorul este valid înainte de a retrograda
    if (!valid()) {
        throw exception("Iterator invalid!");
    }

    // Retrogradează la valoarea precedentă din lista de valori din nodul curent
    if (itValoareCurenta != nodCurent->valori.begin()) {
        --itValoareCurenta;
    }
    else {
        // Dacă am ajuns la începutul listei de valori,
        // retrogradează la nodul precedent și setează iteratorul de valori
        nodCurent = nodCurent->precedent;
        if (nodCurent != nullptr) {
            itValoareCurenta = std::prev(nodCurent->valori.end());
        }
    }
}

bool IteratorMDO::valid() const {
    // Iteratorul este valid dacă nodul curent nu este nullptr
    // și iteratorul de valori din nodul curent este valid
    return nodCurent != nullptr && itValoareCurenta != nodCurent->valori.end();
}

std::pair<TCheie, TValoare> IteratorMDO::element() const {
    // Verifică dacă iteratorul este valid înainte de a returna elementul curent
    if (!valid()) {
        throw exception("Iterator invalid!");
    }

    // Returnează perechea (cheie-valoare) curentă
    //return std::make_pair<TCheie, TValoare>(nodCurent->cheie, *itValoareCurenta);
    return std::pair<TCheie, TValoare>(nodCurent->cheie, *itValoareCurenta);
}
