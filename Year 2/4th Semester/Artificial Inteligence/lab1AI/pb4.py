print("pb 4")

text = input("Enter text: ")

def word_count(text):
    words = text.split()

    count = {}
    for word in words:
        if word in count:
            count[word] += 1
        else:
            count[word] = 1

    word_count1 = [word for word in count if count[word] == 1]

    return word_count1


text1 = word_count(text)
print(text1)

assert(word_count("ana ana are mere ana")) == ['are', 'mere']
assert(word_count("ana are are mere mere")) == ['ana']