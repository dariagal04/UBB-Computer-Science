def compute_prefix_sum(matrix):
    """ Construiește matricea de sume prefixate """
    n, m = len(matrix), len(matrix[0])
    prefix = [[0] * m for _ in range(n)]

    # Calculăm suma prefixată
    for i in range(n):
        for j in range(m):
            prefix[i][j] = matrix[i][j]
            if i > 0:
                prefix[i][j] += prefix[i - 1][j]
            if j > 0:
                prefix[i][j] += prefix[i][j - 1]
            if i > 0 and j > 0:
                prefix[i][j] -= prefix[i - 1][j - 1]

    return prefix


def submatrix_sum(prefix, p, q, r, s):
    """ Returnează suma sub-matricii definite de (p, q) și (r, s) """
    total = prefix[r][s]
    if p > 0:
        total -= prefix[p - 1][s]
    if q > 0:
        total -= prefix[r][q - 1]
    if p > 0 and q > 0:
        total += prefix[p - 1][q - 1]
    return total


# Exemplu de utilizare
matrix = [
    [0, 2, 5, 4, 1],
    [4, 8, 2, 3, 7],
    [6, 3, 4, 6, 2],
    [7, 3, 1, 8, 3],
    [1, 5, 7, 9, 4]
]

pairs = [((1, 1), (3, 3)), ((2, 2), (4, 4))]

# Construim matricea de sume prefixate
prefix = compute_prefix_sum(matrix)

# Calculăm suma pentru fiecare pereche de coordonate
for (p, q), (r, s) in pairs:
    print(f"Suma elementelor din sub-matricea ({p}, {q}) - ({r}, {s}): {submatrix_sum(prefix, p, q, r, s)}")


#  O(n × m) (preprocesare) + O(1) (per interogare) temporal , O(n × m) spatial