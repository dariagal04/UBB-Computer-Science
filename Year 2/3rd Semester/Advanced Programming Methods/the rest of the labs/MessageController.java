package src.ubb.javafxlab;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.scene.control.ListCell;
import javafx.scene.control.ListView;
import javafx.scene.control.TextField;
import javafx.stage.Stage;
import src.ubb.javafxlab.domain.Message;
import src.ubb.javafxlab.domain.UserStatus;
import src.ubb.javafxlab.domain.Utilizator;
import src.ubb.javafxlab.networks.Network;

import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.List;
import java.util.Optional;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

import static javafx.scene.control.ListView.*;

public class MessageController {

    private Network network;
    private Stage stage;
    private Optional<Utilizator> userMe;
    private Optional<Utilizator> user2;

    @FXML
    private ListView<Message> messagesList;
    @FXML
    private TextField messageInput;

    private ObservableList<Message> messages = FXCollections.observableArrayList();

    @FXML
    public void initialize() {
        messagesList.setItems(messages);
        messagesList.setCellFactory(listView -> new ListCell<>() {

            @Override
            protected void updateItem(Message message, boolean empty) {
                super.updateItem(message, empty);
                if (empty || message == null) {
                    setText(null);
                    setGraphic(null);
                } else {
                    StringBuilder displayText = new StringBuilder();
                    // Include informații despre reply dacă există
                    if (message.getReply() != null) {
                        displayText.append("Reply to: ").append(message.getReply().getMessage()).append("\n");
                    }

                    // Adaugă textul mesajului
                    if (message.getIdSender().equals(userMe.map(Utilizator::getId).orElse(null))) {
                        displayText.append(userMe.map(Utilizator::getUserName).orElse(null)).append(": ").append(message.getMessage());
                        setStyle("-fx-alignment: center-right; -fx-background-color: lightblue; -fx-padding: 5;");
                    } else {
                        displayText.append(user2.map(Utilizator::getUserName).orElse(null)).append(": ").append(message.getMessage());
                        setStyle("-fx-alignment: center-left; -fx-background-color: lightgrey; -fx-padding: 5;");
                    }

                    DateTimeFormatter formatter = DateTimeFormatter.ofPattern("HH:mm:ss");
                    displayText.append("\n").append(message.getDate().format(formatter)).append("\n");

                    setText(displayText.toString());
                }
            }

        });
    }

    private void initModel() {
        if (userMe.isPresent() && user2.isPresent()) {
            List<Message> userMessages = network.getMessagesBetweenUsers(userMe.get(), user2.get());

            messages.setAll(userMessages);
        }
    }


    @FXML
    private void handleSendMessage() {
        String text = messageInput.getText();
        if (text != null && !text.isEmpty()) {
            Long id = network.getnewMessageId();
            Utilizator sender = this.userMe.orElseThrow(() -> new IllegalStateException("Sender not set"));
            Utilizator receiver = this.user2.orElseThrow(() -> new IllegalStateException("Receiver not set"));
            LocalDateTime date = LocalDateTime.now();
            Message message = new Message(id, sender.getId(), receiver.getId(), text,date);

            messages.add(message);
            network.addMessage(message);

            messageInput.clear();
            initModel();
        }
    }


    @FXML
    private void handleReplyMessage() {
        Message selectedMessage = messagesList.getSelectionModel().getSelectedItem();
        if (selectedMessage == null) {
            System.out.println("No message selected for reply!");
            return;
        }

        String text = messageInput.getText();
        if (text != null && !text.isEmpty()) {
            Long id = network.getnewMessageId();
            Utilizator sender = this.userMe.orElseThrow(() -> new IllegalStateException("Sender not set"));
            Utilizator receiver = this.user2.orElseThrow(() -> new IllegalStateException("Receiver not set"));

            Message replyMessage = new Message(id, sender.getId(), receiver.getId(), text, selectedMessage);

            messages.add(replyMessage);
            network.addMessage(replyMessage);

            messageInput.clear();
            initModel();
        }
    }


    public void setService(Network network, Stage stage, Optional<Utilizator> userMe, Optional<Utilizator> user2) {
        this.network = network;
        this.stage = stage;
        this.userMe = userMe;
        this.user2 = user2;
        initModel();
    }
}
