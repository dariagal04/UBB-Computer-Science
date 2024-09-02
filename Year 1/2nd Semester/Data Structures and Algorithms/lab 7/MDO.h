#pragma once

#include <vector>
#include <utility>
#include <unordered_map>
#include <map>


typedef int TCheie;
typedef int TValoare;

typedef std::pair<TCheie, TValoare> TElem;
typedef bool(*Relatie)(TCheie, TCheie);


class IteratorMDO;

class MDO {
    friend class IteratorMDO;
private:
    struct Nod {
        TElem elem;
        Nod* stanga;
        Nod* dreapta;
        Nod(TElem e, Nod* s = nullptr, Nod* d = nullptr) : elem(e), stanga(s), dreapta(d) {}
    };

    Nod* radacina;
    Relatie rel;
    int dimensiune;

    void distruge(Nod* nod);
    Nod* adauga_rec(Nod* nod, TCheie c, TValoare v);
    Nod* sterge_rec(Nod* nod, TCheie c, TValoare v, bool& gasit);
    Nod* minValueNode(Nod* node);
    std::vector<TValoare> cauta_rec(Nod* nod, TCheie c) const;

public:
    // constructorul implicit al MultiDictionarului Ordonat
    MDO(Relatie r);

    // adauga o pereche (cheie, valoare) in MDO
    void adauga(TCheie c, TValoare v);

    // cauta o cheie si returneaza vectorul de valori asociate
    std::vector<TValoare> cauta(TCheie c) const;

    // sterge o cheie si o valoare
    bool sterge(TCheie c, TValoare v);

    // returneaza numarul de perechi (cheie, valoare) din MDO
    int dim() const;

    // verifica daca MultiDictionarul Ordonat e vid
    bool vid() const;

    //returneaza cea mai frecventa valoare din MultiDictionarul Ordonat
    TCheie ceaMaiFreqCheie();

    void ceaMaiFreqCheieRec(Nod* nod, std::map<TCheie, int>& frecvente) const;

    // se returneaza iterator pe MDO
    IteratorMDO iterator() const;

    // destructorul
    ~MDO();
};
