CREATE DATABASE Carmangerii;
GO

USE Carmangerii;
GO


CREATE TABLE Carmangerii
(
    idCarmangerie INT IDENTITY(1,1) PRIMARY KEY,
    denumire VARCHAR(100),
    idLocatie INT FOREIGN KEY REFERENCES Locatie(idLocatie)
);

CREATE TABLE TipuriDeCarne 
(
    idTip INT IDENTITY(1,1) PRIMARY KEY,
    denumire VARCHAR(100),
    descriere VARCHAR(255)
);

CREATE TABLE Carne
(
    idCarne INT IDENTITY(1,1) PRIMARY KEY,
    denumire VARCHAR(100),
    idTip INT FOREIGN KEY REFERENCES TipuriDeCarne(idTip),
    gramaj INT,
    dataLivrare DATE,
	cantitateDisponibila INT,
    dataExpirarii DATE,
    idCarmangerie INT FOREIGN KEY REFERENCES Carmangerii(idCarmangerie)
);

CREATE TABLE Locatie
(
	idLocatie INT IDENTITY(1,1) PRIMARY KEY,
	denumire VARCHAR(50),
	oras VARCHAR(50),
	strada VARCHAR(50),
	numar INT
);


INSERT INTO Locatie (denumire, oras, strada, numar)
VALUES 
('Locatie 1', 'Oradea', 'Strada Mare', 12),
('Locatie 2', 'Cluj-Napoca', 'Strada Mică', 45),
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




CREATE OR ALTER PROCEDURE AdaugaSauActualizeazaCarne
    @denumireCarne VARCHAR(100),
    @idCarmangerie INT,
    @idTip INT,
    @gramaj INT,
    @cantitateDisponibila INT,
    @dataLivrare DATE,
    @dataExpirare DATE
AS
BEGIN
    -- Verificam daca carnea exista deja in carmangerie
    IF EXISTS (
        SELECT 1
        FROM Carne
        WHERE denumire = @denumireCarne AND idCarmangerie = @idCarmangerie
    )
    BEGIN
        -- Daca exista, actualizam cantitatea disponibila și data de expirare
        UPDATE Carne
        SET 
            cantitateDisponibila = cantitateDisponibila + @cantitateDisponibila,
            dataExpirarii = @dataExpirare
        WHERE denumire = @denumireCarne AND idCarmangerie = @idCarmangerie;

        PRINT 'Carnea a fost actualizată cu noua cantitate și data de expirare.';
    END
    ELSE
    BEGIN
        -- Dacă nu există, o adăugăm
        INSERT INTO Carne (denumire, idTip, gramaj, dataLivrare, cantitateDisponibila, dataExpirarii, idCarmangerie)
        VALUES (@denumireCarne, @idTip, @gramaj, @dataLivrare, @cantitateDisponibila, @dataExpirare, @idCarmangerie);

        PRINT 'Carnea a fost adăugată în carmangerie.';
    END
END;
GO


EXEC AdaugaSauActualizeazaCarne 
    @denumireCarne = 'carne',
    @idCarmangerie = 1,
    @idTip = 1,
    @gramaj = 500,
    @cantitateDisponibila = 10,
    @dataLivrare = '2025-01-14',
    @dataExpirare = '2025-02-01';

SELECT * FROM Carne


CREATE OR ALTER VIEW CarneInMinimTreiCarmangerii AS
SELECT 
    c.denumire AS DenumireCarne
FROM 
    Carne c
GROUP BY 
    c.denumire
HAVING 
    COUNT(DISTINCT c.idCarmangerie) >= 3;
GO


SELECT * FROM CarneInMinimTreiCarmangerii;
