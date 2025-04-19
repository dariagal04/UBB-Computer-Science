import math

def euclidian(p1, p2):
    x1, y1 = p1
    x2, y2 = p2
    e = math.sqrt((x2 - x1) ** 2 + (y2 - y1) ** 2)
    return e


p1 = (1, 5)
p2 = (4, 1)
print(euclidian(p1, p2))
