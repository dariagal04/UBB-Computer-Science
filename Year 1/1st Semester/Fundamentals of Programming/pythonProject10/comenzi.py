from infrastructura import *
from business import*

def validare_input(comanda_split):
     if comanda_split[0] == 'add' and len(comanda_split) == 3:
         return True
     elif comanda_split[0] == 'del' and len(comanda_split) == 2:
        return True
     elif comanda_split[0] == 'filter' and len(comanda_split) == 1:
        return True
     elif comanda_split[0] == 'show' and len(comanda_split) == 1:
        return True
     elif comanda_split[0] == 'stop' and len(comanda_split) == 1:
        return True
     else:
        print("Eroare: Comanda incorecta!")
        return False


def meniu_comenzi():
    lista = [domeniu.creeaza_nrcomplex(1, 2), domeniu.creeaza_nrcomplex(3, 4)]
    comanda = input()
    comenzi_split = comanda.split(';')

    for comanda in comenzi_split:
        comanda_split = comanda.strip().split()
        if validare_input(comanda_split):
            tip_comanda = comanda_split[0]
            if tip_comanda == 'add':
                adaug(lista, int(comanda_split[1]), int(comanda_split[2]))
                print(lista)
            elif tip_comanda == 'filter':
                filtrare_prime(lista)
                print(lista)
            elif tip_comanda == 'del':
                sterge_depe_poz(lista, int(comanda_split[1]))
                print(lista)
            elif tip_comanda == 'show':
                print(lista)
            elif tip_comanda == 'stop':
                exit()


meniu_comenzi()