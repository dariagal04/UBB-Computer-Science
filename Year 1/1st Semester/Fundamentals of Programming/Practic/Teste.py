from Domain import *
from Business import *
from Validate import *


class Teste:

    def teste_creeare_carte(self):
        id = 1
        titlu = "Volum poezii"
        autor = "Mihai Eminescu"
        anAparitie = 1890
        carte = Carti(id, titlu, autor, anAparitie)
        assert carte.get_id() == id
        assert carte.get_titlu() == titlu
        assert carte.get_autor() == autor
        assert carte.get_anAparitie() == anAparitie
        #pentru a verifica daca s-a construit cum trebuie obiectul, am verificat getterii

    def teste_validare_carte(self):
        id = 1
        titlu = "Volum poezii"
        autor = "Mihai Eminescu"
        anAparitie = 1890
        carte = Carti(id, titlu, autor, anAparitie)
        validate = Validare()
        validate.validare_Carte(carte)
        id = 0
        titlu = "Volum poezii"
        autor = "Mihai Eminescu"
        anAparitie = 1890
        carte2 = Carti(id, titlu, autor, anAparitie)
        try:
            validate.validare_Carte(carte2)
            assert False
        except Exception as ex:
            assert(str(ex) == "id invalid")



    def test_adaugare_carte(self):
        lista = [[1, 'Volum Poezii', 'Mihai Eminescu', 1890], [2, 'Viata', 'Andreea Pop', 2009]]
        id = 3
        titlu = "Poezii"
        autor = "Popescu Mihai"
        anAparitie = 2008
        a= Adaugare()
        assert a.adauga(lista, id, titlu, autor, anAparitie) == [[1, 'Volum Poezii', 'Mihai Eminescu', 1890], [2, 'Viata', 'Andreea Pop', 2009], [3, 'Poezii', 'Popescu Mihai', 2008]]


    def test_sterge(self):
        lista = [[1, 'Volum Poezii', 'Mihai Eminescu', 1890], [2, 'Viata', 'Andreea Pop', 2009]]
        cifra = 8
        s = Sterge()
        assert s.sterge(lista, cifra) == [[2, 'Viata', 'Andreea Pop', 2009]]


    def run_all_tests(self):
        print("tests are ok")
        self.teste_creeare_carte()
        self.test_adaugare_carte()
        self.test_sterge()
        self.teste_validare_carte()
        #aici se apleleaza toate testele scrise mai sus

