package org.example.Retea;

import org.example.domain.Prietenie;
import org.example.domain.Utilizator;
import org.example.domain.validators.ValidationException;
import org.example.repository.memory.InMemoryRepository;

import java.util.Vector;

public class Network {
    private final InMemoryRepository<Long,Utilizator> repositoryUtilizator;
    private final InMemoryRepository<Long, Prietenie>repositoryPrietenie;

    public Network(InMemoryRepository<Long, Utilizator> repositoryUtilizator, InMemoryRepository<Long, Prietenie> repositoryPrietenie) {
        this.repositoryUtilizator = repositoryUtilizator;
        this.repositoryPrietenie = repositoryPrietenie;
    }

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
        return repositoryUtilizator.findOne(id);
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
        try{
            Utilizator utilizator = repositoryUtilizator.findOne(id);
            if(utilizator != null) {
                Vector<Long> del = new Vector<>();
                for(Prietenie prietenie :getPrietenii ()) {
                    if(prietenie.getUserId2().equals(id) || prietenie.getUserId1().equals(id)) {
                        del.add(prietenie.getId());
                    }
                }
                for(Long delId : del) {
                    repositoryPrietenie.delete(delId);
                }
                Utilizator newUtilizator = repositoryUtilizator.delete(id);
                for(Utilizator prieten: utilizator.getPrieteni())
                    prieten.removePrieten(utilizator);
                return newUtilizator;
            }
            throw new IllegalArgumentException("User doesn't exist");
        }
        catch(IllegalArgumentException e){
            System.out.println("User invalid");
        }
        return null;
    }

    public void addPrietenie(Prietenie prietenie) {
        Utilizator utilizator1 = repositoryUtilizator.findOne(prietenie.getUserId1());
        Utilizator utilizator2 = repositoryUtilizator.findOne(prietenie.getUserId2());
        if(getPrietenii()!=null) {
            for(Prietenie p: getPrietenii()) {
                if(p.getUserId1().equals(prietenie.getUserId1()) && p.getUserId2().equals(prietenie.getUserId2())) {
                    throw new ValidationException("Prietenie already exists");
                }
            }
            if(repositoryUtilizator.findOne(prietenie.getUserId1()) == null || repositoryUtilizator.findOne(prietenie.getUserId2()) == null) {
                throw new ValidationException("User doesn't exist");
            }
            if(prietenie.getUserId1().equals((prietenie.getUserId2())))
                throw new ValidationException("Id is the same");
        }

        prietenie.setId(getnewPrietenie());
        repositoryPrietenie.save(prietenie);
        utilizator1.addPrieten(utilizator2);
        utilizator2.addPrieten(utilizator1);
    }

    public void removePrietenie(Long prietenieId1, Long prietenieId2) {
        Utilizator utilizator1 = repositoryUtilizator.findOne(prietenieId1);
        Utilizator utilizator2 = repositoryUtilizator.findOne(prietenieId2);

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

