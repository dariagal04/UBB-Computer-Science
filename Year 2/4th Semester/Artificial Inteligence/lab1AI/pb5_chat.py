def gaseste_dublura_math(lista):
    n = len(lista)
    suma_asteptata = sum(range(1, n))  # Suma numerelor de la 1 la n-1
    suma_reala = sum(lista)  # Suma numerelor din listă
    return suma_reala - suma_asteptata  # Diferența dă numărul care s-a repetat

# Test
print(gaseste_dublura_math([1, 2, 3, 4, 2]))  # Output: 2
