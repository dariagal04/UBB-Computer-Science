#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <unistd.h>

#define PORT 1234
#define BUFFER_SIZE 1024

int main() {
    int client_socket;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE], str[BUFFER_SIZE], ch;

    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0) {
        perror("Socket creation error");
        return 1;
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        return 1;
    }

    printf("Enter a string: ");
    fgets(str, BUFFER_SIZE, stdin);
    str[strcspn(str, "\n")] = 0;  // remove newline character

    printf("Enter a character: ");
    scanf(" %c", &ch);

    snprintf(buffer, sizeof(buffer), "%s|%c", str, ch);

    send(client_socket, buffer, strlen(buffer), 0);
    memset(buffer, 0, BUFFER_SIZE);
    recv(client_socket, buffer, BUFFER_SIZE, 0);

    printf("Positions: %s\n", buffer);

    close(client_socket);
    return 0;
}
