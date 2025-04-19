print("pb 7")


n = int(input("n = "))
k = int(input("k = "))
vector = []


for i in range(n):
    v = int(input())
    vector.append(v)

def quicksort_desc(arr):
    if len(arr) <= 1:
        return arr

    pivot = arr[len(arr) // 2]
    left = [x for x in arr if x > pivot]
    mid = [x for x in arr if x == pivot]
    right = [x for x in arr if x < pivot]

    return quicksort_desc(left) + mid + quicksort_desc(right)

def kth_largest(vector, k):
    sorted_vector = quicksort_desc(vector)
    return sorted_vector[k-1]

print(kth_largest(vector,k))
assert(kth_largest([7,4,6,3,9,1], 2)) == 7
assert(kth_largest([1,2,3,4,5],3)) == 3
