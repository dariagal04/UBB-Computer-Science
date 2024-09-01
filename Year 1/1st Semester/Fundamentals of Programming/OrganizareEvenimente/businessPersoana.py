from domain.DomainPersoana import *
import random
import string
from Repository.RepoPersoana import *
class AdaugaPersoana:


    def adauga_persoana(self,lista_persoane, persoanaID, nume): #, adresa):
        persoana = Persoana(persoanaID, nume).create_persoana(persoanaID, nume)
        """ persoana = Persoana(persoanaID, nume, adresa).create_persoana(persoanaID, nume, adresa)"""
        self.adaug(lista_persoane, persoana)

    def adaug(self, lista_persoane, persoana):
        lista_persoane.append(persoana)
        return lista_persoane


class ModificarePersoana:

    def modificare_nume(self, lista_persoane, persoanaID, nume):
        for elem in lista_persoane:
            if elem['persoanaID'] == persoanaID:
                elem['nume'] = nume

    #def modificare_adresa(self, lista_persoane, persoanaID, adresa):
      #  for elem in lista_persoane:
          #  if elem['persoanaID'] == persoanaID:
               # elem['adresa'] = adresa


class RandomPersoane:


    def adauga_persoane_aleatorii(self, lista_persoane, numar_entitati):
        for x in range(numar_entitati):
            persoanaID = len(lista_persoane) + 1
            nume = ''.join(random.choice(string.ascii_letters) for x in range(random.randint(5, 10)))

            #adresa = ''.join(random.choice(string.ascii_letters + string.digits) for x in range(random.randint(10, 20)))

            lista_persoane.append({'persoanaID': persoanaID, 'nume': nume}) # , 'adresa': adresa})


class CeleMaiMulteParticipari:

    def numara_participari(self,lista_participari, len_persoane):
        lista = []
        for id in range(1, len_persoane+1):
            nr = 0
            for elem in lista_participari:
                if elem[0] == id:
                    nr = nr+1
            lista.append([id, nr])
        return lista

    def cele_mai_multe_participari(self, lista, lista_persoane):
        maxim = max(elem[1] for elem in lista)
        lista1 = []
        for elem in lista:
            if elem[1] == maxim:
                pers = CautarePersoana(lista_persoane).cautare_persoana(elem[0])
                lista1.append(pers)
        return lista1

