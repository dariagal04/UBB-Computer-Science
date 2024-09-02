#include "MDO.h"
#include "Iterator.h"
#include <stdexcept>

MDO::MDO(Relatie r) : primulNod(nullptr), relatia(r) {
    // Constructorul inițializează multidicționarul gol și relația de ordine dată
}

void MDO::adauga(TCheie c, TValoare v) {
    // Creează un nod nou și îl adaugă în lista înlănțuită în funcție de relația de ordine
    Nod* newNod = new Nod(c, v);

    if (primulNod == nullptr) {
        // Dacă multidicționarul este gol, adaugă nodul nou ca primul no d
        primulNod = newNod;
        return;
    }

    // Parcurge lista pentru a găsi locul de inserare
    Nod* current = primulNod;
    Nod* previous = nullptr;

    while (current != nullptr) {
        if (relatia(c, current->cheie)) {
            // Dacă relația de ordine este îndeplinită, oprește căutarea
            break;
        }
        previous = current;
        current = current->urmator;
    }

    if (previous == nullptr) {
        // Inserare la începutul listei
        newNod->urmator = primulNod;
        primulNod = newNod;
    }
    else {
        // Inserare între previous și current
        newNod->urmator = current;
        previous->urmator = newNod;
    }
}

std::vector<TValoare> MDO::cauta(TCheie c) const {
    // Parcurge lista pentru a găsi cheia căutată și returnează valorile asociate
    Nod* current = primulNod;
    while (current != nullptr) {
        if (current->cheie == c) {
            // Cheia a fost găsită, returnează lista de valori asociate
            return std::vector<TValoare>(current->valori.begin(), current->valori.end());
        }
        current = current->urmator;
    }
    // Dacă nu a fost găsită, returnează un vector gol
    return std::vector<TValoare>();
}

bool MDO::sterge(TCheie c, TValoare v) {
    // Parcurge lista pentru a găsi cheia și valoarea de șters
    Nod* current = primulNod;
    while (current != nullptr) {
        if (current->cheie == c) {
            // Cheia a fost găsită, verifică valorile asociate
            for (auto it = current->valori.begin(); it != current->valori.end(); ++it) {
                if (*it == v) {
                    // Valoarea a fost găsită, șterge-o din lista
                    current->valori.erase(it);
                    // Dacă lista de valori devine goală, șterge nodul
                    if (current->valori.empty()) {
                        if (current->precedent != nullptr) {
                            current->precedent->urmator = current->urmator;
                        }
                        else {
                            primulNod = current->urmator;
                        }
                        if (current->urmator != nullptr) {
                            current->urmator->precedent = current->precedent;
                        }
                        delete current;
                    }
                    return true; // Ștergerea a avut succes
                }
            }
        }
        current = current->urmator;
    }
    return false; // Nu a fost găsită cheia sau valoarea
}

int MDO::dim() const {
    // Parcurge lista pentru a număra toate perechile (cheie, valoare) din multidicționar
    int count = 0;
    Nod* current = primulNod;
    while (current != nullptr) {
        // Adaugă numărul de valori din nod la contorul total
        count += current->valori.size();
        current = current->urmator;
    }
    return count;
}

bool MDO::vid() const {
    // Verifică dacă multidicționarul este gol
    return primulNod == nullptr;
}

IteratorMDO MDO::iterator() const {
    // Returnează un iterator care pornește de la începutul multidicționarului
    return IteratorMDO(*this);
}

MDO::~MDO() {
    // Eliberează memoria alocată pentru toate nodurile din multidicționar
    Nod* current = primulNod;
    while (current != nullptr) {
        Nod* temp = current;
        current = current->urmator;
        delete temp;
    }
}
