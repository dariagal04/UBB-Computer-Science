
from Validare.validarePersoana import *
from business.businessPersoana import *
from Repository.RepoPersoana import *
from participare import *

class TestePersoana:

    def test_create_persoana(self):
        persoanaID = 101
        nume = 'Gal Daria'
        # adresa = 'Strada Gh. Doja, nr. 95'
        persoana = Persoana(persoanaID, nume)#, adresa)
        assert persoanaID == persoana.get_persoanaID()
        assert nume == persoana.get_nume()
        #assert adresa == persoana.get_adresa()

    def test_validare_persoana(self):
        validate = ValidarePersoana()
        persoanaID = 101
        nume = "Gal Daria"
        #adresa = "Strada Gh. Doja, nr. 95"
        persoana1 = Persoana(persoanaID, nume) #, adresa)
        validate.validare_persoana(persoana1)
        persoanaID = 100
        nume = ""
        #adresa = "calea motilor"
        persoana2 = Persoana(persoanaID, nume) #, adresa)
        try:
            validate.validare_persoana(persoana2)
            assert False
        except Exception as ex:
            assert (str(ex) == "nume invalid")

    def test_adaugare_persoana(self):
        adauga_persoana_instance = AdaugaPersoana()
        lista_test = []
        adauga_persoana_instance.adauga_persoana(lista_test, 1, 'John') #, 'strada')
        assert lista_test == [{'persoanaID': 1, 'nume': 'John'}] #, 'adresa': 'strada'}]

    def test_modificare_persoana(self):
        modificare_persoana_instance = ModificarePersoana()
        lista_test = [{'persoanaID': 1, 'nume': 'John'}] #, 'adresa': 'strada'}]
        modificare_persoana_instance.modificare_nume(lista_test, 1, 'Doe')  #, 'str')
        assert lista_test == [{'persoanaID': 1, 'nume': 'Doe'}] #, 'adresa': 'str'}]

    def test_sterge_persoana(self):
        sterge_persoana_instance = StergePersoana()
        persoane_test = [{'persoanaID': 1, 'nume': 'John'}, {'persoanaID': 2, 'nume': 'Jane'}, {'persoanaID': 3, 'nume': 'Doe'}]
        #  persoane_test = [{'persoanaID': 1, 'nume': 'John', 'adresa': 'strada'}, {'persoanaID': 2, 'nume': 'Jane', 'adresa': str}, {'persoanaID': 3, 'nume': 'Doe', 'adresa': aleea}]
        sterge_persoana_instance.sterge_persoana(persoane_test, 2)
        assert persoane_test == [{'persoanaID': 1, 'nume': 'John'}, {'persoanaID': 3, 'nume': 'Doe'}]
        # assert persoane_test == [{'persoanaID': 1, 'nume': 'John', 'adresa': 'strada'}, {'persoanaID': 3, 'nume': 'Doe', 'adresa': 'aleea'}]

    def test_cautare_persoana(self):
        persoane_test = [{'persoanaID': 1, 'nume': 'John'}, {'persoanaID': 2, 'nume': 'Jane'}, {'persoanaID': 3, 'nume': 'Doe'}]
        #  persoane_test = [{'persoanaID': 1, 'nume': 'John', 'adresa': 'strada'}, {'persoanaID': 2, 'nume': 'Jane', 'adresa': str}, {'persoanaID': 3, 'nume': 'Doe', 'adresa': aleea}]
        cautare_persoana_instance = CautarePersoana(persoane_test)
        rezultat_cautare = cautare_persoana_instance.cautare_persoana(1)
        assert rezultat_cautare == {'persoanaID': 1, 'nume': 'John'}
        #assert rezultat_cautare == {'persoanaID': 1, 'nume': 'John', 'adresa': 'strada'}

    def test_persoana_participa(self):
        participare_instance = ParticiparePersoanaLaEveniment()
        lista_participare_test = []
        participare_instance.participare(lista_participare_test, 1, 101)
        participare_instance.participare(lista_participare_test, 2, 101)
        participare_instance.participare(lista_participare_test, 1, 102)
        assert lista_participare_test == [[1, 101], [2, 101], [1, 102]]

    def test_sterge_participare_persoana(self):
        participare_instance = ParticiparePersoanaLaEveniment()
        lista_participare_test = []
        participare_instance.participare(lista_participare_test, 1, 101)
        participare_instance.participare(lista_participare_test, 2, 101)
        participare_instance.participare(lista_participare_test, 1, 102)
        participare_instance.sterge_participare(lista_participare_test, 1)
        assert lista_participare_test == [[2, 101]]

    def test_participare_ordonata(self):
        participare_instance = ParticiparePersoanaLaEveniment()
        evenimente_test = [{'ID': 1, 'data': '2023-12-20', 'timp': '15:00', 'descriere': 'Eveniment B'},{'ID': 2, 'data': '2023-12-20', 'timp': '14:00', 'descriere': 'Eveniment A'},{'ID': 3, 'data': '2023-12-21', 'timp': '16:00', 'descriere': 'Eveniment C'},]
        lista_participare_test = [[1, 1],[1, 2],[2, 1],]
        persoanaID_cautata = 1
        rezultat_asteptat = [{'ID': 2, 'data': '2023-12-20', 'timp': '14:00', 'descriere': 'Eveniment A'},{'ID': 1, 'data': '2023-12-20', 'timp': '15:00', 'descriere': 'Eveniment B'},]
        rezultat_real = participare_instance.lista_participare_ordonata(lista_participare_test, persoanaID_cautata,evenimente_test)
        assert rezultat_real == rezultat_asteptat

    def test_cele_mai_multe_participari(self):
        participare_instance = CeleMaiMulteParticipari()
        lista_participari_test = [[1, 1],[1, 2],[2, 1],[3, 1],[3, 2]]
        lista_persoane_test = [{'persoanaID': 1, 'nume': 'John'},{'persoanaID': 2, 'nume': 'Alice'},{'persoanaID': 3, 'nume': 'Bob'}]
        numar_participari = participare_instance.numara_participari(lista_participari_test, len(lista_persoane_test))
        cele_mai_multe_participari = participare_instance.cele_mai_multe_participari(numar_participari,lista_persoane_test)
        assert cele_mai_multe_participari == [{'persoanaID': 1, 'nume': 'John'}, {'persoanaID': 3, 'nume': 'Bob'}]

    def test_shake_sort(self):
        lista_persoane_test = [{'persoanaID': 1, 'nume': 'John'}, {'persoanaID': 3, 'nume': 'Alice'},{'persoanaID': 2, 'nume': 'Bob'}]
        sortare = CautarePersoana(lista_persoane_test)
        assert sortare.sortare_persoane_crescator() == [{'persoanaID': 1, 'nume': 'John'}, {'persoanaID': 2, 'nume': 'Bob'},{'persoanaID': 3, 'nume': 'Alice'}]
    def run_all_tests(self):
        self.test_create_persoana()
        self.test_validare_persoana()
        self.test_adaugare_persoana()
        self.test_modificare_persoana()
        self.test_sterge_persoana()
        self.test_cautare_persoana()
        self.test_persoana_participa()
        self.test_sterge_participare_persoana()
        self.test_participare_ordonata()
        self.test_cele_mai_multe_participari()
        self.test_shake_sort()
        print("tests Persoana are ok")