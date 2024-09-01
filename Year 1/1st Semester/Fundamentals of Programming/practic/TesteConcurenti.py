from ValidareConcurenti import *
from DomainConcurenti import *

class TesteCon:

    def tests_create_concurent(self):
        id = 1
        nume = "Popescu"
        tara = "Romania"
        data_nasterii = "13.09.2000"
        concurent = Concurenti(id, nume, tara, data_nasterii)
        assert concurent.get_id_concurent() == id
        assert concurent.get_nume() == nume
        assert concurent.get_tara() == tara
        assert concurent.get_data_nasterii() == data_nasterii

    def tests_validate_Concurenti(self):
        validator = ValidareCon()
        id = 1
        nume = "Popescu"
        tara = "Romania"
        data_nasterii = "13.09.2000"
        concurent = Concurenti(id, nume, tara, data_nasterii)
        validator.validare_concurenti(concurent)
        id = 1
        nume = "Popescu"
        tara = ""
        data_nasterii = "13.09.2000"
        concurent2 = Concurenti(id, nume, tara, data_nasterii)
        try :
            validator.validare_concurenti(concurent2)
            assert False
        except Exception as ex:
            assert (str(ex) == "tara invalida")


    def run_all_tests(self):
        self.tests_create_concurent()
        self.tests_validate_Concurenti()
        print("tests Concurenti are ok")