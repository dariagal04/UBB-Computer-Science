package src.ubb.galdaria_practic.repository.DBRepository;

import src.ubb.galdaria_practic.domain.SeatReservation;
import src.ubb.galdaria_practic.repository.Repository;

import java.sql.*;
import java.util.*;

public class SeatReservationsDbRepo implements Repository<Long, SeatReservation> {
    private final String urlDb;
    private final String usernameDb;
    private final String passwordDb;

    public SeatReservationsDbRepo(String urlDb, String usernameDb, String passwordDb) {
        this.urlDb = urlDb;
        this.usernameDb = usernameDb;
        this.passwordDb = passwordDb;
    }

    private Connection getConnection() throws SQLException {
        return DriverManager.getConnection(urlDb, usernameDb, passwordDb);
    }

    public SeatReservation findOne(Long id) {
        String query = "SELECT * FROM SeatReservations WHERE id = ?";
        try (Connection con = getConnection();
             PreparedStatement ps = con.prepareStatement(query)) {
            ps.setLong(1, id);
            ResultSet rs = ps.executeQuery();
            if (rs.next()) {
                return new SeatReservation(
                        rs.getString("user_email"),
                        rs.getInt("show_id")
                );
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        throw new NoSuchElementException("SeatReservation with ID " + id + " not found");
    }

    public List<SeatReservation> findAll() {
        List<SeatReservation> reservations = new ArrayList<>();
        String query = "SELECT * FROM SeatReservations";
        try (Connection con = getConnection();
             PreparedStatement ps = con.prepareStatement(query);
             ResultSet rs = ps.executeQuery()) {
            while (rs.next()) {
                reservations.add(new SeatReservation(rs.getString("user_email"), rs.getInt("show_id")));
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        return reservations;
    }

    public SeatReservation save(SeatReservation entity) {
        String query = "INSERT INTO SeatReservations (user_email, show_id) VALUES (?, ?)";
        try (Connection con = getConnection();
             PreparedStatement ps = con.prepareStatement(query)) {
            ps.setString(1, entity.getUserEmail());
            ps.setInt(2, entity.getShowId());
            ps.executeUpdate();
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        return entity;
    }

    public SeatReservation delete(Long id) {
        throw new UnsupportedOperationException("SeatReservations cannot be deleted by ID directly.");
    }

    @Override
    public SeatReservation update(SeatReservation entity) {
        return null;
    }
}
