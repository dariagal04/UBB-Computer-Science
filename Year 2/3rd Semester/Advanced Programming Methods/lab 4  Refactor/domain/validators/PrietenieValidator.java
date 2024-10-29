package org.example.domain.validators;

import org.example.domain.Prietenie;
import org.example.repository.Repository;
import org.example.domain.Utilizator;
import org.example.repository.memory.InMemoryRepository;

import java.util.Optional;

public class PrietenieValidator implements Validator<Prietenie> {

    private InMemoryRepository<Long, Utilizator> repo;
    public PrietenieValidator(InMemoryRepository<Long, Utilizator> repo) {
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