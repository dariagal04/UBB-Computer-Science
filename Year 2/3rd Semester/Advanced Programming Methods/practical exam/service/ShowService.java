package src.ubb.galdaria_practic.service;

import src.ubb.galdaria_practic.domain.Show;
import src.ubb.galdaria_practic.repository.DBRepository.ShowsDbRepo;

import java.time.LocalDateTime;
import java.util.List;

public class ShowService {
    private final ShowsDbRepo showDbRepo;

    public ShowService(ShowsDbRepo showDbRepo) {
        this.showDbRepo = showDbRepo;
    }

    public Show findById(Long id) {
        return showDbRepo.findOne(id);
    }

    public List<Show> findAll() {
        return showDbRepo.findAll();
    }

    public Show save(Show show) {
        return showDbRepo.save(show);
    }

    public void delete(Long id) {
        showDbRepo.delete(id);
    }

    public void update(Show show) {
        // Implementare update dacă este necesar
    }

    public boolean isOverlapping(LocalDateTime startDate, int duration) {
        List<Show> shows = showDbRepo.findAll();

        LocalDateTime endDate = startDate.plusMinutes(duration);

        for (Show show : shows) {
            LocalDateTime showStart = show.getStartDate();
            LocalDateTime showEnd = showStart.plusMinutes(show.getDurationMinutes());

            if (startDate.isBefore(showEnd) && endDate.isAfter(showStart)) {
                return true; // Se suprapune cu alt spectacol
            }
        }
        return false;
    }

}
