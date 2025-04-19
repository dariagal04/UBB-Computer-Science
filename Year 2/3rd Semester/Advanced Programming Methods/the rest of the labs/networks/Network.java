package src.ubb.javafxlab.networks;

import src.ubb.javafxlab.domain.*;
import  src.ubb.javafxlab.domain.validators.ValidationException;
import  src.ubb.javafxlab.repository.database.FriendshipRepoDB;
import  src.ubb.javafxlab.repository.database.UserRepoDB;
import src.ubb.javafxlab.utils.Observer;
import src.ubb.javafxlab.utils.events.UtilizatorEntityChangeEvent;
import src.ubb.javafxlab.utils.paging.Page;
import src.ubb.javafxlab.utils.paging.Pageable;

import java.util.*;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

import static java.util.Arrays.stream;

public class Network {
    //private final InMemoryRepository<Long,Utilizator> repositoryUtilizator;
    //private final InMemoryRepository<Long, Prietenie>repositoryPrietenie;

    private final UserRepoDB repositoryUtilizator;
    private final FriendshipRepoDB repositoryPrietenie;
    private final List<Observer<UtilizatorEntityChangeEvent>> observers;

    public Network(UserRepoDB repositoryUtilizator, FriendshipRepoDB repositoryPrietenie) {
        this.repositoryUtilizator = repositoryUtilizator;
        this.repositoryPrietenie = repositoryPrietenie;
        observers = new ArrayList<>();
    }
//    public Network(InMemoryRepository<Long, Utilizator> repositoryUtilizator, InMemoryRepository<Long, Prietenie> repositoryPrietenie) {
//        this.repositoryUtilizator = repositoryUtilizator;
//        this.repositoryPrietenie = repositoryPrietenie;
//    }

    public Iterable<Utilizator> getUtilizatori() {
        return repositoryUtilizator.findAll();
    }

    public Long getnewUtilizatorId() {
        Long id = 0L;
        for(Utilizator utilizator : repositoryUtilizator.findAll()) {
            id = utilizator.getId();
        }
        id++;
        return id;
    }


    public Utilizator findUtilizator(Long id) {
        return repositoryUtilizator.findOne(id).orElseThrow(() -> new ValidationException("No user"));
    }

    public Utilizator findUtilizatorUsername(String username) {
        return repositoryUtilizator.findByUserName(username).orElseThrow(() -> new ValidationException("No user"));
    }

    public Utilizator addUtilizator(Utilizator utilizator) {
        utilizator.setId(getnewUtilizatorId());
        repositoryUtilizator.save(utilizator);
        return utilizator;
    }




    public Iterable<Prietenie> getPrietenii() {
        return repositoryPrietenie.findAll();
    }




    public Long getnewPrietenie() {
        Long id = 0L;
        for(Prietenie prietenie : repositoryPrietenie.findAll()) {
            id = prietenie.getId();
        }
        id++;
        return id;
    }

    public Utilizator removeUtilizator(Long id) {
        Utilizator utilizator = null;
        try{
            utilizator = repositoryUtilizator.findOne(id).orElseThrow(() -> new ValidationException("User doesn't exist!"));
            if(utilizator != null) {
                Vector<Long> del = new Vector<>();
                getPrietenii().forEach(prietenie ->  {
                    if(prietenie.getUserId2().equals(id) || prietenie.getUserId1().equals(id)) {
                        del.add(prietenie.getId());
                    }
                });

//                del.forEach(repositoryPrietenie::delete);
//                repositoryUtilizator.delete(id);
                Utilizator newUtilizator = repositoryUtilizator.delete(id).orElseThrow(() -> new ValidationException("User doesn't exist!"));
                for(Utilizator prieten: utilizator.getPrieteni())
                    prieten.removePrieten(utilizator);
                return utilizator;
            }
            throw new IllegalArgumentException("User doesn't exist");
        }
        catch(IllegalArgumentException e){
            System.out.println("Illegal argument");
        }
        return utilizator;
    }


    public void addPrietenie(Prietenie prietenie) {
        Utilizator utilizator1 = null;
        Utilizator utilizator2 = null;
        try {
            utilizator1 = repositoryUtilizator.findOne(prietenie.getUserId1()).orElseThrow(ValidationException::new);
            utilizator2 = repositoryUtilizator.findOne(prietenie.getUserId2()).orElseThrow(ValidationException::new);
        } catch (ValidationException v) {
            System.out.println();
        }
        if(getPrietenii()!=null) {
            getPrietenii().forEach(p -> {
                if(p.getUserId1().equals(prietenie.getUserId1()) && p.getUserId2().equals(prietenie.getUserId2())) {
                    throw new ValidationException("Prietenie already exists");
                }
            });
            if(repositoryUtilizator.findOne(prietenie.getUserId1()) == null || repositoryUtilizator.findOne(prietenie.getUserId2()) == null) {
                throw new ValidationException("User doesn't exist");
            }
            if(prietenie.getUserId1().equals((prietenie.getUserId2())))
                throw new ValidationException("Id is the same");
        }

        prietenie.setId(getnewPrietenie());
        //repositoryPrietenie.save(prietenie);
        assert utilizator1 != null;
        utilizator1.addPrieten(utilizator2);
        assert utilizator2 != null;
        utilizator2.addPrieten(utilizator1);
        repositoryPrietenie.save(prietenie);
    }

    public List<Utilizator> getListFriends(Utilizator user){
        List<Utilizator> friends = new ArrayList<>();
        getPrietenii().forEach(friendship -> {
            if(friendship.getUserId1().equals(user.getId())){
                friends.add(findUtilizator(friendship.getUserId2()));
            }else if(friendship.getUserId2().equals(user.getId())){
                friends.add(findUtilizator(friendship.getUserId1()));
            }
        });
        return friends;
    }



    public void  removePrietenie(Long prietenieId1, Long prietenieId2) {
        Utilizator utilizator1 = null;
        Utilizator utilizator2 = null;
        try {
            utilizator1 = repositoryUtilizator.findOne(prietenieId1).orElseThrow(() -> new ValidationException("User with id " + prietenieId1 + " doesn't exist!"));
            utilizator2 = repositoryUtilizator.findOne(prietenieId2).orElseThrow(() -> new ValidationException("User with id " + prietenieId2 + " doesn't exist!"));
        } catch (ValidationException v) {
            System.out.println();
        }
        Long id=0L;
        for(Prietenie p : repositoryPrietenie.findAll()) {
            if (p.getUserId2().equals(prietenieId2) && p.getUserId1().equals(prietenieId1) || (p.getUserId1().equals(prietenieId2)) && p.getUserId2().equals(prietenieId1)) {
                id = p.getId();
            }
        }
        if(id == 0L)
            throw new IllegalArgumentException("Prietenie doesn't exist");
        repositoryPrietenie.delete(id);

        utilizator1.removePrieten(utilizator2);
        utilizator2.removePrieten(utilizator1);

    }

    public void addObserver(Observer<UtilizatorEntityChangeEvent> e){
        observers.add(e);
    }






    public Optional<Utilizator> authenticate(String userName, String password) {
        Optional<Utilizator> user = repositoryUtilizator.findByUserName(userName);
        if (user != null  && user.get().getPassword().equals(password)) {
            return user;
        }
        return Optional.empty();
    }




//    public List<Message> getMessagesBetweenUsers(Utilizator user1, Utilizator user2) {
//        Collection<Message> messagesCollection = (Collection<Message>) getMessages(); // Get messages as a Collection
//        List filteredMessages= messagesCollection.stream()
//                .filter(message ->
//                        (message.getIdSender().equals(user1.getId()) && message.getIdReceiver().equals(user2.getId())) ||
//                                (message.getIdSender().equals(user2.getId()) && message.getIdReceiver().equals(user1.getId()))
//                )
//                .collect(Collectors.toList());
//        List<Message> allMessages = filteredMessages.stream()
//                .flatMap(message -> getMessageWithReplies(message).stream())
//                .collect(Collectors.toList());
//        return allMessages;
//
//    }




    //////
    public Long getnewMessageId() {
        Long id = 0L;
        for(Message message : repositoryPrietenie.findAllMessages()) {
            id = message.getId();
        }
        id++;
        return id;
    }

    public Message addMessage(Message message) {
        message.setId(getnewMessageId());
        repositoryPrietenie.addMessage(message);
        return message;
    }

    public Iterable<Message> getMessages() {
        return repositoryPrietenie.findAllMessages();
    }

    public List<Message> getMessagesBetweenUsers(Utilizator user1, Utilizator user2) {
        Collection<Message> messagesCollection = (Collection<Message>) getMessages(); // Get messages as a Collection

        List<Message> filteredMessages = messagesCollection.stream()
                .filter(message ->
                        (message.getIdSender().equals(user1.getId()) && message.getIdReceiver().equals(user2.getId())) ||
                                (message.getIdSender().equals(user2.getId()) && message.getIdReceiver().equals(user1.getId()))
                )
                .collect(Collectors.toList());

        List<Message> allMessages = filteredMessages.stream()
                .flatMap(message -> getMessageWithReplies(message).stream())
                .collect(Collectors.toList());

        return allMessages;
    }
    private List<Message> getMessageWithReplies(Message message) {
        List<Message> result = new ArrayList<>();
        result.add(message);

        Message reply = message.getReply();
        while (reply != null) {
            result.add(reply);
            reply = reply.getReply();
        }

        return result;
    }


    ///////
    public CererePrietenie findCerere(Long idSender) {
        return repositoryPrietenie.findOneCerere(idSender).orElseThrow(() -> new ValidationException("No cerere"));
    }

    public CererePrietenie addCerere(CererePrietenie cerere) {
        repositoryPrietenie.addFriendRequest(cerere);
        return cerere;
    }

    public Iterable<CererePrietenie> getCereriPrietenie() {
        return repositoryPrietenie.findAllCereri();
    }


    public CererePrietenie removeCerere(Long id1, Long id2) {
        try {
            CererePrietenie cererePrietenie = repositoryPrietenie.findOneCerere(id1)
                    .orElseThrow(() -> new ValidationException("Cerere doesn't exist!"));

            List<Long> idsToDelete = new ArrayList<>();
            getCereriPrietenie().forEach(cerere -> {
                if (cerere.getIdSender().equals(id1) && cerere.getIdReceiver().equals(id2)) {
                    idsToDelete.add(cerere.getIdSender());
                }
            });


            idsToDelete.forEach(repositoryPrietenie::deleteCerere);

            return cererePrietenie;
        } catch (ValidationException e) {
            System.out.println("Validation failed: " + e.getMessage());
        } catch (IllegalArgumentException e) {
            System.out.println("Illegal argument: " + e.getMessage());
        }

        return null;
    }




    public List<UserStatus> getListCereri(Utilizator user){
        List<UserStatus> cereri = new ArrayList<>();
        getCereriPrietenie().forEach(cerere -> {
            if(cerere.getIdReceiver().equals(user.getId())) {
                Utilizator utilizator = findUtilizator(cerere.getIdSender());
                UserStatus userStatus = new UserStatus(utilizator.getId(),utilizator.getFirstName(),utilizator.getLastName(),utilizator.getUserName(),cerere.getSentDate(),cerere.getStatus());
                cereri.add(userStatus);
            }
        });

        return cereri;
    }

    public Page<Utilizator> getPaginatedUtilizatori(int pageNumber, int pageSize) {
        Pageable pageable = new Pageable(pageNumber, pageSize);
        return repositoryUtilizator.findAll(pageable);
    }

    public Page<Prietenie> getPaginatedFriends2(Utilizator user,int pageNumber, int pageSize) {
        Pageable pageable = new Pageable(pageNumber, pageSize);
        return repositoryPrietenie.findAllUserFriends(pageable, user.getId());
    }


    public Page<Utilizator> getPaginatedFriends(Utilizator user, int pageNumber, int pageSize) {
        // Retrieve all friendships
        List<Prietenie> allFriendships = (List<Prietenie>) getPrietenii();
        List<Prietenie> userFriendships = new ArrayList<>();

        // Filter the friendships for the given user
        for (Prietenie friendship : allFriendships) {
            if (friendship.getUserId1().equals(user.getId()) || friendship.getUserId2().equals(user.getId())) {
                userFriendships.add(friendship);
            }
        }

        // Calculate pagination indexes
        int fromIndex = pageNumber * pageSize;
        int toIndex = Math.min(fromIndex + pageSize, userFriendships.size());

        // Paginate the friendships
        List<Prietenie> pagedFriendships = userFriendships.subList(fromIndex, toIndex);

        // Convert the friendships to a list of users
        List<Utilizator> usersOnPage = new ArrayList<>();
        for (Prietenie friendship : pagedFriendships) {
            if (friendship.getUserId1().equals(user.getId())) {
                usersOnPage.add(findUtilizator(friendship.getUserId2()));  // Get the second user in the friendship
            } else {
                usersOnPage.add(findUtilizator(friendship.getUserId1()));  // Get the first user in the friendship
            }
        }

        // Return a Page object containing the users on this page and the total number of friendships
        return new Page<>(usersOnPage, userFriendships.size());
    }


    public Page<Utilizator> getListFriends(Long userId, Pageable pageable) {
        var friendshipsPage = repositoryPrietenie.findAllUserFriends(pageable, userId);

        List<Utilizator> friends = new ArrayList<>();
        for (var friendship : friendshipsPage.getElementsOnPage()) {
            Long friendId = friendship.getUserId1().equals(userId) ?
                    friendship.getUserId2() :
                    friendship.getUserId1();

            repositoryUtilizator.findOne(friendId).ifPresent(friends::add);
        }

        return new Page<>(friends, friendshipsPage.getTotalNumberOfElements());
    }



}
