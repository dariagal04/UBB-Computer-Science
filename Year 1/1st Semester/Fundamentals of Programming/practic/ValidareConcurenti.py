import datetime

class ValidareCon:

    def validare_concurenti(self, Concurenti):
        self.validare_id_concurent(Concurenti.get_id_concurent())
        self.validare_nume(Concurenti.get_nume())
        self.validare_tara(Concurenti.get_tara())
        self.validate_data(Concurenti.get_data_nasterii())

    def validare_id_concurent(self, id_concurent):
        if id_concurent < 0:
            raise Exception("id invalid")

    def validare_nume(self, nume):
        if nume == "":
            raise Exception("nume invalid")

    def validare_tara(self, tara):
        if tara == "":
            raise Exception("tara invalida")

    def validate_data(self, data_nastere):
        try:
            dateformat = "%d.%m.%Y"
            datetime.datetime.strptime(data_nastere, dateformat)
        except ValueError:
            raise ValueError("data invalida")