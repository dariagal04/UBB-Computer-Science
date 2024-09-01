class Concurenti:

    def __init__(self, id_concurent, nume, tara, data_nasterii):
        self.__id_concurent = id_concurent
        self.__nume = nume
        self.__tara = tara
        self.__data_nasterii = data_nasterii

    def get_id_concurent(self):
        return self.__id_concurent

    def get_nume(self):
        return self.__nume

    def get_tara(self):
        return self.__tara

    def get_data_nasterii(self):
        return self.__data_nasterii

    def get_an(self):
        return self.__data_nasterii[6:9]

    def set_id_concurent(self, value):
         self.__id_concurent = value

    def set_nume(self, value):
        self.__nume = value

    def set_tara(self, value):
        self.__tara = value

    def set_data_nasterii(self, value):
        self.__data_nasterii = value

