from bisect import bisect_left

def linie_cu_cei_mai_multi_1(matrice):
    n, m = len(matrice), len(matrice[0])  # Dimensiuni matrice
    max_1 = 0  # Număr maxim de 1 găsit
    index_max = -1  # Indexul liniei cu cei mai mulți 1

    for i in range(n):
        linie = matrice[i]
        index_primul_1 = bisect_left(linie, 1)  # Căutăm primul 1 în linie (O(log m))
        numar_1 = m - index_primul_1  # Numărul de 1 este diferența până la final

        if numar_1 > max_1:  # Comparăm și actualizăm
            max_1 = numar_1
            index_max = i

    return index_max  # Returnăm indexul liniei cu cei mai mulți 1

# Test
matrice = [
    [0, 0, 0, 1, 1],
    [0, 1, 1, 1, 1],
    [0, 0, 1, 1, 1]
]
print(linie_cu_cei_mai_multi_1(matrice))  # Output: 1 (a doua linie)
