#pragma once

#include <vector>
#include <utility>
#include "Iterator.h"

typedef int TCheie;
typedef int TValoare;

typedef bool (*Relatie)(TCheie, TCheie);

class MDO {

private:
    friend class IteratorMDO; // Iteratorul are acces la membrii privați ai clasei MDO

    struct Nod {
        TCheie cheie; // Cheie din multidicționar
        //std::list<TValoare> valori; // Lista de valori asociate cheii
        TValoare* valori;
        Nod* urmator; // Nodul următor în lista înlănțuită simplă

        // Constructor pentru nod 
        Nod(TCheie c, TValoare v) : cheie(c), valori(nullptr), urmator(nullptr) {}
    };

    // Pointer către primul nod din lista înlănțuită simplă de chei distincte ordonate
    Nod* primulNod;

    // Relația de ordine între chei
    Relatie relatia;

public:
    // Constructorul implicit al multidicționarului
    MDO(Relatie r);

    // Adaugă o pereche (cheie, valoare) în multidicționar
    void adauga(TCheie c, TValoare v);

    // Caută o cheie și returnează vectorul de valori asociate acesteia
    std::vector<TValoare> cauta(TCheie c) const;

    // Șterge o pereche (cheie, valoare) și returnează adevărat dacă s-a găsit și șters
    bool sterge(TCheie c, TValoare v);

    // Returnează numărul de perechi (cheie, valoare) din multidicționar
    int dim() const;

    // Verifică dacă multidicționarul este gol
    bool vid() const;

    // Returnează un iterator pe multidicționar
    IteratorMDO iterator() const;

    // Destructorul multidicționarului
    ~MDO();
};
