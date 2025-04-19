package src.ubb.javafxlab.domain;

import java.time.LocalDate;
import java.time.LocalDateTime;

public class UserStatus {

    private Long id;
    private String firstName;
    private String lastName;
    private String userName;
    private LocalDateTime sentDate;
    private String status;

    public UserStatus(Long id, String firstName, String lastName, String userName,LocalDateTime sentDate, String status) {
        this.id = id;
        this.firstName = firstName;
        this.lastName = lastName;
        this.userName = userName;
        this.sentDate = sentDate;
        this.status = status;
    }
    public Long getId() {
        return id;
    }
    public void setId(Long id) {
        this.id = id;
    }
    public String getFirstName() {
        return firstName;
    }
    public void setFirstName(String firstName) {
        this.firstName = firstName;
    }
    public String getLastName() {
        return lastName;
    }
    public void setLastName(String lastName) {
        this.lastName = lastName;
    }
    public String getUserName() {
        return userName;
    }
    public void setUserName(String userName) {
        this.userName = userName;
    }
    public LocalDateTime getSentDate() {
        return sentDate;
    }
    public void setSentDate(LocalDateTime sentDate) {
        this.sentDate = sentDate;
    }
    public String getStatus() {
        return status;
    }
    public void setStatus(String status) {
        this.status = status;
    }
}
