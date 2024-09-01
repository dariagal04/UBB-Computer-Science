from domain.DomainEveniment import *
from Validare.validareEveniment import *
from business.businessEveniment import *
from Repository.RepoEveniment import *
from participare import *
class TesteEveniment:

    def test_create_eveniment(self):
        ID = 102
        data = "24-12-2023"
        timp = "18:30"
        descriere = "Concert Craciun"
        eveniment = Eveniment(ID, data, timp, descriere)
        assert ID == eveniment.get_ID()
        assert data == eveniment.get_data()
        assert timp == eveniment.get_timp()
        assert descriere == eveniment.get_descriere()

    def test_validare_eveniment(self):
        validate = ValidareEveniment()
        ID = 102
        data = "24-12-2023"
        timp = "18:30"
        descriere = "Concert Craciun"
        eveniment1 = Eveniment(ID, data, timp, descriere)
        validate.validare_eveniment(eveniment1)
        ID = -1
        data = "24-12-2023"
        timp = "18:30"
        descriere = "Concert Craciun"
        eveniment2 = Eveniment(ID, data, timp, descriere)
        try:
            validate.validare_eveniment(eveniment2)
            assert False
        except Exception as ex:
            assert (str(ex) == "ID invalid")


    def test_adaugare_eveniment(self):
        adauga_eveniment_instance = AdaugaEveniment()
        evenimente_test = []
        adauga_eveniment_instance.adauga_eveniment(evenimente_test, 1, '20-12-2023', '15:00', 'Descriere eveniment')
        assert evenimente_test == [{'ID': 1, 'data': '20-12-2023', 'timp': '15:00', 'descriere': 'Descriere eveniment'}]

    def test_sterge_eveniment(self):
        sterge_eveniment_instance = StergeEveniment()
        evenimente_test = [{'ID': 1, 'data': '20-12-2023', 'timp': '15:00', 'descriere': 'Descriere eveniment'}, {'ID': 2, 'data': '21-12-2023', 'timp': '15:00', 'descriere': 'Descriere eveniment2'},{'ID': 3, 'data': '22-12-2023', 'timp': '15:00', 'descriere': 'Descriere eveniment3'}]
        sterge_eveniment_instance.sterge_eveniment(evenimente_test, 2)
        assert evenimente_test == [{'ID': 1, 'data': '20-12-2023', 'timp': '15:00', 'descriere': 'Descriere eveniment'},{'ID': 3, 'data': '22-12-2023', 'timp': '15:00', 'descriere': 'Descriere eveniment3'}]

    def test_cautare_eveniment(self):
        evenimente_test = [{'ID': 1, 'data': '20-12-2023', 'timp': '15:00', 'descriere': 'Descriere eveniment'}, {'ID': 2, 'data': '21-12-2023', 'timp': '15:00', 'descriere': 'Descriere eveniment2'},{'ID': 3, 'data': '22-12-2023', 'timp': '15:00', 'descriere': 'Descriere eveniment3'}]
        cautare_eveniment_instance = CautareEveniment(evenimente_test)
        rezultat_cautare = cautare_eveniment_instance.cautare_eveniment(1)
        assert rezultat_cautare == {'ID': 1, 'data': '20-12-2023', 'timp': '15:00', 'descriere': 'Descriere eveniment'}

    def test_sterge_participare_eveniment(self):
        participare_instance = ParticiparePersoanaLaEveniment()
        lista_participare_test = []
        participare_instance.participare(lista_participare_test, 1, 101)
        participare_instance.participare(lista_participare_test, 2, 101)
        participare_instance.participare(lista_participare_test, 1, 102)
        participare_instance.sterge_participare2(lista_participare_test, 101)
        assert lista_participare_test == [[1, 102]]

    def test_primele_20_evenimente(self):
        participare_instance = PrimeleEvenimente()
        lista_participari_test = [[1, 2],[2, 2],[2, 1],[3, 1],[3, 2]]
        lista_evenimente_test = [{'ID': 1, 'data': '20-12-2023', 'timp': '15:00', 'descriere': 'Eveniment A'},{'ID': 2, 'data': '21-12-2023', 'timp': '14:00', 'descriere': 'Eveniment B'},{'ID': 3, 'data': '22-12-2023', 'timp': '16:00', 'descriere': 'Eveniment C'},{'ID': 4, 'data': '23-12-2023', 'timp': '17:00', 'descriere': 'Eveniment D'},{'ID': 5, 'data': '24-12-2023', 'timp': '18:00', 'descriere': 'Eveniment E'}]
        numar_participari = participare_instance.numara_participari2(lista_participari_test, len(lista_evenimente_test))
        primele_20_evenimente = participare_instance.primele_20_evenimente(numar_participari, lista_evenimente_test)
        assert primele_20_evenimente == [{'ID': 2, 'data': '21-12-2023', 'timp': '14:00', 'descriere': 'Eveniment B'}]

    def test_selection_sort(self):
        lista_evenimente_test = [{'ID': 1, 'data': '20-12-2023', 'timp': '15:00', 'descriere': 'Eveniment A'},
                                 {'ID': 3, 'data': '21-12-2023', 'timp': '14:00', 'descriere': 'Eveniment B'},
                                 {'ID': 2, 'data': '22-12-2023', 'timp': '16:00', 'descriere': 'Eveniment C'}]
        sortare = CautareEveniment(lista_evenimente_test)
        assert sortare.sortare_evenimente_crescator() == [{'ID': 1, 'data': '20-12-2023', 'timp': '15:00', 'descriere': 'Eveniment A'},
                                 {'ID': 2, 'data': '22-12-2023', 'timp': '16:00', 'descriere': 'Eveniment C'},
                                 {'ID': 3, 'data': '21-12-2023', 'timp': '14:00', 'descriere': 'Eveniment B'},
                                                          ]


    def run_all_tests2(self):
        self.test_create_eveniment()
        self.test_validare_eveniment()
        self.test_adaugare_eveniment()
        self.test_sterge_eveniment()
        self.test_cautare_eveniment()
        self.test_sterge_participare_eveniment()
        self.test_primele_20_evenimente()
        self.test_selection_sort()
        print("tests Eveniment are ok")