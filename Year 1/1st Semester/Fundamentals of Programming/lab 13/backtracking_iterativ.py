def coliniar(p1, p2, p3):
    return (p2[1] - p1[1]) * (p3[0] - p2[0]) == (p3[1] - p2[1]) * (p2[0] - p1[0])

def puncte_coliniare_iteraiv(puncte):
    n = len(puncte)
    if n < 3:
        print("nu sunt suficiente puncte")
        return
    puncte_colineare = []
    for i in range(n):
        for j in range(i+1, n):
            for k in range(j+1, n):
                if coliniar(puncte[i], puncte[j], puncte[k]):
                    puncte_colineare.append([puncte[i], puncte[j], puncte[k]])
    if puncte_colineare:
        for i in puncte_colineare:
            print(i)
    else:
        print("nu exista multimi de puncte colineare")

def start():
    punctee = []
    n = int(input("cate puncte doresti sa introduci?: "))
    for i in range (1,n+1):
        print("x", i, "=")
        x = int(input())
        print("y", i, "=")
        y = int(input())
        punct = [x, y]
        punctee.append(punct)
    puncte_coliniare_iteraiv(punctee)

#from backtracking_recursiv import *
start()


