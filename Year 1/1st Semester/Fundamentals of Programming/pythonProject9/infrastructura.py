import math
import domeniu

def adauga_nr_complex(lista, parte_z, parte_i):
    domeniu.adaug(lista, parte_z, parte_i)
    print(lista)
    return lista


def adauga_pe_poz(lista, parte_z, parte_i, poz):
    numar = domeniu.creeaza_nrcomplex(parte_z, parte_i)
    lista.insert(poz, numar)
    print(lista)
    return lista


def sterge_depe_poz(lista, poz):
    del lista[poz]
    print(lista)
    return lista


def inlocuire_nr_complex(lista, pz, pi, parte_z, parte_i):
    numar = domeniu.creeaza_nrcomplex(parte_z, parte_i)
    for i in range(0, len(lista)):
        if lista[i][0] == pz and lista[i][1] == pi:
            lista[i] = numar
    print(lista)
    return lista


def tipareste_pi(lista, poz1, poz2, lista2):
    j = 0
    for i in range(poz1, poz2):
        lista2.insert(j, lista[i][1])
        j = j + 1
    print(lista2)
    return lista2



def prim(n):
    if n == 2:
        return 1
    if n < 2:
        return 0
    if n % 2 == 0:
        return 0
    d = 3
    while d * d <= n:
        if n % d == 0:
            return 0
        d += 2
    return 1


def suma_subsecventa(lista, poz1, poz2):
    suma_re = 0
    suma_im = 0
    for i in range(poz1, poz2):
        suma_re = suma_re + lista[i][0]
        suma_im = suma_im + lista[i][1]
    suma_secv = [suma_re, suma_im]
    print(suma_secv)
    return suma_secv


def prod_subsecventa(lista, poz1, poz2):
    prod_re = 1
    prod_im = 1
    for i in range(poz1, poz2):
        prod_re = prod_re * lista[i][0]
        prod_im = prod_im * lista[i][1]
    prod_secv = [prod_re, prod_im]
    print(prod_secv)
    return prod_secv


def sorteaza_descrescator(lista):
    lista_sortata = sorted(lista, key=lambda x: x[1], reverse=True)
    print(lista_sortata)
    return lista_sortata

listac = []

def copie(lista):
    listac = lista
    return listac

def undo():
   lista = listac
   print(lista)
   return lista