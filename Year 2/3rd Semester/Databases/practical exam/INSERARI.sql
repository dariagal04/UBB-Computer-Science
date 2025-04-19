USE Carmangerii




INSERT INTO Locatie (denumire, oras, strada, numar)
VALUES 
('Locatie 1', 'Oradea', 'Strada Mare', 12),
('Locatie 2', 'Cluj-Napoca', 'Strada Mică', 45);
('Locatie 3', 'Cluj-Napoca', 'Strada Mică', 56);

INSERT INTO Carmangerii (denumire, idLocatie)
VALUES 
('Carmangeria 1', 1),
('Carmangeria 2', 2),
('Carmangeria 3', 3);


INSERT INTO TipuriDeCarne (denumire, descriere)
VALUES 
('Vită', 'Carne roșie, ideală pentru fripturi'),
('Pui', 'Carne albă, slabă și sănătoasă');


INSERT INTO Carne (denumire, idTip, gramaj, dataLivrare, cantitateDisponibila, dataExpirarii, idCarmangerie)
VALUES 
('Cotlet de vită', 1, 500, '2025-01-10', 20, '2025-02-01', 1),
('Piept de pui', 2, 700, '2025-01-12', 15, '2025-01-25', 2);

SELECT * FROM Locatie
SELECT * FROM Carmangerii
SELECT * FROM TipuriDeCarne
SELECT * FROM Carne
