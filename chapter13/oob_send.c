#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define BUF_SIZE 30
void error_handling(char *message);

int main(int argc, char *argv[])
{
	int sock;
	struct sockaddr_in recv_adr;

	if (argc != 3)
	{
		printf("Usage : %s <IP> <port>\n", argv[0]);
		exit(1);
	}

	sock = socket(PF_INET, SOCK_STREAM, 0);
	memset(&recv_adr, 0, sizeof(recv_adr));
	recv_adr.sin_family = AF_INET;
	recv_adr.sin_addr.s_addr = inet_addr(argv[1]);
	recv_adr.sin_port = htons(atoi(argv[2]));

	if (connect(sock, (struct sockaddr *)&recv_adr, sizeof(recv_adr)) == -1)
		error_handling("connect() error!");

	write(sock, "123", strlen("123"));

	send(sock, "4", strlen("4"), MSG_OOB);		// 긴급으로 데이터를 전송하고 있다.
	write(sock, "567", strlen("567"));
	send(sock, "890", strlen("890"), MSG_OOB);	// 긴급으로 데이터를 전송하고 있다.
	close(sock);
	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
