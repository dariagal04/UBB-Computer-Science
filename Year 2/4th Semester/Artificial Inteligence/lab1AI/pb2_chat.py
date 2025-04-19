import math

def distanta_euclidiana(p1, p2):
    x1, y1 = p1
    x2, y2 = p2
    return math.sqrt((x2 - x1) ** 2 + (y2 - y1) ** 2)

# Test
p1 = (1, 5)
p2 = (4, 1)
print(distanta_euclidiana(p1, p2))  # Output: 5.0
