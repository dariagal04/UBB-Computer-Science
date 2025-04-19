package src.ubb.galdaria_practic.service;

import src.ubb.galdaria_practic.domain.User;
import src.ubb.galdaria_practic.repository.DBRepository.UsersDbRepo;

import java.util.List;

public class UserService {
    private final UsersDbRepo usersDbRepo;

    public UserService(UsersDbRepo usersDbRepo) {
        this.usersDbRepo = usersDbRepo;
    }

    public User findByEmail(String email) {
        return usersDbRepo.findOne(email);
    }

    public List<User> findAll() {
        return usersDbRepo.findAll();
    }

    public User save(User user) {
        return usersDbRepo.save(user);
    }

    public void delete(String email) {
        usersDbRepo.delete(email);
    }

    public void update(User user) {
        // Implementare update dacă este necesar
    }
}
