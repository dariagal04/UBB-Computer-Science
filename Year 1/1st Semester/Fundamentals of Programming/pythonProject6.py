lista = [5, 6, -4, 13, 12, -1]

def optiune1(lista):
    n = int(input("n= "))
    for i in range(0, n):
        element = int(input())
        lista.append(element)
    return lista


def optiune2(lista):
    s = 0
    smax = 0
    l = 0
    cn = 0
    for i in range(0, len(lista)):
        cn = cn + 1
        if s + int(lista[i]) < s:
            l = 0
            s = 0
        else:
            s = s + int(lista[i])
            l = l + 1
            if s > smax:
                smax = s
                lmax = cn
                llmax = l
    return lista[llmax-lmax:lmax]




def optiune3(lista):
    cn = 1
    elm = 1
    lmax = 1
    el = int(lista[0])
    for i in range(1, len(lista)):
        if el > 0 and int(lista[i]) > 0:
            cn = 1
        if el < 0 and int(lista[i]) < 0:
            cn = 1
        else:
            cn = cn + 1
            if cn >= lmax:
                lmax = cn
                elm = i
        el = int(lista[i])
    return lista[elm - lmax + 2:elm + 1]

def optiune4(lista):
    el1 = int(lista[0])
    el2 = int(lista[1])
    el3 = int(lista[2])
    cn = 2
    lmax = 1
    elm = 0
    for i in range(3, len(lista)):
        if len(lista) == 1:
            print(int(lista[0]))
        if len(lista) == 2:
            print(lista[0:1])
        if el2 - el1 > 0 and el3 - el2 > 0:
            cn = 2
        if el2 - el1 < 0 and el3 - el2 < 0:
            cn = 2
        else:
            cn = cn + 1
            if cn >= lmax:
                lmax = cn
                elm = i
        el1 = el2
        el2 = el3
        el3 = int(lista[i])
    if lmax >= 2:
        return lista[elm - lmax + 1:elm]



def teste():
    assert optiune2([5, 6, -4, 13, 12, -1]) == [13, 12]
    assert optiune3([1, 7, -4, 15, 12, -4]) == [7, -4, 15]
    assert optiune4([5, 6, -4, 13, 12, -1]) == [6, -4, 13, 12]

def meniu():
    print("MENIU")
    print("1. citire lista de numere intregi")
    print("2. afisare secventa maxima cu proprietatea ca are suma maxima")
    print("3. afisare secventa maxima cu proprietatea ca oricare doua numere alaturate au semne diferite:")
    print("4. afisare secventa maxima cu proprietatea ca p=1 sau diferentele (x[j+1] - x[j]) si (x[j+2] - x[j+1]) au semne contrare")
    print("0. iesire din aplicatie")

teste()
meniu()
optiune = int(input("alegeti o optiune din meniu:"))



while optiune != 0:
    if optiune == 1:
        optiune1(lista)
    if optiune == 2:
        print(optiune2(lista))
    if optiune == 3:
        print(optiune3(lista))
    if optiune == 4:
        print(optiune4(lista))
    meniu()
    optiune = int(input("alegeti o optiune din meniu: "))