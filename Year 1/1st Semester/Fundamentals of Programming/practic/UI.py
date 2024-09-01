from  businessConcurenti import *
from DomainConcurenti import *

class Start:

    def meniu(self):
        print("1. afisarea pe ecran a concurenrilor nascuti dupa un an dat de utilizator")
        print("2. afisarea clasamentului pe tari, cu punctajul aferent fiecarei tari")

    def start(self):
        self.meniu()

        while True:
            option = int(input("dati optiunea: "))
            if option == 1:
                an = int(input("dati anul: "))
                b = Business()
                lista = b.preluare_concurenti()
                lista2 = b.comparare_an(lista, an)
                print(lista2)