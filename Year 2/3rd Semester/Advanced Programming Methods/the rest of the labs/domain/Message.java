package src.ubb.javafxlab.domain;

import java.time.LocalDateTime;

public class Message {

    private Long id;
    private Long idSender;
    private Long idReceiver;
    private String text;
    private Message reply;
    private LocalDateTime date;

    public Message(Long id, Long idSender, Long idReceiver, String text, LocalDateTime date) {
        this.id = id;
        this.idSender = idSender;
        this.idReceiver = idReceiver;
        this.text = text;
        this.date = date;
    }

    public Message(Long id, Long idSender, Long idReceiver, String text, Message reply) {
        this.id = id;
        this.idSender = idSender;
        this.idReceiver = idReceiver;
        this.text = text;
        this.reply = reply;
    }
    public Long getId() {
        return id;
    }
    public void setId(Long id) {
        this.id = id;
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
    public String getMessage() {
        return text;
    }
    public void setMessage(String text) {
        this.text = text;
    }
    public Message getReply() {
        return reply;
    }
    public void setReply(Message reply) {
        this.reply = reply;
    }

    public LocalDateTime getDate() {
        return date;
    }
    public void setDate(LocalDateTime date) {
        this.date = date;
    }
}
