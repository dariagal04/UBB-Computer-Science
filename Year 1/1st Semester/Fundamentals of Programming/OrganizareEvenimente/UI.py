from business.businessPersoana import *
from business.businessEveniment import *
from Repository.RepoPersoana import *
from Repository.RepoEveniment import *
from participare import *
class Start:
    def meniu(self):
        print("1. Adauga participant")
        print("2. Adauga eveniment")
        print("3. Sterge participant")
        print("4. Sterge eveniment")
        print("5. Afiseaza lista persoane")
        print("6. Afisesaza lista evenimente")
        print("7. Modifica persoana")
        print("8. Inscriere persoana la eveniment")
        print("9. Cautare persoana")
        print("10. Cautare eveniment")
        print("11. Afisare participari")
        print("12. Generati persoane")
        print("13. Generati evenimente")
        print("14. Lista de evenimente la care participă o persoană ordonat alfabetic după descriere, după dată")
        print("15. Persoane participante la cele mai multe evenimente")
        print("16. Primele 20% evenimente cu cei mai mulți participanți (descriere, număr participanți)")
        print("17. Puneti persoanele si evenimentele in fisierele persoane.txt si evenimente.txt")
        print("18. Citeste persoane si evenimente din fisiere")



    def start(self):
        self.meniu()
        lista_persoane = []
        lista_evenimente = []
        lista_participare = []
        #fisier = CitirePersoaneFisier("persoane.txt")
        #lista_persoane = fisier.citeste_persoane_din_fisier()
        #fisier2 = CitireEvenimentFisier("evenimente.txt")
        #lista_evenimente = fisier2.citeste_evenimente_din_fisier()
        while True:
            option = int(input("introduceti optiunea: "))
            if option == 1:
                persoanaID = int(input("persoanaID = "))
                nume = input("nume = ")
                #adresa = input("adresa = ")
                ad = AdaugaPersoana()
                ad.adauga_persoana(lista_persoane, persoanaID, nume)#, adresa)
                sortare = CautarePersoana(lista_persoane)
                lista_persoane = sortare.shake_sort_persoane_crescator()
                print(lista_persoane)
                #ID = int(input("Id-ul evenimentului la care participa ="))
                #part = ParticiparePersoanaLaEveniment()
                #part.participare(lista_participare, persoanaID, ID)
            elif option == 2:
                ID = int(input("Id = "))
                data = input("data = ")
                timp = input("timp = ")
                descriere = input("descriere = ")
                ad = AdaugaEveniment()
                ad.adauga_eveniment(lista_evenimente, ID, data, timp, descriere)
                sortare = CautareEveniment(lista_evenimente)
                lista_evenimente = sortare.sortare_evenimente_crescator()
                print(lista_evenimente)
            elif option == 3:
                persoanaID = int(input("introduceti id-ul persoanei pe care doriti sa o stergeti: "))
                st = StergePersoana()
                st.sterge_persoana(lista_persoane, persoanaID)
                stp = ParticiparePersoanaLaEveniment()
                stp.sterge_participare(lista_participare, persoanaID)
            elif option == 4:
                ID = int(input("introduceti id-ul evenimentului pe care doriti sa il stergeti: "))
                st = StergeEveniment()
                st.sterge_eveniment(lista_evenimente, ID)
                stp = ParticiparePersoanaLaEveniment()
                stp.sterge_participare2(lista_participare, ID)
            elif option == 5:
                print(lista_persoane)
            elif option == 6:
                print(lista_evenimente)
            elif option == 7:
                persoanaID = int(input("id-ul persoanei pe care doriti sa o modificati: "))
                nume = input("nume nou = ")
                #adresa = input("adresa noua = ")
                sc = ModificarePersoana()
                sc.modificare_nume(lista_persoane, persoanaID, nume)
                #sc.modificare_adresa(lista_persoane, persoanaID, adresa)
                print(lista_persoane)
            elif option == 8:
                persoanaID = int(input("id-ul persoanei = "))
                ID = int(input("id-ul evenimentului = "))
                pa = ParticiparePersoanaLaEveniment()
                pa.participare(lista_participare, persoanaID, ID)
                print(lista_participare)
            elif option == 9:
                persoanaID = int(input("dati id-ul persoanei = "))
                pers = CautarePersoana(lista_persoane).cautare_persoana(persoanaID)
                print(pers)
            elif option == 10:
                ID = int(input("dati id-ul evenimentului = "))
                even = CautareEveniment(lista_evenimente).cautare_eveniment(ID)
                print(even)
            elif option == 11:
                print(lista_participare)
            elif option == 12:
                numar_entitati = int(input("dati numar entitati: "))
                gen = RandomPersoane()
                gen.adauga_persoane_aleatorii(lista_persoane, numar_entitati)
                print(lista_persoane)
            elif option == 13:
                numar_entitati = int(input("dati numar entitati: "))
                gen = RandomEvenimente()
                gen.adauga_evenimente_aleatorii(lista_evenimente, numar_entitati)
                print(lista_evenimente)
            elif option == 14:
                persoanaID = int(input("dati id-ul persoanei: "))
                part = ParticiparePersoanaLaEveniment()
                lista = part.lista_participare_ordonata(lista_participare, persoanaID, lista_evenimente)
                print(lista)
            elif option == 15:
                part = CeleMaiMulteParticipari()
                lista = part.numara_participari(lista_participare, len(lista_persoane))
                lista1 = part.cele_mai_multe_participari(lista, lista_persoane)
                print(lista1)
            elif option == 16:
                part = PrimeleEvenimente()
                listaeven = part.numara_participari2(lista_participare, len(lista_evenimente))
                lista_even = part.primele_20_evenimente(listaeven, lista_evenimente)
                print(lista_even)
            elif option == 17:
                add_fisier = CitirePersoaneFisier("persoane.txt")
                add_fisier.scrie_persoane_in_fisier(lista_persoane)
                add_fisier2 = CitireEvenimentFisier("evenimente.txt")
                add_fisier2.scrie_evenimente_in_fisier(lista_evenimente)
            elif option == 18:
                fisier = CitirePersoaneFisier("persoane.txt")
                lista_persoane = fisier.citeste_persoane_din_fisier()
                sortare = CautarePersoana(lista_persoane)
                lista_persoane = sortare.shake_sort_persoane_crescator()
                fisier2 = CitireEvenimentFisier("evenimente.txt")
                lista_evenimente = fisier2.citeste_evenimente_din_fisier()
                sortare = CautareEveniment(lista_evenimente)
                lista_evenimente = sortare.sortare_evenimente_crescator()

            else:
                exit()
