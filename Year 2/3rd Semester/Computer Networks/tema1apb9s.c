#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int main() {
  int s;
  struct sockaddr_in server, client;
  int c, l;

  s = socket(AF_INET, SOCK_STREAM, 0);
  if (s < 0) {
    printf("Eroare la crearea socketului server\n");
    return 1;
  }

  memset(&server, 0, sizeof(server));
  server.sin_port = htons(1234);
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;

  if (bind(s, (struct sockaddr *) &server, sizeof(server)) < 0) {
    printf("Eroare la bind\n");
    return 1;
  }

  listen(s, 5);

  l = sizeof(client);
  memset(&client, 0, sizeof(client));
 while (1) {
    uint16_t j,n,nr1, nr2,v1[50],v2[50],v3[50];
    c = accept(s, (struct sockaddr *) &client, &l);
    printf("S-a conectat un client.\n");
    // deservirea clientului
    recv(c, &nr1, sizeof(nr1), MSG_WAITALL);
    nr1 = ntohs(nr1);
    for(int i =1; i<=nr1;i++){
       recv(c, &n, sizeof(n), MSG_WAITALL);
       n = ntohs(n);
       v1[i] = n;
    }
    recv(c, &nr2, sizeof(nr2), MSG_WAITALL);
    nr2 = ntohs(nr2);
    for(int i =1; i<=nr2;i++){
       recv(c, &n, sizeof(n), MSG_WAITALL);
       n = ntohs(n);
       v2[i] = n;
    }
    j = 1;
    for(int i=1;i<=nr1;i++){
        int count = 0;
        for(int k=1;k<=nr2;k++){
            if(v1[i] == v2[k]){
               count++;
            }
        }
        if(count == 0){
           v3[j] = v1[i];
           j++;
        }
    }
    int cp = j;
    j = htons(j);
    send(c, &j, sizeof(j), 0);
    for(int i=1;i<=cp;i++){
        v3[i] = htons(v3[i]);
        send(c, &v3[i], sizeof(v3[i]), 0);
    }
    close(c);
    // sfarsitul deservirii clientului;
  }
}
