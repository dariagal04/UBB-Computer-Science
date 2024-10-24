package org.example.domain;

import java.util.List;
import java.util.Objects;
import java.util.Optional;
import java.util.Vector;

public class Utilizator extends Entity<Long> {
    private String firstName;
    private String lastName;
    List<Utilizator> prieteni;

    public Utilizator(String firstName, String lastName) {
        this.firstName = firstName;
        this.lastName = lastName;
        prieteni = new Vector<Utilizator>();
    }

    public String getFirstName() {
        return firstName;
    }

    public void setFirstName(String firstName) {
        this.firstName = firstName;
    }

    public String getLastName() {
        return lastName;
    }

    public void setLastName(String lastName) {
        this.lastName = lastName;
    }

    public void addPrieten(Utilizator user){
        prieteni.add(user);
    }

    public void removePrieten(Utilizator user){
        prieteni.remove(user);
    }

    public List<Utilizator> getPrieteni() {
        return prieteni;
    }

    @Override
    public String toString() {
        return "Utilizator{" +
                "firstName='" + firstName + '\'' +
                ", lastName='" + lastName + '\'' +
                ", friends=" + prieteni +'\''+
                '}';
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Utilizator)) return false;
        Utilizator that = (Utilizator) o;
        return getFirstName().equals(that.getFirstName()) &&
                getLastName().equals(that.getLastName()) &&
                getPrieteni().equals(that.getPrieteni());
    }

    @Override
    public int hashCode() {
        return Objects.hash(getFirstName(), getLastName(), getPrieteni());
    }
}