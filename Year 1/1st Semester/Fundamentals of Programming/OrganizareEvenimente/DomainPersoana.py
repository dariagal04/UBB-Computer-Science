class Persoana:

    def __init__(self, persoanaID, nume): #adresa):
        self.__persoanaID = persoanaID
        self.__nume = nume
       # self.__adresa = adresa

    def get_persoanaID(self):
        return  self.__persoanaID

    def get_nume(self):
        return self.__nume

   # def get_adresa(self):
       # return self.__adresa

    def set_persoanaID(self, value):
        self.__persoanaID = value

    def set_nume(self, value):
        self.__nume = value

    #def set_adresa(self, value):
        #self.__adresa = value


    def create_persoana(self, __persoanaID, __nume):# __adresa):
        persoana = {'persoanaID': __persoanaID, 'nume': __nume} #'adresa': __adresa}
        return persoana

