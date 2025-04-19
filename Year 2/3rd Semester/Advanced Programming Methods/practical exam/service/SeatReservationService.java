package src.ubb.galdaria_practic.service;

import src.ubb.galdaria_practic.domain.SeatReservation;
import src.ubb.galdaria_practic.repository.DBRepository.SeatReservationsDbRepo;
import src.ubb.galdaria_practic.repository.DBRepository.SeatReservationsDbRepo;

import java.util.List;

public class SeatReservationService {
    private final SeatReservationsDbRepo seatReservationDbRepo;

    public SeatReservationService(SeatReservationsDbRepo seatReservationDbRepo) {
        this.seatReservationDbRepo = seatReservationDbRepo;
    }

    public SeatReservation findById(Long id) {
        return seatReservationDbRepo.findOne(id);
    }

    public List<SeatReservation> findAll() {
        return seatReservationDbRepo.findAll();
    }

    public SeatReservation save(SeatReservation seatReservation) {
        return seatReservationDbRepo.save(seatReservation);
    }

    public void delete(Long id) {
        seatReservationDbRepo.delete(id);
    }

    public void update(SeatReservation seatReservation) {
        // Implementare update dacă este necesar
    }
}
