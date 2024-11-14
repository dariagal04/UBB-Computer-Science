#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

int main() {
    int s;
    struct sockaddr_in server, client;
    socklen_t client_len = sizeof(client);
    char letter = 'M';
    char guess;
    char response[50];

    // Create the socket
    s = socket(AF_INET, SOCK_DGRAM, 0);
    if (s < 0) {
        printf("Error creating server socket\n");
        return 1;
    }

    // Set up the server address
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(1234);
    server.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket to the address
    if (bind(s, (struct sockaddr *)&server, sizeof(server)) < 0) {
        printf("Error binding server socket\n");
        close(s);
        return 1;
    }

    printf("Server is running and waiting for client guesses...\n");

    while (1) {
        
        recvfrom(s, &guess, sizeof(guess), 0, (struct sockaddr *)&client, &client_len);

        
        if (guess == letter) {
            strcpy(response, "Felicitari");
        } else if (guess >letter) {
            strcpy(response, "Inainte");
        } else {
            strcpy(response, "Dupa");
        }

        
        sendto(s, response, strlen(response) + 1, 0, (struct sockaddr *)&client, client_len);
    }

    close(s);
    return 0;
}
