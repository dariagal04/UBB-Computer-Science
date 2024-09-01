def creeaza_nrcomplex(real, imag):
    numar = {"real": real, "imag": imag}
    return numar


def set_re(numar, re):
    numar["real"] = re


def set_im(numar, im):
    numar["imag"] = im


def get_re(numar):
    return numar["real"]


def get_im(numar):
    return numar["imag"]

