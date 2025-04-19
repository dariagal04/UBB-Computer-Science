def scalar_product(x, y):
    if len(x) != len(y):
        return
    product = 0
    for i in range(len(x)):
        product += x[i] * y[i]
    return product

assert scalar_product([1,0,2,0,3], [1,2,0,3,1]) == 4
