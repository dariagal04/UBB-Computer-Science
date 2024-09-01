class Adaugare:

    def adauga(self, lista_carti, id, titlu, autor, anAparitie):
        lista_carti.append([int(id), titlu, autor, int(anAparitie)])
        return lista_carti
    #adauga in lista noul element

class Sterge:

    def sterge(self, lista_carti, cifra):
        lista = []
        for carte in lista_carti:
            an = int(carte[3])
            nr = 0
            while an > 0:
                uc = an % 10 #se ia mereu ultima cifra si se compara cu cifra data
                an = an // 10 #dupa ce luam ultima cifra, scapam de ea impartind an la 10
                if uc == cifra:
                    nr = nr + 1 #se numara de c ate ori apare cifra in numar
            if nr == 0:
                lista.append([int(carte[0]), carte[1], carte[2], int(carte[3])]) #daca apare de 0 ori atunci se va face o lista noua in care vor fi adaugate aceste elemente
        return lista