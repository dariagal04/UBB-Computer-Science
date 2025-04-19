package src.ubb.javafxlab.domain;

import java.util.List;
import java.util.Objects;
import java.util.Optional;
import java.util.Vector;

public class Utilizator extends src.ubb.javafxlab.domain.Entity<Long> {
    private String firstName;
    private String lastName;
    private String userName;
    private String password;
    List<Utilizator> prieteni;

    public Utilizator(String firstName, String lastName, String password,String userName) {
        this.firstName = firstName;
        this.lastName = lastName;
        this.userName = userName;
        this.password = password;
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

    public String getUserName() {
        return userName;
    }

    public void setUserName(String userName) {
        this.userName = userName;
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    public List<Utilizator> getPrieteni() {
        return prieteni;
    }

    @Override
    public String toString() {
        return "Utilizator{" +
                "firstName='" + firstName + '\'' +
                ", lastName='" + lastName + '\'' +
                ", userName='" + userName + '\'' +
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
                getPassword().equals(that.getPassword()) &&
                getUserName().equals(that.getUserName()) &&
                getPrieteni().equals(that.getPrieteni());
    }

    @Override
    public int hashCode() {
        return Objects.hash(getFirstName(), getLastName(),getPassword(),getUserName(), getPrieteni());
    }
}