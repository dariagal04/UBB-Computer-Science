package src.ubb.domain.validators;

import src.ubb.domain.Prietenie;
import src.ubb.repository.Repository;
import src.ubb.domain.Utilizator;
import src.ubb.repository.database.UserRepoDB;
import src.ubb.repository.memory.InMemoryRepository;

import java.util.Optional;

public class PrietenieValidator implements Validator<Prietenie> {

    //private InMemoryRepository<Long, Utilizator> repo;
    private UserRepoDB repo;
    public PrietenieValidator(UserRepoDB repo) {
        this.repo = repo;
    }

    @Override
    public void validate(Prietenie entity) throws ValidationException {

        Optional<Utilizator> user1 = repo.findOne(entity.getUserId1());
        Optional<Utilizator> user2 = repo.findOne(entity.getUserId2());

        if(entity.getUserId1() == null || entity.getUserId2() == null) {
            throw new ValidationException(" Id can't be null");}
        if( user1 == null || user2 == null)   {
            throw new ValidationException(" Id doesn't exist");
        }
    }
}