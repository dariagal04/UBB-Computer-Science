package src.ubb.networks;

import  src.ubb.domain.Prietenie;
import  src.ubb.domain.Utilizator;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

public class Communities {
    private Network communities;
    private HashMap<Long, List<Long>> adjacencyList;

    public Communities(Network communities) {
        this.communities = communities;
        this.adjacencyList = new HashMap<>();
    }

    private void depthFirstSearch(Long userId, HashMap<Long, Boolean> visited) {
        visited.put(userId, true);
        System.out.println(userId + " " + communities.findUtilizator(userId).getFirstName() + " " + communities.findUtilizator(userId).getLastName());

        if (adjacencyList.containsKey(userId)) {
            adjacencyList.get(userId).stream().filter(x -> !visited.containsKey(x)).forEach(x -> depthFirstSearch(x, visited));
        }
    }

    private void buildAdjacencyList() {
        adjacencyList.clear();
        communities.getUtilizatori().forEach(user -> {
            List<Long> friends = new ArrayList<>();
            communities.getPrietenii().forEach(friendship->{
                if (friendship.getUserId1().equals(user.getId())) {
                    friends.add(friendship.getUserId2());
                } else if (friendship.getUserId2().equals(user.getId())) {
                    friends.add(friendship.getUserId1());
                }
            });
            if (!friends.isEmpty()) {
                adjacencyList.put(user.getId(), friends);
            }
        });
    }

    public int Connect() {
        buildAdjacencyList();
        List<Long> userIds = new ArrayList<>();
        communities.getUtilizatori().forEach(user-> {
            userIds.add(user.getId());
        });

        int numberOfCommunities = 0;
        HashMap<Long, Boolean> visited = new HashMap<>();
        for (Long userId : userIds) {
            if (!visited.containsKey(userId)) {
                depthFirstSearch(userId, visited);
                numberOfCommunities++;
                System.out.println();
            }
        }
        return numberOfCommunities;
    }

    public List<Long> MostSocial() {
        buildAdjacencyList();
        List<Long> mostSocialCommunity = new ArrayList<>();
        for (Long userId : adjacencyList.keySet()) {
            List<Long> friends = adjacencyList.get(userId);
            if (mostSocialCommunity.size() < friends.size() + 1) {
                mostSocialCommunity = new ArrayList<>(friends);
                mostSocialCommunity.add(userId);
            }
        }
        return mostSocialCommunity;
    }
}