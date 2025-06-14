USE MagazineCosmetice;
GO


CREATE TABLE DeadlockLog (
    Id INT IDENTITY PRIMARY KEY,
    ProcedureName NVARCHAR(100),
    Timestamp DATETIME DEFAULT GETDATE(),
    Message NVARCHAR(255)
);


-- Read Transactions 

-- Dirty Reads 
SET TRANSACTION ISOLATION LEVEL READ UNCOMMITTED -- dirty reads
-- SET TRANSACTION ISOLATION LEVEL READ COMMITED -- dirty reads solution
BEGIN TRAN;
SELECT * FROM Produse WHERE Pid= (SELECT MAX(Pid) FROM Produse);
WAITFOR DELAY '00:00:05';
SELECT * FROM Produse WHERE Pid= (SELECT MAX(Pid) FROM Produse);
COMMIT TRAN;

-- Unrepeatable Reads
SET TRANSACTION ISOLATION LEVEL READ COMMITTED -- unrepeatable reads
-- SET TRANSACTION ISOLATION LEVEL REPEATABLE READ -- unrepeatable reads solution
BEGIN TRAN;
SELECT * FROM Produse WHERE Pid= (SELECT MAX(Pid) FROM Produse);
WAITFOR DELAY '00:00:05';
SELECT * FROM Produse WHERE Pid= (SELECT MAX(Pid) FROM Produse);
COMMIT TRAN;

-- Phantom Reads 
SET TRANSACTION ISOLATION LEVEL REPEATABLE READ -- phantom reads
-- SET TRANSACTION ISOLATION LEVEL SERIALIZABLE -- phantom reads solutions
BEGIN TRAN;
SELECT * FROM Produse WHERE Pid= (SELECT MAX(Pid) FROM Produse);
WAITFOR DELAY '00:00:05';
SELECT * FROM Produse WHERE Pid= (SELECT MAX(Pid) FROM Produse);
COMMIT TRAN;

-- Deadlock 
GO
CREATE OR ALTER PROC deadlock_transaction2 AS
BEGIN
    SET DEADLOCK_PRIORITY NORMAL;

    BEGIN TRY
        BEGIN TRAN;

        UPDATE Categorii
        SET NumeCategorie= 'Deadlock' + CONVERT(VARCHAR(3), ABS(CHECKSUM(NEWID()) % 300) + 1)
        WHERE Cid = (SELECT MAX(Cid) FROM Categorii);

        INSERT INTO DeadlockLog (ProcedureName, Message)
        VALUES ('deadlock_transaction2', 'Updated Categorii');

        WAITFOR DELAY '00:00:05';

        UPDATE Produse
        SET Denumire = 'Deadlock' + CONVERT(VARCHAR(3), ABS(CHECKSUM(NEWID()) % 300) + 1)
        WHERE Pid = (SELECT MAX(Pid) FROM Produse);

        INSERT INTO DeadlockLog (ProcedureName, Message)
        VALUES ('deadlock_transaction2', 'Updated Produse');

        COMMIT TRAN;
    END TRY
    BEGIN CATCH
        ROLLBACK TRAN;
        INSERT INTO DeadlockLog (ProcedureName, Message)
        VALUES ('deadlock_transaction2', 'Transaction failed: ' + ERROR_MESSAGE());
    END CATCH
END;
GO
EXEC deadlock_transaction2;

SELECT * FROM Produse WHERE Pid= (SELECT MAX(Pid) FROM Produse);
SELECT * FROM Categorii WHERE Cid= (SELECT MAX(Cid) FROM Categorii);


SELECT * FROM DeadlockLog ORDER BY Timestamp DESC;
