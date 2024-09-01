from business import Adaug


class AdaugaPersoana():

    def adauga_persoana(self, lista_persoane, persoanaID, nume, adresa):
        Adaug.adaug(lista_persoane, persoanaID, nume, adresa)
        return lista_persoane
