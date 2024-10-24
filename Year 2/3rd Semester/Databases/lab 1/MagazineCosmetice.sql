CREATE DATABASE MagazineCosmetice;
GO
USE MagazineCosmetice;
GO
CREATE TABLE Produse(
    Pid INT PRIMARY KEY IDENTITY,
    Denumire VARCHAR(50),
    Categorie VARCHAR(50),
    Pret DECIMAL(10, 2),
    NrBucati INT CHECK (NrBucati >= 0)
);

CREATE TABLE Categorii(
    Cid INT PRIMARY KEY IDENTITY,
    NumeCategorie VARCHAR(50)
);

CREATE TABLE Branduri(
    Bid INT PRIMARY KEY IDENTITY,
    NumeBrand VARCHAR(50)
);

CREATE TABLE Magazine(
    Mid INT PRIMARY KEY IDENTITY,
    NumeMagazin VARCHAR(50),
    NumarAngajati INT
);

-- Tabel Angajati (relație 1:m Magazine si Angajati)
CREATE TABLE Angajati(
    Aid INT PRIMARY KEY IDENTITY,
    NumeAngajat VARCHAR(50),
    Functie VARCHAR(50),
    MagazinID INT FOREIGN KEY REFERENCES Magazine(Mid)
);

CREATE TABLE Clienti(
    ClientID INT PRIMARY KEY IDENTITY,
    NumeClient VARCHAR(50),
    Email VARCHAR(50),
    Telefon VARCHAR(20)
);

CREATE TABLE Comenzi(
    ComandaID INT PRIMARY KEY IDENTITY,
    ClientID INT FOREIGN KEY REFERENCES Clienti(ClientID),
    Mid INT FOREIGN KEY REFERENCES Magazine(Mid),
    SumaTotala DECIMAL(10, 2)
);

CREATE TABLE ArticoleComanda(
    ArticolComandaID INT PRIMARY KEY IDENTITY,
    ComandaID INT FOREIGN KEY REFERENCES Comenzi(ComandaID),
    Pid INT FOREIGN KEY REFERENCES Produse(Pid),
    Cantitate INT CHECK (Cantitate > 0),
    Pret DECIMAL(10, 2)
);

CREATE TABLE ProduseBranduri(
    Pid INT FOREIGN KEY REFERENCES Produse(Pid),
    Bid INT FOREIGN KEY REFERENCES Branduri(Bid),
    CONSTRAINT pk_ProduseBranduri PRIMARY KEY (Pid, Bid)
);

-- Tabel Recenzii
CREATE TABLE Recenzii(
    RecenzieID INT PRIMARY KEY IDENTITY,
    Pid INT FOREIGN KEY REFERENCES Produse(Pid),
    Rating INT CHECK (Rating BETWEEN 1 AND 5),
    Comentariu VARCHAR(255),
    DataRecenzie DATE
);

-- Tabel ProduseCategorii (relație m:n Produse si Categorii)
CREATE TABLE ProduseCategorii(
    Pid INT FOREIGN KEY REFERENCES Produse(Pid),
    Cid INT FOREIGN KEY REFERENCES Categorii(Cid),
    CONSTRAINT pk_ProduseCategorii PRIMARY KEY (Pid, Cid)
);
