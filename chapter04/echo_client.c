#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024
#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 7325

void error_handling(char *message);

int main(int argc, char *argv[])
{
	int nSock;
	char message[BUF_SIZE];
	int nSizeString;
	struct sockaddr_in oSockServer;

	nSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (nSock == -1)
	{
		error_handling("socket error");
	}

	memset(&oSockServer, 0, sizeof(oSockServer));
	oSockServer.sin_family = AF_INET;
	oSockServer.sin_addr.s_addr = inet_addr(SERVER_IP);
	oSockServer.sin_port = htons(SERVER_PORT);

	if (connect(nSock, (struct sockaddr *)&oSockServer, sizeof(oSockServer)) == -1)
	{
		error_handling("connect error");
	}
	else
	{
		puts("Connected...");
	}

	while (1)
	{
		fputs("Input message(Q to quit): ", stdout);
		fgets(message, BUF_SIZE, stdin);

		if (!strcmp(message, "q\n") || !strcmp(message, "Q\n"))
		{
			break;
		}

		write(nSock, message, strlen(message));
		nSizeString = read(nSock, message, BUF_SIZE - 1);
		message[nSizeString] = 0;
		printf("Message from server: %s", message);
	}
	close(nSock);

	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}