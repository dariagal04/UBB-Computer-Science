package src.mpp2024.lab5.repository;

import src.mpp2024.lab5.model.Identifiable;

import java.util.Collection;

public interface Repository<Tid, T extends Identifiable<Tid>> {
    T  add(T elem);
    void delete(T elem);
    void update(T elem, Tid id);
    T findById(Tid id);
    Iterable<T> findAll();
    Collection<T> getAll();
}
