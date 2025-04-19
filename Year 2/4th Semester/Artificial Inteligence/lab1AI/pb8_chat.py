n = int(input("Introduceți n: "))

for i in range(1, n + 1):
    print(bin(i)[2:])

# aceleasi complexitati O(nlogn) si O(logn)