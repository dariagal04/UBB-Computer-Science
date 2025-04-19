package src.ubb.galdaria_practic.repository.DBRepository;

import src.ubb.galdaria_practic.domain.User;
import src.ubb.galdaria_practic.repository.Repository;

import java.sql.*;
import java.util.*;

public class UsersDbRepo implements Repository<String,User> {
    private final String urlDb;
    private final String usernameDb;
    private final String passwordDb;

    public UsersDbRepo(String urlDb, String usernameDb, String passwordDb) {
        this.urlDb = urlDb;
        this.usernameDb = usernameDb;
        this.passwordDb = passwordDb;
    }

    private Connection getConnection() throws SQLException {
        return DriverManager.getConnection(urlDb, usernameDb, passwordDb);
    }

    public User findOne(String email) {
        String query = "SELECT * FROM Users WHERE email = ?";
        try (Connection con = getConnection();
             PreparedStatement ps = con.prepareStatement(query)) {
            ps.setString(1, email);
            ResultSet rs = ps.executeQuery();
            if (rs.next()) {
                return new User(rs.getString("email"), rs.getString("name"));
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        throw new NoSuchElementException("User with email " + email + " not found");
    }

    public List<User> findAll() {
        List<User> users = new ArrayList<>();
        String query = "SELECT * FROM Users";
        try (Connection con = getConnection();
             PreparedStatement ps = con.prepareStatement(query);
             ResultSet rs = ps.executeQuery()) {
            while (rs.next()) {
                users.add(new User(rs.getString("email"), rs.getString("name")));
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        return users;
    }

    public User save(User entity) {
        String query = "INSERT INTO Users (email, name) VALUES (?, ?)";
        try (Connection con = getConnection();
             PreparedStatement ps = con.prepareStatement(query)) {
            ps.setString(1, entity.getEmail());
            ps.setString(2, entity.getName());
            ps.executeUpdate();
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        return entity;
    }

    public User delete(String email) {
        String query = "DELETE FROM Users WHERE email = ?";
        try (Connection con = getConnection();
             PreparedStatement ps = con.prepareStatement(query)) {
            ps.setString(1, email);
            if (ps.executeUpdate() == 0) {
                throw new NoSuchElementException("User with email " + email + " not found");
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        return null;
    }

    @Override
    public User update(User entity) {
        return null;
    }
}
