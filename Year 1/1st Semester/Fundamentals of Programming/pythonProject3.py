n = int(input("n="))
lista = []
for i in range(0, n):
    print(i)
    elem = int(input())
    lista.append(elem)
    i=0
    nr=1
    mx=0
    p = 0
    while i<len(lista)-1:
        j=i+1
        if (int(lista[i])>0 and int(lista[j])<0) or (int(lista[i])<0 and int(lista[j])>0):
            nr+=1
            p=j
        else:
            if nr>mx:
                mx=nr
                pm=p
                nr=1
            if nr>mx:
                mx=nr
                pm=p
    i = i + 1
print(lista[pm-mx+1:pm+1])