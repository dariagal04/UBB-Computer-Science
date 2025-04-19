def produs_scalar(vector1, vector2):
    produs = 0
    for i in range(len(vector1)):
        if vector1[i] != 0 and vector2[i] != 0:  # Optimizare: calculăm doar pentru elemente nenule
            produs += vector1[i] * vector2[i]
    return produs

# Test
v1 = [1, 0, 2, 0, 3]
v2 = [1, 2, 0, 3, 1]
print(produs_scalar(v1, v2))  # Output: 4
