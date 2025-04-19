package src.mpp2024.lab5.model;

public interface Identifiable<Tid> {
    Tid getID();
    void setID(Tid id);
}
