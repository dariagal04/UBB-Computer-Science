from domain import Persoana
from domain import Eveniment
from domain import create_date
from domain import create_time
class Teste():

    def __init__(self):
        pass

    def ruleaza_teste_domeniu(self):
        self.__persoanaID = '001'
        self.__nume = 'Daria'
        self.__adresa = 'strada Gh. Doja, numar 95'
        self.__persoana = Persoana(self.__persoanaID, self.__nume, self.__adresa)
        assert self.__persoana.get_persoanaID() == self.__persoanaID
        assert self.__persoana.get_nume() == self.__nume
        assert self.__persoana.get_adresa() == self.__adresa
        self.__ID = '001'
        self.__data = create_date(25,12,2023)
        self.__timp = create_time(18, 30)
        self.__descriere = 'eveniment craciun'
        self.__eveniment = Eveniment(self.__ID, self.__data, self.__timp, self.__descriere)
        assert self.__eveniment.get_ID() == self.__ID
        assert self.__eveniment.get_data() == self.__data
        assert self.__eveniment.get_timp() == self.__timp
        assert self.__eveniment.get_descriere() == self.__descriere


    def ruleaza_toate_testele(self):
        print('tests running')
        self.ruleaza_teste_domeniu()
