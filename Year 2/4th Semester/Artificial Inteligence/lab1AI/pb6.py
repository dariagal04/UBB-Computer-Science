print("pb 6")

n = int(input("n = "))
vector = []
count = {}


for i in range(n):
    v = int(input())
    vector.append(v)

def major(vector):
    for v in vector:
        if v in count:
            count[v] += 1
            if count[v] > n/2:
                return v
        else:
            count[v] = 1

print(major(vector))

assert(major([2,8,7,2,2,5,2,3,1,2,2])) == 2
assert(major([1,1,1,1,1,1,2])) == 1