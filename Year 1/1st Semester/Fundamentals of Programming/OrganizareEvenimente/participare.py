class ParticiparePersoanaLaEveniment:

    def participare(self, lista_participare, persoanaID, ID):
        elem = [persoanaID, ID]
        lista_participare.append(elem)

    """
    def lista_participare_ordonata(self, lista_participare, persoanaID, lista_evenimente):
        evenimente_participate = [elem[1] for elem in lista_participare if elem[0] == persoanaID]
        evenimente_persoana = [eveniment for eveniment in lista_evenimente if eveniment['ID'] in evenimente_participate]
        evenimente_persoana_ordonate = sorted(evenimente_persoana, key=lambda x: (x['descriere'], x['data']))
        return evenimente_persoana_ordonate
    """

    def lista_participare_ordonata(self, lista_participare, persoanaID, lista_evenimente):
        evenimente_participate = [elem[1] for elem in lista_participare if elem[0] == persoanaID]
        evenimente_persoana = [eveniment for eveniment in lista_evenimente if eveniment['ID'] in evenimente_participate]

        n = len(evenimente_persoana)

        for i in range(n - 1):
            min_index = i
            for j in range(i + 1, n):
                # Comparăm evenimentele în funcție de descriere și apoi de data
                if (evenimente_persoana[j]['descriere'], evenimente_persoana[j]['data']) < (evenimente_persoana[min_index]['descriere'], evenimente_persoana[min_index]['data']):
                    min_index = j

            # Schimbăm evenimentele la pozițiile i și min_index
            evenimente_persoana[i], evenimente_persoana[min_index] = evenimente_persoana[min_index], evenimente_persoana[i]

        return evenimente_persoana



    def sterge_participare(self, lista_participare, persoanaID):
        lista_participare[:] = [elem for elem in lista_participare if elem[0] != persoanaID]

    def sterge_participare2(self, lista_participare, ID):
        lista_participare[:] = [elem for elem in lista_participare if elem[1] != ID]
