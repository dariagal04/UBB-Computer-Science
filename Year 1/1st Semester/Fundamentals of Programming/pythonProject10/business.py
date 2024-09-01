import infrastructura
import domeniu
import math

def adauga(lista, numar):
    lista.append(numar)


def adaug(lista, x, y):
    numar = domeniu.creeaza_nrcomplex(x, y)
    adauga(lista, numar)

def sterg_interval(lista, poz1, poz2):
    for i in range(poz1,poz2):
        infrastructura.sterge_depe_poz(lista,i)
    return lista

def modul_numar_maimic(lista, lista3):
    j = 0
    for i in range(0, len(lista) - 1):
        real = domeniu.get_re(lista[i])
        imaginar = domeniu.get_im(lista[i])
        nr = math.sqrt(real * real + imaginar * imaginar)
        if nr < 10:
            lista3.insert(j, domeniu.creeaza_nrcomplex(real, imaginar))
            j = j + 1
    return lista3

def modul_numar_egal(lista, lista4):
    j = 0
    for i in range(0, len(lista) - 1):
        real = domeniu.get_re(lista[i])
        imaginar = domeniu.get_im(lista[i])
        nr = math.sqrt(real * real + imaginar * imaginar)
        if nr == 10:
            lista4.insert(j, domeniu.creeaza_nrcomplex(real, imaginar))
            j = j + 1
    return lista4

def suma_subsecventa(lista, poz1, poz2):
    suma_re = 0
    suma_im = 0
    for i in range(poz1, poz2):
        suma_re = suma_re + domeniu.get_re(lista[i])
        suma_im = suma_im + domeniu.get_im(lista[i])
    suma_secv = domeniu.creeaza_nrcomplex(suma_re, suma_im)
    return suma_secv


def prod_subsecventa(lista, poz1, poz2):
    prod_re = 1
    prod_im = 1
    for i in range(poz1, poz2):
        prod_re = prod_re * domeniu.get_re(lista[i])
        prod_im = prod_im * domeniu.get_im(lista[i])
    prod_secv = domeniu.creeaza_nrcomplex(prod_re, prod_im)
    return prod_secv

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

def filtrare_prime(lista):
    i = 0
    while i < len(lista):
        if prim(domeniu.get_re(lista[i])):
            del lista[i]
        else:
            i += 1
    return lista

def filtrare_modul(lista, semn, numar_comp):
    for i in range(0, len(lista) - 1):
        real = domeniu.get_re(lista[i])
        imaginar = domeniu.get_im(lista[i])
        nr = math.sqrt(real * real + imaginar * imaginar)
        if semn == '<' and nr < numar_comp:
            del lista[i]
        if semn == '=' and nr == numar_comp:
            del lista[i]
        if semn == '>' and nr > numar_comp:
            del lista[i]
    return lista