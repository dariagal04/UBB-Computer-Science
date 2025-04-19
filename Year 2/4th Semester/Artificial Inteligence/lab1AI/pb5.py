print("pb 5")

n = int(input("n= "))
vector = []
count = {}

i = 0
while i < n:
    v = int(input())
    if v < n:
        vector.append(v)
        i += 1
    else:
        print("enter number under " + str(n))

def counts(vector, count):
    result = -1
    for v in vector:
        if v in count:
            count[v] += 1
        else:
            count[v] = 1
        if count[v] > 1:
            result = v
    return result

print(counts(vector, count))

assert(counts([1,2,3,4,2],{})) == 2
assert(counts([1,1,2,3,4],{})) == 1
