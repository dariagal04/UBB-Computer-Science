package src.ubb.galdaria_practic.domain;

public class Entity<ID> {
    ID id;
    public int getId() {
        return (int) id;
    }
    public void setId(ID id) {
        this.id = id;
    }
}

