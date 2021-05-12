#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

void error_handling(char *message);

int main(int argc, char *argv[]) {
	int sock;

	// 서버주소 구조체
	struct sockaddr_in serv_addr;
	char message[30];
	int str_len;

	// 서버주소 파라미터 검증
	if (argc != 3) {
		printf("Usage : %s <IP> <port>\n", argv[0]);
		exit(1);
	}

	// IPV4 TCP 소켓 생성
	sock = socket(PF_INET, SOCK_STREAM, 0);
	if (sock == -1) {
		error_handling("socket() error");
	}

	// SERVER 접속 정보 구조체 초기화
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
	serv_addr.sin_port = htons(atoi(argv[2]));

	// 클라 -> 서버로 접속 시도 (서버는 이를 받으면, accept 가 일어난다.)
	if (connect(sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) == -1) {
		error_handling("connect() error!");
	}

	// 서버로부터 read 가 일어난다.
	str_len = read(sock, message, sizeof(message) - 1);
	if (str_len == -1) {
		error_handling("read() error!");
	}

	// 서버로부터 받은 메시지 출력
	printf("Message from server: %s \n", message);
	close(sock);
	return 0;
}

void error_handling(char *message) {
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
