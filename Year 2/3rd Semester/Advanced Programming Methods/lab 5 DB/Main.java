package src.ubb;

import src.ubb.domain.Prietenie;
import src.ubb.networks.Network;
import src.ubb.UI.Consola;
import src.ubb.domain.Utilizator;
import src.ubb.domain.validators.PrietenieValidator;
import src.ubb.domain.validators.UtilizatorValidator;
import src.ubb.repository.database.FriendshipRepoDB;
import src.ubb.repository.database.UserRepoDB;
import java.sql.SQLException;

// Press Shift twice to open the Search Everywhere dialog and type `show whitespaces`,
// then press Enter. You can now see whitespace characters in your code.
public class Main {
    public static void main(String[] args) throws SQLException {

        //InMemoryRepository<Long, Utilizator> repo =  new InMemoryRepository<>(new UtilizatorValidator());
        //InMemoryRepository<Long, Prietenie> prietenieRepository = new InMemoryRepository<>(new PrietenieValidator(repo));
        UserRepoDB userRepoDB = new UserRepoDB(new UtilizatorValidator());
        FriendshipRepoDB friendshipRepoDB = new FriendshipRepoDB(new PrietenieValidator(userRepoDB));
        Network network = new Network(userRepoDB, friendshipRepoDB);
        Consola ui = new Consola(network);

        Utilizator u1 = new Utilizator("IONUT", "a");
        u1.setId(1L);
        Utilizator u2 = new Utilizator("Mihai", "b");
        u2.setId(2L);
        Prietenie p = new Prietenie(u1.getId(), u2.getId());

//        Utilizator u3 = new Utilizator("Andreea", "c");
//        Utilizator u4 = new Utilizator("Paula", "d");
//        Utilizator u5 = new Utilizator("Mike", "e");
//        Utilizator u6 = new Utilizator("Andrei", "f");
//
        //network.addUtilizator(u1);
        //network.addUtilizator(u2);

//        network.removeUtilizator(u1.getId());
//        network.addUtilizator(u2);
//        network.addUtilizator(u3);
//        network.addUtilizator(u4);
//        network.addUtilizator(u5);
//        network.addUtilizator(u6);
//        u3.setId(3L);
//        u4.setId(4L);
//        u5.setId(5L);
//        u6.setId(6L);
//        u1.setId(1L);
//        u2.setId(2L);
//        try {
//            repoFile.save(u1);
//            repoFile.save(u2);
//            repoFile.save(u3);
//            repoFile.save(u4);
//            repoFile.save(u5);
//            repoFile.save(u6);
//        }catch(IllegalArgumentException | ValidationException e)
//        {
//            System.out.println(e.getMessage());
//        }
//        System.out.println();



        ui.run();

    }
}