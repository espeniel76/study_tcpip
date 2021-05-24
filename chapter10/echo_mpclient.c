#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 30
void error_handling(char *message);
void read_routine(int sock, char *buf);
void write_routine(int sock, char *buf);

int main(int argc, char *argv[])
{
	int sock;
	pid_t pid;
	char buf[BUF_SIZE];
	struct sockaddr_in serv_adr;

	sock = socket(PF_INET, SOCK_STREAM, 0);
	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family = AF_INET;
	serv_adr.sin_addr.s_addr = inet_addr("127.0.0.1");
	serv_adr.sin_port = htons(7325);

	if (connect(sock, (struct sockaddr *)&serv_adr, sizeof(serv_adr)) == -1)
		error_handling("connect() error!");

	pid = fork();
	/**
	 * @brief Construct a new if object
	 * 부모/자식 프로세스로 읽기/쓰기 루틴 분할
	 */
	if (pid == 0)
	{
		write_routine(sock, buf);
	}
	else
	{
		read_routine(sock, buf);
	}

	close(sock);
	return 0;
}

void read_routine(int sock, char *buf)
{
	while (1)
	{
		int str_len = read(sock, buf, BUF_SIZE);
		if (str_len == 0)
			return;

		buf[str_len] = 0;
		printf("Message from server: %s", buf);
	}
}
void write_routine(int sock, char *buf)
{
	while (1)
	{
		fgets(buf, BUF_SIZE, stdin);
		if (!strcmp(buf, "q\n") || !strcmp(buf, "Q\n"))
		{
			/**
			 * @brief Construct a new shutdown object
			 * 서버로의 EOF 전달을 위해서 shutdown 함수가 호출되었다.
			 * 파일 디스크립터가 복사된 상황이므로, 한번의 close 함수 호출로 EOF의 전달을 기대할 수 없다.
			 * 따라서 반드시 shutdown 함수 호출을 통해서 EOF의 전달을 별도로 명시해야 한다.
			 */
			shutdown(sock, SHUT_WR);
			return;
		}
		write(sock, buf, strlen(buf));
	}
}
void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}