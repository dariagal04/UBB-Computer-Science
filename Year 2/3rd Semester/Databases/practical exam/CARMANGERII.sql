CREATE DATABASE Carmangerii;
GO

USE Carmangerii;
GO

-- Creare tabele
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