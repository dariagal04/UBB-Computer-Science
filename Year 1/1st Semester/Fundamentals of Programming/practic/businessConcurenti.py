from RepoConcurenti import *
from DomainConcurenti import *

class Business:

    def preluare_concurenti(self):
        c = ConcurentiFromFile("Concurenti.txt")
        lista_con = c.read_concurenti()
        return lista_con


    def comparare_an(self, lista, an):
        lista2 = []
        for elem in lista:
            id = elem[0]
            nume = elem[1]
            tara = elem[2]
            data = elem[3]
            d = Concurenti(id, nume, tara, data)
            anul = int(d.get_an())
            if anul > an:
                lista2.append(elem)
        return lista2

