package src.ubb.javafxlab.repository;

import src.ubb.javafxlab.domain.Entity;
import src.ubb.javafxlab.utils.paging.Page;
import src.ubb.javafxlab.utils.paging.Pageable;

public interface PagingRepository<ID, E extends Entity<ID>> extends Repository<ID, E> {
    Page<E> findAll(Pageable pageable);
}