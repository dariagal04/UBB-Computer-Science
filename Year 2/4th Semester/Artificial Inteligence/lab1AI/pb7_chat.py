import random


def quickselect(vector, k):
    if len(vector) == 1:
        return vector[0]  # Dacă avem un singur element, returnăm acel element

    pivot = random.choice(vector)  # Alegem pivot aleatoriu

    left = [x for x in vector if x > pivot]  # Elemente mai mari decât pivotul
    mid = [x for x in vector if x == pivot]  # Elemente egale cu pivotul
    right = [x for x in vector if x < pivot]  # Elemente mai mici decât pivotul

    if k <= len(left):
        return quickselect(left, k)  # Căutăm în partea stângă (numere mai mari)
    elif k <= len(left) + len(mid):
        return pivot  # Am găsit al k-lea cel mai mare element
    else:
        return quickselect(right, k - len(left) - len(mid))  # Căutăm în partea dreaptă


# Test
vector = [7, 4, 6, 3, 9, 1]
k = 2
print(quickselect(vector, k))  # Output: 7
