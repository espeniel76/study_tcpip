#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

void error_handling(char *message);

int main(int argc, char *argv[]) {
	int serv_sock;
	int clnt_sock;

	// 서버/클라 주소 구조체
	struct sockaddr_in serv_addr, clnt_addr;

	// 이놈은 뭐하는 놈?
	socklen_t clnt_addr_size;

	// 클라에 던져줄 메시지
	char message[] = "Hello World!";

	// 포트 인자를 제대로 할당 받지 못 했을 시
	if (argc != 2) {
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}

	// 서버 소켓 생성
	// 소켓 역시 파일로 다루어지기 때문에 반환값은 파일디스크립터(fd) 입니다.
	// 소켓을 여는데 실패하면 -1을 리턴 합니다.
	serv_sock = socket(PF_INET, SOCK_STREAM, 0);
	if (serv_sock == -1) {
		error_handling("socket() error");
	}

	// 서버 주소 구조체 초기화?
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(atoi(argv[1]));

	// 소켓을 바인딩 합니다.
	// fd 와 이 프로세스를 묶는다는 의미
	if (bind(serv_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) == -1) {
		error_handling("bind() error");
	}

	// 소켓을 통해 들어오는 연결을 듣습니다.
	if (listen(serv_sock, 5) == -1) {
		error_handling("listen() error");
	}

	// 클라주소 뭐시기...
	clnt_addr_size = sizeof(clnt_addr);

	// 클라로부터 연결을 받아들인다.
	clnt_sock = accept(serv_sock, (struct sockaddr*) &clnt_addr, &clnt_addr_size);
	if (clnt_sock == -1) {
		error_handling("accept() error");
	}

	// 클라에게 send 한다.
	write(clnt_sock, message, sizeof(message));

	// 클라 소켓을 닫는다.
	close(clnt_sock);

	// 서버 소켓을 닫는다.
	close(serv_sock);

	// 프로세스 반환
	return 0;
}

void error_handling(char *message) {
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
