USE Carmangerii

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
