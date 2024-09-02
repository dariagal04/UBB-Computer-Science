#pragma once

#include "MDO.h"

class IteratorMDO {
    friend class MDO;
private:
    const MDO& dict;
    MDO::Nod* current;
    std::vector<MDO::Nod*> stack;

    IteratorMDO(const MDO& dictionar);

public:
    void prim();
    void urmator();
    bool valid() const;
    TElem element() const;
};
