class Participari:

    def __init__(self, cod_particiare, id_concurent, punctaj):
        self.__cod_participare = cod_particiare
        self.__id_concurent = id_concurent
        self.__punctaj = punctaj


    def get_cod_participare(self):
        return self.__cod_participare

    def get_id_concurent(self):
        return self.__id_concurent

    def get_punctaj(self):
        return self.__punctaj

    def set_cod_participare(self, value):
        self.__cod_participare = value

    def set_id_concurent(self, value):
        self.__id_concurent = value

    def set_punctaj(self, value):
        self.__punctaj = value