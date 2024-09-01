class AdaugaE:

    def adauga_eveniment(self, AdaugaEveniment, lista_evenimente, ID, data, timp, descriere):
        AdaugaEveniment.adauga_eveniment( lista_evenimente, ID, data, timp, descriere)
        return lista_evenimente

class StergeEveniment:

    def sterge_eveniment(self, lista_evenimente, ID):
        del lista_evenimente[ID - 1]


class CautareEveniment:
    def __init__(self, lista_evenimente):
        self.lista_evenimente = lista_evenimente

    def cautare_eveniment(self, ID, index=0):
        if index < len(self.lista_evenimente):
            if self.lista_evenimente[index]['ID'] == ID:
                return self.lista_evenimente[index]
            else:
                return self.cautare_eveniment(ID, index + 1)
        else:
            return None

    """
    def cautare_eveniment(self, ID):
        for eveniment in self.lista_evenimente:
            if eveniment['ID'] == ID:
                return eveniment
        return None
    """

    def sortare_evenimente_crescator(self):
        n = len(self.lista_evenimente)
        for i in range(n - 1):
            min_index = i
            for j in range(i + 1, n):
                if self.lista_evenimente[j]['ID'] < self.lista_evenimente[min_index]['ID']:
                    min_index = j
            self.lista_evenimente[i], self.lista_evenimente[min_index] = self.lista_evenimente[min_index], \
            self.lista_evenimente[i]
        return self.lista_evenimente



class CitireEvenimentFisier:
    def __init__(self, nume_fisier):
        self.nume_fisier = nume_fisier
        self.lista_evenimente = self.citeste_evenimente_din_fisier()

    def citeste_evenimente_din_fisier(self):
        lista_evenimente = []

        try:
            with open(self.nume_fisier, 'r') as file:
                for linie in file:
                    linie = linie.strip()
                    if linie:
                        ID, data, timp, descriere = linie.split(',')
                        lista_evenimente.append({'ID': int(ID), 'data': data, 'timp': timp, 'descriere': descriere})
        except FileNotFoundError:
            print(f"Fisierul {self.nume_fisier} nu a fost gasit.")
        except Exception as e:
            print(f"Eroare la citirea fisierului: {e}")
        return lista_evenimente

    def scrie_evenimente_in_fisier(self, lista_evenimente):
        with open(self.nume_fisier, 'w') as file:
            for eveniment in lista_evenimente:
                ID, data, timp, descriere = eveniment
                file.write(f"{eveniment[ID]},{eveniment[data]},{eveniment[timp]},{eveniment[descriere]}\n")
