#include "IteratorMDO.h"
#include "MDO.h"
#include <stdexcept>

IteratorMDO::IteratorMDO(const MDO& d) : dict(d), current(nullptr) {
    prim();
}

void IteratorMDO::prim() {
    current = dict.radacina;
    stack.clear();
    while (current != nullptr) {
        stack.push_back(current);
        current = current->stanga;
    }
    if (!stack.empty()) {
        current = stack.back();
        stack.pop_back();
    }
    else {
        current = nullptr;
    }
}

void IteratorMDO::urmator() {
    if (!valid()) {
        throw std::runtime_error("Iterator invalid");
    }
    if (current->dreapta != nullptr) {
        current = current->dreapta;
        while (current != nullptr) {
            stack.push_back(current);
            current = current->stanga;
        }
    }
    if (!stack.empty()) {
        current = stack.back();
        stack.pop_back();
    }
    else {
        current = nullptr;
    }
}

bool IteratorMDO::valid() const {
    return current != nullptr;
}

TElem IteratorMDO::element() const {
    if (!valid()) {
        throw std::runtime_error("Iterator invalid");
    }
    return current->elem;
}
