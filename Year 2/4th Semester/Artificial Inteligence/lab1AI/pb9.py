def submatrix_sum(matrix, top_left, bottom_right):
    total_sum = 0
    for i in range(top_left[0], bottom_right[0] + 1):
        for j in range(top_left[1], bottom_right[1] + 1):
            total_sum += matrix[i][j]
    return total_sum
matrix = [
    [0, 2, 5, 4, 1],
    [4, 8, 2, 3, 7],
    [6, 3, 4, 6, 2],
    [7, 3, 1, 8, 3],
    [1, 5, 7, 9, 4]
]

pairs = [((1, 1), (3, 3)), ((2, 2), (4, 4))]


for pair in pairs:
    top_left, bottom_right = pair
    result = submatrix_sum(matrix, top_left, bottom_right)
    print(result)


# O(r*c) dimensiunile matricei O(n*m) in cel mai rau caz O(1) la spatiu