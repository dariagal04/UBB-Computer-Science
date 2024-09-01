from domain import Persoana
class Adaug():

    def adaug(self, lista_persoane, persoanaID, nume, adresa):
        persoana = Persoana.create_persoana(persoanaID, nume, adresa)