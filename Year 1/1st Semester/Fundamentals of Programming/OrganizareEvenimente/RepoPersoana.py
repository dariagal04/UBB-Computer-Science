
class AdaugaP:

    def adauga_persoana(self, AdaugaPersoana, lista_persoane, persoanaID, nume):#, adresa):
        AdaugaPersoana.adauga_persoana(lista_persoane, persoanaID, nume) #, adresa)
        return lista_persoane

class StergePersoana:

    def sterge_persoana(self, lista_persoane, persoanaID):
        del lista_persoane[persoanaID-1]

class CautarePersoana:
    def __init__(self, lista_persoane):
        self.lista_persoane = lista_persoane

    def cautare_persoana(self, persoanaID, index=0):
        if index < len(self.lista_persoane):
            if self.lista_persoane[index]['persoanaID'] == persoanaID:
                return self.lista_persoane[index]
            else:
                return self.cautare_persoana(persoanaID, index + 1)
        else:
            return None

    def sortare_persoane_crescator(self):
        n = len(self.lista_persoane)
        for i in range(n - 1):
            min_index = i
            for j in range(i + 1, n):
                if self.lista_persoane[j]['persoanaID'] < self.lista_persoane[min_index]['persoanaID']:
                    min_index = j
            self.lista_persoane[i], self.lista_persoane[min_index] = self.lista_persoane[min_index], self.lista_persoane[i]
        return self.lista_persoane

    def shake_sort_persoane_crescator(self):
        n = len(self.lista_persoane)
        schimbat = True
        start = 0
        end = n - 1
        while (schimbat == True):
            schimbat = False
            # Merge de la stanga la dreapta
            for i in range(start, end):
                if (self.lista_persoane[i]['persoanaID'] > self.lista_persoane[i + 1]['persoanaID']):
                    self.lista_persoane[i], self.lista_persoane[i + 1] = self.lista_persoane[i + 1], self.lista_persoane[i]
                    schimbat = True
            if (schimbat == False):
                break

            # Actualizeaza indicele de final, deoarece cel mai mare element este acum pe ultima pozitie corecta
            end = end - 1

            schimbat = False
            # Merge de la dreapta la stanga
            for i in range(end - 1, start - 1, -1):
                if (self.lista_persoane[i]['persoanaID'] > self.lista_persoane[i + 1]['persoanaID']):
                    self.lista_persoane[i], self.lista_persoane[i + 1] = self.lista_persoane[i + 1], self.lista_persoane[i]
                    schimbat = True

            # Actualizează indicele de start, deoarece cel mai mic element este acum pe prima poziție corectă
            start = start + 1
        return self.lista_persoane


class CitirePersoaneFisier:
    def __init__(self, nume_fisier):
        self.nume_fisier = nume_fisier
        self.lista_persoane = self.citeste_persoane_din_fisier()

    def citeste_persoane_din_fisier(self):
        lista_persoane = []

        try:
            with open(self.nume_fisier, 'r') as file:
                for linie in file:
                    linie = linie.strip()
                    if linie:
                        persoanaID = int(linie)
                        nume = file.readline().strip()
                        lista_persoane.append({'persoanaID': int(persoanaID), 'nume': nume})
        except FileNotFoundError:
            print(f"Fisierul {self.nume_fisier} nu a fost gasit.")
        except Exception as e:
            print(f"Eroare la citirea fisierului: {e}")
        return lista_persoane

    def scrie_persoane_in_fisier(self, lista_persoane):
        with open(self.nume_fisier, 'w') as file:
            for persoana in lista_persoane:
                persoanaID, nume = persoana
                file.write(f"{persoana[persoanaID]} \n{persoana[nume]}\n")
