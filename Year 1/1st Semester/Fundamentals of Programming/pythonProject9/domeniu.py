def creeaza_nrcomplex(real, imag):
    numar = [real, imag]
    return numar


def set_re(numar, re):
    numar[0] = re


def set_im(numar, im):
    numar[1] = im


def get_re(numar):
    return numar[0]


def get_im(numar):
    return numar[1]


def adauga(lista, numar):
    lista.append(numar)

def adaug(lista, x, y):
    numar = creeaza_nrcomplex(x, y)
    adauga(lista, numar)
