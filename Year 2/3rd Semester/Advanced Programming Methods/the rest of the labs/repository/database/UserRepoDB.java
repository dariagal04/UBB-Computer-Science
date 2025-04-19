package src.ubb.javafxlab.repository.database;
import src.ubb.javafxlab.domain.CererePrietenie;
import src.ubb.javafxlab.domain.Utilizator;

import src.ubb.javafxlab.domain.validators.UtilizatorValidator;
import src.ubb.javafxlab.repository.PagingRepository;
import src.ubb.javafxlab.repository.Repository;
import src.ubb.javafxlab.utils.paging.Page;
import src.ubb.javafxlab.utils.paging.Pageable;

import java.sql.*;
import java.time.LocalDateTime;
import java.util.*;

public class UserRepoDB implements PagingRepository<Long, Utilizator> {


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
                String userName = rs.getString("username");
                String password = rs.getString("password");
                utilizator = new Utilizator(firstName,lastName,password,userName);
                utilizator.setId(aLong);
            }
        }catch(SQLException e) {
            throw new RuntimeException(e);
        }
        return Optional.ofNullable(utilizator);
    }

    //@Override
    public Optional<Utilizator> findByUserName(String userName) {
        String query = "SELECT * FROM Users WHERE username = ?";
        Utilizator utilizator = null;
        try (Connection con = DriverManager.getConnection(url, username, password);
             PreparedStatement ps = con.prepareStatement(query)) {

            ps.setString(1, userName);
            ResultSet rs = ps.executeQuery();

            if (rs.next()) {
                String firstName = rs.getString("firstname");
                String lastName = rs.getString("lastname");
                String password = rs.getString("password");
                Long id = rs.getLong("id");

                utilizator = new Utilizator(firstName, lastName, password, userName);
                utilizator.setId(id);
            }
        } catch (SQLException e) {
            throw new RuntimeException("Error retrieving user by username: " + userName, e);
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
                String userName = rs.getString("username");
                String password = rs.getString("password");
                utilizator = new Utilizator(firstName,lastName, password, userName);
                utilizator.setId(id);

                utilizatorHashMap.put(utilizator.getId(), utilizator);
            }
        }catch(SQLException e) {
            throw new RuntimeException(e);
        }
        return utilizatorHashMap.values();
    }

    @Override
    public Iterable<CererePrietenie> findAllCereri() {
        List<CererePrietenie> cereri = new ArrayList<>();
        String query = "SELECT * FROM friend_requests ";
        //Prietenie prietenie = null;
        CererePrietenie cererePrietenie = null;
        try(Connection con = DriverManager.getConnection(url,username,password);
            PreparedStatement ps = con.prepareStatement(query);){
            ResultSet rs = ps.executeQuery();
            while(rs.next()) {
                Long idSender = rs.getLong("sender_id");
                Long idReceiver = rs.getLong("receiver_id");
                LocalDateTime sentDate = rs.getTimestamp("sent_date").toLocalDateTime();
                String status = rs.getString("status");
                cererePrietenie = new CererePrietenie(idSender, idReceiver,sentDate,status);
                //cerere

                cereri.add(cererePrietenie);
            }
        }catch(SQLException e) {
            throw new RuntimeException(e);
        }
        return cereri;
    }


    @Override
    public Optional<Utilizator> save(Utilizator entity) {
        if(entity.getId() == null) {
            throw new IllegalArgumentException("Utilizator cannot be null");
        }
        String query = "INSERT INTO Users (id,firstname,lastname,password,username) VALUES (?,?,?,?,?)";
        try(Connection con = DriverManager.getConnection(url,username,password);
            PreparedStatement ps = con.prepareStatement(query);){
            ps.setLong(1,entity.getId());
            ps.setString(2,entity.getFirstName());
            ps.setString(3,entity.getLastName());
            ps.setString(4,entity.getPassword());
            ps.setString(5,entity.getUserName());

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

        return Optional.ofNullable(utilizator);
    }

    @Override
    public Optional<Utilizator> update(Utilizator entity) {
        return Optional.empty();
    }

    @Override
    public Page<Utilizator> findAll(Pageable pageable) {
        List<Utilizator> userList = new ArrayList<>();
        try(Connection connection= DriverManager.getConnection(this.url,this.username,this.password);
            PreparedStatement pagePreparedStatement=connection.prepareStatement("SELECT * FROM Users " +
                    "LIMIT ? OFFSET ?");

            PreparedStatement countPreparedStatement = connection.prepareStatement
                    ("SELECT COUNT(*) AS count FROM users ");

        ) {
            pagePreparedStatement.setInt(1, pageable.getPageSize());
            pagePreparedStatement.setInt(2, pageable.getPageSize() * pageable.getPageNumber());
            try (ResultSet pageResultSet = pagePreparedStatement.executeQuery();
                 ResultSet countResultSet = countPreparedStatement.executeQuery(); ) {
                while (pageResultSet.next()) {
                    Long id = pageResultSet.getLong("id");
                    String firstName =pageResultSet.getString("firstname");
                    String lastName = pageResultSet.getString("lastname");
                    String userName = pageResultSet.getString("username");
                    String password = pageResultSet.getString("password");
                    Utilizator utilizator = new Utilizator(firstName,lastName, password, userName);
                    utilizator.setId(id);
                    userList.add(utilizator);
                }
                int totalCount = 0;
                if(countResultSet.next()) {
                    totalCount = countResultSet.getInt("count");
                }

                return new Page<>(userList, totalCount);

            }
        }
        catch (SQLException e){
            throw new RuntimeException(e);
        }
    }
}
