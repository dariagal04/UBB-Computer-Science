def coliniar(p1, p2, p3):
    return (p2[1] - p1[1]) * (p3[0] - p2[0]) == (p3[1] - p2[1]) * (p2[0] - p1[0])

def puncte_coliniare_recursiv(puncte, selectate, start, k):
    nr = 0
    if k == 0:
        # Verificam coliniaritatea pentru combinatia curenta
        colineare = [puncte[i] for i in selectate]
        for i in range(len(colineare) +1):
            for j in range(i + 1, len(colineare)):
                for l in range(j + 1, len(colineare)):
                    if coliniar(colineare[i], colineare[j], colineare[l]):
                        # Dacă avem cel puțin trei puncte colineare, le tipărim
                        print(colineare)
                        nr = nr + 1
                        return nr
        return nr
    else:
    # Generam combinatiile recursiv
        for i in range(start, len(puncte)):
            selectate[k - 1] = i
            nr += puncte_coliniare_recursiv(puncte, selectate, i + 1, k - 1)
        return nr
"""
def gaseste_puncte_colineare(puncte):
    gasit = False
    selectate = [0] * 3
    nr = puncte_coliniare_recursiv(puncte, selectate, 0, 3)
    if nr > 0:
        gasit = True

    if not gasit:
        print("Nu s-au gasit puncte coliniare.")
"""

def gaseste_puncte_colineare(puncte):
    gasit = False
    for k in range(3, len(puncte) + 1):
        selectate = [0] * k
        nr = puncte_coliniare_recursiv(puncte, selectate, 0, k)
        if nr > 0:
            gasit = True

    if not gasit:
        print("Nu s-au gasit puncte coliniare.")


def start2():
    punctee = []
    n = int(input("cate puncte doresti sa introduci?: "))
    for i in range (1,n+1):
        print("x", i, "=")
        x = int(input())
        print("y", i, "=")
        y = int(input())
        punct = [x, y]
        punctee.append(punct)
    gaseste_puncte_colineare(punctee)

