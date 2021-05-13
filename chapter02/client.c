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
	int str_len = 0;
	int idx = 0, read_len = 0;

	sock = socket(PF_INET, SOCK_STREAM, 0);
	if (sock == -1)
		error_handling("socket() error");

	memset(&oAddrServer, 0, sizeof(oAddrServer));
	oAddrServer.sin_family = AF_INET;
	oAddrServer.sin_addr.s_addr = inet_addr("127.0.0.1");
	oAddrServer.sin_port = htons(7325);

	if (connect(sock, (struct sockaddr *)&oAddrServer, sizeof(oAddrServer)) == -1)
		error_handling("connect() error!");

	while (read_len = read(sock, &message[idx++], 1))
	{
		printf("%d %d %d %s\n", read_len, str_len, idx, message);
		if (read_len == -1)
		{
			error_handling("read() error!");
		}

		str_len += read_len;
	}

	printf("Message from server: %s \n", message);
	printf("Function read call count: %d \n", str_len);
	close(sock);
	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}