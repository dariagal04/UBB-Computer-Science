import math


def citestenumar():
    x  =int(input("valoarea reala a numarului: "))
    y = int(input("valoarea imaginara a numarului: "))
    adaug(lista, x, y)


def creeaza_nrcomplex(real, imag):
    numar =[real, imag]
    return numar


def set_re(numar, re):
    numar[0] = re


def set_im(numar, im):
    numar[1] = im


def get_re(numar):
    return numar[0]


def get_im(numar):
    return numar[1]


lista = []


def adauga(lista, numar):
    lista.append(numar)


def adauga_nr_complex(lista, parte_z, parte_i):
    adaug(lista, parte_z, parte_i)
    print(lista)
    return lista


def adauga_pe_poz(lista, parte_z, parte_i, poz):
    numar = creeaza_nrcomplex(parte_z, parte_i)
    lista.insert(poz, numar)
    print(lista)
    return lista


def sterge_depe_poz(lista, poz):
    del lista[poz]
    print(lista)
    return lista

def sterg_interval(lista, poz1, poz2):
    for i in range(poz2 - poz1 + 1):
        del lista[poz1]
    print(lista)
    return lista


def inlocuire_nr_complex(lista, pz, pi, parte_z, parte_i):
    numar = creeaza_nrcomplex(parte_z, parte_i)
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


def modul_numar_maimic(lista, lista3):
    j = 0
    for i in range(0, len(lista)-1):
        real = get_re(lista[i])
        imaginar = get_im(lista[i])
        nr = math.sqrt(real*real + imaginar*imaginar)
        if nr < 10:
            lista3.insert(j, creeaza_nrcomplex(real, imaginar))
            j = j + 1
    print(lista3)
    return lista3





def modul_numar_egal(lista, lista4):
    j = 0
    for i in range(0, len(lista)-1):
        real = get_re(lista[i])
        imaginar = get_im(lista[i])
        nr = math.sqrt(real * real + imaginar * imaginar)
        if nr == 10:
            lista4.insert(j, creeaza_nrcomplex(real, imaginar))
            j = j + 1
    print(lista4)
    return lista4


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
        if prim(int(lista[i][0])):
            del lista[i]
        else:
            i += 1
    print(lista)
    return lista

def suma_subsecventa(lista, poz1, poz2):
    suma_re = 0
    suma_im = 0
    for i in range (poz1, poz2):
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


def filtrare_modul(lista, semn, numar_comp):
    for i in range(0, len(lista)-1):
        real = get_re(lista[i])
        imaginar = get_im(lista[i])
        nr = math.sqrt(real * real + imaginar * imaginar)
        if semn == '<' and nr < numar_comp:
            del lista[i]
        if semn == '=' and nr == numar_comp:
            del lista[i]
        if semn == '>' and nr > numar_comp:
            del lista[i]
    print(lista)
    return lista



def adaug(lista, x, y):
    numar = creeaza_nrcomplex(x, y)
    adauga(lista, numar)


def meniu():
    print("MENIU")
    print("1. adaugare nr in lista")
    print("2. modificare numere lista")
    print("3. cautare numere")
    print("4. operatii cu numere din lista")
    print("5. filtrare")
    print("6. undo")
    print("0. iesire aplicatie")
    
def meniu1():
    print("MENIU OPTIUNE 1")
    print("1. Adaugă număr complex la sfârșitul listei")
    print("2. Inserare număr complex pe o poziție dată")
    print("3. iesire")
    
def meniu2():
    print("MENIU OPTIUNEA 2")
    print("1. Șterge element de pe o poziție dată")
    print("2. Șterge elementele de pe un interval de poziții.")
    print("3. Înlocuiește toate aparițiile unui număr complex cu un alt număr complex.")
    print("4. iesire")
    
def meniu3():
    print("MENIU OPTIUNEA 3")
    print("1. Tipărește partea imaginara pentru numerele din listă. Se dă intervalul de poziții (sub secvența).")
    print("2. Tipărește toate numerele complexe care au modulul mai mic decât 10")
    print("3. Tipărește toate numerele complexe care au modulul egal cu 10")
    print("4. iesire")
    
def meniu4():
    print("MENIU OPTIUNEA 5")
    print("1. Tipărește suma numerelor dintr-o subsecventă dată (se da poziția de început și sfârșit)")
    print("2. Tipărește Produsul numerelor dintr-o subsecventă dată (se da poziția de început și sfârșit)")
    print("3. Tipărește lista sortată descrescător după partea imaginara")
    print("4. iesire")

def meniu5():
    print("MENIU OPTIUNEA 5")
    print("1. Filtrare parte reala prim – elimină din listă numerele complexe la care partea reala este prim")
    print("2. Filtrare modul – elimina din lista numerele complexe la care modulul este <,= sau > decât un număr dat.")
    print("3. iesire")

def teste():
    assert adauga_nr_complex([[1, 2], [3, 4], [5, 6], [7, 8]], 9, 10) == [[1, 2], [3, 4], [5, 6], [7, 8], [9, 10]]
    assert adauga_pe_poz([[1, 2], [3, 4], [5, 6], [7, 8]], 9, 10, 2) == [[1, 2], [3, 4], [9, 10],[5, 6], [7, 8]]
    assert sterge_depe_poz([[1, 2], [3, 4], [5, 6], [7, 8]], 3) == [[1, 2], [3, 4], [5, 6]]
    assert sterg_interval([[1, 2], [3, 4], [5, 6], [7, 8]], 1, 2) == [[1, 2], [7, 8]]
    assert inlocuire_nr_complex([[1, 2], [3, 4], [3, 4], [7, 8]], 3, 4, 9, 10) == [[1, 2], [9, 10], [9, 10], [7, 8]]
    assert tipareste_pi([[1, 2], [3, 4], [5, 6], [7, 8]], 1, 3, []) == [4, 6]
    assert modul_numar_maimic([[1, 0], [10, 0], [5, 0], [11, 0]], []) == [[1, 0], [5, 0]]
    assert modul_numar_egal([[1, 0], [10, 0], [5, 0], [11, 0]], []) == [[10, 0]]
    assert suma_subsecventa([[1, 2], [3, 4], [5, 6], [7, 8]], 1, 3) == [8, 10]
    assert prod_subsecventa([[1, 2], [3, 4], [5, 6], [7, 8]], 1, 3) == [15, 24]
    assert sorteaza_descrescator([[1, 2], [3, 4], [5, 6], [7, 8]]) == [[7, 8], [5, 6], [3, 4], [1, 2]]
    assert filtrare_prime([[1, 2], [3, 4], [5, 6], [8, 8]]) == [[1, 2], [8, 8]]
    assert filtrare_modul([[1, 0], [10, 0], [5, 0], [11, 0]], '=', 10) == [[1, 0], [5, 0], [11, 0]]

teste()


def start():
    meniu()
    lungime = int(input("lungimea listei: "))
    while lungime:
        citestenumar()
        lungime = lungime - 1
    while True:
        option = input("scrie optiunea: ")
        if option == '1':
            meniu1()
            optiune = input("scrie optiunea: ")
            if optiune == '1':
                parte_z = int(input("parte reala: "))
                parte_i = int(input("parte imaginara: "))
                adauga_nr_complex(lista, parte_z, parte_i)
            elif optiune == '2':
                parte_z = int(input("parte reala: "))
                parte_i = int(input("parte imaginara: "))
                poz = int(input("pozitia: "))
                adauga_pe_poz(lista, parte_z, parte_i, poz)
            elif optiune == '3':
                return start()
        elif option == '2':
            meniu2()
            optiune = input("scrie optiunea: ")
            if optiune == '1':
                poz = int(input("pozitia: "))
                sterge_depe_poz(lista, poz)
            elif optiune == '2':
                poz1 = int(input("pozitiade inceput: "))
                poz2 = int(input("pozitia de sfarsit: "))
                sterg_interval(lista, poz1, poz2)
            elif optiune == '3':
                pz = int(input("parte reala numar existent: "))
                pi = int(input("parte imaginara numar existent: "))
                parte_z = int(input("parte reala numar nou: "))
                parte_i = int(input("parte imaginara numar nou: "))
                inlocuire_nr_complex(lista, pz, pi, parte_z, parte_i)
            elif optiune == '4':
                return start()
        elif option == '3':
            meniu3()
            optiune = input("scrie optiunea: ")
            if optiune == '1':
                lista2 = []
                poz1 = int(input("pozitiade inceput: "))
                poz2 = int(input("pozitia de sfarsit: "))
                tipareste_pi(lista, poz1, poz2, lista2)
            elif optiune == '2':
                lista3 = []
                modul_numar_maimic(lista, lista3)
            elif optiune == '3':
                lista4 = []
                modul_numar_egal(lista, lista4)
            elif optiune == '4':
                return start()
        elif option == '4':
            meniu4()
            optiune = input("scrie optiunea: ")
            if optiune == '1':
                poz1 = int(input("pozitiade inceput: "))
                poz2 = int(input("pozitia de sfarsit: "))
                suma_subsecventa(lista, poz1, poz2)
            elif optiune == '2':
                poz1 = int(input("pozitiade inceput: "))
                poz2 = int(input("pozitia de sfarsit: "))
                prod_subsecventa(lista, poz1, poz2)
            elif optiune == '3':
                sorteaza_descrescator(lista)
            elif optiune == '4':
                return start()
        elif option == '5':
            meniu5()
            optiune = input("scrie optiunea: ")
            if optiune == '1':
                filtrare_prime(lista)
            elif optiune == '2':
                numar_comp = float(input("numar cu care se compara: "))
                semn = str(input("semnul: "))
                filtrare_modul(lista, semn, numar_comp)
            elif optiune == '3':
                return start()
        elif option == '0':
            return



start()







