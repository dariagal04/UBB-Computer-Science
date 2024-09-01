class Validare:

    def validare_Carte(self, Carti):
        self.validare_id(Carti.get_id())
        self.validare_titlu(Carti.get_titlu())
        self.validare_autor(Carti.get_autor())
        self.validare_anAparitie(Carti.get_anAparitie())

    def validare_id(self, id):
        if int(id) <= 0:
            raise Exception("id invalid") #pentru ca id-ul sa fie valid, trebuie sa fie mai mare de 0

    def validare_titlu(self, titlu):
        if titlu == "":
            raise Exception("titlu invalid") # pentru ca titlul sa fie valid, acesta trebuie sa contina ceva(sa nui fie nul)

    def validare_autor(self, autor):
        if autor == "":
            raise Exception("autor invalid") # pentru ca autorul sa fie valid, acesta trebuie sa contina ceva(sa nui fie nul)

    def validare_anAparitie(self, anAparitie):
        if int(anAparitie) < 0 and int(anAparitie) > 2024:
            raise Exception("anAparitie invalid(intre 0 si 2024)") #pentru ca anul aparitiei sa fie valid, acesta trebuie sa fie cuprins intre 0 si 2024
