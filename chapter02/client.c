#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

void error_handling(char *message);

int main(int argc, char *argv[])
{
	int sock;
	struct sockaddr_in oAddrServer;
	char message[30];
	int nTotalBytes = 0;
	int nNowRead = 0;
	int idx = 0;

	sock = socket(PF_INET, SOCK_STREAM, 0);
	if (sock == -1)
		error_handling("socket() error");

	memset(&oAddrServer, 0, sizeof(oAddrServer));
	oAddrServer.sin_family = AF_INET;
	oAddrServer.sin_addr.s_addr = inet_addr("127.0.0.1");
	oAddrServer.sin_port = htons(7325);

	if (connect(sock, (struct sockaddr *)&oAddrServer, sizeof(oAddrServer)) == -1)
		error_handling("connect() error!");

	// 1 byte 씩 읽는다.
	while (nNowRead = read(sock, &message[idx++], 1))
	{
		printf("nNowRead: %d, nTotalBytes: %d, idx: %d, message: %s\n", nNowRead, nTotalBytes, idx, message);
		if (nNowRead == -1)
		{
			error_handling("read() error!");
		}

		nTotalBytes += nNowRead;
	}

	printf("Message from server: %s \n", message);
	printf("Function read call count: %d \n", nNowRead);
	close(sock);
	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}