USE MagazineCosmetice
GO

DROP TABLE IF EXISTS Versiune;
CREATE TABLE Versiune(
      numar INT
)

INSERT INTO Versiune(numar) VALUES (0);

SELECT * FROM Versiune

CREATE PROCEDURE do_proc_1 AS
BEGIN
	ALTER TABLE Produse
	ALTER COLUMN Denumire VARCHAR(100);
	PRINT 'S-A MODIFICAT COLOANA [DENUMIRE] DIN TABELUL [PRODUSE]';
END;
GO

CREATE PROCEDURE undo_proc_1 AS
BEGIN
	ALTER TABLE Produse
	ALTER COLUMN Denumire VARCHAR(50);
	PRINT 'S-A MODIFICAT COLOANA [DENUMIRE] DIN TABELUL [PRODUSE]';
END;
GO





CREATE PROCEDURE do_proc_2 AS
BEGIN
	ALTER TABLE Produse
	ADD CONSTRAINT pret_default DEFAULT 0 FOR Pret;
	PRINT 'S-A ADAUGAT CONSTRAINT PENTRU [PRET] DIN [PRODUSE]';
END;
GO

CREATE PROCEDURE undo_proc_2 AS
BEGIN 
	ALTER TABLE Produse
	DROP CONSTRAINT pret_default;
	PRINT 'S-A STERS CONSTRAINT PENTRU [PRET] DIN [PRODUSE]';
END;
GO





CREATE PROCEDURE do_proc_3 AS
BEGIN
	CREATE TABLE ComenziFinalizate(
		Cid INT NOT NULL PRIMARY KEY,
		Finalizat INT NOT NULL);
		PRINT 'S-A CREAT TABELUL NOU [COMENZI FINALIZATE]';
END;
GO

CREATE PROCEDURE undo_proc_3 AS
BEGIN
	DROP TABLE ComenziFinalizate;
	PRINT 'S-A STERS TABELUL NOU [COMENZI FINALIZATE';
END;
GO





CREATE PROCEDURE do_proc_4 AS
BEGIN
	ALTER TABLE ComenziFinalizate
	ADD Data_comanda DATE;
	PRINT 'S-A ADAUGAT CAMPUL NOU [DATA_COMANDA] IN [COMENZIFINALIZATE]';
END;
GO

CREATE PROCEDURE undo_proc_4 AS
BEGIN
	ALTER TABLE ComenziFinalizate
	DROP COLUMN Data_comanda
	PRINT 'S-A STERS CAMPUL NOU [DATA_COMANDA] DIN [COMENZIFINALIZATE]';
END;
GO




CREATE PROCEDURE do_proc_5 AS
BEGIN
	ALTER TABLE ComenziFinalizate
	ADD CONSTRAINT CFid FOREIGN KEY (Cid) REFERENCES Comenzi(ComandaID);
	PRINT 'S-A ADAUGAT CHEIE STRAINA IN [COMENZIFINALIZATE]';
END;
GO

CREATE PROCEDURE undo_proc_5 AS
BEGIN
	ALTER TABLE ComenziFinalizate
	DROP CONSTRAINT CFid;
	PRINT 'S-A STERS CHEIE STRAINA DIN [COMENZIFINALIZATE]';
END;
GO

CREATE OR ALTER PROCEDURE main (@versiune INT)
AS
BEGIN
    -- Verifica daca versiunea este valida
    IF @versiune < 0 OR @versiune > 5
    BEGIN
        PRINT 'Versiunea este invalida!';
        RETURN;
    END;

    -- Obtine versiunea curenta din tabelul Versiune
    DECLARE @versiune_curenta AS INT;
    SET @versiune_curenta = (SELECT numar FROM Versiune);

    -- Daca versiunea dorita este deja curenta
    IF @versiune = @versiune_curenta
    BEGIN
        PRINT 'Versiunea actuala este deja cea curenta!';
        RETURN;
    END;

    -- Declaratiile pentru executarea procedurilor
    DECLARE @proc VARCHAR(20);
    DECLARE @proc_undo VARCHAR(20);
    DECLARE @ok AS INT;
    SET @ok = 0;

    -- Actualizeaza versiunea curenta
    DELETE FROM Versiune;
    INSERT INTO Versiune (numar) VALUES (@versiune);

    -- Create versiunea curenta pana la versiunea dorita
    WHILE (@versiune_curenta < @versiune)
    BEGIN
        SET @ok = @ok + 1;
        SET @versiune_curenta = @versiune_curenta + 1;
        SET @proc = 'do_proc_' + CAST(@versiune_curenta AS VARCHAR(10));
        PRINT 'Se executa ' + @proc;
        EXEC @proc;
    END;

    -- Daca versiunea a fost modificata, opreste executia
    IF (@ok > 0)
    BEGIN
        RETURN;
    END;

    -- Daca versiunea trebuie sa scada, executa procedurile inverse
    WHILE (@versiune_curenta > @versiune)
    BEGIN
        SET @proc_undo = 'undo_proc_' + CAST(@versiune_curenta AS VARCHAR(10));
        PRINT 'Se executa ' + @proc_undo;
        EXEC @proc_undo;
        SET @versiune_curenta = @versiune_curenta - 1;
    END;
END;
GO


--do_proc_1
--undo_proc_1
--do_proc_2
exec main 0
exec main 1
exec main 2
exec main 3
exec main 4
exec main 5
exec main 10
SELECT * FROM Versiune

