package src.ubb.javafxlab.UI;

import src.ubb.javafxlab.networks.Communities;
import src.ubb.javafxlab.networks.Network;
import src.ubb.javafxlab.domain.Prietenie;
import src.ubb.javafxlab.domain.Utilizator;
import src.ubb.javafxlab.domain.validators.ValidationException;

import java.time.LocalDateTime;
import java.util.List;
import java.util.Scanner;

public class Consola {
    private Network network;
    private Communities communities;

    public Consola(Network network) {
        this.network = network;
        this.communities = new Communities(network);
    }

    void Meniu() {
        System.out.println("Meniu");
        System.out.println("1. Add user");
        System.out.println("2. Add friendship");
        System.out.println("3. Remove user");
        System.out.println("4. Remove friendship");
        System.out.println("5. Show users");
        System.out.println("6. Show friendships");
        System.out.println("7. Show communities");
        System.out.println("8. Most Social community");
        System.out.println("9. Exit");
    }

    void addUtilizator() {
        System.out.println("Add utilizator");
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter utilizator first name: ");
        String firstName = scanner.nextLine();
        System.out.println("Enter utilizator last name: ");
        String lastName = scanner.nextLine();
        System.out.println("Enter utilizator username: ");
        String username = scanner.nextLine();
        System.out.println("Enter utilizator password: ");
        String password = scanner.nextLine();
        try {
            network.addUtilizator(new Utilizator(firstName, lastName, password,username));
        } catch (ValidationException e) {
            System.out.println("Utilizator invalid");
        } catch (IllegalArgumentException e) {
            System.out.println("Utilizator invalid");
        }
    }

    void addFriendship() {
        System.out.println("Add friendship");
        Scanner scanner = new Scanner(System.in);
        System.out.println("First utilizator ID: ");
        String utilizatorID1 = scanner.nextLine();
        System.out.println("Second utilizator ID: ");
        String utilizatorID2 = scanner.nextLine();
        try {
            Long id1 = Long.parseLong(utilizatorID1);
            Long id2 = Long.parseLong(utilizatorID2);
            LocalDateTime date = LocalDateTime.now();
            network.addPrietenie(new Prietenie(id1, id2, date));
        } catch (ValidationException e) {
            System.out.println("Friendship is invalid!");
        } catch (IllegalArgumentException e) {
            System.out.println("ID must be a number! It can't contain letters or symbols!");
        }
    }

    void removeUtilizator() {
        System.out.println("Remove utilizator");
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter utilizatorID: ");
        String utilizatorID = scanner.nextLine();
        try {
            Long id = Long.parseLong(utilizatorID);
            Utilizator u = network.findUtilizator(id);
            if(u == null) throw new ValidationException("Utilizator not found");
            network.removeUtilizator(id);
        } catch (IllegalArgumentException e) {
            System.out.println("Utilizator id invalid");
        }
    }

    void removeFriendship() {
        System.out.println("Remove friendship");
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter first utilizatorID: ");
        String utilizatorID1 = scanner.nextLine();
        System.out.println("Enter second utilizatorID: ");
        String utilizatorID2 = scanner.nextLine();
        try {
            Long id1 = Long.parseLong(utilizatorID1);
            Long id2 = Long.parseLong(utilizatorID2);
            network.removePrietenie(id1, id2);
        } catch (IllegalArgumentException e) {
            System.out.println("ID must be a number! It can't contain letters or symbols!");
        }
    }

    void showUsers() {
        System.out.println("Show users");
        for (Utilizator utilizator : network.getUtilizatori()) {
            System.out.println(utilizator.getId() + " " + utilizator.getFirstName() + " " + utilizator.getLastName());
        }
    }

    void showFriendships() {
        System.out.println("Show friendships");
        for (Utilizator utilizator : network.getUtilizatori()) {
            System.out.println(utilizator.getFirstName() + " " + utilizator.getLastName() + " with Friends:" + network.getListFriends(utilizator).size());
//            if (!utilizator.getPrieteni().isEmpty()) {
//                for (Utilizator prieten : utilizator.getPrieteni()) {
//                    System.out.println("ID:" + prieten.getId() + " " + prieten.getFirstName() + " " + prieten.getLastName());
//                }
//            }
            network.getListFriends(utilizator).forEach(friend ->{
                System.out.println(friend.getId() + ":" + friend.getFirstName() + " " + friend.getLastName());
            });
        }
    }

    void showCommunities() {
        System.out.println("Show communities");
        int NbCommunities = communities.Connect();
        System.out.println("Number of communities: " + NbCommunities);
    }

    void showMostSocialCommunities() {
        System.out.println("Show most social community");
        List<Long> most = communities.MostSocial();
        most.forEach(System.out::println);
    }

    public void run() {
        Scanner scanner = new Scanner(System.in);
        boolean run = true;
        while (run) {
            Meniu();
            String command = scanner.nextLine();
            switch (command) {
                case "1":
                    addUtilizator();
                    break;
                case "2":
                    addFriendship();
                    break;
                case "3":
                    removeUtilizator();
                    break;
                case "4":
                    removeFriendship();
                    break;
                case "5":
                    showUsers();
                    break;
                case "6":
                    showFriendships();
                    break;
                case "7":
                    showCommunities();
                    break;
                case "8":
                    showMostSocialCommunities();
                    break;
                case "9":
                    run = false;
                    break;
                default:
                    System.out.println("Invalid command");
                    break;
            }
        }
    }
}