#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int main() {
  int c;
  struct sockaddr_in server;
  uint16_t n,nr1,nr2,j;

  c = socket(AF_INET, SOCK_STREAM, 0);
  if (c < 0) {
    printf("Eroare la crearea socketului client\n");
    return 1;
  }

  memset(&server, 0, sizeof(server));
  server.sin_port = htons(1234);
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = inet_addr("127.0.0.1");

  if (connect(c, (struct sockaddr *) &server, sizeof(server)) < 0) {
    printf("Eroare la conectarea la server\n");
    return 1;
  }
printf("nr1 = ");
  scanf("%hu", &nr1);
  int cp1 = nr1;
  nr1 = htons(nr1);
  send(c, &nr1, sizeof(nr1), 0);
  for(int i = 1;i<=cp1;i++){
      scanf("%hu", &j);
      j = htons(j);
      send(c, &j, sizeof(j), 0);
  }
  printf("nr2 = ");
  scanf("%hu", &nr2);
  int cp2 = nr2;
  nr2 = htons(nr2);
  send(c, &nr2, sizeof(nr2), 0);
  for(int i = 1;i<=cp2;i++){
      scanf("%hu", &j);
      j = htons(j);
      send(c, &j, sizeof(j), 0);
  }
  recv(c, &j, sizeof(j), 0);
  j = ntohs(j);
  for(int i =1;i<j;i++){
     recv(c, &n, sizeof(n), 0);
     n = ntohs(n);
     printf(" %hu\n", n);
  }
  close(c);
}
