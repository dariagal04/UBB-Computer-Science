CREATE DATABASE InghetataCofetarie;
GO


USE InghetataCofetarie;
GO


CREATE TABLE Cofetarii (
    cod VARCHAR(10) PRIMARY KEY,
    adresa VARCHAR(255) NOT NULL,
    an_infiintare INT CHECK (an_infiintare > 1800 AND an_infiintare <= YEAR(GETDATE()))
);
GO

CREATE TABLE Inghetate (
    cod VARCHAR(10) PRIMARY KEY,                      
    nume VARCHAR(100) NOT NULL,
    ingrediente TEXT NOT NULL,
    valoare_vanzari_an_precedent DECIMAL(10,2) CHECK (valoare_vanzari_an_precedent >= 0),
    cod_cofetarie VARCHAR(10) NOT NULL,               
    FOREIGN KEY (cod_cofetarie) REFERENCES Cofetarii(cod)
);
GO

INSERT INTO Cofetarii (cod, adresa, an_infiintare) VALUES
('CF001', 'Str. Lalelelor 10', 2005),
('CF002', 'Bd. Unirii 45', 2010),
('CF003', 'Piata Libertatii 3', 2018);
GO

ALTER TABLE Cofetarii
ADD nume VARCHAR(100) NOT NULL DEFAULT 'Nedefinit';

UPDATE Cofetarii SET nume = 'Cofetaria Lalelelor' WHERE cod = 'CF001';
UPDATE Cofetarii SET nume = 'Cofetaria Unirii' WHERE cod = 'CF002';
UPDATE Cofetarii SET nume = 'Cofetaria Libertatii' WHERE cod = 'CF003';


INSERT INTO Inghetate (cod, nume, ingrediente, valoare_vanzari_an_precedent, cod_cofetarie) VALUES
('IG001', 'Gelato Ciocolato', 'lapte, zahăr, cacao, smântână', 10500.75, 'CF001'),
('IG002', 'Vanilla Dream', 'lapte, vanilie naturală, zahăr', 8700.00, 'CF001'),
('IG003', 'Tropical Mix', 'ananas, mango, banană, lapte de cocos', 6700.50, 'CF002'),
('IG004', 'Pistachio Deluxe', 'lapte, fistic, smântână, zahăr', 9500.00, 'CF002'),
('IG005', 'Forest Berry', 'afine, zmeură, căpșuni, frișcă', 7450.30, 'CF003');
GO


CREATE TABLE Vanzari
(
    CodVanzare INT IDENTITY(1,1) PRIMARY KEY,     
    CodCofetarie VARCHAR(10) NOT NULL,            
    DataVanzare DATE NOT NULL,                      
    Suma DECIMAL(18, 2) NOT NULL                    
);

ALTER TABLE Vanzari
ADD CONSTRAINT FK_Vanzari_Cofetarii
FOREIGN KEY (CodCofetarie) REFERENCES Cofetarii(cod);



INSERT INTO Vanzari (CodCofetarie, DataVanzare, Suma) VALUES
('CF001', '2021-03-15', 25000),
('CF001', '2022-07-20', 30000),
('CF001', '2023-11-10', 35000),
('CF001', '2024-05-25', 40000),
('CF001', '2025-01-15', 50000),

('CF002', '2021-02-10', 12000),
('CF002', '2022-06-30', 15000),
('CF002', '2023-10-05', 13000),
('CF002', '2024-04-12', 11000),
('CF002', '2025-02-18', 14000),

('CF003', '2021-01-20', 80000),
('CF003', '2022-08-15', 85000),
('CF003', '2023-09-10', 90000),
('CF003', '2024-03-20', 95000),
('CF003', '2025-01-05', 100000);


INSERT INTO Vanzari (CodCofetarie, DataVanzare, Suma) VALUES
('CF003', '2025-01-06', 10000000000);




--codul cofetariilor pentru care media vanzarilor din ultimii 5 ani depaseste 100.000
SELECT c.cod
FROM Cofetarii c
JOIN Vanzari v ON c.cod = v.CodCofetarie
WHERE v.DataVanzare >= DATEADD(YEAR, -5, GETDATE())
GROUP BY c.cod
HAVING AVG(v.Suma) > 100000;


--numele cofetariilor care nu au inghetata de valinie dar au de ciocolata
SELECT DISTINCT c.nume
FROM Cofetarii c
JOIN Inghetate i ON c.cod = i.cod_cofetarie
WHERE i.nume = 'Ciocolata'
AND c.nume NOT IN (
    SELECT cod_cofetarie
    FROM Inghetate
    WHERE nume = 'Vanilie'
);



CREATE NONCLUSTERED INDEX idx_vanzari_cod_data ON Vanzari (CodCofetarie, DataVanzare);
