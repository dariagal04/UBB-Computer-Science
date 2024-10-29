USE MagazineCosmetice

-- 1. Selecteaza ID-ul, denumirea si pretul produselor care au pretul mai mare sau egal cu 60.
SELECT Pid, Denumire, Pret
FROM Produse
WHERE Pret >= 60;

-- 2. Selecteaza ID-ul, numele angajatului si functia angajatilor care lucreaza in magazinul cu ID-ul 1.
SELECT Aid, NumeAngajat, Functie
FROM Angajati
WHERE MagazinID = 1
GROUP BY Aid, NumeAngajat, Functie;

-- 3. Selecteaza ID-urile distincte ale recenziilor pentru produsul cu rating 5.
SELECT DISTINCT Pid
FROM Recenzii
WHERE Rating= 5;

-- 4. Selecteaza denumirile produselor si numele brandurilor distincte pentru produsele care au pretul mai mic sau egal cu 60.
SELECT DISTINCT P.Denumire, B.NumeBrand
FROM Produse P
JOIN ProduseBranduri PB ON PB.Pid = P.Pid
JOIN Branduri B ON PB.Bid = B.Bid
WHERE P.Pret <= 60.00;

-- 5. Selecteaza numele magazinelor si numarul de angajati pentru magazinele care au cel putin 2 angajati.
SELECT M.NumeMagazin, COUNT(A.Aid) as NrAngajati
FROM Magazine M
JOIN Angajati A ON M.Mid = A.MagazinID
JOIN Comenzi C ON M.Mid = C.Mid
GROUP BY M.NumeMagazin
HAVING COUNT(A.Aid) >= 2;

-- 6. Selecteaza numele clientilor si suma totala cheltuita de fiecare client care a cheltuit mai mult de 300.
SELECT CL.NumeClient, SUM(C.SumaTotala) as TotalCheltuit
FROM Clienti CL
JOIN Comenzi C ON CL.ClientID = C.ClientID
JOIN ArticoleComanda AC ON C.ComandaID = AC.ComandaID
GROUP BY CL.NumeClient
HAVING SUM(C.SumaTotala) > 50;

-- 7. Selecteaza denumirile produselor si categoriile lor pentru produsele care au pretul mai mare de 50.
SELECT P.Denumire, C.NumeCategorie
FROM Produse P
JOIN ProduseCategorii PC ON P.Pid = PC.Pid
JOIN Categorii C ON PC.Cid = C.Cid
WHERE P.Pret > 50.00;

-- 8. Selecteaza numele clientilor, denumirile produselor si numele magazinelor unde au fost facute comenzi
SELECT CL.NumeClient, P.Denumire, M.NumeMagazin
FROM Clienti CL
JOIN Comenzi C ON CL.ClientID = C.ClientID
JOIN ArticoleComanda AC ON C.ComandaID = AC.ComandaID
JOIN Produse P ON AC.Pid = P.Pid
JOIN Magazine M ON C.Mid = M.Mid;


-- 9. Selecteaza numele clientilor si denumirile produselor comandate din categoria 'Machiaj'.
SELECT CL.NumeClient, P.Denumire
FROM Clienti CL
JOIN Comenzi CM ON CL.ClientID = CM.ClientID
JOIN ArticoleComanda AC ON CM.ComandaID = AC.ComandaID
JOIN Produse P ON AC.Pid = P.Pid
JOIN ProduseCategorii PC ON P.Pid = PC.Pid
JOIN Categorii C ON PC.Cid = C.Cid
WHERE C.NumeCategorie = 'Machiaj';

-- 10. Selecteaza numele magazinelor si suma totala a articolelor comandate din brandul 'BrandB'.
SELECT M.NumeMagazin, SUM(AC.Pret * AC.Cantitate) as TotalArticoleBrand
FROM Magazine M
JOIN Comenzi CM ON M.Mid = CM.Mid
JOIN ArticoleComanda AC ON CM.ComandaID = AC.ComandaID
JOIN Produse P ON AC.Pid = P.Pid
JOIN ProduseBranduri PB ON P.Pid = PB.Pid
JOIN Branduri B ON PB.Bid = B.Bid
WHERE B.NumeBrand = 'BrandB'
GROUP BY M.NumeMagazin;
