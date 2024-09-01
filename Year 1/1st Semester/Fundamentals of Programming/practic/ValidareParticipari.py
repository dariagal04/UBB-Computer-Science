class ValidarePart:

    def validare_participari(self, Participari):
        pass

    def validare_cod_participare(self, cod_participare):
        if cod_participare < 0:
            raise Exception("cod invalid")

    def validare_id_concurent(self, id_concurent):
        if id_concurent < 0:
            raise Exception("id invalid")

    def validare_punctaj(self, punctaj):
        if punctaj < 0 and punctaj > 100:
            raise Exception("punctajul trebuie sa fie cuprins intre 0 si 100")