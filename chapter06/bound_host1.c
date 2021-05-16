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
	struct sockaddr_in my_adr, your_adr;
	socklen_t adr_sz;
	int str_len, i;

	sock = socket(PF_INET, SOCK_DGRAM, 0);

	memset(&my_adr, 0, sizeof(my_adr));
	my_adr.sin_family = AF_INET;
	my_adr.sin_addr.s_addr = htonl(INADDR_ANY);
	my_adr.sin_port = htons(7325);

	if (bind(sock, (struct sockaddr *)&my_adr, sizeof(my_adr)) == -1)
		error_handling("bind() error");

	// 3회에 걸쳐 데이터를 받는다.
	// 송신/수신의 횟수가 일치 해야 한다.
	for (i = 0; i < 3; i++)
	{
		adr_sz = sizeof(your_adr);
		str_len = recvfrom(sock, message, BUF_SIZE, 0, (struct sockaddr *)&your_adr, &adr_sz);
		printf("Message %d: %s \n", i + 1, message);
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

/*
root@my_linux:/home/swyoon/tcpip# gcc bound_host1.c -o host1
root@my_linux:/home/swyoon/tcpip# ./host1 
Usage : ./host1 <port>
root@my_linux:/home/swyoon/tcpip# ./host1 9190
Message 1: Hi! 
Message 2: I'm another UDP host! 
Message 3: Nice to meet you 
root@my_linux:/home/swyoon/tcpip# 
*/
