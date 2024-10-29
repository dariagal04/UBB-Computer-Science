package org.example;

import org.example.Retea.Network;
import org.example.UI.Consola;
import org.example.domain.Prietenie;
import org.example.domain.Utilizator;
//import data.*;
import org.example.domain.validators.PrietenieValidator;
import org.example.domain.validators.UtilizatorValidator;
import org.example.domain.validators.ValidationException;
import org.example.domain.validators.Validator;
import org.example.repository.Repository;
import org.example.repository.file.UtilizatorRepository;
import org.example.repository.memory.InMemoryRepository;

// Press Shift twice to open the Search Everywhere dialog and type `show whitespaces`,
// then press Enter. You can now see whitespace characters in your code.
public class Main {
    public static void main(String[] args) {

        InMemoryRepository<Long, Utilizator> repo =  new InMemoryRepository<>(new UtilizatorValidator());
        Repository<Long, Utilizator> repoFile = (Repository<Long, Utilizator>) new UtilizatorRepository(new UtilizatorValidator(), "C:\\Users\\user\\AppData\\Roaming\\JetBrains\\IntelliJIdea2024.2\\extensions\\com.intellij.database\\data\\utilizatori.txt");
        InMemoryRepository<Long, Prietenie> prietenieRepository = new InMemoryRepository<>(new PrietenieValidator(repo));
        Network network = new Network(repo, prietenieRepository);
        Consola ui = new Consola(network);

        Utilizator u1 = new Utilizator("IONUT", "a");
        Utilizator u2 = new Utilizator("Mihai", "b");
        Utilizator u3 = new Utilizator("Andreea", "c");
        Utilizator u4 = new Utilizator("Paula", "d");
        Utilizator u5 = new Utilizator("Mike", "e");
        Utilizator u6 = new Utilizator("Andrei", "f");

        network.addUtilizator(u1);
        network.addUtilizator(u2);
        network.addUtilizator(u3);
        network.addUtilizator(u4);
        network.addUtilizator(u5);
        network.addUtilizator(u6);

        u3.setId(3L);
        u4.setId(4L);
        u5.setId(5L);
        u6.setId(6L);
        u1.setId(1L);
        u2.setId(2L);
        try {
            repoFile.save(u1);
            repoFile.save(u2);
            repoFile.save(u3);
            repoFile.save(u4);
            repoFile.save(u5);
            repoFile.save(u6);
        }catch(IllegalArgumentException | ValidationException e)
        {
            System.out.println(e.getMessage());
        }
        System.out.println();



        ui.run();

    }
}