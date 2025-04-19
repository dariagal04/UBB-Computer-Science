package src.ubb.galdaria_practic;

import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.layout.VBox;
import src.ubb.galdaria_practic.domain.SeatReservation;
import src.ubb.galdaria_practic.domain.Show;
import src.ubb.galdaria_practic.domain.User;
import src.ubb.galdaria_practic.service.SeatReservationService;
import src.ubb.galdaria_practic.service.ShowService;

import java.util.List;

public class UserController {

    @FXML
    private Label emailLabel; // Eticheta pentru email-ul utilizatorului

    @FXML
    private TableView<Show> showsTable; // Tabelul pentru afișarea spectacolelor

    @FXML
    private TableColumn<Show, String> showNameColumn; // Coloana pentru numele spectacolului

    @FXML
    private TableColumn<Show, String> showDateColumn; // Coloana pentru data spectacolului

    @FXML
    private Button reserveSeatButton; // Butonul pentru rezervare locuri

    @FXML
    private VBox messageBox; // Container pentru mesajul de avertizare

    private User user;
    private SeatReservationService seatReservationService;
    private ShowService showService;

    // Setează serviciile și utilizatorul pentru acest controller
    public void setServiceClient(User user, SeatReservationService seatReservationService, ShowService showService) {
        this.user = user;
        this.seatReservationService = seatReservationService;
        this.showService = showService;
        initialize();
    }

    // Inițializează controller-ul
    private void initialize() {
        // Setează email-ul utilizatorului
        emailLabel.setText(user.getEmail());

        // Configurează coloanele tabelului
        showNameColumn.setCellValueFactory(new PropertyValueFactory<>("name"));
        showDateColumn.setCellValueFactory(new PropertyValueFactory<>("date"));

        // Populează tabelul cu spectacolele ordonate după dată
        List<Show> shows = showService.findAll();
        shows.sort((s1, s2) -> s1.getDate().compareTo(s2.getDate()));
        showsTable.getItems().addAll(shows);

        // Configurează butonul de rezervare
        reserveSeatButton.setOnAction(event -> handleReservation());
    }

    // Handler pentru rezervarea unui loc la spectacolul selectat
    private void handleReservation() {
        Show selectedShow = showsTable.getSelectionModel().getSelectedItem();
        if (selectedShow == null) {
            showMessage("Please select a show to reserve a seat.");
            return;
        }

        // Verifică dacă utilizatorul a rezervat deja locul
        boolean isReserved = seatReservationService.findAll().stream()
                .anyMatch(reservation -> reservation.getUserEmail().equals(user.getEmail()) && reservation.getShowId() == selectedShow.getId());

        if (isReserved) {
            showMessage("You have already reserved a seat for this show.");
        } else {
            // Rezervă locul și adaugă o rezervare
            SeatReservation reservation = new SeatReservation(user.getEmail(), selectedShow.getId());
            seatReservationService.save(reservation);
            showMessage("Your seat has been successfully reserved.");
        }
    }

    // Afișează mesajul de avertizare
    private void showMessage(String message) {
        messageBox.getChildren().clear();
        Label messageLabel = new Label(message);
        messageBox.getChildren().add(messageLabel);
    }
}
