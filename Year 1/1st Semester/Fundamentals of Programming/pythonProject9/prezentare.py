import infrastructura
import domeniu
import business

lista = []
def citestenumar():
    x = int(input("valoarea reala a numarului: "))
    y = int(input("valoarea imaginara a numarului: "))
    domeniu.adaug(lista, x, y)
def meniu():
    print("MENIU")
    print("1. adaugare nr in lista")
    print("2. modificare numere lista")
    print("3. cautare numere")
    print("4. operatii cu numere din lista")
    print("5. filtrare")
    print("6. undo")
    print("0. iesire aplicatie")


def meniu1():
    print("MENIU OPTIUNE 1")
    print("1. Adaugă număr complex la sfârșitul listei")
    print("2. Inserare număr complex pe o poziție dată")
    print("3. iesire")


def meniu2():
    print("MENIU OPTIUNEA 2")
    print("1. Șterge element de pe o poziție dată")
    print("2. Șterge elementele de pe un interval de poziții.")
    print("3. Înlocuiește toate aparițiile unui număr complex cu un alt număr complex.")
    print("4. iesire")


def meniu3():
    print("MENIU OPTIUNEA 3")
    print("1. Tipărește partea imaginara pentru numerele din listă. Se dă intervalul de poziții (sub secvența).")
    print("2. Tipărește toate numerele complexe care au modulul mai mic decât 10")
    print("3. Tipărește toate numerele complexe care au modulul egal cu 10")
    print("4. iesire")


def meniu4():
    print("MENIU OPTIUNEA 4")
    print("1. Tipărește suma numerelor dintr-o subsecventă dată (se da poziția de început și sfârșit)")
    print("2. Tipărește Produsul numerelor dintr-o subsecventă dată (se da poziția de început și sfârșit)")
    print("3. Tipărește lista sortată descrescător după partea imaginara")
    print("4. iesire")


def meniu5():
    print("MENIU OPTIUNEA 5")
    print("1. Filtrare parte reala prim – elimină din listă numerele complexe la care partea reala este prim")
    print("2. Filtrare modul – elimina din lista numerele complexe la care modulul este <,= sau > decât un număr dat.")
    print("3. iesire")

def meniu6():
    print("MENIU OPTIUNEA 6")
    print("1. Reface ultima operație (lista de numere revine la numerele ce existau înainte de ultima operație care a modificat lista) – Nu folosiți funcția deepCopy")


def start():
    meniu()
    lista = []
    lungime = int(input("lungimea listei: "))
    while lungime:
        citestenumar()
        lungime = lungime - 1
    while True:
        option = input("scrie optiunea: ")
        if option == '1':
            meniu1()
            optiune = input("scrie optiunea: ")
            if optiune == '1':
                infrastructura.copie(lista)
                parte_z = int(input("parte reala: "))
                parte_i = int(input("parte imaginara: "))
                infrastructura.adauga_nr_complex(lista, parte_z, parte_i)
            elif optiune == '2':
                infrastructura.copie(lista)
                parte_z = int(input("parte reala: "))
                parte_i = int(input("parte imaginara: "))
                poz = int(input("pozitia: "))
                infrastructura.adauga_pe_poz(lista, parte_z, parte_i, poz)
            elif optiune == '3':
                return start()
        elif option == '2':
            meniu2()
            optiune = input("scrie optiunea: ")
            if optiune == '1':
                infrastructura.copie(lista)
                poz = int(input("pozitia: "))
                infrastructura.sterge_depe_poz(lista, poz)
            elif optiune == '2':
                infrastructura.copie(lista)
                poz1 = int(input("pozitia de inceput: "))
                poz2 = int(input("pozitia de sfarsit: "))
                business.sterg_interval(lista, poz1, poz2)
            elif optiune == '3':
                infrastructura.copie(lista)
                pz = int(input("parte reala numar existent: "))
                pi = int(input("parte imaginara numar existent: "))
                parte_z = int(input("parte reala numar nou: "))
                parte_i = int(input("parte imaginara numar nou: "))
                infrastructura.inlocuire_nr_complex(lista, pz, pi, parte_z, parte_i)
            elif optiune == '4':
                return start()
        elif option == '3':
            meniu3()
            optiune = input("scrie optiunea: ")
            if optiune == '1':
                lista2 = []
                poz1 = int(input("pozitiade inceput: "))
                poz2 = int(input("pozitia de sfarsit: "))
                infrastructura.tipareste_pi(lista, poz1, poz2, lista2)
            elif optiune == '2':
                lista3 = []
                business.modul_numar_maimic(lista, lista3)
            elif optiune == '3':
                lista4 = []
                business.modul_numar_egal(lista, lista4)
            elif optiune == '4':
                return start()
        elif option == '4':
            meniu4()
            optiune = input("scrie optiunea: ")
            if optiune == '1':
                poz1 = int(input("pozitiade inceput: "))
                poz2 = int(input("pozitia de sfarsit: "))
                infrastructura.suma_subsecventa(lista, poz1, poz2)
            elif optiune == '2':
                poz1 = int(input("pozitiade inceput: "))
                poz2 = int(input("pozitia de sfarsit: "))
                infrastructura.prod_subsecventa(lista, poz1, poz2)
            elif optiune == '3':
                infrastructura.sorteaza_descrescator(lista)
            elif optiune == '4':
                return start()
        elif option == '5':
            meniu5()
            optiune = input("scrie optiunea: ")
            if optiune == '1':
                infrastructura.copie(lista)
                business.filtrare_prime(lista)
            elif optiune == '2':
                infrastructura.copie(lista)
                numar_comp = float(input("numar cu care se compara: "))
                semn = str(input("semnul: "))
                business.filtrare_modul(lista, semn, numar_comp)
            elif optiune == '3':
                return start()
        elif option == '6':
            meniu6()
            infrastructura.undo()
        elif option == '0':
            return

