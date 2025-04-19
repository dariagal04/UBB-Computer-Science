package src.ubb.galdaria_practic.domain;

import java.time.LocalDateTime;

public class Show extends Entity<Long>{

    int id;
    String name;
    int durationMinutes;
    LocalDateTime startDate;
    int numberOfSeats;
    LocalDateTime creationDate;

    public Show(int id, String name, int durationMinutes, LocalDateTime startDate, int numberOfSeats, LocalDateTime creationDate) {
        this.id = id;
        this.name = name;
        this.durationMinutes = durationMinutes;
        this.startDate = startDate;
        this.numberOfSeats = numberOfSeats;
        this.creationDate = creationDate;
    }

    @Override
    public int getId() {
        return  id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getDurationMinutes() {
        return durationMinutes;
    }

    public void setDurationMinutes(int durationMinutes) {
        this.durationMinutes = durationMinutes;
    }

    public LocalDateTime getStartDate() {
        return startDate;
    }

    public void setStartDate(LocalDateTime startDate) {
        this.startDate = startDate;
    }

    public int getNumberOfSeats() {
        return numberOfSeats;
    }

    public void setNumberOfSeats(int numberOfSeats) {
        this.numberOfSeats = numberOfSeats;
    }

    public LocalDateTime getCreationDate() {
        return creationDate;
    }

    public void setCreationDate(LocalDateTime creationDate) {
        this.creationDate = creationDate;
    }

    public int compareTo(Show otherShow) {
        return this.startDate.compareTo(otherShow.startDate);
    }

    public LocalDateTime getDate() {
        return this.startDate;
    }
}
