from Domain import *
class CartiDinFisier:

    def __init__(self, nume_fisier):
        self.nume_fisier = nume_fisier
        self.lista_carti = self.citeste_din_fisier()

    #am definit obiectul CartiDinFisier avand parametru numele fisierului din care/in care se vor lua/pune elemente

    def citeste_din_fisier(self):
        lista_carti = []
        try:
            with open(self.nume_fisier, 'r') as file:
                for linie in file:
                    linie = linie.strip()  #luam linie cu linie
                    if linie:
                        id, titlu, autor, anAparitie = linie.split(',') #elementele din fisier sunt separate prin ','
                        carte = Carti(int(id), titlu, autor, int(anAparitie)) #il facem obiect si il punem mai apoi in lista
                        lista_carti.append([carte.get_id(), carte.get_titlu(), carte.get_autor(), carte.get_anAparitie()])
        except FileNotFoundError:
            print(f"Fisierul {self.nume_fisier} nu a fost gasit.")
        except Exception as e:
            print(f"Eroare la citirea fisierului: {e}")
        return lista_carti


    def scrie_in_fisier(self, lista):
        with open(self.nume_fisier, 'w') as file:
            for carte in lista:
                #id, titlu, autor, anAparitie = carte
                file.write(f"{carte[0]},{carte[1]},{carte[2]},{carte[3]}\n")#fiecare obiect este pus in fisier, elementele fiind separate prin ','
