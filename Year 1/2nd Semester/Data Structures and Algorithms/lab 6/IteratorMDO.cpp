#include "IteratorMDO.h"
#include "MDO.h"
#include <exception>

IteratorMDO::IteratorMDO(const MDO& d) : dict(d) {
    prim();
}

void IteratorMDO::prim() {
    itTabla = dict.tabela.begin();
    while (itTabla != dict.tabela.end() && itTabla->empty()) {
        ++itTabla;
    }
    if (itTabla != dict.tabela.end()) {
        itLista = itTabla->begin();
        itValori = itLista->second.begin();
    }
}

void IteratorMDO::urmator() {
    if (!valid()) {
        throw exception();
    }
    ++itValori;
    if (itValori == itLista->second.end()) {
        ++itLista;
        if (itLista == itTabla->end()) {
            ++itTabla;
            while (itTabla != dict.tabela.end() && itTabla->empty()) {
                ++itTabla;
            }
            if (itTabla != dict.tabela.end()) {
                itLista = itTabla->begin();
                itValori = itLista->second.begin();
            }
        }
        else {
            itValori = itLista->second.begin();
        }
    }
}

bool IteratorMDO::valid() const {
    return itTabla != dict.tabela.end() && itLista != itTabla->end() && itValori != itLista->second.end();
}

TElem IteratorMDO::element() const {
    if (!valid()) {
        throw exception();
    }
    return { itLista->first, *itValori };
}
