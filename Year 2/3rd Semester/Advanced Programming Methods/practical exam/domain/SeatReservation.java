package src.ubb.galdaria_practic.domain;

public class SeatReservation extends Entity<Long>{
    String userEmail;
    int showId;

    public SeatReservation(String userEmail, int showId) {
        this.userEmail = userEmail;
        this.showId = showId;
    }

    public String getUserEmail() {
        return userEmail;
    }

    public void setUserEmail(String userEmail) {
        this.userEmail = userEmail;
    }

    public int getShowId() {
        return showId;
    }

    public void setShowId(int showId) {
        this.showId = showId;
    }


}
