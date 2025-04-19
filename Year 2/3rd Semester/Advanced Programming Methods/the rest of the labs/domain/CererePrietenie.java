package src.ubb.javafxlab.domain;


import java.sql.Timestamp;
import java.time.LocalDateTime;

public class CererePrietenie {
    private Long idSender;
    private Long idReceiver;
    private LocalDateTime sentDate;
    private String status;

    public CererePrietenie(Long idSender, Long idReceiver, LocalDateTime sentDate, String status) {
        this.idSender = idSender;
        this.idReceiver = idReceiver;
        this.sentDate = sentDate;
        this.status = status;
    }

    public Long getIdSender() {
        return idSender;
    }

    public void setIdSender(Long idSender) {
        this.idSender = idSender;
    }

    public Long getIdReceiver() {
        return idReceiver;
    }

    public void setIdReceiver(Long idReceiver) {
        this.idReceiver = idReceiver;
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

