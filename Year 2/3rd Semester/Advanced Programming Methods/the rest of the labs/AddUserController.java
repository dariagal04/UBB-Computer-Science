package src.ubb.javafxlab;

import javafx.fxml.FXML;
import javafx.scene.control.TextField;
import javafx.stage.Stage;
import src.ubb.javafxlab.domain.Utilizator;
import src.ubb.javafxlab.domain.validators.ValidationException;
import src.ubb.javafxlab.networks.Network;


public class AddUserController {


    @FXML
    private TextField textFieldFirstName;

    @FXML
    private TextField textFieldLastName;

    @FXML
    private TextField textFieldUserName;

    @FXML
    private TextField textFieldPassword;

    private Network network;
    Stage stage;
    Utilizator utilizator;

    @FXML
    private void initialize() {}

    public void setService(Network network, Stage stage, Utilizator utilizator) {
        this.network = network;
        this.stage = stage;
        this.utilizator = utilizator;
        if(utilizator != null) {
            setFields(utilizator);
        }
    }

    private void setFields(Utilizator utilizator) {
//        textFieldId.setText(utilizator.getId().toString());
        textFieldFirstName.setText(utilizator.getFirstName());
        textFieldLastName.setText(utilizator.getLastName());
        textFieldUserName.setText(utilizator.getUserName());
        textFieldPassword.setText(utilizator.getPassword());
    }

    public Utilizator getUser() {
        return utilizator;
    }

    @FXML
    public void handleCancel(){
        stage.close();
    }

    @FXML
    public void handleSave(){
        try{
            String firstName = textFieldFirstName.getText();
            String lastName = textFieldLastName.getText();
            String userName = textFieldUserName.getText();
            String password = textFieldPassword.getText();

            if(firstName.isEmpty() || lastName.isEmpty() || password.isEmpty()) {
                throw new ValidationException("All fields are required");
            }

            Utilizator utilizator = new Utilizator(firstName, lastName, password, userName);
            utilizator.setId(network.getnewUtilizatorId());

            if(this.utilizator == null) {
                Utilizator addedUser = network.addUtilizator(utilizator);
                if(addedUser == null) {
                    stage.close();
                }
            }
            stage.close();
        } catch (NumberFormatException e) {
            System.out.println("Invalid ID format: " + e.getMessage());
        } catch (ValidationException e) {
            System.out.println("Validation error: " + e.getMessage());
        } catch (Exception e) {
            System.out.println("Error saving user: " + e.getMessage());
        }
    }

}
