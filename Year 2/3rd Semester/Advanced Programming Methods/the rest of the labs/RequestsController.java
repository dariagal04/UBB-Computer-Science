package src.ubb.javafxlab;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Alert;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.stage.Stage;
import src.ubb.javafxlab.domain.CererePrietenie;
import src.ubb.javafxlab.domain.Prietenie;
import src.ubb.javafxlab.domain.UserStatus;
import src.ubb.javafxlab.domain.Utilizator;
import src.ubb.javafxlab.networks.Network;

import java.time.LocalDateTime;
import java.util.*;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

public class RequestsController {


    private Network network;
    ObservableList<UserStatus> model = FXCollections.observableArrayList();
    Stage stage;
    Optional<Utilizator> utilizator;



    @FXML
    TableView<UserStatus> tableView;

    @FXML
    TableColumn<UserStatus, Long> tableUserId;

    @FXML
    TableColumn<UserStatus, String> tableUserFirstName;

    @FXML
    TableColumn<UserStatus, String> tableUserLastName;

    @FXML
    TableColumn<UserStatus, String> tableUserName;

    @FXML
    TableColumn<UserStatus, LocalDateTime> tableSentDate;
    @FXML
    TableColumn<UserStatus, String> tableStatus;


    @FXML
    public void initialize() {

        tableUserId.setCellValueFactory(new PropertyValueFactory<UserStatus, Long>("id"));
        tableUserFirstName.setCellValueFactory(new PropertyValueFactory<UserStatus, String>("firstName"));
        tableUserLastName.setCellValueFactory(new PropertyValueFactory<UserStatus, String>("lastName"));
        tableUserName.setCellValueFactory(new PropertyValueFactory<UserStatus, String>("userName"));
        tableSentDate.setCellValueFactory(new PropertyValueFactory<UserStatus,LocalDateTime>("sentDate"));
        tableStatus.setCellValueFactory(new PropertyValueFactory<UserStatus, String>("status"));
        tableView.setItems(model);
    }

    @FXML
    private void initModel() {
        List<UserStatus> users = network.getListCereri(this.utilizator.get());
        List<UserStatus> userList = StreamSupport.stream(users.spliterator(), false).collect(Collectors.toList());
        model.setAll(userList);
    }


    public void setService(Network network, Stage stage, Optional<Utilizator> utilizator) {
        this.network = network;
        this.stage = stage;
        this.utilizator = utilizator;
        initModel();
    }


    public void acceptRequest(ActionEvent event) {
        UserStatus selectedUser = tableView.getSelectionModel().getSelectedItem();
        Utilizator loggedinUser = this.utilizator.get();
        LocalDateTime date = LocalDateTime.now();

        Prietenie prietenie = new Prietenie(loggedinUser.getId(),selectedUser.getId(),date);
        network.addPrietenie(prietenie);
        CererePrietenie cererePrietenie = network.findCerere(selectedUser.getId());
        if(!Objects.equals(cererePrietenie.getStatus(), "ACCEPTED") && !Objects.equals(cererePrietenie.getStatus(), "REJECTED")) {
            CererePrietenie copy = cererePrietenie;
            String status = "ACCEPTED";
            copy.setStatus(status);
            network.removeCerere(selectedUser.getId(), loggedinUser.getId());
            network.addCerere(copy);
            Alert alert = new Alert(Alert.AlertType.INFORMATION);
            alert.setTitle("Friend Request");
            alert.setHeaderText("Friend Request accepted");
            alert.setContentText("You are now friends with " + selectedUser.getUserName());
            alert.showAndWait();
        } else{
            Alert alert = new Alert(Alert.AlertType.ERROR);
            alert.setTitle("Friend Request");
            alert.setHeaderText("Fail");
            alert.setContentText("You can't proccess this request again");
            alert.showAndWait();
        }

    }

    public void rejectRequest(ActionEvent event) {
        UserStatus selectedUser = tableView.getSelectionModel().getSelectedItem();
        Utilizator loggedinUser = this.utilizator.get();

        CererePrietenie cererePrietenie = network.findCerere(selectedUser.getId());
        if(!Objects.equals(cererePrietenie.getStatus(), "ACCEPTED") && !Objects.equals(cererePrietenie.getStatus(), "REJECTED")) {

            CererePrietenie copy = cererePrietenie;
            String status = "REJECTED";
            copy.setStatus(status);
            network.removeCerere(selectedUser.getId(), loggedinUser.getId());
            network.addCerere(copy);
            Alert alert = new Alert(Alert.AlertType.INFORMATION);
            alert.setTitle("Friend Request");
            alert.setHeaderText("Friend Request rejected");
            alert.setContentText("You refused to be friends with " + selectedUser.getUserName());
            alert.showAndWait();
        }else{
            Alert alert = new Alert(Alert.AlertType.ERROR);
            alert.setTitle("Friend Request");
            alert.setHeaderText("Fail");
            alert.setContentText("You can't proccess this request again");
            alert.showAndWait();

        }
    }

    @FXML
    public void handleClose(ActionEvent actionEvent) {
        stage.close();
    }

}
