class Persoana:

    def __init__(self, persoanaID, nume, adresa):
        self.__persoanaID = persoanaID
        self.__nume = nume
        self.__adresa = adresa

    def get_persoanaID(self):
        return self.__persoanaID

    def get_nume(self):
        return self.__nume

    def get_adresa(self):
        return self.__adresa

    def set_persoanaID(self, value):
        self.__persoanaID = value

    def set_nume(self, value):
        self.__nume = value

    def set_adresa(self, value):
        self.__adresa = value

    def create_persoana(self, ):
        persoana = {'persoanaID': self.get_persoanaID(), 'nume': self.get_nume(), 'adresa': self.get_adresa()}
        return persoana

def create_date(day, month, year):
    date = {'ziua':day, 'luna':month, 'anul':year}
    return date

def create_time(hour, minute):
    time = {'ora':hour, 'minute':minute}
    return time
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