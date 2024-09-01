class Carti:

    def __init__(self, id, titlu, autor, anAparitie):
        self.__id = id
        self.__titlu = titlu
        self.__autor = autor
        self.__anAparitie = anAparitie

    #In domeniu am definit elementul Carte asa cum trebuie el folosit(i-am definit structura pe care trebuie sa o aiba) .Aici avem si setteri si getteri
    def get_id(self):
        return self.__id

    def get_titlu(self):
        return self.__titlu

    def get_autor(self):
        return self.__autor

    def get_anAparitie(self):
        return self.__anAparitie

    def set_id(self, value):
        self.__id = value

    def set_titlu(self, value):
        self.__titlu = value

    def set_autor(self, value):
        self.__autor = value

    def set_anAparitie(self, value):
        self.__anAparitie = value

