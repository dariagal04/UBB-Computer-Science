import infrastructura
import domeniu
import math

def sterg_interval(lista, poz1, poz2):
    for i in range(poz2 - poz1 + 1):
        infrastructura.sterge_depe_poz(lista, i)
    print(lista)
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
    print(lista3)
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
    print(lista4)
    return lista4

def filtrare_prime(lista):
    i = 0
    while i < len(lista):
        if infrastructura.prim(int(lista[i][0])):
            del lista[i]
        else:
            i += 1
    print(lista)
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
    print(lista)
    return lista