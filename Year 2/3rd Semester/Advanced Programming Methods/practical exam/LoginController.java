package src.ubb.galdaria_practic;

import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.TextField;
import javafx.stage.Stage;
import javafx.scene.Scene;
import javafx.fxml.FXMLLoader;
import src.ubb.galdaria_practic.domain.User;
import src.ubb.galdaria_practic.service.UserService;
import src.ubb.galdaria_practic.service.SeatReservationService;
import src.ubb.galdaria_practic.service.ShowService;

import java.io.IOException;

public class LoginController {

    @FXML
    private TextField nameTextField;  // TextField pentru numele utilizatorului

    @FXML
    private Button loginButton;  // Butonul pentru Login

    private SeatReservationService seatReservationService;  // Serviciul care interacționează cu repo-ul pentru Client
    private UserService userService;
    private ShowService showService;

    // Setează serviciile necesare pentru acest controller
    public void setServices(SeatReservationService seatReservationService, ShowService showService, UserService userService) {
        this.seatReservationService = seatReservationService;
        this.showService = showService;
        this.userService = userService;
    }

    // Handler-ul pentru butonul Login
    @FXML
    public void onLoginButtonClick() throws IOException {
        String name = nameTextField.getText();  // Obține numele din TextField

        if (name == null || name.isEmpty()) {
            // Afișează un mesaj de eroare dacă nu s-a introdus un nume
            System.out.println("Please enter a valid name.");
            return;
        }

        // Căutăm clientul cu numele dat
        User client = userService.findAll().stream()
                .filter(c -> c.getName().equals(name))
                .findFirst()
                .orElse(null);

        if (client == null) {
            // Dacă clientul nu există, afișează un mesaj
            System.out.println("Client not found!");
            return;
        }

        // Dacă clientul există, deschide o fereastră nouă
        FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource("user.fxml"));  // Schimbă fișierul FXML la cel corespunzător
        Scene scene = new Scene(fxmlLoader.load());
        UserController ctr1 = fxmlLoader.getController();
        ctr1.setServiceClient(client, seatReservationService, showService);

        Stage stage = new Stage();
        stage.setTitle(client.getName());
        stage.setScene(scene);
        stage.show();

        // Închide fereastra curentă (de login)
        Stage currentStage = (Stage) loginButton.getScene().getWindow();
        currentStage.close();
    }


}
