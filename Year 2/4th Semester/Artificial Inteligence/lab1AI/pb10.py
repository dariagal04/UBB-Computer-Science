print("pb 10")

n = int(input("n = "))
m = int(input("m = "))

matrice = []
i = 0
while i < n:
    line = list(map(int, input().split()))
    if len(line) == m:
        matrice.append(line)
        i += 1
    else:
        print("O linie trebuie să aibă " + str(m) + " elemente!")

def search_line(matrice):
    n = len(matrice)
    m = len(matrice[0])
    one_count = 0
    index = -1

    for i in range(n):
        left, right = 0, m - 1
        count = 0

        while left <= right:
            mid = (left + right) // 2
            if matrice[i][mid] == 1:
                count = m - mid
                right = mid - 1
            else:
                left = mid + 1

        if count > one_count:
            one_count = count
            index = i

    return index + 1


assert search_line([[0, 0, 0, 1, 1],
                    [0, 1, 1, 1, 1],
                    [0, 0, 1, 1, 1]]) == 2
assert search_line([[0, 1, 1, 1, 1],
                    [0, 0, 0, 1, 1],
                    [1, 1, 1, 1, 1],
                    [0, 0, 0, 0, 1]]) == 3

print(search_line(matrice))
