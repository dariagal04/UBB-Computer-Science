package org.example.repository.memory;


import org.example.domain.Entity;
import org.example.domain.validators.ValidationException;
import org.example.domain.validators.Validator;
import org.example.repository.Repository;

import java.util.HashMap;
import java.util.Map;

public class InMemoryRepository<ID, E extends Entity<ID>> implements Repository<ID,E> {

    private Validator<E> validator;
    protected Map<ID,E> entities;

    public InMemoryRepository(Validator<E> validator) {
        this.validator = validator;
        entities=new HashMap<ID,E>();
    }

    @Override
    public E findOne(ID id) {
        if(id==null)
            throw new ValidationException("id can't be null");
        return entities.get(id);
    }

    @Override
    public Iterable<E> findAll() {

        return entities.values();
    }

    @Override
    public E save(E entity) throws ValidationException {

        /**
         *
         * @param entity
         *         entity must be not null
         * @return null- if the given entity is saved
         *         otherwise returns the entity (id already exists)
         * @throws ValidationException
         *            if the entity is not valid
         * @throws IllegalArgumentException
         *             if the given entity is null.     *
         */

        if(entity==null)
            throw new IllegalArgumentException("ENTITY CANNOT BE NULL");
        validator.validate(entity);
        if(entities.containsKey(entity.getId()))
            return entity;
        else{
            entities.put(entity.getId(),entity);
            return null;
        }


    }

    @Override
    public E delete(ID id) {
        if(id==null)
            throw new IllegalArgumentException("ID CANNOT BE NULL");
        return entities.remove(id);
    }

    @Override
    public E update(E entity) {
        if(entity==null)
            throw new IllegalArgumentException("ENTITY CANNOT BE NULL");
        validator.validate(entity);

        entities.put(entity.getId(),entity);

        if(entities.get(entity.getId())!=null){
            entities.put(entity.getId(),entity);
            return null;
        }
        return entity;
    }
}
