class ValidarePersoana:

    def validare_persoana(self, Persoana):
        self.validare_persoanaID(Persoana.get_persoanaID())
        self.validare_nume(Persoana.get_nume())
        #self.validare_adresa(Persoana.get_adresa())

    def validare_persoanaID(self, persoanaID):
        if persoanaID < 0 :
            raise Exception("ID invalid")

    def validare_nume(self, nume):
        if nume == "":
            raise Exception("nume invalid")

    #def validare_adresa(self, adresa):
        #if adresa == "":
            #raise Exception("adresa invalida")