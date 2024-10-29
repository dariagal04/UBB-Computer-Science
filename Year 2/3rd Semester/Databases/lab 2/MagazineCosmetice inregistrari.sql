USE MagazineCosmetice

-- Pentru tabelul Produse
INSERT INTO Produse (Denumire, Categorie, Pret, NrBucati) 
VALUES ('Ruj', 'Cosmetice', 50.00, 100);
INSERT INTO Produse (Denumire, Categorie, Pret, NrBucati) 
VALUES ('Fond de ten', 'Cosmetice', 70.00, 150);
INSERT INTO Produse (Denumire, Categorie, Pret, NrBucati) 
VALUES ('Mascara', 'Cosmetice', 60.00, 200);
INSERT INTO Produse (Denumire, Categorie, Pret, NrBucati) 
VALUES ('Anticearcan', 'Cosmetice', 30.00, 400);

-- Pentru tabelul Categorii
INSERT INTO Categorii (NumeCategorie) 
VALUES ('Machiaj');
INSERT INTO Categorii (NumeCategorie) 
VALUES ('Ingrijire personala');
INSERT INTO Categorii (NumeCategorie) 
VALUES ('Parfumuri');

-- Pentru tabelul Branduri
INSERT INTO Branduri (NumeBrand) 
VALUES ('BrandA');
INSERT INTO Branduri (NumeBrand) 
VALUES ('BrandB');
INSERT INTO Branduri (NumeBrand) 
VALUES ('BrandC');

-- Pentru tabelul Magazine
INSERT INTO Magazine (NumeMagazin, NumarAngajati) 
VALUES ('Magazin1', 2);
INSERT INTO Magazine (NumeMagazin, NumarAngajati) 
VALUES ('Magazin2', 2);
INSERT INTO Magazine (NumeMagazin, NumarAngajati) 
VALUES ('Magazin3', 1);

-- Pentru tabelul Angajati
INSERT INTO Angajati (NumeAngajat, Functie, MagazinID) 
VALUES ('Angajat1', 'Casier', 1);
INSERT INTO Angajati (NumeAngajat, Functie, MagazinID) 
VALUES ('Angajat2', 'Manager', 2);
INSERT INTO Angajati (NumeAngajat, Functie, MagazinID) 
VALUES ('Angajat3', 'Vanzator', 3);
INSERT INTO Angajati (NumeAngajat, Functie, MagazinID) 
VALUES ('Angajat4', 'Vanzator', 1);
INSERT INTO Angajati (NumeAngajat, Functie, MagazinID) 
VALUES ('Angajat5', 'Vanzator', 2);

-- Pentru tabelul Clienti
INSERT INTO Clienti (NumeClient, Email, Telefon) 
VALUES ('Client1', 'client1@yahoo.com', '1234567890');
INSERT INTO Clienti (NumeClient, Email, Telefon) 
VALUES ('Client2', 'client2@yahoo.com', '0987654321');
INSERT INTO Clienti (NumeClient, Email, Telefon) 
VALUES ('Client3', 'client3@yahoo.com', '1243568790');
INSERT INTO Clienti (NumeClient, Email, Telefon) 
VALUES ('Client4', 'client4@yahoo.com', '1243658790');

-- Pentru tabelul Comenzi
INSERT INTO Comenzi (ClientID, Mid, SumaTotala) 
VALUES (1, 1, 150.00);
INSERT INTO Comenzi (ClientID, Mid, SumaTotala) 
VALUES (2, 2, 200.00);
INSERT INTO Comenzi (ClientID, Mid, SumaTotala) 
VALUES (3, 3, 250.00);
INSERT INTO Comenzi (ClientID, Mid, SumaTotala) 
VALUES (4, 2, 260.00);

-- Pentru tabelul ArticoleComanda
INSERT INTO ArticoleComanda (ComandaID, Pid, Cantitate, Pret) 
VALUES (1, 1, 2, 100.00);
INSERT INTO ArticoleComanda (ComandaID, Pid, Cantitate, Pret) 
VALUES (2, 2, 3, 210.00);
INSERT INTO ArticoleComanda (ComandaID, Pid, Cantitate, Pret) 
VALUES (3, 3, 1, 60.00);
INSERT INTO ArticoleComanda (ComandaID, Pid, Cantitate, Pret) 
VALUES (4, 4, 5, 300.00);


-- Pentru tabelul ProduseBranduri
INSERT INTO ProduseBranduri (Pid, Bid) VALUES (1, 1);
INSERT INTO ProduseBranduri (Pid, Bid) VALUES (2, 2);
INSERT INTO ProduseBranduri (Pid, Bid) VALUES (3, 3);
INSERT INTO ProduseBranduri (Pid, Bid) VALUES (3, 2);

-- Pentru tabelul Recenzii
INSERT INTO Recenzii ( Pid, Rating, Comentariu, DataRecenzie) 
VALUES ( 1, 4, 'Foarte bun', '2024-01-01');
INSERT INTO Recenzii (Pid, Rating, Comentariu, DataRecenzie) 
VALUES ( 2, 5, 'Excelent', '2024-01-02');
INSERT INTO Recenzii ( Pid, Rating, Comentariu, DataRecenzie) 
VALUES ( 3, 3, 'Acceptabil', '2024-01-03');
INSERT INTO Recenzii ( Pid, Rating, Comentariu, DataRecenzie) 
VALUES ( 4, 5, 'Excelent', '2024-01-04');

-- Pentru tabelul ProduseCategorii
INSERT INTO ProduseCategorii (Pid, Cid) VALUES (1, 1);
INSERT INTO ProduseCategorii (Pid, Cid) VALUES (2, 1);
INSERT INTO ProduseCategorii (Pid, Cid) VALUES (3, 1);
INSERT INTO ProduseCategorii (Pid, Cid) VALUES (4, 1);


-- Pentru a vedea înregistrările din tabelul Produse
SELECT * FROM Produse;

-- Pentru a vedea înregistrările din tabelul Categorii
SELECT * FROM Categorii;

-- Pentru a vedea înregistrările din tabelul Branduri
SELECT * FROM Branduri;

-- Pentru a vedea înregistrările din tabelul Magazine
SELECT * FROM Magazine;

-- Pentru a vedea înregistrările din tabelul Angajati
SELECT * FROM Angajati;

-- Pentru a vedea înregistrările din tabelul Clienti
SELECT * FROM Clienti;

-- Pentru a vedea înregistrările din tabelul Comenzi
SELECT * FROM Comenzi;

-- Pentru a vedea înregistrările din tabelul ArticoleComanda
SELECT * FROM ArticoleComanda;

-- Pentru a vedea înregistrările din tabelul ProduseBranduri
SELECT * FROM ProduseBranduri;

-- Pentru a vedea înregistrările din tabelul Recenzii
SELECT * FROM Recenzii;

-- Pentru a vedea înregistrările din tabelul ProduseCategorii
SELECT * FROM ProduseCategorii;
