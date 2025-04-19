package src.ubb.javafxlab.domain.validators;

import src.ubb.javafxlab.domain.Prietenie;
import src.ubb.javafxlab.repository.Repository;
import src.ubb.javafxlab.domain.Utilizator;
import src.ubb.javafxlab.repository.database.UserRepoDB;
import src.ubb.javafxlab.repository.memory.InMemoryRepository;

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