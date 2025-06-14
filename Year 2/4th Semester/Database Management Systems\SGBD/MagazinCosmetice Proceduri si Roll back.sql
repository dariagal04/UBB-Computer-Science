USE MagazineCosmetice
go;

CREATE TABLE Logs (
    log_id INT IDENTITY PRIMARY KEY,
    source_procedure VARCHAR(100),
    log_type VARCHAR(10),
    log_message NVARCHAR(MAX),
    created_at DATETIME DEFAULT GETDATE()
);

go;

CREATE OR ALTER PROCEDURE AdaugaProdusCuCategoriiBranduri
    @Denumire VARCHAR(50),
    @Pret DECIMAL(10, 2),
    @NrBucati INT,
    @Categorii NVARCHAR(MAX), 
    @Branduri NVARCHAR(MAX)   
AS
BEGIN
    BEGIN TRY
        BEGIN TRANSACTION

        
        IF @Denumire IS NULL OR LTRIM(RTRIM(@Denumire)) = ''
            RAISERROR('Denumirea produsului este obligatorie.', 16, 1)
        IF @Pret <= 0
            RAISERROR('Prețul trebuie să fie pozitiv.', 16, 1)
        IF @NrBucati < 0
            RAISERROR('Numărul de bucăți nu poate fi negativ.', 16, 1)

        -- Inserare produs
        INSERT INTO Produse (Denumire, Pret, NrBucati)
        VALUES (@Denumire, @Pret, @NrBucati)

        DECLARE @Pid INT = SCOPE_IDENTITY()

        -- Inserare categorii
        DECLARE @Categoria NVARCHAR(50)
        DECLARE CategoriiCursor CURSOR FOR
            SELECT LTRIM(RTRIM(value)) FROM STRING_SPLIT(@Categorii, ',')
        OPEN CategoriiCursor
        FETCH NEXT FROM CategoriiCursor INTO @Categoria
        WHILE @@FETCH_STATUS = 0
        BEGIN
            IF NOT EXISTS (SELECT 1 FROM Categorii WHERE NumeCategorie = @Categoria)
                INSERT INTO Categorii (NumeCategorie) VALUES (@Categoria)

            DECLARE @Cid INT = (SELECT Cid FROM Categorii WHERE NumeCategorie = @Categoria)
            INSERT INTO ProduseCategorii (Pid, Cid) VALUES (@Pid, @Cid)

            FETCH NEXT FROM CategoriiCursor INTO @Categoria
        END
        CLOSE CategoriiCursor
        DEALLOCATE CategoriiCursor

        -- Inserare branduri
        DECLARE @Brand NVARCHAR(50)
        DECLARE BranduriCursor CURSOR FOR
            SELECT LTRIM(RTRIM(value)) FROM STRING_SPLIT(@Branduri, ',')
        OPEN BranduriCursor
        FETCH NEXT FROM BranduriCursor INTO @Brand
        WHILE @@FETCH_STATUS = 0
        BEGIN
            IF NOT EXISTS (SELECT 1 FROM Branduri WHERE NumeBrand = @Brand)
                INSERT INTO Branduri (NumeBrand) VALUES (@Brand)

            DECLARE @Bid INT = (SELECT Bid FROM Branduri WHERE NumeBrand = @Brand)
            INSERT INTO ProduseBranduri (Pid, Bid) VALUES (@Pid, @Bid)

            FETCH NEXT FROM BranduriCursor INTO @Brand
        END
        CLOSE BranduriCursor
        DEALLOCATE BranduriCursor

        -- Logare
        INSERT INTO Logs (source_procedure, log_type, log_message)
        VALUES (OBJECT_NAME(@@PROCID), 'Info', 'Produsul a fost inserat cu succes.')

        COMMIT TRANSACTION
    END TRY
    BEGIN CATCH
        ROLLBACK TRANSACTION
        INSERT INTO Logs (source_procedure, log_type, log_message)
        VALUES (OBJECT_NAME(@@PROCID), 'ERROR', ERROR_MESSAGE())
    END CATCH
END
go;

CREATE OR ALTER PROCEDURE AdaugaProdusCuCategoriiBranduri_Partial
    @Denumire VARCHAR(50),
    @Pret DECIMAL(10, 2),
    @NrBucati INT,
    @Categorii NVARCHAR(MAX), 
    @Branduri NVARCHAR(MAX)  
AS
BEGIN
    BEGIN TRY
        -- Inserare categorii
        DECLARE @Categoria NVARCHAR(50)
        DECLARE CategoriiCursor CURSOR FOR
            SELECT LTRIM(RTRIM(value)) FROM STRING_SPLIT(@Categorii, ',')
        OPEN CategoriiCursor
        FETCH NEXT FROM CategoriiCursor INTO @Categoria
        WHILE @@FETCH_STATUS = 0
        BEGIN
            IF NOT EXISTS (SELECT 1 FROM Categorii WHERE NumeCategorie = @Categoria)
                INSERT INTO Categorii (NumeCategorie) VALUES (@Categoria)

            FETCH NEXT FROM CategoriiCursor INTO @Categoria
        END
        CLOSE CategoriiCursor
        DEALLOCATE CategoriiCursor

        -- Inserare branduri
        DECLARE @Brand NVARCHAR(50)
        DECLARE BranduriCursor CURSOR FOR
            SELECT LTRIM(RTRIM(value)) FROM STRING_SPLIT(@Branduri, ',')
        OPEN BranduriCursor
        FETCH NEXT FROM BranduriCursor INTO @Brand
        WHILE @@FETCH_STATUS = 0
        BEGIN
            IF NOT EXISTS (SELECT 1 FROM Branduri WHERE NumeBrand = @Brand)
                INSERT INTO Branduri (NumeBrand) VALUES (@Brand)

            FETCH NEXT FROM BranduriCursor INTO @Brand
        END
        CLOSE BranduriCursor
        DEALLOCATE BranduriCursor

        -- Logare inserare categorii si branduri
        INSERT INTO Logs (source_procedure, log_type, log_message)
        VALUES (OBJECT_NAME(@@PROCID), 'Info', 'Categorii și branduri inserate cu succes.')
    END TRY
    BEGIN CATCH
        INSERT INTO Logs (source_procedure, log_type, log_message)
        VALUES (OBJECT_NAME(@@PROCID), 'ERROR', ERROR_MESSAGE())
    END CATCH

    -- Inserare produs si relatii m:n cu tranzactie
    BEGIN TRY
        BEGIN TRANSACTION

        -- Validare parametri
        IF @Denumire IS NULL OR LTRIM(RTRIM(@Denumire)) = ''
            RAISERROR('Denumirea produsului este obligatorie.', 16, 1)
        IF @Pret <= 0
            RAISERROR('Prețul trebuie să fie pozitiv.', 16, 1)
        IF @NrBucati < 0
            RAISERROR('Numărul de bucăți nu poate fi negativ.', 16, 1)

        -- Inserare produs
        INSERT INTO Produse (Denumire, Pret, NrBucati)
        VALUES (@Denumire, @Pret, @NrBucati)

        DECLARE @Pid INT = SCOPE_IDENTITY()

        -- Inserare relatii cu categorii
        DECLARE @Cid INT
        DECLARE CategoriiCursor2 CURSOR FOR
            SELECT Cid FROM Categorii WHERE NumeCategorie IN (SELECT LTRIM(RTRIM(value)) FROM STRING_SPLIT(@Categorii, ','))
        OPEN CategoriiCursor2
        FETCH NEXT FROM CategoriiCursor2 INTO @Cid
        WHILE @@FETCH_STATUS = 0
        BEGIN
            INSERT INTO ProduseCategorii (Pid, Cid) VALUES (@Pid, @Cid)
            FETCH NEXT FROM CategoriiCursor2 INTO @Cid
        END
        CLOSE CategoriiCursor2
        DEALLOCATE CategoriiCursor2

        -- Inserare relatii cu branduri
        DECLARE @Bid INT
        DECLARE BranduriCursor2 CURSOR FOR
            SELECT Bid FROM Branduri WHERE NumeBrand IN (SELECT LTRIM(RTRIM(value)) FROM STRING_SPLIT(@Branduri, ','))
        OPEN BranduriCursor2
        FETCH NEXT FROM BranduriCursor2 INTO @Bid
        WHILE @@FETCH_STATUS = 0
        BEGIN
            INSERT INTO ProduseBranduri (Pid, Bid) VALUES (@Pid, @Bid)
            FETCH NEXT FROM BranduriCursor2 INTO @Bid
        END
        CLOSE BranduriCursor2
        DEALLOCATE BranduriCursor2

        -- Logare 
        INSERT INTO Logs (source_procedure, log_type, log_message)
        VALUES (OBJECT_NAME(@@PROCID), 'Info', 'Produsul și relațiile m:n au fost inserate cu succes.')

        COMMIT TRANSACTION
    END TRY
    BEGIN CATCH
        ROLLBACK TRANSACTION
        INSERT INTO Logs (source_procedure, log_type, log_message)
        VALUES (OBJECT_NAME(@@PROCID), 'ERROR', ERROR_MESSAGE())
    END CATCH
END


EXEC AdaugaProdusCuCategoriiBranduri
    @Denumire = 'Test Produs A',
    @Pret = 123.45,
    @NrBucati = 10,
    @Categorii = 'Skincare, Makeup',
    @Branduri = 'L''Oreal, Nivea';


SELECT * FROM Produse WHERE Denumire = 'Test Produs A';
SELECT * FROM Categorii WHERE NumeCategorie IN ('Skincare', 'Makeup');
SELECT * FROM Branduri WHERE NumeBrand IN ('L''Oreal', 'Nivea');
SELECT * FROM ProduseCategorii pc
JOIN Produse p ON pc.Pid = p.Pid
WHERE p.Denumire = 'Test Produs A';
SELECT * FROM ProduseBranduri pb
JOIN Produse p ON pb.Pid = p.Pid
WHERE p.Denumire = 'Test Produs A';
SELECT * FROM Logs ORDER BY created_at DESC;


EXEC AdaugaProdusCuCategoriiBranduri
    @Denumire = '', -- invalid
    @Pret = 50,
    @NrBucati = 5,
    @Categorii = 'Haircare',
    @Branduri = 'Pantene';

EXEC AdaugaProdusCuCategoriiBranduri_Partial
    @Denumire = '', -- invalid
    @Pret = 50,
    @NrBucati = 5,
    @Categorii = 'Haircare',
    @Branduri = 'Pantene';



go;

SELECT * FROM Logs ORDER BY created_at DESC;


SELECT * FROM Produse

