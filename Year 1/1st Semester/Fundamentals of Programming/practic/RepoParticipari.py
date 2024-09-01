
class ParticipariFromFile:

    def __init__(self, participari_file_path):
        self.participari_file_path = participari_file_path

    def read_participari(self):
        self._participari = []
        with open(self.participari_file_path, 'r') as f:
            for line in f:
                line = line.strip()
                element = line.split(",")
                cod_participare = int(element[0])
                id_concurent = int(element[1])
                punctaj  = int(element[2])
                participare ={"cod_participare": cod_participare, "id_concurent": id_concurent, "punctaj":punctaj}
                self._participari.append(participare)
        return self._participari