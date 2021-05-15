#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024
#define PORT 7325

void error_handling(char *message);

int main(int argc, char *argv[])
{
	int nSockServer;
	int nSockClient;
	char message[BUF_SIZE];
	int nSizeString;
	int i;
	struct sockaddr_in oSockServer;
	struct sockaddr_in oSockClient;
	socklen_t nClntAdrSize;

	nSockServer = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (nSockServer == -1)
	{
		error_handling("socket error");
	}

	memset(&oSockServer, 0, sizeof(oSockServer));
	oSockServer.sin_family = AF_INET;
	oSockServer.sin_addr.s_addr = htonl(INADDR_ANY);
	oSockServer.sin_port = htons(PORT);

	if (bind(nSockServer, (struct sockaddr *)&oSockServer, sizeof(oSockServer)) == -1)
	{
		error_handling("bind error");
	}

	if (listen(nSockServer, 5) == -1)
	{
		error_handling("listen error");
	}

	nClntAdrSize = sizeof(oSockClient);

	for (i = 0; i < 5; i++)
	{
		nSockClient = accept(nSockServer, (struct sockaddr *)&oSockClient, &nClntAdrSize);
		if (nSockClient == -1)
		{
			error_handling("accept error");
		}
		else
		{
			printf("Connected client %d \n", i + 1);
		}

		while ((nSizeString = read(nSockClient, message, BUF_SIZE)) != 0)
		{
			write(nSockClient, message, nSizeString);
		}

		close(nSockClient);
	}
	close(nSockServer);

	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}