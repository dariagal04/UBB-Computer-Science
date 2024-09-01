def meniu():
    print("MENIU")
    print("1. adaugare nr in lista")
    print("2. modificare numere lista")
    print("3. cautare numere")
    print("4. operatii cu numere din lista")
    print("5. filtrare")
    print("6. undo")
    print("0. iesire aplicatie")

meniu()
optiune = int(input("alegeti o optiune din meniu:"))
lista = [2, 3, 10, 11]


def optiune1(lista):
    meniu1()
    opt1 = int(input("alegeti o optiune din meniu:"))
    while opt1 != 3:
        if opt1 == 1:
            print(optiunea11(lista))
            break
        if opt1 == 2:
            print(optiunea12(lista))
            break
    return lista


def meniu1():
    print("MENIU OPTIUNE 1")
    print("1. Adaugă număr complex la sfârșitul listei")
    print("2. Inserare număr complex pe o poziție dată")
    print("3. iesire")


def optiunea11(lista):
    element = complex(input("element = "))
    lista.append(element)
    return lista


def optiunea12(lista):
    p = int(input("pozitia= "))
    nr = complex(input("numarul care se va insera= "))
    lista.insert(p, nr)
    return lista


def optiune2(lista,nre,nri):
    meniu2()
    opt2 = int(input("alegeti o optiune din meniu:"))
    while opt2 != 4:
        if opt2 == 1:
            print(optiunea21(lista))
            break
        if opt2 == 2:
            print(optiunea22(lista))
            break
        if opt2 == 3:
            print(optiunea23(lista, nre, nri))
            break
    return lista


def meniu2():
    print("MENIU OPTIUNEA 2")
    print("1. Șterge element de pe o poziție dată")
    print("2. Șterge elementele de pe un interval de poziții.")
    print("3. Înlocuiește toate aparițiile unui număr complex cu un alt număr complex.")
    print("4. iesire")


def optiunea21(lista):
    p = int(input("pozitia= "))
    del lista[p]
    return lista


def optiunea22(lista):
    poz1 = int(input("pozitia de inceput= "))
    poz2 = int(input("pozitia de sfarsit= "))
    for i in range(poz2-poz1+1):
         del lista[poz1]
    return lista


def optiunea23(lista, nre, nri):
    for i in range(0,len(lista)):
        if lista[i] == nre:
            lista[i] = nri
    return lista


def optiune3(lista):
    meniu3()
    opt3 = int(input("alegeti o optiune din meniu:"))
    while opt3 != 4:
        if opt3 == 1:
            optiunea31(lista)
            break
        if opt3 == 2:
            optiunea32(lista)
            break
        if opt3 == 3:
            optiunea33(lista)
            break
    return lista


def meniu3():
    print("MENIU OPTIUNEA 3")
    print("1. Tipărește partea imaginara pentru numerele din listă. Se dă intervalul de poziții (sub secvența).")
    print("2. Tipărește toate numerele complexe care au modulul mai mic decât 10")
    print("3. Tipărește toate numerele complexe care au modulul egal cu 10")
    print("4. iesire")


def optiunea31(lista):
    poz1 = int(input("pozitia de inceput= "))
    poz2 = int(input("pozitia de sfarsit= "))
    for i in range (poz1, poz2):
        print(lista[i].imag)


def optiunea32(lista):
    for i in range(len(lista)):
        if abs(lista[i]) < 10:
            print(lista[i])

def optiunea33(lista):
    for i in range(len(lista)):
        if abs(lista[i]) == 10:
            print(lista[i])




while optiune != 0:
    if optiune == 1:
        optiune1(lista)
    if optiune == 2:
        optiune2(lista)
    if optiune == 3:
        optiune3(lista)
    meniu()

    optiune = int(input("alegeti o optiune din meniu: "))