n = int(input("n ="))


def binary(n):
    nr = ""
    while n > 0:
        nr = str(n % 2) + nr
        n //= 2
    return nr


for i in range(1, n + 1):
    print(binary(i))
