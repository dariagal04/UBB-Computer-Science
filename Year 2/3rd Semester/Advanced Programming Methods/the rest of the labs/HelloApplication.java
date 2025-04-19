package src.ubb.javafxlab;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;
import src.ubb.javafxlab.domain.validators.PrietenieValidator;
import src.ubb.javafxlab.domain.validators.UtilizatorValidator;
import src.ubb.javafxlab.networks.Network;
import src.ubb.javafxlab.repository.database.UserRepoDB;
import src.ubb.javafxlab.repository.database.FriendshipRepoDB;
import src.ubb.javafxlab.domain.validators.UtilizatorValidator;
import java.io.IOException;

public class HelloApplication extends Application {

    UserRepoDB userRepoDB;
    FriendshipRepoDB friendshipRepoDB;
    Network network;

    @Override
    public void start(Stage stage) throws IOException {
        userRepoDB = new UserRepoDB(new UtilizatorValidator());
        friendshipRepoDB = new FriendshipRepoDB(new PrietenieValidator(userRepoDB));
        network = new Network(userRepoDB, friendshipRepoDB);
        init(stage);
        stage.setTitle("Network");
        stage.show();

    }

    private void init(Stage stage) throws IOException {
        FXMLLoader fxmlLoader = new FXMLLoader();
        Scene scene = new Scene(fxmlLoader.load(getClass().getResourceAsStream("hello-view.fxml")));
        stage.setScene(scene);

        HelloController controller = fxmlLoader.getController();
        controller.setSocialNetwork(network);

    }
    public static void main(String[] args) {
        launch();
    }
}