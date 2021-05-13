#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024

void error_handling(char *message);

int main()
{
	int serv_sock;
	int clnt_sock;
	int serv_port = 7325;
	int str_len, i;

	struct sockaddr_in serv_addr, clnt_addr;
	socklen_t clnt_addr_size;
	char message[] = "Hello World!";

	serv_sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (serv_sock == -1)
	{
		error_handling("socket() error");
	}

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(serv_port);

	if (bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
	{
		error_handling("bind() error");
	}

	if (listen(serv_sock, 5) == -1)
	{
		error_handling("listen() error");
	}

	clnt_addr_size = sizeof(clnt_addr);

	clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_addr_size);
	if (clnt_sock == -1)
	{
		error_handling("accept() error");
	}

	write(clnt_sock, message, sizeof(message));
	
	close(clnt_sock);
	close(serv_sock);

	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
