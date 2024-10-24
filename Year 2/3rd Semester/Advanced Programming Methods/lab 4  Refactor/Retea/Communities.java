package org.example.Retea;

import org.example.domain.Prietenie;
import org.example.domain.Utilizator;

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
            for (Long friendId : adjacencyList.get(userId)) {
                if (!visited.containsKey(friendId)) {
                    depthFirstSearch(friendId, visited);
                }
            }
        }
    }

    private void buildAdjacencyList() {
        adjacencyList.clear();
        for (Utilizator user : communities.getUtilizatori()) {
            List<Long> friends = new ArrayList<>();
            for (Prietenie friendship : communities.getPrietenii()) {
                if (friendship.getUserId1().equals(user.getId())) {
                    friends.add(friendship.getUserId2());
                } else if (friendship.getUserId2().equals(user.getId())) {
                    friends.add(friendship.getUserId1());
                }
            }
            if (!friends.isEmpty()) {
                adjacencyList.put(user.getId(), friends);
            }
        }
    }

    public int Connect() {
        buildAdjacencyList();
        List<Long> userIds = new ArrayList<>();
        for (Utilizator user : communities.getUtilizatori()) {
            userIds.add(user.getId());
        }

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