def menu():
    print("MENIU")
    print("1. citire lista de numere intregi")
    print("2. afisare secventa maxima cu proprietatea ca are suma maxima")
    print("3. afisare secventa maxima cu proprietatea ca oricare doua numere alaturate au semne diferite:")
    print("4. afisare secventa maxima cu proprietatea ca p=1 sau diferentele (x[j+1] - x[j]) si (x[j+2] - x[j+1]) au semne contrare")
    print("0. iesire din aplicatie")


def optiune1():
    n = int(input("n="))
    list = []
    for i in range(0, n):
        elem = int(input())
        list.append(elem)
    return list


def optiune2(list):
    s = 0
    smax = 0
    l = 0
    cn = 0
    for i in range(0, len(list)):
        cn = cn + 1
        if s + int(list[i]) < s:
            l = 0
            s = 0
        else:
            s = s + int(list[i])
            l = l + 1
            if s > smax:
                smax = s
                lmax = cn
                llmax = l
    j = lmax - llmax
    while j < lmax:
        print(list[j])
        j = j + 1

def optiune3(list):
    cn = 1
    elm = 1
    lmax = 1
    el = int(list[0])
    for i in range(1, n):
        if el > 0 and int(list[i]) > 0:
            cn = 1
        if el < 0 and int(list[i]) < 0:
            cn = 1
        else:
            cn = cn + 1
            if cn >= lmax:
                lmax = cn
                elm = i
        el = int(list[i])
    print(list[elm - lmax + 1:elm + 1])

def optiune4(list):
    el1 = int(list[0])
    el2 = int(list[1])
    el3 = int(list[2])
    cn = 2
    lmax = 1
    elm = 0
    for i in range(3, n):
        if len(list) == 1:
            print(int(list[0]))
        if len(list) == 2:
            print(list[0:1])
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
        el3 = int(list[i])
    if lmax >= 3:
        print(list[elm - lmax + 1:elm])

menu()
optiune = int(input("alege optiunea: "))

list = optiune1()
while optiune != 0:
    optiune = input("alege optiunea: ")
    if optiune == 1:
        optiune1()
    if optiune == 2:
        optiune2(list)
    if optiune == 3:
        optiune3(list)
    if optiune == 4:
        optiune4(list)


    menu()
    optiune = int(input("alege optiunea: "))


