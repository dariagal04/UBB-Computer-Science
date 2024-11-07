#include <sys/types.h> 
#include <sys/socket.h> 
#include <stdio.h> 
#include <netinet/in.h> 
#include <netinet/ip.h> 
#include <string.h> 
#include <unistd.h> 
#include <arpa/inet.h> 

int main() {
    int clientSocket; 
    struct sockaddr_in serverAddress; 
    char inputString[1024]; 
    char receivedMessage[1024];

    // Crearea socketului
    clientSocket = socket(AF_INET, SOCK_STREAM, 0); 
    if (clientSocket < 0) { 
        perror("Eroare la crearea socketului client"); 
        return 1; 
    }

    
    memset(&serverAddress, 0, sizeof(serverAddress)); 
    serverAddress.sin_port = htons(2468); // Seteaza portul (2468) in ordine de byte de retea
    serverAddress.sin_family = AF_INET; // Seteaza familia de adrese la IPv4
    serverAddress.sin_addr.s_addr = inet_addr("172.30.244.61"); // Seteaza adresa IP a serverului

    // Conectarea la server
    if (connect(clientSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) < 0) {
        perror("Eroare la conectarea la server"); 
        close(clientSocket); 
        return 1; 
    }


    int bytesReceived = recv(clientSocket, receivedMessage, sizeof(receivedMessage) - 1, 0); // Primeste primul mesaj
    if (bytesReceived < 0) {
        perror("Eroare la primirea primului mesaj de la server"); 
        close(clientSocket); 
        return 1;
    }
    receivedMessage[bytesReceived] = '\0';
    printf("Primul mesaj de la server: %s\n", receivedMessage); 

    
    printf("Introduceti un sir de caractere: ");
    fgets(inputString, sizeof(inputString), stdin);

    
    if (send(clientSocket, inputString, strlen(inputString), 0) < 0) { 
        perror("Eroare la trimiterea mesajului la server"); 
        close(clientSocket); 
        return 1;
    }

    
    bytesReceived = recv(clientSocket, receivedMessage, sizeof(receivedMessage) - 1, 0);
    if (bytesReceived < 0) { 
        perror("Eroare la primirea celui de-al doilea mesaj de la server"); 
        close(clientSocket); 
        return 1;
    }
    receivedMessage[bytesReceived] = '\0';
    printf("Al doilea mesaj de la server: %s\n", receivedMessage); 

    
    printf("Introduceti un alt sir de caractere: ");
    fgets(inputString, sizeof(inputString), stdin);

   
    if (send(clientSocket, inputString, strlen(inputString), 0) < 0) { 
        perror("Eroare la trimiterea celui de-al doilea mesaj la server"); 
        close(clientSocket); 
        return 1;
    }

   
    bytesReceived = recv(clientSocket, receivedMessage, sizeof(receivedMessage) - 1, 0);
    if (bytesReceived < 0) { 
        perror("Eroare la primirea celui de-al treilea mesaj de la server"); 
        close(clientSocket); 
        return 1;
    }
    receivedMessage[bytesReceived] = '\0';
    printf("Al treilea mesaj de la server: %s\n", receivedMessage); 

    
    close(clientSocket); 
    return 0; 
}
