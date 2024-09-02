#pragma once

#include "MDO.h"
#include <exception>
#include <list>
#include <utility>

typedef int TCheie;
typedef int TValoare;
typedef int TElem;
typedef bool (*Relatie)(TCheie, TCheie);
using namespace std;
using std::make_pair;
using std::pair;
class IteratorMDO {
private:
    friend class MDO; // MDO poate accesa membrii privați ai iteratorului

    // Referință către MDO pe care îl iterează
    const MDO& dict;

    // Pointer către nodul curent în MDO
    MDO::Nod* nodCurent; 

    // Iterator pentru lista de valori din nodul curent
    std::list<TValoare>::const_iterator itValoareCurenta;

    // Constructorul primește o referință către MDO
    IteratorMDO(const MDO& dictionar);

public:
    // Resetează poziția iteratorului la începutul MDO
    void prim();

    // Avansează iteratorul la următorul element din MDO
    // Aruncă o excepție dacă iteratorul nu este valid
    void urmator();

    // Retrogradează iteratorul la elementul precedent din MDO
    void precedent();

    // Verifică dacă iteratorul este valid (adică indică un element din MDO)
    bool valid() const;

    // Returnează elementul (perechea cheie-valoare) referit de iterator
    // Aruncă o excepție dacă iteratorul nu este valid
    std::pair<TCheie, TValoare> element() const;
};
