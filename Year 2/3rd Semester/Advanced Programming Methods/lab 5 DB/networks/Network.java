package  src.ubb.networks;

import  src.ubb.domain.Prietenie;
import  src.ubb.domain.Utilizator;
import  src.ubb.domain.validators.ValidationException;
import  src.ubb.repository.database.FriendshipRepoDB;
import  src.ubb.repository.database.UserRepoDB;
import  src.ubb.repository.memory.InMemoryRepository;
import  src.ubb.repository.database.UserRepoDB;

import java.util.ArrayList;
import java.util.List;
import java.util.Optional;
import java.util.Vector;
import java.util.stream.StreamSupport;

public class Network {
    //private final InMemoryRepository<Long,Utilizator> repositoryUtilizator;
    //private final InMemoryRepository<Long, Prietenie>repositoryPrietenie;

    private final UserRepoDB repositoryUtilizator;
    private final FriendshipRepoDB repositoryPrietenie;

    public Network(UserRepoDB repositoryUtilizator, FriendshipRepoDB repositoryPrietenie) {
        this.repositoryUtilizator = repositoryUtilizator;
        this.repositoryPrietenie = repositoryPrietenie;
    }
//    public Network(InMemoryRepository<Long, Utilizator> repositoryUtilizator, InMemoryRepository<Long, Prietenie> repositoryPrietenie) {
//        this.repositoryUtilizator = repositoryUtilizator;
//        this.repositoryPrietenie = repositoryPrietenie;
//    }

    public Iterable<Utilizator> getUtilizatori() {
        return repositoryUtilizator.findAll();
    }

    public Long getnewUtilizatorId() {
        Long id = 0L;
        for(Utilizator utilizator : repositoryUtilizator.findAll()) {
            id = utilizator.getId();
        }
        id++;
        return id;
    }



    public Utilizator findUtilizator(Long id) {
        return repositoryUtilizator.findOne(id).orElseThrow(() -> new ValidationException("No user"));
    }

    public void addUtilizator(Utilizator utilizator) {
        utilizator.setId(getnewUtilizatorId());
        repositoryUtilizator.save(utilizator);
    }
    public Iterable<Prietenie> getPrietenii() {
        return repositoryPrietenie.findAll();
    }
    public Long getnewPrietenie() {
        Long id = 0L;
        for(Prietenie prietenie : repositoryPrietenie.findAll()) {
            id = prietenie.getId();
        }
        id++;
        return id;
    }

    public Utilizator removeUtilizator(Long id) {
        Utilizator utilizator = null;
        try{
            utilizator = repositoryUtilizator.findOne(id).orElseThrow(() -> new ValidationException("User doesn't exist!"));
            if(utilizator != null) {
                Vector<Long> del = new Vector<>();
                getPrietenii().forEach(prietenie ->  {
                    if(prietenie.getUserId2().equals(id) || prietenie.getUserId1().equals(id)) {
                        del.add(prietenie.getId());
                    }
                });

//                del.forEach(repositoryPrietenie::delete);
//                repositoryUtilizator.delete(id);
                Utilizator newUtilizator = repositoryUtilizator.delete(id).orElseThrow(() -> new ValidationException("User doesn't exist!"));
                for(Utilizator prieten: utilizator.getPrieteni())
                    prieten.removePrieten(utilizator);
                return utilizator;
            }
            throw new IllegalArgumentException("User doesn't exist");
        }
        catch(IllegalArgumentException e){
            System.out.println("Illegal argument");
        }
        return utilizator;
    }

    public void addPrietenie(Prietenie prietenie) {
        Utilizator utilizator1 = null;
        Utilizator utilizator2 = null;
        try {
            utilizator1 = repositoryUtilizator.findOne(prietenie.getUserId1()).orElseThrow(ValidationException::new);
            utilizator2 = repositoryUtilizator.findOne(prietenie.getUserId2()).orElseThrow(ValidationException::new);
        } catch (ValidationException v) {
            System.out.println();
        }
        if(getPrietenii()!=null) {
            getPrietenii().forEach(p -> {
                if(p.getUserId1().equals(prietenie.getUserId1()) && p.getUserId2().equals(prietenie.getUserId2())) {
                    throw new ValidationException("Prietenie already exists");
                }
            });
            if(repositoryUtilizator.findOne(prietenie.getUserId1()) == null || repositoryUtilizator.findOne(prietenie.getUserId2()) == null) {
                throw new ValidationException("User doesn't exist");
            }
            if(prietenie.getUserId1().equals((prietenie.getUserId2())))
                throw new ValidationException("Id is the same");
        }

        prietenie.setId(getnewPrietenie());
        //repositoryPrietenie.save(prietenie);
        assert utilizator1 != null;
        utilizator1.addPrieten(utilizator2);
        assert utilizator2 != null;
        utilizator2.addPrieten(utilizator1);
        repositoryPrietenie.save(prietenie);
    }

    public List<Utilizator> getListFriends(Utilizator user){
        List<Utilizator> friends = new ArrayList<>();
        getPrietenii().forEach(friendship -> {
            if(friendship.getUserId1().equals(user.getId())){
                friends.add(findUtilizator(friendship.getUserId2()));
            }else if(friendship.getUserId2().equals(user.getId())){
                friends.add(findUtilizator(friendship.getUserId1()));
            }
        });
        return friends;
    }

//public void addPrietenie(Prietenie friendship) {
//    if (getPrietenii() != null) {
//        getPrietenii().forEach(f -> {
//            if (f.getUserId1().equals(friendship.getUserId1()) && f.getUserId2().equals(friendship.getUserId2())) {
//                throw new ValidationException("The friendship already exist! ");
//            }
//        });
//        if (repositoryUtilizator.findOne(friendship.getUserId1()).isEmpty() || repositoryUtilizator.findOne(friendship.getUserId2()).isEmpty()) {
//            throw new ValidationException("User doesn't exist! ");
//        }
//        if (friendship.getUserId1().equals(friendship.getUserId2()))
//            throw new ValidationException("IDs can't be the same!!! ");
//    }
//
//    friendship.setId(getnewPrietenie());
//    repositoryPrietenie.save(friendship);
//
//}

    public void removePrietenie(Long prietenieId1, Long prietenieId2) {
        Utilizator utilizator1 = null;
        Utilizator utilizator2 = null;
        try {
            utilizator1 = repositoryUtilizator.findOne(prietenieId1).orElseThrow(() -> new ValidationException("User with id " + prietenieId1 + " doesn't exist!"));
            utilizator2 = repositoryUtilizator.findOne(prietenieId2).orElseThrow(() -> new ValidationException("User with id " + prietenieId2 + " doesn't exist!"));
        } catch (ValidationException v) {
            System.out.println();
        }
        Long id=0L;
        for(Prietenie p : repositoryPrietenie.findAll()) {
            if (p.getUserId2().equals(prietenieId2) && p.getUserId1().equals(prietenieId1) || (p.getUserId1().equals(prietenieId2)) && p.getUserId2().equals(prietenieId1)) {
                id = p.getId();
            }
        }
        if(id == 0L)
            throw new IllegalArgumentException("Prietenie doesn't exist");
        repositoryPrietenie.delete(id);

        utilizator1.removePrieten(utilizator2);
        utilizator2.removePrieten(utilizator1);

    }

}
