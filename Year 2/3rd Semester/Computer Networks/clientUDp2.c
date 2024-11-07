#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>

int main() {
	int c;
	struct sockaddr_in server;
	char msg[100];
	
	c = socket(AF_INET, SOCK_DGRAM, 0);
	
	if (c < 0) {
		printf("Eroare la crearea socketului...\n");;
		return 1;
	}
	
	memset(&server, 0, sizeof(server));
	server.sin_port = htons(1234);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	printf("Dati mesajul: ");
	fgets(msg,  sizeof(msg), stdin);
	printf("Trimit catre server stringul: %s\n", msg);
	sendto(c, msg, sizeof(msg), 0, (struct sockaddr *) &server, sizeof(server));
	printf("Am trimis!\n");



	char backMsg[100];
	printf("Incerc sa primesc ceva!\n");
	int l = sizeof(server);
	recvfrom(c, &backMsg, sizeof(backMsg), 0, (struct sockaddr *) &server, &l);
	printf("Serverul mi-a raspuns cu: '%s' pe portul: %d\n", backMsg, ntohs(server.sin_port));
        int a,b;

	printf("Dati mesajul: a=");
	//fgets(msg, sizeof(msg), stdin);
        scanf("%hu",a);
	int code = sendto(c, msg, sizeof(msg), 0, (struct sockaddr *) &server, sizeof(server));

	printf("Am trimis %d octeti (%s)\n", code, msg);


 	printf("Incerc sa primesc ceva!\n");
        recvfrom(c, &backMsg, sizeof(backMsg), 0, (struct sockaddr *) &server, &l);
        printf("Serverul mi-a raspuns cu: '%s' pe portul: %d\n", backMsg, ntohs(server.sin_port));


	close(c);
}
