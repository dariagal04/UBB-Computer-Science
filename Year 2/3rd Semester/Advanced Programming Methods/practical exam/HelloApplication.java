package src.ubb.galdaria_practic;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;
import src.ubb.galdaria_practic.domain.SeatReservation;
import src.ubb.galdaria_practic.domain.Show;
import src.ubb.galdaria_practic.repository.DBRepository.SeatReservationsDbRepo;
import src.ubb.galdaria_practic.repository.DBRepository.ShowsDbRepo;
import src.ubb.galdaria_practic.repository.DBRepository.UsersDbRepo;
import src.ubb.galdaria_practic.service.SeatReservationService;
import src.ubb.galdaria_practic.service.ShowService;
import src.ubb.galdaria_practic.service.UserService;

import java.io.IOException;

public class HelloApplication extends Application {

    private SeatReservationService seatReservationService;
    private ShowService showService;
    private UserService userService;


    public void start() {
        String urlDb = "jdbc:postgresql://localhost:5432/practic";
        String usernameDb = "postgres";
        String passDb = "PgPass";

        // Creăm repo-urile
        SeatReservationsDbRepo seatReservationsDbRepo = new SeatReservationsDbRepo(urlDb, usernameDb, passDb);
        ShowsDbRepo showsDbRepo = new ShowsDbRepo(urlDb, usernameDb, passDb);
        UsersDbRepo usersDbRepo = new UsersDbRepo(urlDb, usernameDb, passDb);

        // Creăm serviciile
        seatReservationService = new SeatReservationService(seatReservationsDbRepo);
        showService = new ShowService(showsDbRepo);
        userService = new UserService(usersDbRepo);
    }
    @Override
    public void start(Stage stage) throws IOException {
        start();

        FXMLLoader fxmlLoader = new FXMLLoader(HelloApplication.class.getResource("hello-view.fxml"));
        Scene scene = new Scene(fxmlLoader.load(), 320, 240);
        AdminController ctr = fxmlLoader.getController();
        ctr.setServices(seatReservationService, showService, userService); // Setează serviciile


        stage.setTitle("Hello!");
        stage.setScene(scene);
        stage.show();
    }

    public static void main(String[] args) {
        launch();
    }
}

