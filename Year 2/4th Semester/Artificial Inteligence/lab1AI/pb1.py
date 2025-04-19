
text = input("Enter text: ")

def alphabetic(text):
    words = text.split()
    last = words[0]

    for word in words[1:]:
        if word > last:
            last = word

    return last

print(alphabetic(text))
