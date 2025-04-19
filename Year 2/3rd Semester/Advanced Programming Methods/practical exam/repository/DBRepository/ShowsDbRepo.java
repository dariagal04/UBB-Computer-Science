package src.ubb.galdaria_practic.repository.DBRepository;

import src.ubb.galdaria_practic.domain.Show;
import src.ubb.galdaria_practic.repository.Repository;

import java.sql.*;
import java.time.LocalDateTime;
import java.util.*;

public class ShowsDbRepo implements Repository<Long, Show> {
    private final String urlDb;
    private final String usernameDb;
    private final String passwordDb;

    public ShowsDbRepo(String urlDb, String usernameDb, String passwordDb) {
        this.urlDb = urlDb;
        this.usernameDb = usernameDb;
        this.passwordDb = passwordDb;
    }

    private Connection getConnection() throws SQLException {
        return DriverManager.getConnection(urlDb, usernameDb, passwordDb);
    }

    public Show findOne(Long id) {
        String query = "SELECT * FROM shows WHERE id = ?";
        try (Connection con = getConnection();
             PreparedStatement ps = con.prepareStatement(query)) {
            ps.setLong(1, id);
            ResultSet rs = ps.executeQuery();
            if (rs.next()) {
                return new Show(
                        rs.getInt("id"),
                        rs.getString("name"),
                        rs.getInt("duration_minutes"),
                        rs.getTimestamp("start_date").toLocalDateTime(),
                        rs.getInt("number_of_seats"),
                        rs.getTimestamp("creation_date").toLocalDateTime()
                );
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        throw new NoSuchElementException("Show with ID " + id + " not found");
    }

    public List<Show> findAll() {
        List<Show> shows = new ArrayList<>();
        String query = "SELECT * FROM shows";
        try (Connection con = getConnection();
             PreparedStatement ps = con.prepareStatement(query);
             ResultSet rs = ps.executeQuery()) {
            while (rs.next()) {
                shows.add(new Show(
                        rs.getInt("id"),
                        rs.getString("name"),
                        rs.getInt("duration_minutes"),
                        rs.getTimestamp("start_date").toLocalDateTime(),
                        rs.getInt("number_of_seats"),
                        rs.getTimestamp("creation_date").toLocalDateTime()
                ));
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        return shows;
    }

    public Show save(Show entity) {
        String query = "INSERT INTO shows (name, duration_minutes, start_date, number_of_seats) VALUES (?, ?, ?, ?)";
        try (Connection con = getConnection();
             PreparedStatement ps = con.prepareStatement(query, Statement.RETURN_GENERATED_KEYS)) {
            ps.setString(1, entity.getName());
            ps.setInt(2, entity.getDurationMinutes());
            ps.setTimestamp(3, Timestamp.valueOf(entity.getStartDate()));
            ps.setInt(4, entity.getNumberOfSeats());
            ps.executeUpdate();

            ResultSet rs = ps.getGeneratedKeys();
            if (rs.next()) {
                entity.setId(rs.getInt(1));
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        return entity;
    }

    public Show delete(Long id) {
        String query = "DELETE FROM shows WHERE id = ?";
        try (Connection con = getConnection();
             PreparedStatement ps = con.prepareStatement(query)) {
            ps.setLong(1, id);
            if (ps.executeUpdate() == 0) {
                throw new NoSuchElementException("Show with ID " + id + " not found");
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        return null;
    }

    @Override
    public Show update(Show entity) {
        return null;
    }
}

