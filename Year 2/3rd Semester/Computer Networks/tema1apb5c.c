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
  uint16_t n,nr,j;
  
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
  
  printf("nr = ");
  scanf("%hu", &nr);
  nr = htons(nr);
  send(c, &nr, sizeof(nr), 0);
  recv(c, &j, sizeof(j), 0);
  for(int i =1;i<j;i++){
     recv(c, &n, sizeof(n), 0);
     n = ntohs(n);
     printf(" %hu\n", n);
  }
  close(c);
}
