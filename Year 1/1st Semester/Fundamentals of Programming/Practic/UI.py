from Repo import *
from Business import *


class Start:

    def meniu(self):
        print("0. Stop")
        print("1. Adaugare carte")
        print("2. Sterge carte")
        print("3. Undo ultima operatie de stergere")

    def start(self):
        citire = CartiDinFisier("Carti.txt")
        lista_carti = citire.citeste_din_fisier()
        lista_copy = lista_carti
        self.meniu()
        print("lista de carti din fisier: ", lista_carti)
        option = 1
        while option :
            option = int(input("introduceti optiunea:"))
            if option == 1:
                id = int(input("dati id:"))
                titlu = input("dati titlu:")
                autor = input("dati autor:")
                anAparitie = int(input("dati anul aparitiei"))
                carte = Carti(id, titlu, autor, anAparitie)
                a = Adaugare()
                lista_carti = a.adauga(lista_carti, carte.get_id(), carte.get_titlu(), carte.get_autor(), carte.get_anAparitie())
                print(lista_carti)
                lista_copy = a.adauga(lista_copy, carte.get_id(), carte.get_titlu(), carte.get_autor(), carte.get_anAparitie())
                citire.scrie_in_fisier(lista_carti)
            if option == 2:
                lista_copy = lista_carti
                cifra = int(input("dati o cifra:"))
                s = Sterge()
                lista_carti = s.sterge(lista_carti, cifra)
                print(lista_carti)
                citire.scrie_in_fisier(lista_carti)
            if option == 3:
                lista_carti = lista_copy
                print(lista_carti)
                citire.scrie_in_fisier(lista_carti)