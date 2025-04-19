from collections import Counter

def cuvinte_unice(text):
    cuvinte = text.split()  # Separă cuvintele după spații
    frecvente = Counter(cuvinte)  # Numără aparițiile fiecărui cuvânt
    return [cuvant for cuvant, frecventa in frecvente.items() if frecventa == 1]

# Test
text = "ana are ana are mere rosii ana"
print(cuvinte_unice(text))
