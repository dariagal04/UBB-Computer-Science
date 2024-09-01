import datetime
class ValidareEveniment:

    def validare_eveniment(self, Eveniment):
        self.validare_ID(Eveniment.get_ID())
        self.validare_data(Eveniment.get_data())
        self.validare_timp(Eveniment.get_timp())
        self.validare_descriere(Eveniment.get_descriere())
    def validare_ID(self, ID):
        if ID < 0:
            raise Exception("ID invalid")

    def validare_data(self, data):
        try:
            dateformat = "%d-%m-%Y"
            datetime.datetime.strptime(data, dateformat)
        except ValueError:
            raise ValueError("data invalida")

    def validare_timp(self, timp):
        try:
            timeformat = "%H:%M"
            datetime.datetime.strptime(timp, timeformat)
        except ValueError:
            raise ValueError("timp invalid")

    def validare_descriere(self, descriere):
        if descriere == "":
            raise Exception("descriere invalida")