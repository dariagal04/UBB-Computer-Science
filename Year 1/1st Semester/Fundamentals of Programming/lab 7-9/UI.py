class Start():

    def meniu(self):
        print("1. Adauga persoana si eveniment")
        print("2. Sterge persoana si eveniment")
        print("3. Modifica evenimentul la care participa o persoana")
        print("4. Afiseaza lista persoane")
        print("5. Afiseaza lista evenimente")
        print("6. Cauta o persoana")
        print("7. Cauta un eveniment")

    def start(self):
        self.meniu()
        while True:
            optiune = input("Introduceti optiunea")
            if optiune == 1:


