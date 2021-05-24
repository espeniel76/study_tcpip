#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 30
void error_handling(char *message);
void read_childproc(int sig);

int main(int argc, char *argv[])
{
	int serv_sock, clnt_sock;
	struct sockaddr_in serv_adr, clnt_adr;

	pid_t pid;
	struct sigaction act;
	socklen_t adr_sz;
	int str_len, state;
	char buf[BUF_SIZE];

	// 좀비 프로세스 방어코드
	act.sa_handler = read_childproc;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	state = sigaction(SIGCHLD, &act, 0);

	serv_sock = socket(PF_INET, SOCK_STREAM, 0);
	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family = AF_INET;
	serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_adr.sin_port = htons(7325);

	if (bind(serv_sock, (struct sockaddr *)&serv_adr, sizeof(serv_adr)) == -1)
		error_handling("bind() error");
	if (listen(serv_sock, 5) == -1)
		error_handling("listen() error");

	while (1)
	{
		adr_sz = sizeof(clnt_adr);

		clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_adr, &adr_sz);
		if (clnt_sock == -1)
			continue;
		else
			puts("new client connected...");

		/**
		 * @brief 
		 * accept 통해서 만들어진 소켓의 파일 디스크립터를 부모 프로세스와 자식 프로세스가
		 * 동시에 하나씩 갖게 된다.
		 */
		pid = fork();
		if (pid == -1)
		{
			close(clnt_sock);
			continue;
		}

		// 자식 프로세스 영역
		if (pid == 0)
		{
			/**
			 * @brief Construct a new close object
			 * 서버 소켓을 닫는다.
			 * 이는 자식 프로세스로 서버 소켓의 파일 디스크립터까지 복사되기 때문이다.
			 * 뭔말인지...
			 */
			close(serv_sock);
			while ((str_len = read(clnt_sock, buf, BUF_SIZE)) != 0)
			{
				write(clnt_sock, buf, str_len);
			}

			close(clnt_sock);
			puts("client disconnected...");
			return 0;
		}
		else
		{
			/**
			 * @brief Construct a new close object
			 * accept 함수호출을 통해서 만들어진 소켓의 파일디스크립터가 자식 프로세스에게 복사되었으니,
			 * 서버는 자신의 소유하고 있는 파일 디스크립터를 소멸시켜야 한다.
			 */
			close(clnt_sock);
		}
	}
	close(serv_sock);
	return 0;
}

void read_childproc(int sig)
{
	pid_t pid;
	int status;
	pid = waitpid(-1, &status, WNOHANG);
	printf("removed proc id: %d \n", pid);
}
void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}