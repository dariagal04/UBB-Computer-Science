package src.ubb.javafxlab;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.TextField;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.stage.Stage;
import src.ubb.javafxlab.domain.Utilizator;
import src.ubb.javafxlab.networks.Network;
import src.ubb.javafxlab.utils.paging.Page;

import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

public class UsersController {

    private Network network;
    private Stage stage;
    private ObservableList<Utilizator> model = FXCollections.observableArrayList();

    private int currentPage = 0;
    private final int pageSize = 5;

    @FXML
    TableView<Utilizator> table;

    @FXML
    TableColumn<Utilizator, Long> tableUserId;

    @FXML
    TableColumn<Utilizator, String> tableUserFirstName;

    @FXML
    TableColumn<Utilizator, String> tableUserLastName;

    @FXML
    TableColumn<Utilizator, String> tableUserUsername;

    @FXML
    public void initialize() {
        tableUserId.setCellValueFactory(new PropertyValueFactory<>("id"));
        tableUserFirstName.setCellValueFactory(new PropertyValueFactory<>("firstName"));
        tableUserLastName.setCellValueFactory(new PropertyValueFactory<>("lastName"));
        tableUserUsername.setCellValueFactory(new PropertyValueFactory<>("userName"));
        table.setItems(model);
    }

    @FXML
    private void initModel(int pageNumber, int pageSize) {
        Page<Utilizator> userPage = network.getPaginatedUtilizatori(pageNumber, pageSize);

        List<Utilizator> usersOnPage = StreamSupport
                .stream(userPage.getElementsOnPage().spliterator(), false)
                .collect(Collectors.toList());

        model.setAll(usersOnPage);
    }


    public void setService(Network network, Stage stage) {
        this.network = network;
        this.stage = stage;
        initModel(0, pageSize); // Load the first page
    }

    @FXML
    public void handleClose(ActionEvent actionEvent) {
        stage.close();
    }

    @FXML
    public void handleNextPage(ActionEvent actionEvent) {
        currentPage++;
        initModel(currentPage, pageSize);
    }

    @FXML
    public void handlePreviousPage(ActionEvent actionEvent) {
        if (currentPage > 0) {
            currentPage--;
            initModel(currentPage, pageSize);
        }
    }
}
