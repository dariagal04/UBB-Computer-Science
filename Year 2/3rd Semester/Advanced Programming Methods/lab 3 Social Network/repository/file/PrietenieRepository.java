//package org.example.repository.file;
//
//import org.example.domain.Prietenie;
//import org.example.domain.Pereche;
//import org.example.domain.Utilizator;
//import org.example.domain.Prietenie;
//import java.time.LocalDateTime;
//import java.time.format.DateTimeFormatter;
//
//public class PrietenieRepository extends AbstractFileRepository<Pereche<Long, Long>, Prietenie> {
//
//    public PrietenieRepository(String fileName) {
//        super(fileName);
//    }
//
//    @Override
//    public Prietenie createEntity(String line) {
//        String[] splited = line.split(";");
//        Pereche<String, String> tuple = new Pereche<>(splited[0], splited[1]);
//        Prietenie friendship = new Prietenie(tuple);
//        return friendship;
//    }
//
//    @Override
//    public String saveEntity(Prietenie entity) {
//        Prietenie friendship = (Prietenie) entity;
//        Pereche<Long, Long> usersTuple = friendship.getId();
//        LocalDateTime date = friendship.getDate();
//        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("HH:mm:ss");
//        String formattedTime = date.format(formatter);
//        return  usersTuple.getE1() + ";" + usersTuple.getE2() + ";" + formattedTime ;
//
//    }
//
//
//}