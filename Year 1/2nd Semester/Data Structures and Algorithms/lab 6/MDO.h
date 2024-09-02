#pragma once

#include <vector>
#include <list>
#include <utility>

typedef int TCheie;
typedef int TValoare;

typedef std::pair<TCheie, TValoare> TElem;
using namespace std;

class IteratorMDO;

typedef bool(*Relatie)(TCheie, TCheie);

class MDO {
    friend class IteratorMDO;
private:
    vector<list<pair<TCheie, vector<TValoare>>>> tabela; // lista de liste pentru rezolvarea coliziunilor
    Relatie rel;
    int m; // capacitatea tabelei
    int dimensiune; // numarul de elemente din tabelă

    int dispersie(TCheie c) const; // funcția de dispersie

public:
    // constructorul implicit al MultiDictionarului Ordonat
    MDO(Relatie r);

    // adauga o pereche (cheie, valoare) in MDO
    void adauga(TCheie c, TValoare v);

    // cauta o cheie si returneaza vectorul de valori asociate
    vector<TValoare> cauta(TCheie c) const;

    // sterge o cheie si o valoare
    // returneaza adevarat daca s-a gasit cheia si valoarea de sters
    bool sterge(TCheie c, TValoare v);

    // returneaza numarul de perechi (cheie, valoare) din MDO 
    int dim() const;

    // verifica daca MultiDictionarul Ordonat e vid 
    bool vid() const;

    //returneaza cea mai frecventa valoare din MultiDictionarul Ordonat
    TCheie ceaMaiFreqCheie();

    // se returneaza iterator pe MDO
    // iteratorul va returna perechile in ordine in raport cu relatia de ordine
    IteratorMDO iterator() const;

    // destructorul 	
    ~MDO();
};
