package src.ubb.javafxlab;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.layout.AnchorPane;
import javafx.scene.layout.VBox;
import javafx.stage.Modality;
import javafx.stage.Stage;
import src.ubb.javafxlab.domain.CererePrietenie;
import src.ubb.javafxlab.domain.Prietenie;
import src.ubb.javafxlab.domain.Utilizator;
import src.ubb.javafxlab.networks.Network;
import src.ubb.javafxlab.utils.paging.Page;
import src.ubb.javafxlab.utils.paging.Pageable;

import java.io.IOException;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;
import java.util.Objects;
import java.util.Optional;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

public class LoginController {
//
//    private Network network;
//    ObservableList<Utilizator> model = FXCollections.observableArrayList();
//    Stage stage;
//    Optional<Utilizator> utilizator;
//
//    private int currentPage = 0;
//    private final int pageSize = 1;
//
//    public void setService(Network network, Stage stage) {
//        this.network = network;
//        this.stage = stage;
//
//        initModel(0, pageSize);
//    }
//
//    @FXML
//    TableView<Utilizator> tableView;
//
//    @FXML
//    TableColumn<Utilizator, Long> tableUserId;
//
//    @FXML
//    TableColumn<Utilizator, String> tableUserFirstName;
//
//    @FXML
//    TableColumn<Utilizator, String> tableUserLastName;
//
//    @FXML
//    TableColumn<Utilizator, String> tableUserName;
//
//    @FXML
//    Label userNameLabel;
//
//    @FXML
//    private TextField textFieldUsername;
//
//
//    @FXML
//    public void initialize() {
//
//
//        tableUserId.setCellValueFactory(new PropertyValueFactory<Utilizator, Long>("id"));
//        tableUserFirstName.setCellValueFactory(new PropertyValueFactory<Utilizator, String>("firstName"));
//        tableUserLastName.setCellValueFactory(new PropertyValueFactory<Utilizator, String>("lastName"));
//        tableUserName.setCellValueFactory(new PropertyValueFactory<Utilizator, String>("userName"));
//        tableView.setItems(model);
//    }
//
//    @FXML
//    private void initModel(int pageNumber, int pageSize) {
//        if (utilizator == null || utilizator.isEmpty()) {
//            System.out.println("No user set for initModel.");
//            return;
//        }
//
//        Utilizator loggedInUser = utilizator.get();
////        Iterable<Utilizator> friends = network.getListFriends(loggedInUser);
////        List<Utilizator> userList = StreamSupport.stream(friends.spliterator(), false).collect(Collectors.toList());
////        model.setAll(userList);
//
//        Page<Utilizator> friends = network.getPaginatedFriends(loggedInUser,pageNumber, pageSize);
//
//        List<Utilizator> usersOnPage = StreamSupport
//                .stream(friends.getElementsOnPage().spliterator(), false)
//                .collect(Collectors.toList());
//
//        model.setAll(usersOnPage);
//
//    }
//
//
//    @FXML
//    public void handleNextPage(ActionEvent actionEvent) {
//        currentPage++;
//        initModel(currentPage, pageSize);
//    }
//
//    @FXML
//    public void handlePreviousPage(ActionEvent actionEvent) {
//        if (currentPage > 0) {
//            currentPage--;
//            initModel(currentPage, pageSize);
//        }
//    }


    private Network network;
    ObservableList<Utilizator> model = FXCollections.observableArrayList();
    Stage stage;
    Optional<Utilizator> utilizator;

    private int currentPage = 0;
    private final int pageSize = 1;  // You can adjust the page size as needed
    private int totalElements = 0;  // To keep track of the total number of elements

    @FXML
    TableView<Utilizator> tableView;

    @FXML
    TableColumn<Utilizator, Long> tableUserId;

    @FXML
    TableColumn<Utilizator, String> tableUserFirstName;

    @FXML
    TableColumn<Utilizator, String> tableUserLastName;

    @FXML
    TableColumn<Utilizator, String> tableUserName;

    @FXML
    Label userNameLabel;

    @FXML
    private TextField textFieldUsername;


    public void setService(Network network, Stage stage) {
        this.network = network;
        this.stage = stage;
        initModel(currentPage, pageSize);  // Initialize the first page
    }

    @FXML
    public void initialize() {
        tableUserId.setCellValueFactory(new PropertyValueFactory<Utilizator, Long>("id"));
        tableUserFirstName.setCellValueFactory(new PropertyValueFactory<Utilizator, String>("firstName"));
        tableUserLastName.setCellValueFactory(new PropertyValueFactory<Utilizator, String>("lastName"));
        tableUserName.setCellValueFactory(new PropertyValueFactory<Utilizator, String>("userName"));
        tableView.setItems(model);
    }

    @FXML
    private void initModel(int pageNumber, int pageSize) {
        if (utilizator == null || utilizator.isEmpty()) {
            System.out.println("No user set for initModel.");
            return;
        }

        Utilizator loggedInUser = utilizator.get();
        Page<Utilizator> friendsPage = network.getListFriends(loggedInUser.getId(),new Pageable(pageNumber,pageSize));

        List<Utilizator> usersOnPage = StreamSupport
                .stream(friendsPage.getElementsOnPage().spliterator(), false)
                .collect(Collectors.toList());

        model.setAll(usersOnPage);
        totalElements = friendsPage.getTotalNumberOfElements();

    }

    @FXML
    public void handleNextPage(ActionEvent actionEvent) {
        if ((currentPage + 1) * pageSize < totalElements) {
            currentPage++;
            initModel(currentPage, pageSize);
        }
    }

    @FXML
    public void handlePreviousPage(ActionEvent actionEvent) {
        if (currentPage > 0) {
            currentPage--;
            initModel(currentPage, pageSize);
        }
    }





    public void setUser(Optional<Utilizator> user) {
        this.utilizator = user;

        if (user != null) {
            Utilizator loggedInUser = this.utilizator.get();

            System.out.println("Logged in user: " + loggedInUser.getUserName());

            userNameLabel.setText(loggedInUser.getFirstName() + " " + loggedInUser.getLastName());

            List<Utilizator> friends = network.getListFriends(loggedInUser);

            Iterable<CererePrietenie> cereri =  network.getCereriPrietenie();
            for(CererePrietenie c : cereri){
                if(c.getIdReceiver() == loggedInUser.getId() && Objects.equals(c.getStatus(), "PENDING"))
                {
                    Utilizator u = network.findUtilizator(c.getIdSender());
                    Alert alert = new Alert(Alert.AlertType.INFORMATION);
                    alert.setTitle("FRIEND REQUEST");
                    alert.setHeaderText("NEW FRIEND REQUEST");
                    alert.setContentText("You have a new friend request from "+ u.getUserName());
                    alert.showAndWait();
                }
            }



            model.setAll(friends);

        } else {
            userNameLabel.setText("No user logged in.");
            System.out.println("No user logged in.");
        }
    }

    @FXML
    public void handleDeleteUser() {
        Utilizator loggedInUser = this.utilizator.get();
        Alert confirmationAlert = new Alert(Alert.AlertType.CONFIRMATION);
        confirmationAlert.setTitle("Delete User");
        confirmationAlert.setHeaderText("Are you sure you want to delete this user?");
        confirmationAlert.setContentText("User ID: " + loggedInUser.getId() +
                "\nFirst Name: " + loggedInUser.getFirstName() +
                "\nLast Name: " + loggedInUser.getLastName());

        confirmationAlert.showAndWait().ifPresent(response -> {
            if (response == ButtonType.OK) {
                network.removeUtilizator(loggedInUser.getId());

                Alert successAlert = new Alert(Alert.AlertType.INFORMATION);
                successAlert.setTitle("Delete Successful");
                successAlert.setHeaderText(null);
                successAlert.setContentText("The user has been deleted successfully.");
                successAlert.showAndWait();
                stage.close();
            }
        });
    }

    @FXML
    public void handleDeleteFriend(){
        Utilizator loggedInUser = this.utilizator.get();
        Utilizator selectedUser = tableView.getSelectionModel().getSelectedItem();

        network.removePrietenie(loggedInUser.getId(), selectedUser.getId());

        if (selectedUser != null) {
            Alert confirmationAlert = new Alert(Alert.AlertType.CONFIRMATION);
            confirmationAlert.setTitle("Delete friend");
            confirmationAlert.setHeaderText("Are you sure you want to delete this friend?");
            confirmationAlert.setContentText("User ID: " + selectedUser.getId() +
                    "\nFirst Name: " + selectedUser.getFirstName() +
                    "\nLast Name: " + selectedUser.getLastName() +
                    "\nUsername: "+ selectedUser.getUserName());

            confirmationAlert.showAndWait().ifPresent(response -> {
                if (response == ButtonType.OK) {
                    network.removePrietenie(loggedInUser.getId(), selectedUser.getId());

                    //initModel();

                    Alert successAlert = new Alert(Alert.AlertType.INFORMATION);
                    successAlert.setTitle("Delete Successful");
                    successAlert.setHeaderText(null);
                    successAlert.setContentText("The friend has been deleted successfully.");
                    successAlert.showAndWait();
                }
            });
        } else {
            Alert warningAlert = new Alert(Alert.AlertType.WARNING);
            warningAlert.setTitle("No Selection");
            warningAlert.setHeaderText("No user selected!");
            warningAlert.setContentText("Please select a user from the table to delete.");
            warningAlert.showAndWait();
        }
    }


    @FXML
    public void handleSendRequest() {
        Utilizator loggedInUser = this.utilizator.get();
        String userName = textFieldUsername.getText();

        Utilizator friend = network.findUtilizatorUsername(userName);
        if (userName.isEmpty()) {
            Alert alert = new Alert(Alert.AlertType.INFORMATION);
            alert.setTitle("Add Friend");
            alert.setHeaderText("Error");
            alert.setContentText("Username cannot be empty.");
            System.out.println("username and password cannot be empty.");
            return;
        }

        LocalDateTime date = LocalDateTime.now();
        String status = "PENDING";
        CererePrietenie cererePrietenie=new CererePrietenie(loggedInUser.getId(), friend.getId(),date,status);

        sendRequestToServer(cererePrietenie);

    }

    private void sendRequestToServer(CererePrietenie request) {
        try {
            network.addCerere(request);
            System.out.println("Friend request sent to server successfully: " + request);
            Alert confirmationAlert = new Alert(Alert.AlertType.CONFIRMATION);
            confirmationAlert.setTitle("Confirmation");
            confirmationAlert.setHeaderText("Request sent");
            confirmationAlert.setContentText("Your request has been sent.");
            confirmationAlert.showAndWait();
        } catch (Exception e) {
            System.err.println("Failed to send friend request: " + e.getMessage());
            Alert alert = new Alert(Alert.AlertType.ERROR);
            alert.setTitle("Error");
            alert.setHeaderText(null);
            alert.setContentText("Failed to send friend request: " + e.getMessage());
        }
    }


    public void handleUserRequests() {
        try {
            FXMLLoader loader = new FXMLLoader(getClass().getResource("requests.fxml"));
            AnchorPane root = loader.load();


            Stage stage = new Stage();
            stage.setTitle("FRIEND REQUESTS");
            stage.initModality(Modality.WINDOW_MODAL);
            stage.setScene(new Scene(root));


            RequestsController controller = loader.getController();
            controller.setService(network, stage, Optional.of(this.utilizator.get()));


            stage.showAndWait();

        } catch (IOException e) {
            e.printStackTrace();
            System.err.println("Error showing requests: " + e.getMessage());
        }
    }


    @FXML
    public void handleMessage(){
        try {
            FXMLLoader loader = new FXMLLoader(getClass().getResource("message.fxml"));
            AnchorPane root = loader.load();




            Utilizator selectedUser = tableView.getSelectionModel().getSelectedItem();
            Utilizator loggedInUser = this.utilizator.get();

            Stage stage = new Stage();
            stage.setTitle(selectedUser.getUserName());
            stage.initModality(Modality.WINDOW_MODAL);
            stage.setScene(new Scene(root));
            MessageController controller = loader.getController();
            controller.setService(network, stage, Optional.of(loggedInUser),Optional.of(selectedUser));


            stage.showAndWait();

        } catch (IOException e) {
            e.printStackTrace();
            System.err.println("Error showing requests: " + e.getMessage());
        }
    }

    @FXML
    private void handleLogout() {
        stage.close();
    }
}
