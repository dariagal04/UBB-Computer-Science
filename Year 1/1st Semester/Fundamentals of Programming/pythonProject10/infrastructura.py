import domeniu
import business

def adauga_nr_complex(lista, parte_z, parte_i):
    business.adaug(lista, parte_z, parte_i)
    return lista


def adauga_pe_poz(lista, parte_z, parte_i, poz):
    numar = domeniu.creeaza_nrcomplex(parte_z, parte_i)
    lista.insert(poz, numar)
    return lista


def sterge_depe_poz(lista, poz):
    del lista[poz]
    return lista


def inlocuire_nr_complex(lista, pz, pi, parte_z, parte_i):
    numar = domeniu.creeaza_nrcomplex(parte_z, parte_i)
    for i in range(0, len(lista)):
        if domeniu.get_re(lista[i]) == pz and domeniu.get_im(lista[i]) == pi:
            lista[i] = numar
    return lista


def tipareste_pi(lista, poz1, poz2, lista2):
    j = 0
    for i in range(poz1, poz2):
        lista2.insert(j, domeniu.get_im(lista[i]))
        j = j + 1
    return lista2


def sorteaza_descrescator(lista):
    lista_sortata = sorted(lista, key=lambda x: x['imag'], reverse=True)
    return lista_sortata

listac = []

def copie(lista):
    listac = lista
    return listac

def undo():
   lista = listac
   print(lista)
   return lista

