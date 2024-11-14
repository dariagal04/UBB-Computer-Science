package src.ubb.repository.database;
import src.ubb.domain.Utilizator;

import src.ubb.domain.validators.UtilizatorValidator;
import src.ubb.repository.Repository;

import java.sql.*;
import java.util.HashMap;
import java.util.Objects;
import java.util.Optional;

public class UserRepoDB implements Repository<Long, Utilizator> {


    UtilizatorValidator utilizatorValidator;

    public UserRepoDB(UtilizatorValidator utilizatorValidator) {
        this.utilizatorValidator = utilizatorValidator;
    }

    String url = "jdbc:postgresql://localhost:5432/networks";
    String username = "postgres";
    String password = "PgPass";

    @Override
    public Optional<Utilizator> findOne(Long aLong) {
        String query = "SELECT * FROM Users WHERE id = ?";
        Utilizator utilizator = null;
        try(Connection con = DriverManager.getConnection(url,username,password);
            PreparedStatement ps = con.prepareStatement(query);){
            ps.setLong(1,aLong);
            ResultSet rs = ps.executeQuery();
            while(rs.next()) {
                String firstName = rs.getString("firstname");
                String lastName = rs.getString("lastname");
                utilizator = new Utilizator(firstName,lastName);
                utilizator.setId(aLong);
            }
        }catch(SQLException e) {
            throw new RuntimeException(e);
        }
        return Optional.ofNullable(utilizator);
    }

    @Override
    public Iterable<Utilizator> findAll() {
        HashMap<Long, Utilizator> utilizatorHashMap = new HashMap<>();
        String query = "SELECT * FROM Users";
        Utilizator utilizator = null;
        try(Connection con = DriverManager.getConnection(url,username,password);
            PreparedStatement ps = con.prepareStatement(query);){
            ResultSet rs = ps.executeQuery();
            while(rs.next()) {
                Long id = rs.getLong("id");
                String firstName = rs.getString("firstname");
                String lastName = rs.getString("lastname");
                utilizator = new Utilizator(firstName,lastName);
                utilizator.setId(id);

                utilizatorHashMap.put(utilizator.getId(), utilizator);
            }
        }catch(SQLException e) {
            throw new RuntimeException(e);
        }
        return utilizatorHashMap.values();
    }

    @Override
    public Optional<Utilizator> save(Utilizator entity) {
        if(entity.getId() == null) {
            throw new IllegalArgumentException("Utilizator cannot be null");
        }
        String query = "INSERT INTO Users (id,firstname,lastname) VALUES (?,?,?)";
        try(Connection con = DriverManager.getConnection(url,username,password);
            PreparedStatement ps = con.prepareStatement(query);){
            ps.setLong(1,entity.getId());
            ps.setString(2,entity.getFirstName());
            ps.setString(3,entity.getLastName());
            ps.executeUpdate();

        }catch(SQLException e) {
            throw new RuntimeException(e);
        }
        return Optional.of(entity);
    }

    @Override
    public Optional<Utilizator> delete(Long aLong) {

        Utilizator utilizator = findOne(aLong).orElse(null);
        if (utilizator == null) {
            return Optional.empty();
        }
        String query = "DELETE FROM Users WHERE id = ?";
        try(Connection con = DriverManager.getConnection(url,username,password);
            PreparedStatement ps = con.prepareStatement(query);){
            ps.setLong(1,aLong);
            ps.executeUpdate();

        }catch(SQLException e) {
            throw new RuntimeException(e);
        }
//        Utilizator utilizator = null;
//        for(Utilizator util : findAll()) {
//            //assert utilizator != null;
//            if(Objects.equals(utilizator.getId(), aLong)) {
//                utilizator = util;
//            }
//        }
        return Optional.ofNullable(utilizator);
    }

    @Override
    public Optional<Utilizator> update(Utilizator entity) {
        return Optional.empty();
    }
}
