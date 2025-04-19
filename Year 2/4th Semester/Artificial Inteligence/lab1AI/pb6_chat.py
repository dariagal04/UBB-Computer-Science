from collections import Counter


def element_majoritar(nums):
    frecventa = Counter(nums)
    n = len(nums)

    for num, count in frecventa.items():
        if count > n // 2:
            return num
    return None  # Dacă nu există un element majoritar


# Test
sir = [2, 8, 7, 2, 2, 5, 2, 3, 1, 2, 2]
print(element_majoritar(sir))  # Output: 2
