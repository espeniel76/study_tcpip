#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 30
void error_handling(char *message);

int main(int argc, char *argv[])
{
	int sock;
	char message[BUF_SIZE];
	int str_len;
	socklen_t adr_sz;

	struct sockaddr_in serv_adr, from_adr;

	sock = socket(PF_INET, SOCK_DGRAM, 0);

	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family = AF_INET;
	serv_adr.sin_addr.s_addr = inet_addr("127.0.0.1");
	serv_adr.sin_port = htons(7325);

	while (1)
	{
		// Just print screen
		fputs("Insert message(q to quit): ", stdout);

		// Get string from user input
		fgets(message, sizeof(message), stdin);

		// if user input is q or Q, then exit program
		if (!strcmp(message, "q\n") || !strcmp(message, "Q\n"))
			break;

		// send udp message
		sendto(sock, message, strlen(message), 0, (struct sockaddr *)&serv_adr, sizeof(serv_adr));
		adr_sz = sizeof(from_adr);
		str_len = recvfrom(sock, message, BUF_SIZE, 0, (struct sockaddr *)&from_adr, &adr_sz);

		message[str_len] = 0;
		printf("Message from server: %s", message);
	}
	close(sock);
	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
