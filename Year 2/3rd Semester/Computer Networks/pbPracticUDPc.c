#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int c;
    struct sockaddr_in server;
    char guess;
    char response[50];
    socklen_t server_len = sizeof(server);

    // Create the socket
    c = socket(AF_INET, SOCK_DGRAM, 0);
    if (c < 0) {
        printf("Error creating client socket\n");
        return 1;
    }

    // Set up the server address
    memset(&server, 0, sizeof(server));
    server.sin_port = htons(1234);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    printf("Try to guess the letter (A-Z):\n");

    while (1) {
        
        printf("Guess: ");
        scanf(" %c", &guess);

        
        sendto(c, &guess, sizeof(guess), 0, (struct sockaddr *)&server, server_len);

        
        recvfrom(c, response, sizeof(response), MSG_WAITALL, (struct sockaddr *)&server, &server_len);
        
        
        printf("%s\n", response);

        
        if (strcmp(response, "Felicitari") == 0) {
            break;
        }
    }

    
    close(c);
    return 0;
}
