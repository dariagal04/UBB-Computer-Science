package org.example.repository.file;

import org.example.domain.Entity;
import org.example.domain.Utilizator;
import org.example.domain.validators.Validator;
import org.example.repository.Repository;
import org.example.repository.memory.InMemoryRepository;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.Buffer;
import java.util.Optional;

public abstract class AbstractFileRepository<ID, E extends Entity<ID>> extends InMemoryRepository<ID, E>{
    private String filename;

    public AbstractFileRepository(Validator<E> validator, String fileName) {

        super(validator);
        filename=fileName;
    }


    public abstract E createEntity(String line);
    public abstract String saveEntity(E entity);
    @Override
    public Optional<E> findOne(ID id) {
        return null;
    }

    @Override
    public Iterable<E> findAll() {
        return null;
    }

    @Override
    public Optional<E> save(E entity) {
        Optional<E> e = super.save(entity);
        if (e == null)
            writeToFile();
        return e;
    }

    private void writeToFile() {

        try  ( BufferedWriter writer = new BufferedWriter(new FileWriter(filename))){
            for (E entity: entities.values()) {
                String ent = saveEntity(entity);
                writer.write(ent);
                writer.newLine();
            }
        } catch (IOException e) {
            throw new RuntimeException(e);
        }

    }

    @Override
    public Optional<E> delete(ID id) {
        return null;
    }

    @Override
    public Optional<E> update(E entity) {
        return null;
    }
}