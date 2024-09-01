from domain.DomainEveniment import *
import random
import string
from Repository.RepoEveniment import *

class AdaugaEveniment:

    def adauga_eveniment(self, lista_evenimente, ID, data, timp, descriere):
        eveniment = Eveniment(ID, data, timp, descriere).create_eveniment(ID, data, timp, descriere)
        self.adaug(lista_evenimente, eveniment)

    def adaug(self, lista_evenimente, eveniment):
        lista_evenimente.append(eveniment)

class RandomEvenimente:

    def adauga_evenimente_aleatorii(self, lista_persoane, numar_entitati):
        for x in range(numar_entitati):
            ID = len(lista_persoane) + 1
            data = f"{random.randint(1, 28):02d}-{random.randint(1, 12):02d}-{random.randint(2024, 2025)}"
            timp = f"{random.randint(0, 23):02d}:{random.randint(0, 59):02d}"
            descriere = ''.join(random.choice(string.ascii_letters + string.digits) for x in range(random.randint(10, 20)))

            lista_persoane.append({'ID': ID, 'data': data, 'timp': timp, 'descriere': descriere})

class PrimeleEvenimente:

    def numara_participari2(self, lista_participari, len_evenimente):
        listaeven = []
        for id in range(1, len_evenimente + 1):
            nr = 0
            for elem in lista_participari:
                if elem[1] == id:
                    nr = nr + 1
            listaeven.append([id, nr])
        return listaeven

    def primele_20_evenimente(self, listaeven, lista_evenimente):
        lista_even = []
        listaeven_ordonata = sorted(listaeven, key=lambda x: x[1], reverse=True)
        nr_evenimente = int(0.2 * len(listaeven_ordonata))
        lista_20 = listaeven_ordonata[: nr_evenimente]
        caut = CautareEveniment(lista_evenimente)
        for elem in lista_20:
            eveniment = caut.cautare_eveniment(elem[0])
            lista_even.append(eveniment)
        return lista_even