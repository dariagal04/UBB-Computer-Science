n = int(input("n="))
list = []
for i in range(0, n):
    elem = int(input())
    list.append(elem)
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
    print(list[elm-lmax+1:elm])
