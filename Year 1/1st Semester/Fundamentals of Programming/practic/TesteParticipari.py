from ValidareParticipari import *
from DomainParticipari import *


class TestePart:

    def tests_create_participare(self):
        cod = 1
        id = 1
        punctaj = 23
        participare = Participari(cod, id, punctaj)
        assert participare.get_cod_participare() == cod
        assert participare.get_id_concurent() == id
        assert participare.get_punctaj() == punctaj


    def tests_validate_Participari(self):
        validator = ValidarePart()
        cod = 1
        id = 1
        punctaj = 23
        participare = Participari(cod, id, punctaj)
        validator.validare_participari(participare)


    def run_all_tests(self):
        self.tests_create_participare()
        self.tests_validate_Participari()
        print("tests Participari are ok")