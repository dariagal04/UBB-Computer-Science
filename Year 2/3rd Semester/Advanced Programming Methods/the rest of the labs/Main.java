package src.ubb.javafxlab;

import src.ubb.javafxlab.domain.Prietenie;
import src.ubb.javafxlab.networks.Network;
import src.ubb.javafxlab.UI.Consola;
import src.ubb.javafxlab.domain.Utilizator;
import src.ubb.javafxlab.domain.validators.PrietenieValidator;
import src.ubb.javafxlab.domain.validators.UtilizatorValidator;
import src.ubb.javafxlab.repository.database.FriendshipRepoDB;
import src.ubb.javafxlab.repository.database.UserRepoDB;
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
        //Consola ui = new Consola(network);
        // ui.run();


        HelloApplication.main(args);
    }
}