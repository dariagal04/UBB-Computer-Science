package src.ubb.javafxlab.repository.database;

import src.ubb.javafxlab.domain.CererePrietenie;
import src.ubb.javafxlab.domain.Message;
import src.ubb.javafxlab.domain.Prietenie;
import src.ubb.javafxlab.domain.validators.PrietenieValidator;
import src.ubb.javafxlab.repository.PagingRepository;
import src.ubb.javafxlab.repository.Repository;
import src.ubb.javafxlab.utils.paging.Page;
import src.ubb.javafxlab.utils.paging.Pageable;

import java.sql.*;
import java.time.LocalDateTime;
import java.util.*;

import static java.sql.DriverManager.getConnection;

public class FriendshipRepoDB implements PagingRepository<Long, Prietenie> {

    PrietenieValidator prietenieValidator;

    public FriendshipRepoDB(PrietenieValidator prietenieValidator) {
        this.prietenieValidator = prietenieValidator;
    }
    String url = "jdbc:postgresql://localhost:5432/networks";
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
                LocalDateTime date = rs.getTimestamp("date").toLocalDateTime();
                prietenie = new Prietenie(id1,id2, date);
                prietenie.setId(aLong);
            }
        }catch(SQLException e) {
            throw new RuntimeException(e);
        }
        return Optional.ofNullable(prietenie);
    }

    public Optional<CererePrietenie> findOneCerere(Long aLong) {
        String query = "SELECT * FROM friend_requests WHERE sender_id = ?";
        CererePrietenie cererePrietenie = null;
        try(Connection con = DriverManager.getConnection(url,username,password);
            PreparedStatement ps = con.prepareStatement(query);){
            ps.setLong(1,aLong);
            ResultSet rs = ps.executeQuery();
            while(rs.next()) {
                Long idSender = rs.getLong("sender_id");
                Long idReceiver = rs.getLong("receiver_id");
                LocalDateTime sentDate = rs.getTimestamp("sent_date").toLocalDateTime();
                String status = rs.getString("status");
                cererePrietenie = new CererePrietenie(idSender, idReceiver,sentDate,status);
            }
        }catch(SQLException e) {
            throw new RuntimeException(e);
        }
        return Optional.ofNullable(cererePrietenie);
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
                LocalDateTime date = rs.getTimestamp("date").toLocalDateTime();
                prietenie = new Prietenie(id1,id2,date);
                prietenie.setId(id);

                prietenieHashMap.put(prietenie.getId(), prietenie);
            }
        }catch(SQLException e) {
            throw new RuntimeException(e);
        }
        return prietenieHashMap.values();
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
    public Optional<Prietenie> save(Prietenie entity) {
        if(entity.getId() == null) {
            throw new IllegalArgumentException("Prietenie cannot be null");
        }
        String query = "INSERT INTO Friends (id,id1,id2,date) VALUES (?,?,?,?)";
        try(Connection con = DriverManager.getConnection(url,username,password);
            PreparedStatement ps = con.prepareStatement(query);){
            ps.setLong(1,entity.getId());
            ps.setLong(2,entity.getUserId1());
            ps.setLong(3,entity.getUserId2());
            ps.setTimestamp(4, Timestamp.valueOf(entity.getDate()));
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

    //@Override
    public Optional<CererePrietenie> deleteCerere(Long aLong) {
        String query = "DELETE FROM friend_requests WHERE sender_id = ?";
        try(Connection con = DriverManager.getConnection(url,username,password);
            PreparedStatement ps = con.prepareStatement(query);){
            ps.setLong(1,aLong);
            ps.executeUpdate();

        }catch(SQLException e) {
            throw new RuntimeException(e);
        }
       CererePrietenie cererePrietenie = null;
        for(CererePrietenie cp: findAllCereri()){
            if(cp.getIdReceiver().equals(aLong)) {
                cererePrietenie = cp;
            }
        }

        return Optional.ofNullable(cererePrietenie);
    }

    public void addFriendRequest(CererePrietenie request) {
        String sql = "INSERT INTO friend_requests (sender_id, receiver_id, sent_date, status) VALUES (?, ?, ?, ?)";
        try (Connection connection = getConnection(url,username,password);
             PreparedStatement statement = connection.prepareStatement(sql)) {
            statement.setLong(1, request.getIdSender());
            statement.setLong(2, request.getIdReceiver());
            statement.setTimestamp(3, Timestamp.valueOf(request.getSentDate()));
            statement.setString(4, request.getStatus());
            statement.executeUpdate();
        } catch (SQLException e) {
            throw new RuntimeException("Error adding friend request to database: " + e.getMessage(), e);
        }
    }

    @Override
    public Optional<Prietenie> update(Prietenie entity) {
        return Optional.empty();
    }




    ////



    public Iterable<Message> findAllMessages() {
        HashMap<Long, Message> messageHashMap = new HashMap<>();
        String query = "SELECT * FROM Messages ";
        Message message = null;
        try(Connection con = DriverManager.getConnection(url,username,password);
            PreparedStatement ps = con.prepareStatement(query);){
            ResultSet rs = ps.executeQuery();
            while(rs.next()) {
                Long id = rs.getLong("id");
                Long id1 = rs.getLong("sender_id");
                Long id2 = rs.getLong("receiver_id");
                String text = rs.getString("text");
                LocalDateTime date = rs.getTimestamp("date").toLocalDateTime();
                message = new Message(id,id1,id2,text,date);
                message.setId(id);

                messageHashMap.put(message.getId(), message);
            }
        }catch(SQLException e) {
            throw new RuntimeException(e);
        }
        return messageHashMap.values();
    }

    public void addMessage(Message message) {
        String sql = "INSERT INTO messages (id, sender_id, receiver_id, text,date) VALUES (?, ?, ?, ?,?)";
        try (Connection connection = getConnection(url,username,password);
             PreparedStatement statement = connection.prepareStatement(sql)) {
            statement.setLong(1, message.getId());
            statement.setLong(2, message.getIdSender());
            statement.setLong(3, message.getIdReceiver());
            statement.setString(4, message.getMessage());
            statement.setTimestamp(5, Timestamp.valueOf(LocalDateTime.now()));
            statement.executeUpdate();
        } catch (SQLException e) {
            throw new RuntimeException("Error adding message to database: " + e.getMessage(), e);
        }
    }

    public Optional<Message> deleteMessage(Long aLong) {
        String query = "DELETE FROM messages WHERE sender_id = ?";
        try(Connection con = DriverManager.getConnection(url,username,password);
            PreparedStatement ps = con.prepareStatement(query);){
            ps.setLong(1,aLong);
            ps.executeUpdate();

        }catch(SQLException e) {
            throw new RuntimeException(e);
        }
        Message message1= null;
        for(Message cp: findAllMessages()){
            if(cp.getIdSender().equals(aLong)) {
                message1 = cp;
            }
        }

        return Optional.ofNullable(message1);
    }

    @Override
    public Page<Prietenie> findAll(Pageable pageable) {
        List<Prietenie> friendshipList = new ArrayList<>();
        try(Connection connection= DriverManager.getConnection(this.url,this.username,this.password);
            PreparedStatement pagePreparedStatement=connection.prepareStatement("SELECT * FROM Friends " +
                    "LIMIT ? OFFSET ?");

            PreparedStatement countPreparedStatement = connection.prepareStatement
                    ("SELECT COUNT(*) AS count FROM Friends");

        ) {
            pagePreparedStatement.setInt(1, pageable.getPageSize());
            pagePreparedStatement.setInt(2, pageable.getPageSize() * pageable.getPageNumber());
            try (ResultSet pageResultSet = pagePreparedStatement.executeQuery();
                 ResultSet countResultSet = countPreparedStatement.executeQuery(); ) {
                while (pageResultSet.next()) {
                    Long id = pageResultSet.getLong("id");
                    Long id1 = pageResultSet.getLong("id1");
                    Long id2 = pageResultSet.getLong("id2");
                    LocalDateTime date = pageResultSet.getTimestamp("date").toLocalDateTime();
                    Prietenie prietenie = new Prietenie(id1,id2,date);
                    prietenie.setId(id);
                    friendshipList.add(prietenie);
                }
                int totalCount = 0;
                if(countResultSet.next()) {
                    totalCount = countResultSet.getInt("count");
                }

                return new Page<>(friendshipList, totalCount);

            }
        }
        catch (SQLException e){
            throw new RuntimeException(e);
        }
    }


   // @Override
    public Page<CererePrietenie> findAllCereri(Pageable pageable) {
        List<CererePrietenie> cereri = new ArrayList<>();
        try(Connection connection= DriverManager.getConnection(this.url,this.username,this.password);
            PreparedStatement pagePreparedStatement=connection.prepareStatement("SELECT * FROM Friend_requests " +
                    "LIMIT ? OFFSET ?");

            PreparedStatement countPreparedStatement = connection.prepareStatement
                    ("SELECT COUNT(*) AS count FROM Friend_requests");

        ) {
            pagePreparedStatement.setInt(1, pageable.getPageSize());
            pagePreparedStatement.setInt(2, pageable.getPageSize() * pageable.getPageNumber());
            try (ResultSet pageResultSet = pagePreparedStatement.executeQuery();
                 ResultSet countResultSet = countPreparedStatement.executeQuery(); ) {
                while (pageResultSet.next()) {
                    Long idSender = pageResultSet.getLong("sender_id");
                    Long idReceiver = pageResultSet.getLong("receiver_id");
                    LocalDateTime sentDate = pageResultSet.getTimestamp("sent_date").toLocalDateTime();
                    String status = pageResultSet.getString("status");
                    CererePrietenie cererePrietenie = new CererePrietenie(idSender, idReceiver,sentDate,status);
                    //cerere

                    cereri.add(cererePrietenie);
                }
                int totalCount = 0;
                if(countResultSet.next()) {
                    totalCount = countResultSet.getInt("count");
                }

                return new Page<>(cereri, totalCount);

            }
        }
        catch (SQLException e){
            throw new RuntimeException(e);
        }
    }


    public Page<Prietenie> findAllUserFriends(Pageable pageable, Long idU) {
        List<Prietenie> friendshipList = new ArrayList<>();
        try (Connection connection = DriverManager.getConnection(this.url, this.username, this.password);
             PreparedStatement pagePreparedStatement = connection.prepareStatement(
                     "SELECT * FROM Friends WHERE (Friends.id1 = ? OR Friends.id2 = ?) " +
                             "LIMIT ? OFFSET ?");

             PreparedStatement countPreparedStatement = connection.prepareStatement(
                     "SELECT COUNT(*) AS count FROM Friends WHERE (Friends.id1 = ? OR Friends.id2 = ?)")
        ) {
            // Set parameters for the paginated query
            pagePreparedStatement.setLong(1, idU);
            pagePreparedStatement.setLong(2, idU);
            pagePreparedStatement.setInt(3, pageable.getPageSize());
            pagePreparedStatement.setInt(4, pageable.getPageNumber() * pageable.getPageSize());  // Offset calculation

            // Set parameters for the count query
            countPreparedStatement.setLong(1, idU);
            countPreparedStatement.setLong(2, idU);

            try (ResultSet pageResultSet = pagePreparedStatement.executeQuery();
                 ResultSet countResultSet = countPreparedStatement.executeQuery()) {

                // Process the paginated results
                while (pageResultSet.next()) {
                    Long id = pageResultSet.getLong("id");
                    Long id1 = pageResultSet.getLong("id1");
                    Long id2 = pageResultSet.getLong("id2");
                    LocalDateTime date = pageResultSet.getTimestamp("date").toLocalDateTime();
                    Prietenie prietenie = new Prietenie(id1, id2, date);
                    prietenie.setId(id);
                    friendshipList.add(prietenie);
                }

                // Get total count
                int totalCount = 0;
                if (countResultSet.next()) {
                    totalCount = countResultSet.getInt("count");
                }

                // Return a Page object with the results and total count
                return new Page<>(friendshipList, totalCount);

            }
        } catch (SQLException e) {
            e.printStackTrace();
            // You can log the error or throw a custom exception here
            return new Page<>(friendshipList, 0);  // Return an empty page on error
        }
    }


    public List<CererePrietenie> findAllFriends(Long userId) {
        List<CererePrietenie> friends = new ArrayList<>();
        String query = """
        SELECT sender_id, receiver_id, sent_date, status 
        FROM friend_requests 
        WHERE status = 'ACCEPTED' 
        AND (sender_id = ? OR receiver_id = ?)
    """;

        try (Connection connection = DriverManager.getConnection(this.url, this.username, this.password);
             PreparedStatement preparedStatement = connection.prepareStatement(query)) {
            // Set the parameters for the query
            preparedStatement.setLong(1, userId);
            preparedStatement.setLong(2, userId);

            // Execute the query
            try (ResultSet resultSet = preparedStatement.executeQuery()) {
                while (resultSet.next()) {
                    Long senderId = resultSet.getLong("sender_id");
                    Long receiverId = resultSet.getLong("receiver_id");
                    LocalDateTime sentDate = resultSet.getTimestamp("sent_date").toLocalDateTime();
                    String status = resultSet.getString("status");

                    // Create a CererePrietenie object and add it to the list
                    CererePrietenie friendship = new CererePrietenie(senderId, receiverId, sentDate, status);
                    friends.add(friendship);
                }
            }
        } catch (SQLException e) {
            throw new RuntimeException("Error finding friends: " + e.getMessage(), e);
        }

        return friends;
    }


}
