USE Carmangerii

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
    -- Verificăm dacă carnea există deja în carmangerie
    IF EXISTS (
        SELECT 1
        FROM Carne
        WHERE denumire = @denumireCarne AND idCarmangerie = @idCarmangerie
    )
    BEGIN
        -- Dacă există, actualizăm cantitatea disponibilă și data de expirare
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
    @denumireCarne = 'Ceafa de porc',
    @idCarmangerie = 3,
    @idTip = 1,
    @gramaj = 500,
    @cantitateDisponibila = 10,
    @dataLivrare = '2025-01-14',
    @dataExpirare = '2025-02-01';

SELECT * FROM Carne
