#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
void error_handling(char *message);

int main(int argc, char *argv[])
{
	int tcp_sock, udp_sock;
	int sock_type;
	socklen_t optlen;
	int state;

	optlen = sizeof(sock_type);
	tcp_sock = socket(PF_INET, SOCK_STREAM, 0);
	udp_sock = socket(PF_INET, SOCK_DGRAM, 0);
	printf("SOCK_STREAM: %d \n", SOCK_STREAM);
	printf("SOCK_DGRM: %d \n", SOCK_DGRAM);

	// sock_type 변수에 타입 소켓 타입 정수를 얻고있다.
	state = getsockopt(tcp_sock, SOL_SOCKET, SO_TYPE, (void *)&sock_type, &optlen);
	if (state)
		error_handling("getsockopt error!");
	printf("Socket type one: %d \n", sock_type);

	// sock_type 변수에 타입 소켓 타입 정수를 얻고있다.
	state = getsockopt(udp_sock, SOL_SOCKET, SO_TYPE, (void *)&sock_type, &optlen);
	if (state)
		error_handling("getsockopt error!");
	printf("Socket type two: %d \n", sock_type);

	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}