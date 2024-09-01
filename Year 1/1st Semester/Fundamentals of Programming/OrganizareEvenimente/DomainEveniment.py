class Eveniment:

    def __init__(self, ID, data, timp, descriere):
        self.__ID = ID
        self.__data = data
        self.__timp = timp
        self.__descriere = descriere

    def get_ID(self):
        return self.__ID

    def get_data(self):
        return self.__data

    def get_timp(self):
        return self.__timp

    def get_descriere(self):
        return self.__descriere

    def set_ID(self, value):
        self.__ID = value

    def set_data(self, value):
        self.__data = value

    def set_timp(self, value):
        self.__timp = value

    def set_descriere(self, value):
        self.__descriere = value

    def create_eveniment(self, __ID, __data, __timp, __descriere):
        eveniment = {'ID': __ID, 'data': __data, 'timp': __timp, 'descriere': __descriere}
        return eveniment

