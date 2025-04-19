USE MagazineCosmetice
GO


--------------

CREATE OR ALTER FUNCTION validare_produs(
    @Pid INT,
    @Denumire VARCHAR(50),
    @Pret DECIMAL(10, 2),
    @NrBucati INT
)
RETURNS VARCHAR(1000)
AS
BEGIN
    DECLARE @erori VARCHAR(1000);
    SET @erori = '';

    IF EXISTS (SELECT 1 FROM Produse WHERE Pid = @Pid)
        SET @erori = @erori + 'Exista deja un produs cu ID-ul: ' + CONVERT(VARCHAR, @Pid) + CHAR(13) + CHAR(10);

    IF (@Denumire = '' OR @Denumire IS NULL)
        SET @erori = @erori + 'Denumirea produsului nu poate fi vida.' + CHAR(13) + CHAR(10);

    IF (@Pret <= 0)
        SET @erori = @erori + 'Pretul trebuie sa fie mai mare decat zero.' + CHAR(13) + CHAR(10);

    IF (@NrBucati < 0)
        SET @erori = @erori + 'Numarul de bucati nu poate fi negativ.' + CHAR(13) + CHAR(10);

    RETURN @erori;
END;
GO

CREATE OR ALTER PROCEDURE CRUD_Produse(
    @Pid INT,
    @Denumire VARCHAR(50),
    @Pret DECIMAL(10, 2),
    @NrBucati INT
)
AS
BEGIN
    DECLARE @erori VARCHAR(1000);
    SET @erori = dbo.validare_produs(@Pid, @Denumire, @Pret, @NrBucati);

    IF (@erori != '')
    BEGIN
        PRINT @erori;
        RETURN;
    END;

    -- CREATE
    INSERT INTO Produse (Denumire, Pret, NrBucati)
    VALUES (@Denumire, @Pret, @NrBucati);
    PRINT 'Produs inserat cu succes.';

    -- READ
    SELECT * FROM Produse;

    -- UPDATE
    UPDATE Produse SET Pret = @Pret + 5 WHERE Pid = @Pid;
    PRINT 'Pretul produsului a fost actualizat.';

    -- DELETE
    DELETE FROM Produse WHERE Pid = @Pid;
    PRINT 'Produsul a fost sters.';
END;
GO

EXEC CRUD_Produse @Pid = 5, @Denumire = 'Crema hidratanta', @Pret = 25.00, @NrBucati = 100;

EXEC CRUD_Produse @Pid = 268, @Denumire = 'Ruj2', @Pret = 25.00, @NrBucati = 50;

EXEC CRUD_Produse @Pid = 1, @Denumire = 'Ruj', @Pret = 25.00, @NrBucati = 50;

GO

---------------------------

CREATE OR ALTER FUNCTION validare_comanda(
    @ComandaID INT,
    @ClientID INT,
    @Mid INT,
    @SumaTotala DECIMAL(10, 2)
)
RETURNS VARCHAR(1000)
AS
BEGIN
    DECLARE @erori VARCHAR(1000);
    SET @erori = '';

    IF EXISTS (SELECT 1 FROM Comenzi WHERE ComandaID = @ComandaID)
        SET @erori = @erori + 'Exista deja o comanda cu ID-ul: ' + CONVERT(VARCHAR, @ComandaID) + CHAR(13) + CHAR(10);

    IF NOT EXISTS (SELECT 1 FROM Clienti WHERE ClientID = @ClientID)
        SET @erori = @erori + 'Clientul cu acest ID nu exista.' + CHAR(13) + CHAR(10);

    IF NOT EXISTS (SELECT 1 FROM Magazine WHERE Mid = @Mid)
        SET @erori = @erori + 'Magazinul cu acest ID nu exista.' + CHAR(13) + CHAR(10);

    IF (@SumaTotala < 0)
        SET @erori = @erori + 'Suma totala nu poate fi negativa.' + CHAR(13) + CHAR(10);

    RETURN @erori;
END;
GO


CREATE OR ALTER PROCEDURE CRUD_Comenzi(
    @ComandaID INT,
    @ClientID INT,
    @Mid INT,
    @SumaTotala DECIMAL(10, 2)
)
AS
BEGIN
    DECLARE @erori VARCHAR(1000);
    SET @erori = dbo.validare_comanda(@ComandaID, @ClientID, @Mid, @SumaTotala);

    IF (@erori != '')
    BEGIN
        PRINT @erori;
        RETURN;
    END;

    -- CREATE
    INSERT INTO Comenzi (ClientID, Mid, SumaTotala)
    VALUES (@ClientID, @Mid, @SumaTotala);
    PRINT 'Comanda inserata cu succes.';

    -- READ
    SELECT * FROM Comenzi;

    -- UPDATE
    UPDATE Comenzi SET SumaTotala = @SumaTotala + 50 WHERE ComandaID = @ComandaID;
    PRINT 'Suma totala a comenzii a fost actualizata.';

    -- DELETE
    DELETE FROM Comenzi WHERE ComandaID = @ComandaID;
    PRINT 'Comanda a fost stearsa.';
END;
GO

EXEC CRUD_Comenzi @ComandaID = 2, @ClientID = 1, @Mid = 1, @SumaTotala = 200.00;

EXEC CRUD_Comenzi @ComandaID = 2, @ClientID = 1, @Mid = 1, @SumaTotala = 250.00;

EXEC CRUD_Comenzi @ComandaID = 2, @ClientID = 1, @Mid = 1, @SumaTotala = 250.00;


-------------------------

CREATE OR ALTER FUNCTION validare_produse_categorii(@pid INT, @cid INT)
RETURNS VARCHAR(1000)
AS
BEGIN
    DECLARE @erori VARCHAR(1000);
    SET @erori = '';

    IF NOT EXISTS (SELECT 1 FROM Produse WHERE Pid = @pid)
        SET @erori = @erori + 'Produsul cu ID-ul ' + CONVERT(VARCHAR, @pid) + ' nu există.' + CHAR(13) + CHAR(10);

    IF NOT EXISTS (SELECT 1 FROM Categorii WHERE Cid = @cid)
        SET @erori = @erori + 'Categoria cu ID-ul ' + CONVERT(VARCHAR, @cid) + ' nu există.' + CHAR(13) + CHAR(10);

    IF EXISTS (SELECT 1 FROM ProduseCategorii WHERE Pid = @pid AND Cid = @cid)
        SET @erori = @erori + 'Relația dintre produsul ' + CONVERT(VARCHAR, @pid) + ' și categoria ' + CONVERT(VARCHAR, @cid) + ' deja există.' + CHAR(13) + CHAR(10);

    RETURN @erori;
END
GO 

CREATE OR ALTER PROCEDURE CRUD_produse_categorii(@pid INT, @cid INT)
AS
BEGIN
    DECLARE @erori VARCHAR(1000);
    SET @erori = dbo.validare_produse_categorii(@pid, @cid);

    IF @erori != ''
    BEGIN
        PRINT @erori;
        RETURN;
    END

    -- CREATE
    INSERT INTO ProduseCategorii (Pid, Cid) VALUES (@pid, @cid);
    PRINT 'Am inserat în ProduseCategorii valorile: Pid=' + CONVERT(VARCHAR, @pid) + ', Cid=' + CONVERT(VARCHAR, @cid);

    -- READ
    SELECT * FROM ProduseCategorii;

    -- UPDATE
    PRINT 'Actualizarea nu este aplicabilă pentru relațiile many-to-many.';

    -- DELETE
    DELETE FROM ProduseCategorii WHERE Pid = @pid AND Cid = @cid;
    PRINT 'Am șters relația dintre Pid=' + CONVERT(VARCHAR, @pid) + ' și Cid=' + CONVERT(VARCHAR, @cid);

    -- SELECT FINAL
    SELECT * FROM ProduseCategorii;
END
GO

EXEC CRUD_produse_categorii @pid = 1, @cid = 1;

EXEC CRUD_produse_categorii @pid = 1, @cid = 1;



--------------------------

CREATE OR ALTER FUNCTION validare_produse_branduri(@pid INT, @bid INT)
RETURNS VARCHAR(1000)
AS
BEGIN
    DECLARE @erori VARCHAR(1000);
    SET @erori = '';

    IF NOT EXISTS (SELECT 1 FROM Produse WHERE Pid = @pid)
        SET @erori = @erori + 'Produsul cu ID-ul ' + CONVERT(VARCHAR, @pid) + ' nu există.' + CHAR(13) + CHAR(10);

    IF NOT EXISTS (SELECT 1 FROM Branduri WHERE Bid = @bid)
        SET @erori = @erori + 'Brandul cu ID-ul ' + CONVERT(VARCHAR, @bid) + ' nu există.' + CHAR(13) + CHAR(10);

    IF EXISTS (SELECT 1 FROM ProduseBranduri WHERE Pid = @pid AND Bid = @bid)
        SET @erori = @erori + 'Relația dintre produsul ' + CONVERT(VARCHAR, @pid) + ' și brandul ' + CONVERT(VARCHAR, @bid) + ' deja există.' + CHAR(13) + CHAR(10);

    RETURN @erori;
END
GO

CREATE OR ALTER PROCEDURE CRUD_produse_branduri(@pid INT, @bid INT)
AS
BEGIN
    DECLARE @erori VARCHAR(1000);
    SET @erori = dbo.validare_produse_branduri(@pid, @bid);

    IF @erori != ''
    BEGIN
        PRINT @erori;
        RETURN;
    END

    -- CREATE
    INSERT INTO ProduseBranduri (Pid, Bid) VALUES (@pid, @bid);
    PRINT 'Am inserat în ProduseBranduri valorile: Pid=' + CONVERT(VARCHAR, @pid) + ', Bid=' + CONVERT(VARCHAR, @bid);

    -- READ
    SELECT * FROM ProduseBranduri;

    -- UPDATE
    PRINT 'Actualizarea nu este aplicabilă pentru relațiile many-to-many.';

    -- DELETE
    DELETE FROM ProduseBranduri WHERE Pid = @pid AND Bid = @bid;
    PRINT 'Am șters relația dintre Pid=' + CONVERT(VARCHAR, @pid) + ' și Bid=' + CONVERT(VARCHAR, @bid);

    -- SELECT FINAL
    SELECT * FROM ProduseBranduri;
END
GO

EXEC CRUD_produse_branduri @pid = 2, @bid = 1;
GO

EXEC CRUD_produse_branduri @pid = 2, @bid = 1;
GO


------------------
CREATE OR ALTER FUNCTION validare_articol_comanda(
    @ComandaID INT,
    @Pid INT,
    @Cantitate INT,
    @Pret DECIMAL(10, 2)
)
RETURNS VARCHAR(1000)
AS
BEGIN
    DECLARE @erori VARCHAR(1000);
    SET @erori = '';

    IF NOT EXISTS (SELECT 1 FROM Comenzi WHERE ComandaID = @ComandaID)
        SET @erori = @erori + 'Comanda cu acest ID nu exista.' + CHAR(13) + CHAR(10);

    IF NOT EXISTS (SELECT 1 FROM Produse WHERE Pid = @Pid)
        SET @erori = @erori + 'Produsul cu acest ID nu exista.' + CHAR(13) + CHAR(10);

    IF (@Cantitate <= 0)
        SET @erori = @erori + 'Cantitatea trebuie sa fie mai mare decat zero.' + CHAR(13) + CHAR(10);

    IF (@Pret <= 0)
        SET @erori = @erori + 'Pretul trebuie sa fie mai mare decat zero.' + CHAR(13) + CHAR(10);

    RETURN @erori;
END;
GO

CREATE OR ALTER PROCEDURE CRUD_ArticoleComanda(
    @ComandaID INT,
    @Pid INT,
    @Cantitate INT,
    @Pret DECIMAL(10, 2)
)
AS
BEGIN
    DECLARE @erori VARCHAR(1000);
    SET @erori = dbo.validare_articol_comanda(@ComandaID, @Pid, @Cantitate, @Pret);

    IF (@erori != '')
    BEGIN
        PRINT @erori;
        RETURN;
    END;

    -- CREATE
    INSERT INTO ArticoleComanda (ComandaID, Pid, Cantitate, Pret)
    VALUES (@ComandaID, @Pid, @Cantitate, @Pret);
    PRINT 'Articol adaugat in comanda.';

    -- READ
    SELECT * FROM ArticoleComanda;

    -- UPDATE
    UPDATE ArticoleComanda SET Cantitate = @Cantitate + 1 WHERE ComandaID = @ComandaID AND Pid = @Pid;
    PRINT 'Cantitatea articolului a fost actualizata.';

    -- DELETE
    DELETE FROM ArticoleComanda WHERE ComandaID = @ComandaID AND Pid = @Pid;
    PRINT 'Articolul a fost sters din comanda.';
END;
GO

EXEC CRUD_ArticoleComanda @ComandaID = 1, @Pid = 2, @Cantitate = 3, @Pret = 60.00;

EXEC CRUD_ArticoleComanda @ComandaID = 1, @Pid = 2, @Cantitate = 4, @Pret = 60.00;

EXEC CRUD_ArticoleComanda @ComandaID = 1, @Pid = 2, @Cantitate = 4, @Pret = 60.00;

GO

----------view


CREATE OR ALTER VIEW View_ProduseCategorii AS
SELECT 
    pc.Pid AS ID_Produs,
    p.Denumire AS Nume_Produs,
    c.Cid AS ID_Categorie,
    c.NumeCategorie AS Nume_Categorie
FROM 
    ProduseCategorii pc
JOIN 
    Produse p ON pc.Pid = p.Pid
JOIN 
    Categorii c ON pc.Cid = c.Cid;

GO


CREATE OR ALTER VIEW View_ProduseBranduri AS
SELECT 
    pb.Pid AS ID_Produs,
    p.Denumire AS Nume_Produs,
    b.Bid AS ID_Brand,
    b.NumeBrand AS Nume_Brand
FROM 
    ProduseBranduri pb
JOIN 
    Produse p ON pb.Pid = p.Pid
JOIN 
    Branduri b ON pb.Bid = b.Bid;



SELECT * FROM View_ProduseCategorii;
SELECT * FROM View_ProduseBranduri;



IF EXISTS(SELECT name FROM sys.indexes WHERE name = 'N_idx_ProduseCategorii_Pid_Cid')
    DROP INDEX N_idx_ProduseCategorii_Pid_Cid ON ProduseCategorii;
CREATE NONCLUSTERED INDEX N_idx_ProduseCategorii_Pid_Cid 
ON ProduseCategorii (Pid, Cid);
GO





IF EXISTS(SELECT name FROM sys.indexes WHERE name = 'N_idx_ProduseBranduri_Pid_Bid')
    DROP INDEX N_idx_ProduseBranduri_Pid_Bid ON ProduseBranduri;
CREATE NONCLUSTERED INDEX N_idx_ProduseBranduri_Pid_Bid 
ON ProduseBranduri (Pid, Bid);
GO






