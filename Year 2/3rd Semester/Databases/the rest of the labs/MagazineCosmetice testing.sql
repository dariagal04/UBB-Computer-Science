USE MagazineCosmetice

GO
CREATE OR ALTER VIEW View_1
AS
	SELECT * FROM Comenzi
GO

CREATE OR ALTER VIEW View_2 AS
SELECT 
    c.ComandaID AS comanda,
    cl.ClientID AS client
FROM 
    Comenzi c
JOIN 
    Clienti cl ON c.ClientID = cl.ClientID;
GO

CREATE OR ALTER VIEW View_3
AS
    SELECT c.ComandaID, COUNT(DISTINCT ac.Pid) AS NumarProduseDistincte
    FROM Comenzi c
    JOIN ArticoleComanda ac ON ac.ComandaID = c.ComandaID
    GROUP BY c.ComandaID;
GO


if exists (select * from dbo.sysobjects where id = object_id(N'[FK_TestRunTables_Tables]') and OBJECTPROPERTY(id, N'IsForeignKey') = 1)
ALTER TABLE [TestRunTables] DROP CONSTRAINT FK_TestRunTables_Tables
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[FK_TestTables_Tables]') and OBJECTPROPERTY(id, N'IsForeignKey') = 1)
ALTER TABLE [TestTables] DROP CONSTRAINT FK_TestTables_Tables
GO
 
if exists (select * from dbo.sysobjects where id = object_id(N'[FK_TestRunTables_TestRuns]') and OBJECTPROPERTY(id, N'IsForeignKey') = 1)
ALTER TABLE [TestRunTables] DROP CONSTRAINT FK_TestRunTables_TestRuns
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[FK_TestRunViews_TestRuns]') and OBJECTPROPERTY(id, N'IsForeignKey') = 1)
ALTER TABLE [TestRunViews] DROP CONSTRAINT FK_TestRunViews_TestRuns
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[FK_TestTables_Tests]') and OBJECTPROPERTY(id, N'IsForeignKey') = 1)
ALTER TABLE [TestTables] DROP CONSTRAINT FK_TestTables_Tests
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[FK_TestViews_Tests]') and OBJECTPROPERTY(id, N'IsForeignKey') = 1)
ALTER TABLE [TestViews] DROP CONSTRAINT FK_TestViews_Tests
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[FK_TestRunViews_Views]') and OBJECTPROPERTY(id, N'IsForeignKey') = 1)
ALTER TABLE [TestRunViews] DROP CONSTRAINT FK_TestRunViews_Views
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[FK_TestViews_Views]') and OBJECTPROPERTY(id, N'IsForeignKey') = 1)
ALTER TABLE [TestViews] DROP CONSTRAINT FK_TestViews_Views
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[Tables]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [Tables]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[TestRunTables]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [TestRunTables]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[TestRunViews]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [TestRunViews]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[TestRuns]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [TestRuns]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[TestTables]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [TestTables]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[TestViews]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [TestViews]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[Tests]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [Tests]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[Views]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [Views]
GO

CREATE TABLE [Tables] (
	[TableID] [int] IDENTITY (1, 1) NOT NULL ,
	[Name] [nvarchar] (50) COLLATE SQL_Latin1_General_CP1_CI_AS NOT NULL 
) ON [PRIMARY]
GO

CREATE TABLE [TestRunTables] (
	[TestRunID] [int] NOT NULL ,
	[TableID] [int] NOT NULL ,
	[StartAt] [datetime] NOT NULL ,
	[EndAt] [datetime] NOT NULL 
) ON [PRIMARY]
GO

CREATE TABLE [TestRunViews] (
	[TestRunID] [int] NOT NULL ,
	[ViewID] [int] NOT NULL ,
	[StartAt] [datetime] NOT NULL ,
	[EndAt] [datetime] NOT NULL 
) ON [PRIMARY]
GO

CREATE TABLE [TestRuns] (
	[TestRunID] [int] IDENTITY (1, 1) NOT NULL ,
	[Description] [nvarchar] (2000) COLLATE SQL_Latin1_General_CP1_CI_AS NULL ,
	[StartAt] [datetime] NULL ,
	[EndAt] [datetime] NULL 
) ON [PRIMARY]
GO

CREATE TABLE [TestTables] (
	[TestID] [int] NOT NULL ,
	[TableID] [int] NOT NULL ,
	[NoOfRows] [int] NOT NULL ,
	[Position] [int] NOT NULL 
) ON [PRIMARY]
GO

CREATE TABLE [TestViews] (
	[TestID] [int] NOT NULL ,
	[ViewID] [int] NOT NULL 
) ON [PRIMARY]
GO

CREATE TABLE [Tests] (
	[TestID] [int] IDENTITY (1, 1) NOT NULL ,
	[Name] [nvarchar] (50) COLLATE SQL_Latin1_General_CP1_CI_AS NOT NULL 
) ON [PRIMARY]
GO

CREATE TABLE [Views] (
	[ViewID] [int] IDENTITY (1, 1) NOT NULL ,
	[Name] [nvarchar] (50) COLLATE SQL_Latin1_General_CP1_CI_AS NOT NULL 
) ON [PRIMARY]
GO

ALTER TABLE [Tables] WITH NOCHECK ADD 
	CONSTRAINT [PK_Tables] PRIMARY KEY  CLUSTERED 
	(
		[TableID]
	)  ON [PRIMARY] 
GO

ALTER TABLE [TestRunTables] WITH NOCHECK ADD 
	CONSTRAINT [PK_TestRunTables] PRIMARY KEY  CLUSTERED 
	(
		[TestRunID],
		[TableID]
	)  ON [PRIMARY] 
GO

ALTER TABLE [TestRunViews] WITH NOCHECK ADD 
	CONSTRAINT [PK_TestRunViews] PRIMARY KEY  CLUSTERED 
	(
		[TestRunID],
		[ViewID]
	)  ON [PRIMARY] 
GO

ALTER TABLE [TestRuns] WITH NOCHECK ADD 
	CONSTRAINT [PK_TestRuns] PRIMARY KEY  CLUSTERED 
	(
		[TestRunID]
	)  ON [PRIMARY] 
GO

ALTER TABLE [TestTables] WITH NOCHECK ADD 
	CONSTRAINT [PK_TestTables] PRIMARY KEY  CLUSTERED 
	(
		[TestID],
		[TableID]
	)  ON [PRIMARY] 
GO

ALTER TABLE [TestViews] WITH NOCHECK ADD 
	CONSTRAINT [PK_TestViews] PRIMARY KEY  CLUSTERED 
	(
		[TestID],
		[ViewID]
	)  ON [PRIMARY] 
GO

ALTER TABLE [Tests] WITH NOCHECK ADD 
	CONSTRAINT [PK_Tests] PRIMARY KEY  CLUSTERED 
	(
		[TestID]
	)  ON [PRIMARY] 
GO

ALTER TABLE [Views] WITH NOCHECK ADD 
	CONSTRAINT [PK_Views] PRIMARY KEY  CLUSTERED 
	(
		[ViewID]
	)  ON [PRIMARY] 
GO

ALTER TABLE [TestRunTables] ADD 
	CONSTRAINT [FK_TestRunTables_Tables] FOREIGN KEY 
	(
		[TableID]
	) REFERENCES [Tables] (
		[TableID]
	) ON DELETE CASCADE  ON UPDATE CASCADE ,
	CONSTRAINT [FK_TestRunTables_TestRuns] FOREIGN KEY 
	(
		[TestRunID]
	) REFERENCES [TestRuns] (
		[TestRunID]
	) ON DELETE CASCADE  ON UPDATE CASCADE 
GO

ALTER TABLE [TestRunViews] ADD 
	CONSTRAINT [FK_TestRunViews_TestRuns] FOREIGN KEY 
	(
		[TestRunID]
	) REFERENCES [TestRuns] (
		[TestRunID]
	) ON DELETE CASCADE  ON UPDATE CASCADE ,
	CONSTRAINT [FK_TestRunViews_Views] FOREIGN KEY 
	(
		[ViewID]
	) REFERENCES [Views] (
		[ViewID]
	) ON DELETE CASCADE  ON UPDATE CASCADE 
GO

ALTER TABLE [TestTables] ADD 
	CONSTRAINT [FK_TestTables_Tables] FOREIGN KEY 
	(
		[TableID]
	) REFERENCES [Tables] (
		[TableID]
	) ON DELETE CASCADE  ON UPDATE CASCADE ,
	CONSTRAINT [FK_TestTables_Tests] FOREIGN KEY 
	(
		[TestID]
	) REFERENCES [Tests] (
		[TestID]
	) ON DELETE CASCADE  ON UPDATE CASCADE 
GO

ALTER TABLE [TestViews] ADD 
	CONSTRAINT [FK_TestViews_Tests] FOREIGN KEY 
	(
		[TestID]
	) REFERENCES [Tests] (
		[TestID]
	),
	CONSTRAINT [FK_TestViews_Views] FOREIGN KEY 
	(
		[ViewID]
	) REFERENCES [Views] (
		[ViewID]
	)
GO


INSERT INTO Views(Name) VALUES
('View_1'),('View_1'),('View_1')

INSERT INTO Tests(Name) VALUES
('Insert'),('Delete'),('Evaluate')

SELECT * FROM Views
SELECT * FROM Tests
SELECT * FROM Tables

INSERT INTO TestViews(TestID,ViewID) VALUES
(3,1),(3,2),(3,3)

INSERT INTO Tables(Name) VALUES
('Produse'),('Branduri'),('Categorii'),('Angajati')
,('Comenzi'),('ArticoleComanda')

INSERT INTO TestTables(TestID,TableID,NoOfRows,Position) VALUES
(1,1,50,1),(1,2,50,2),(1,3,50,3),(1,4,50,4),(1,5,50,5),(1,6,50,6)
INSERT INTO TestTables(TestID,TableID,NoOfRows,Position) VALUES
(2,1,50,6),(2,2,50,5),(2,3,50,4),(2,4,50,3),(2,5,50,2),(2,6,50,1)
GO


CREATE OR ALTER PROCEDURE insert_
    @no_of_rows INT,
    @position INT
AS
BEGIN
    -- Produse
    DECLARE @Pid INT
    DECLARE @Denumire VARCHAR(50)
    DECLARE @Categorie VARCHAR(50)
    DECLARE @Pret DECIMAL(10,2)
    DECLARE @NrBucati INT

    -- Categorii
    DECLARE @Cid INT
    DECLARE @NumeCategorie VARCHAR(50)

    -- Branduri
    DECLARE @Bid INT
    DECLARE @NumeBrand VARCHAR(50)

    -- Magazine
    DECLARE @Mid INT
    DECLARE @NumeMagazin VARCHAR(50)
    DECLARE @NumarAngajati INT

    -- Angajati
    DECLARE @Aid INT 
    DECLARE @NumeAngajat VARCHAR(50)
    DECLARE @Functie VARCHAR(50)
    DECLARE @MagazinID INT

    -- Clienti
    DECLARE @ClientID INT
    DECLARE @NumeClient VARCHAR(50)
    DECLARE @Email VARCHAR(50)
    DECLARE @Telefon VARCHAR(20)

    -- Comenzi
    DECLARE @ComandaID INT
    DECLARE @SumaTotala DECIMAL(10,2)

    -- ArticoleComanda
    DECLARE @ArticolComandaID INT
    DECLARE @ComandaID_fk INT
    DECLARE @Pid_fk INT
    DECLARE @Cantitate INT
    DECLARE @Pret_ DECIMAL(10,2)

    DECLARE @cnt INT
    SET @cnt = 1

    WHILE @cnt <= @no_of_rows
    BEGIN
        IF @position = 1 -- Inserare în tabela Produse
        BEGIN
            SET @Denumire = 'Produs ' + CAST(@cnt AS VARCHAR)
            SET @Categorie = 'Categorie ' + CAST(@cnt % 10 AS VARCHAR)
            SET @Pret = 10.00 + @cnt
            SET @NrBucati = @cnt * 2

            INSERT INTO Produse (Denumire, Categorie, Pret, NrBucati)
            VALUES (@Denumire, @Categorie, @Pret, @NrBucati)
        END
        ELSE IF @position = 2 -- Inserare în tabela Categorii
        BEGIN
            SET @NumeCategorie = 'Categorie ' + CAST(@cnt AS VARCHAR)
            INSERT INTO Categorii (NumeCategorie)
            VALUES (@NumeCategorie)
        END
        ELSE IF @position = 3 -- Inserare în tabela Branduri
        BEGIN
            SET @NumeBrand = 'Brand ' + CAST(@cnt AS VARCHAR)
            INSERT INTO Branduri (NumeBrand)
            VALUES (@NumeBrand)
        END
        ELSE IF @position = 4 -- Inserare în tabela Magazine
        BEGIN
            SET @NumeMagazin = 'Magazin ' + CAST(@cnt AS VARCHAR)
            SET @NumarAngajati = 5 + (@cnt % 10)
            INSERT INTO Magazine (NumeMagazin, NumarAngajati)
            VALUES (@NumeMagazin, @NumarAngajati)
        END
        ELSE IF @position = 5 -- Inserare în tabela Angajati
        BEGIN
            SELECT TOP 1 @Mid = Mid FROM Magazine ORDER BY NEWID()
            IF @Mid IS NOT NULL
            BEGIN
                SET @NumeAngajat = 'Angajat ' + CAST(@cnt AS VARCHAR)
                SET @Functie = 'Functie ' + CAST(@cnt % 5 AS VARCHAR)
                INSERT INTO Angajati (NumeAngajat, Functie, MagazinID)
                VALUES (@NumeAngajat, @Functie, @Mid)
            END
        END
        ELSE IF @position = 6 -- Inserare în tabela Clienti
        BEGIN
            SET @NumeClient = 'Client ' + CAST(@cnt AS VARCHAR)
            SET @Email = 'client' + CAST(@cnt AS VARCHAR) + '@example.com'
            SET @Telefon = '07' + CAST((@cnt % 10000000) AS VARCHAR)

            INSERT INTO Clienti (NumeClient, Email, Telefon)
            VALUES (@NumeClient, @Email, @Telefon)
        END
        ELSE IF @position = 7 -- Inserare în tabela Comenzi
        BEGIN
            SELECT TOP 1 @ClientID = ClientID FROM Clienti ORDER BY NEWID()
            SELECT TOP 1 @Mid = Mid FROM Magazine ORDER BY NEWID()

            IF @ClientID IS NOT NULL AND @Mid IS NOT NULL
            BEGIN
                SET @SumaTotala = 100.00 + @cnt * 10
                INSERT INTO Comenzi (ClientID, Mid, SumaTotala)
                VALUES (@ClientID, @Mid, @SumaTotala)
            END
        END
        ELSE IF @position = 8 -- Inserare în tabela ArticoleComanda
        BEGIN
            SELECT TOP 1 @ComandaID = ComandaID FROM Comenzi ORDER BY NEWID()
            SELECT TOP 1 @Pid = Pid FROM Produse ORDER BY NEWID()

            IF @ComandaID IS NOT NULL AND @Pid IS NOT NULL
            BEGIN
                SET @Cantitate = 1 + (@cnt % 10)
                SET @Pret_ = 20.00 + @cnt

                INSERT INTO ArticoleComanda (ComandaID, Pid, Cantitate, Pret)
                VALUES (@ComandaID, @Pid, @Cantitate, @Pret_)
            END
        END

        SET @cnt = @cnt + 1
    END
END
GO


CREATE OR ALTER PROCEDURE delete_
    @no_of_rows INT,
    @position INT
AS
BEGIN
    DECLARE @cnt INT
    SET @cnt = 1

    -- Variabile pentru identificatori
    DECLARE @id_produse INT
    DECLARE @id_categorii INT
    DECLARE @id_branduri INT
    DECLARE @id_magazine INT
    DECLARE @id_angajati INT
    DECLARE @id_clienti INT
    DECLARE @id_comenzi INT
    DECLARE @id_articole INT

    -- Inițializarea variabilelor cu cele mai mici ID-uri disponibile
    SET @id_produse = (SELECT MIN(Pid) FROM Produse)
    SET @id_categorii = (SELECT MIN(Cid) FROM Categorii)
    SET @id_branduri = (SELECT MIN(Bid) FROM Branduri)
    SET @id_magazine = (SELECT MIN(Mid) FROM Magazine)
    SET @id_angajati = (SELECT MIN(Aid) FROM Angajati)
    SET @id_clienti = (SELECT MIN(ClientID) FROM Clienti)
    SET @id_comenzi = (SELECT MIN(ComandaID) FROM Comenzi)
    SET @id_articole = (SELECT MIN(ArticolComandaID) FROM ArticoleComanda)

    WHILE @cnt <= @no_of_rows
    BEGIN
        IF @position = 1 -- stergere din ArticoleComanda
        BEGIN
            DELETE FROM ArticoleComanda WHERE ArticolComandaID = @id_articole
            SET @id_articole = (SELECT MIN(ArticolComandaID) FROM ArticoleComanda)
        END
        ELSE IF @position = 2 -- stergere din Comenzi
        BEGIN
            DELETE FROM ArticoleComanda WHERE ComandaID = @id_comenzi
            DELETE FROM Comenzi WHERE ComandaID = @id_comenzi
            SET @id_comenzi = (SELECT MIN(ComandaID) FROM Comenzi)
        END
        ELSE IF @position = 3 -- stergere din Produse
        BEGIN
            DELETE FROM ProduseBranduri WHERE Pid = @id_produse
            DELETE FROM ProduseCategorii WHERE Pid = @id_produse
            DELETE FROM Recenzii WHERE Pid = @id_produse
            DELETE FROM ArticoleComanda WHERE Pid = @id_produse
            DELETE FROM Produse WHERE Pid = @id_produse
            SET @id_produse = (SELECT MIN(Pid) FROM Produse)
        END
        ELSE IF @position = 4 -- stergere din Categorii
        BEGIN
            DELETE FROM ProduseCategorii WHERE Cid = @id_categorii
            DELETE FROM Categorii WHERE Cid = @id_categorii
            SET @id_categorii = (SELECT MIN(Cid) FROM Categorii)
        END
        ELSE IF @position = 5 -- Ștergere din Branduri
        BEGIN
            DELETE FROM ProduseBranduri WHERE Bid = @id_branduri
            DELETE FROM Branduri WHERE Bid = @id_branduri
            SET @id_branduri = (SELECT MIN(Bid) FROM Branduri)
        END
        ELSE IF @position = 6 -- stergere din Magazine
        BEGIN
            DELETE FROM Angajati WHERE MagazinID = @id_magazine
            DELETE FROM Comenzi WHERE Mid = @id_magazine
            DELETE FROM Magazine WHERE Mid = @id_magazine
            SET @id_magazine = (SELECT MIN(Mid) FROM Magazine)
        END
        ELSE IF @position = 7 -- stergere din Angajati
        BEGIN
            DELETE FROM Angajati WHERE Aid = @id_angajati
            SET @id_angajati = (SELECT MIN(Aid) FROM Angajati)
        END
        ELSE IF @position = 8 -- stergere din Clienti
        BEGIN
            DELETE FROM Comenzi WHERE ClientID = @id_clienti
            DELETE FROM Clienti WHERE ClientID = @id_clienti
            SET @id_clienti = (SELECT MIN(ClientID) FROM Clienti)
        END

        SET @cnt = @cnt + 1
    END
END
GO





CREATE OR ALTER PROCEDURE evaluate_
	@no_of_view INT
AS
BEGIN
	IF @no_of_view=1
	BEGIN
		SELECT * FROM View_1
	END
	ELSE IF @no_of_view=2
	BEGIN
		SELECT * FROM View_2
	END
	ELSE IF @no_of_view=3
	BEGIN
		SELECT * FROM View_3
	END
END
GO


CREATE OR ALTER PROCEDURE TestAll
    @tableID VARCHAR(20)
AS
BEGIN
    SET @tableID = CONVERT(INT, @tableID);

    DECLARE @start DATETIME, @end DATETIME, @intermediate DATETIME;
    DECLARE @table VARCHAR(50), @test VARCHAR(50);
    DECLARE @no_of_rows INT, @position INT, @testID INT;

    SET @start = GETDATE();

    DECLARE delete_cursor CURSOR FOR
    SELECT t.Name, tt.NoOfRows, tt.Position
    FROM Tests t
    INNER JOIN TestTables tt ON t.TestID = tt.TestID
    WHERE tt.TestID = 2;

    OPEN delete_cursor;
    FETCH NEXT FROM delete_cursor INTO @test, @no_of_rows, @position;

    WHILE @@FETCH_STATUS = 0
    BEGIN
        PRINT 'Calling delete with @no_of_rows=' + CAST(@no_of_rows AS VARCHAR) + ', @position=' + CAST(@position AS VARCHAR);
        EXECUTE delete_ @no_of_rows, @position;

        FETCH NEXT FROM delete_cursor INTO @test, @no_of_rows, @position;
    END;
    CLOSE delete_cursor;
    DEALLOCATE delete_cursor;


    DECLARE insert_cursor CURSOR FOR
    SELECT t.Name, tt.NoOfRows, tt.Position
    FROM Tests t
    INNER JOIN TestTables tt ON t.TestID = tt.TestID
    WHERE tt.TestID = 1;

    OPEN insert_cursor;
    FETCH NEXT FROM insert_cursor INTO @test, @no_of_rows, @position;

    WHILE @@FETCH_STATUS = 0
    BEGIN
        PRINT 'Calling insert with @no_of_rows=' + CAST(@no_of_rows AS VARCHAR) + ', @position=' + CAST(@position AS VARCHAR);
        EXECUTE insert_ @no_of_rows, @position;

        FETCH NEXT FROM insert_cursor INTO @test, @no_of_rows, @position;
    END;
    CLOSE insert_cursor;
    DEALLOCATE insert_cursor;

    SET @intermediate = GETDATE();

    DECLARE test_eval_cursor CURSOR FOR
    SELECT t.Name
    FROM Tests t
    INNER JOIN TestViews tv ON t.TestID = tv.TestID
    WHERE tv.TestID = 3;

    OPEN test_eval_cursor;
    FETCH NEXT FROM test_eval_cursor INTO @test;

    WHILE @@FETCH_STATUS = 0
    BEGIN
        PRINT 'Starting test: ' + @test + ' for view ' + CAST(@tableID AS VARCHAR);
        EXECUTE evaluate_ @tableID;

        FETCH NEXT FROM test_eval_cursor INTO @test;
    END;
    CLOSE test_eval_cursor;
    DEALLOCATE test_eval_cursor;

    SET @end = GETDATE();

    INSERT INTO TestRuns(Description, StartAt, EndAt)
    VALUES ('Modified table: ' + CAST(@tableID AS VARCHAR) + ' + eval view ' + CAST(@tableID AS VARCHAR), @start, @end);

    SET @testID = (SELECT MAX(TestRunID) FROM TestRuns);

    INSERT INTO TestRunTables(TestRunID, TableID, StartAt, EndAt)
    VALUES (@testID, @tableID, @start, @intermediate);

    INSERT INTO TestRunViews(TestRunID, ViewID, StartAt, EndAt)
    VALUES (@testID, @tableID, @intermediate, @end);
END;


EXEC TestAll 3

SELECT * FROM TestRunViews
SELECT * FROM TestRuns
SELECT * FROM TestRunTables