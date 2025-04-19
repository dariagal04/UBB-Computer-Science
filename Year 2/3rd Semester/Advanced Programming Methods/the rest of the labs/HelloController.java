package src.ubb.javafxlab;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Modality;
import javafx.stage.Stage;
import src.ubb.javafxlab.domain.CererePrietenie;
import src.ubb.javafxlab.domain.Utilizator;
import src.ubb.javafxlab.domain.validators.ValidationException;
import src.ubb.javafxlab.networks.Network;
import src.ubb.javafxlab.utils.Observer;
import src.ubb.javafxlab.utils.events.UtilizatorEntityChangeEvent;

import java.awt.event.ActionEvent;
import java.awt.print.Pageable;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

public class HelloController implements Observer<UtilizatorEntityChangeEvent> {

    Network network;
    ObservableList<Utilizator> model = FXCollections.observableArrayList();


    @FXML
    private TextField textFieldUsername;

    @FXML
    private TextField textFieldPassword;


    @FXML
    private void initModel() {
        Iterable<Utilizator> users = network.getUtilizatori();
        List<Utilizator> userList = StreamSupport.stream(users.spliterator(), false).collect(Collectors.toList());
        model.setAll(userList);
    }

    @FXML
    public void setSocialNetwork(Network sn) {
        network = sn;
        network.addObserver(this);
        initModel();
    }


    @Override
    public void update(UtilizatorEntityChangeEvent utilizatorEntityChangeEvent) {
        initModel();
    }

    @FXML
    public void handleAddUser(javafx.event.ActionEvent event) {
        Utilizator newUser = showAddUserEditDialog(null);
        if (newUser != null) {
            try{
                network.addUtilizator(newUser);
                initModel();
            }catch(ValidationException e){
                System.out.println("Validation Error:"+e.getMessage());
            }
        }
    }

    private Utilizator showAddUserEditDialog(Utilizator utilizator) {
        try{
            FXMLLoader loader = new FXMLLoader(HelloController.class.getResource("addUser.fxml"));
            AnchorPane root = loader.load();

            Stage dialogstage = new Stage();
            dialogstage.setTitle("Create new account");
            dialogstage.initModality(Modality.WINDOW_MODAL);

            Scene scene = new Scene(root);
            dialogstage.setScene(scene);

            AddUserController controller = loader.getController();
            controller.setService(network,dialogstage,utilizator);

            dialogstage.showAndWait();
            return controller.getUser();

        }catch(IOException e){
            e.printStackTrace();
            System.err.println("FXML load error:" + e.getMessage());
            return null;
        }
    }


    @FXML
    public void handleLogin(javafx.event.ActionEvent ev) {
        String userName = textFieldUsername.getText().trim();
        String password = textFieldPassword.getText().trim();

        if (userName.isEmpty() || password.isEmpty()) {
            System.out.println("username and password cannot be empty.");
            return;
        }

        try {
            Optional<Utilizator> user = network.authenticate(userName, password);

            if (user.isPresent()) {
                System.out.println("Login successful");
                openDashboard(user);

                initModel();
//                textFieldPassword.clear();
//                textFieldUsername.clear();
            } else {
                System.out.println("Invalid username or password.");
                Alert alert = new Alert(Alert.AlertType.ERROR);
                alert.setTitle("Invalid username or password");
                alert.setHeaderText("Invalid username or password");
                alert.setContentText("Invalid username or password");
                alert.showAndWait();
            }
        } catch (ValidationException e) {
            System.out.println("Validation Error: " + e.getMessage());
        }
    }

    private void openDashboard(Optional<Utilizator> user) {

        try {
            FXMLLoader loader = new FXMLLoader(getClass().getResource("loginController.fxml"));
            AnchorPane root = loader.load();


            Stage stage = new Stage();
            stage.setTitle("Account");
            stage.setScene(new Scene(root));
            stage.show();

            LoginController loginController = loader.getController();
            loginController.setService(network,stage);
            loginController.setUser(user);



        } catch (IOException e) {
            e.printStackTrace();
            System.out.println("Error loading dashboard: " + e.getMessage());
        }
    }

    public void handleUsers() {
        try {
            FXMLLoader loader = new FXMLLoader(getClass().getResource("users.fxml"));
            AnchorPane root = loader.load();


            Stage stage = new Stage();
            stage.setTitle("Users");
            stage.initModality(Modality.WINDOW_MODAL);
            stage.setScene(new Scene(root));

            UsersController controller = loader.getController();
            controller.setService(network, stage);


            stage.showAndWait();

        } catch (IOException e) {
            e.printStackTrace();
            System.err.println("Error showing Users: " + e.getMessage());
        }
    }


}