package src.ubb.repository.database;

import src.ubb.domain.Prietenie;
import src.ubb.domain.Utilizator;
import src.ubb.domain.validators.PrietenieValidator;
import src.ubb.repository.Repository;
import java.sql.*;
import java.time.LocalDate;
import java.time.LocalDateTime;
import java.time.ZoneOffset;
import java.time.temporal.TemporalAccessor;
import java.util.Date;
import java.util.HashMap;
import java.util.Map;
import java.util.Objects;
import java.util.Optional;

public class FriendshipRepoDB implements Repository<Long, Prietenie> {

    PrietenieValidator prietenieValidator;

    public FriendshipRepoDB(PrietenieValidator prietenieValidator) {
        this.prietenieValidator = prietenieValidator;
    }
    String url = "jdbc:postgresql://localhost:5432/networks";
    //"jdbc:postgresql://localhost:5432/network";
    String username = "postgres";
    String password = "PgPass";
    @Override
    public Optional<Prietenie> findOne(Long aLong) {
        String query = "SELECT * FROM Friends WHERE id = ?";
        Prietenie prietenie = null;
        try(Connection con = DriverManager.getConnection(url,username,password);
            PreparedStatement ps = con.prepareStatement(query);){
            ps.setLong(1,aLong);
            ResultSet rs = ps.executeQuery();
            while(rs.next()) {
                Long id1 = rs.getLong("id1");
                Long id2 = rs.getLong("id2");
                prietenie = new Prietenie(id1,id2);
                prietenie.setId(aLong);
            }
        }catch(SQLException e) {
            throw new RuntimeException(e);
        }
        return Optional.ofNullable(prietenie);
    }

    @Override
    public Iterable<Prietenie> findAll() {
        HashMap<Long, Prietenie> prietenieHashMap = new HashMap<>();
        String query = "SELECT * FROM Friends ";
        Prietenie prietenie = null;
        try(Connection con = DriverManager.getConnection(url,username,password);
            PreparedStatement ps = con.prepareStatement(query);){
            ResultSet rs = ps.executeQuery();
            while(rs.next()) {
                Long id = rs.getLong("id");
                Long id1 = rs.getLong("id1");
                Long id2 = rs.getLong("id2");
                prietenie = new Prietenie(id1,id2);
                prietenie.setId(id);

                prietenieHashMap.put(prietenie.getId(), prietenie);
            }
        }catch(SQLException e) {
            throw new RuntimeException(e);
        }
        return prietenieHashMap.values();
    }

    @Override
    public Optional<Prietenie> save(Prietenie entity) {
        if(entity.getId() == null) {
            throw new IllegalArgumentException("Prietenie cannot be null");
        }
        String query = "INSERT INTO Friends (id,id1,id2) VALUES (?,?,?)";
        try(Connection con = DriverManager.getConnection(url,username,password);
            PreparedStatement ps = con.prepareStatement(query);){
            ps.setLong(1,entity.getId());
            ps.setLong(2,entity.getUserId1());
            ps.setLong(3,entity.getUserId2());
            ps.executeUpdate();

        }catch(SQLException e) {
            throw new RuntimeException(e);
        }
        return Optional.of(entity);
    }

    @Override
    public Optional<Prietenie> delete(Long aLong) {
        String query = "DELETE FROM Friends WHERE id = ?";
        try(Connection con = DriverManager.getConnection(url,username,password);
            PreparedStatement ps = con.prepareStatement(query);){
            ps.setLong(1,aLong);
            ps.executeUpdate();

        }catch(SQLException e) {
            throw new RuntimeException(e);
        }
        Prietenie prietenie = null;
        for(Prietenie pr: findAll()){
            if(pr.getId().equals(aLong)) {
                prietenie = pr;
            }
        }

        return Optional.ofNullable(prietenie);
    }

    @Override
    public Optional<Prietenie> update(Prietenie entity) {
        return Optional.empty();
    }
}
