USE MagazineCosmetice
GO


CREATE TABLE DeadlockLog (
    Id INT IDENTITY PRIMARY KEY,
    ProcedureName NVARCHAR(100),
    Timestamp DATETIME DEFAULT GETDATE(),
    Message NVARCHAR(255)
);

select * from Produse
-- Update Transactions
DELETE FROM Produse
WHERE Pid > 260;

-- Dirty Reads
BEGIN TRAN;
UPDATE Produse
SET Denumire = 'Dirty' + CONVERT(VARCHAR(3), ABS(CHECKSUM(NEWID()) % 300) + 1)
WHERE Pid = (SELECT MAX(Pid) FROM Produse);
WAITFOR DELAY '00:00:05';
ROLLBACK TRAN;

-- Unrepeatable Reads
BEGIN TRAN;
WAITFOR DELAY '00:00:05';
UPDATE Produse
SET Denumire = 'Unrepeatable' + CONVERT(VARCHAR(3), ABS(CHECKSUM(NEWID()) % 300) + 1)
WHERE Pid = (SELECT MAX(Pid) FROM Produse);
COMMIT TRAN;

-- Phantom Reads 
DELETE FROM Produse WHERE Pid = (SELECT MAX(Pid) FROM Produse);
SELECT * FROM Produse;

BEGIN TRAN;
WAITFOR DELAY '00:00:05';
INSERT INTO Produse(Denumire) VALUES ('Phantom404');
COMMIT TRAN;

-- Deadlock 
GO
CREATE OR ALTER PROC deadlock_transaction AS
BEGIN
    BEGIN TRY
        BEGIN TRAN;

        UPDATE Produse
        SET Denumire = 'Deadlock' + CONVERT(VARCHAR(3), ABS(CHECKSUM(NEWID()) % 300) + 1)
        WHERE Pid = (SELECT MAX(Pid) FROM Produse);

        INSERT INTO DeadlockLog (ProcedureName, Message)
        VALUES ('deadlock_transaction', 'Updated Produse');

        WAITFOR DELAY '00:00:05';

        UPDATE Categorii
        SET NumeCategorie = 'Deadlock' + CONVERT(VARCHAR(3), ABS(CHECKSUM(NEWID()) % 300) + 1)
        WHERE Cid = (SELECT MAX(Cid) FROM Categorii);

        INSERT INTO DeadlockLog (ProcedureName, Message)
        VALUES ('deadlock_transaction', 'Updated Categorii');

        COMMIT TRAN;
    END TRY
    BEGIN CATCH
        ROLLBACK TRAN;
        INSERT INTO DeadlockLog (ProcedureName, Message)
        VALUES ('deadlock_transaction', 'Transaction failed: ' + ERROR_MESSAGE());
    END CATCH
END;
GO

EXEC deadlock_transaction;

SELECT * FROM DeadlockLog ORDER BY Timestamp DESC;
