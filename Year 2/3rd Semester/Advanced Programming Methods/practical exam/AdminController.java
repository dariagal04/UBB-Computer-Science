package src.ubb.galdaria_practic;

import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.Button;
import javafx.scene.control.TextField;
import javafx.scene.control.DatePicker;
import javafx.scene.control.Spinner;
import javafx.scene.control.SpinnerValueFactory;
import javafx.stage.Stage;
import src.ubb.galdaria_practic.domain.Show;
import src.ubb.galdaria_practic.service.SeatReservationService;
import src.ubb.galdaria_practic.service.ShowService;
import src.ubb.galdaria_practic.service.UserService;

import java.io.IOException;
import java.time.LocalDateTime;
import java.time.LocalTime;

public class AdminController {


    @FXML
    private TextField nameField;

    @FXML
    private TextField durationSpinner;

    @FXML
    private DatePicker startDatePicker;

    @FXML
    private TextField numberOfSeatsField;

    @FXML
    private TextField idShowField;

    @FXML
    private Button addShowButton;

    @FXML
    private Button addLoginButton;

    SeatReservationService seatReservationService;
    ShowService showService;
    UserService userService;

    public void setServices(SeatReservationService seatReservationService, ShowService showService, UserService userService) {
        this.seatReservationService = seatReservationService;
        this.showService = showService;
        this.userService = userService;
    }

    @FXML
    private void handleAddShow() {
        try {
            int idShow = Integer.parseInt(idShowField.getText());
            String name = nameField.getText();
            int duration = Integer.parseInt(durationSpinner.getText());
            LocalDateTime startDate = startDatePicker.getValue().atTime(LocalTime.of(19, 0)); // Implicit ora 19:00
            int numberOfSeats = Integer.parseInt(numberOfSeatsField.getText());

            if (name.isEmpty() || numberOfSeats <= 0) {
                throw new IllegalArgumentException("Toate câmpurile trebuie completate corect.");
            }

            // Verificăm suprapunerea spectacolelor
            if (showService.isOverlapping(startDate, duration)) {
                showError("Eroare: Spectacolul se suprapune cu alt spectacol deja existent.");
                return;
            }

            // Creăm și salvăm spectacolul cu ID automat
            Show newShow = new Show(idShow, name, duration, startDate, numberOfSeats, LocalDateTime.now());
            showService.save(newShow);

            showSuccess("Spectacol adăugat cu succes!");

            // Curăță câmpurile
            idShowField.clear();
            nameField.clear();
            startDatePicker.setValue(null);
            numberOfSeatsField.clear();

        } catch (Exception e) {
            showError("Eroare: " + e.getMessage());
        }
    }


    private void showSuccess(String message) {
        Alert alert = new Alert(Alert.AlertType.INFORMATION);
        alert.setTitle("Succes");
        alert.setContentText(message);
        alert.showAndWait();
    }

    private void showError(String message) {
        Alert alert = new Alert(Alert.AlertType.ERROR);
        alert.setTitle("Eroare");
        alert.setContentText(message);
        alert.showAndWait();
    }
    @FXML
    private void handleOpenLogin() {
        try {
            // Încarcă fișierul FXML pentru LoginController
            FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource("login.fxml"));
            Parent loginRoot = fxmlLoader.load();

            // Creează o nouă scenă pentru LoginController
            Scene loginScene = new Scene(loginRoot, 320, 240);

            // Obține controller-ul LoginController
            LoginController loginController = fxmlLoader.getController();
            loginController.setServices(seatReservationService, showService, userService);

            // Setează scena principală a aplicației
            Stage stage = (Stage) addLoginButton.getScene().getWindow();
            stage.setScene(loginScene);
            stage.setTitle("Login");
            stage.show();
        } catch (IOException e) {
            e.printStackTrace();
            showError("Eroare la încărcarea LoginController: " + e.getMessage());
        }
    }

}
