#pragma once

#include "MDO.h"

class IteratorMDO {
    friend class MDO;
private:
    const MDO& dict;
    vector<list<pair<TCheie, vector<TValoare>>>>::const_iterator itTabla;
    list<pair<TCheie, vector<TValoare>>>::const_iterator itLista;
    vector<TValoare>::const_iterator itValori;

    // constructorul primeste o referinta catre Container
    // iteratorul va referi primul element din container
    IteratorMDO(const MDO& dictionar);

public:
    // reseteaza pozitia iteratorului la inceputul containerului
    void prim();

    // muta iteratorul in container
    // arunca exceptie daca iteratorul nu e valid
    void urmator();

    // verifica daca iteratorul e valid (indica un element al containerului)
    bool valid() const;

    // returneaza valoarea elementului din container referit de iterator
    // arunca exceptie daca iteratorul nu e valid
    TElem element() const;
};
