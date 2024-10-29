package org.example.repository.file;

import org.example.domain.Utilizator;
import org.example.domain.validators.Validator;

import java.io.BufferedWriter;

public class UtilizatorRepository extends AbstractFileRepository<Long, Utilizator> {
    public UtilizatorRepository(Validator<Utilizator> validator, String fileName) {
        super(validator, fileName);
    }

    @Override
    public Utilizator createEntity(String line) {
        String[] splited = line.split(";");
        Utilizator u = new Utilizator(splited[1], splited[2]);
        u.setId(Long.parseLong(splited[0]));
        return u;
    }

    @Override
    public String saveEntity(Utilizator entity) {
        return entity.getId() + ";" + entity.getFirstName() + ";" + entity.getLastName();
    }
}
