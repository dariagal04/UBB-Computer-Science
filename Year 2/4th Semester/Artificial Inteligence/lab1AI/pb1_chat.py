def ultimul_cuvant_alfabetic(text):
    cuvinte = text.split()  # Separăm cuvintele după spațiu
    return max(cuvinte)  # Găsim cuvântul maxim alfabetic

# Test
text = "Ana are mere rosii si galbene"
print(ultimul_cuvant_alfabetic(text))  # Output: "si"
