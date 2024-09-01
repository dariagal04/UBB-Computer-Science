
class ConcurentiFromFile:

    def __init__(self, concurenti_file_path):
        self.concurenti_file_path = concurenti_file_path


    """am preluat din fisierul concurenti.txt fiecare concurent si i-am pus intr-o lista """
    
    def read_concurenti(self):
        self._concurenti = []
        with open(self.concurenti_file_path, 'r') as f:
            for line in f:
                line = line.strip()
                element = line.split(",")
                id_concurent = int(element[0])
                nume = element[1]
                tara = element[2]
                data_nasterii = element[3]
                concurent ={"id": id_concurent, "nume": nume, "tara":tara, "data_nasterii": data_nasterii}
                self._concurenti.append(concurent)
        return self._concurenti