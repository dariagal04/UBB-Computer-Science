#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <unistd.h>

#define PORT 1234
#define BUFFER_SIZE 1024

void find_positions(char *str, char ch, char *result) {
    int len = strlen(str);
    int pos_index = 0;
    for (int i = 0; i < len; i++) {
        if (str[i] == ch) {
            pos_index += sprintf(&result[pos_index], "%d ", i);
        }
    }
    if (pos_index == 0) {
        strcpy(result, "Not found");
    } else {
        result[pos_index] = '\0';
    }
}

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);
    char buffer[BUFFER_SIZE], result[BUFFER_SIZE];
    
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("Socket failed");
        return 1;
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(server_socket);
        return 1;
    }

    if (listen(server_socket, 5) < 0) {
        perror("Listen failed");
        close(server_socket);
        return 1;
    }

    printf("Server listening on port %d\n", PORT);

    while (1) {
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &addr_len);
        if (client_socket < 0) {
            perror("Accept failed");
            continue;
        }

        printf("Client connected\n");

        memset(buffer, 0, BUFFER_SIZE);
        recv(client_socket, buffer, BUFFER_SIZE, 0);

        char *str = strtok(buffer, "|");
        char ch = strtok(NULL, "|")[0];

        find_positions(str, ch, result);

        send(client_socket, result, strlen(result), 0);
        close(client_socket);
    }

    close(server_socket);
    return 0;
}
