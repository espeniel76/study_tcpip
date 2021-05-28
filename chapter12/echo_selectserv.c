#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/select.h>

#define BUF_SIZE 100
void error_handling(char *buf);

int main(int argc, char *argv[])
{
	int serv_sock, clnt_sock;
	struct sockaddr_in serv_adr, clnt_adr;
	struct timeval timeout;
	fd_set reads, cpy_reads;

	socklen_t adr_sz;
	int fd_max, str_len, fd_num, i;
	char buf[BUF_SIZE];

	serv_sock = socket(PF_INET, SOCK_STREAM, 0);
	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family = AF_INET;
	serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_adr.sin_port = htons(7325);

	if (bind(serv_sock, (struct sockaddr *)&serv_adr, sizeof(serv_adr)) == -1)
		error_handling("bind() error");
	if (listen(serv_sock, 5) == -1)
		error_handling("listen() error");

	FD_ZERO(&reads);

	/**
	 * select 함수의 두 번째 인자로 전달될 fd_set형 변수 reads 에 서버 소켓을 등록하고 있다.
	 * 이로써 데이터의 수신여부를 관찰하는 관찰대상에 서버 소켓이 포함 되었다.
	 * 참고로 클라이언트의 연결요청도 데이터의 전송을 통해서 이뤄진다.
	 * 따라서 이후에 서버 소켓으로 수신된 데이터가 존재한다는 것은 연결요청이 있었다는 뜻으로 해석해야 한다.
	 */
	FD_SET(serv_sock, &reads);
	fd_max = serv_sock;

	while (1)
	{
		cpy_reads = reads;
		timeout.tv_sec = 5;
		timeout.tv_usec = 5000;

		/**
		 * while 문으로 구성된 무한루프 내에서 select 함수가 호출되고 있다.
		 * select 함수의 세 번째, 그리고 네 번째 매개변수가 비어있다.
		 * 이렇듯 관찰의 목적에 맞게 필요한 인자만 전달하면 된다.
		 */
		if ((fd_num = select(fd_max + 1, &cpy_reads, 0, 0, &timeout)) == -1)
			break;

		if (fd_num == 0)
			continue;

		/**
		 * 상태변화가 확인이 되면 제일먼저 서버 소켓에서 변화가 있었는지 확인한다.
		 * 그리고 서버 소켓의 상태변화가 맞으면 이어서 연결요청에 대한 수락의 과정을 진행한다.
		 */
		for (i = 0; i < fd_max + 1; i++)
		{
			if (FD_ISSET(i, &cpy_reads))
			{
				if (i == serv_sock) // connection request! (상태 변화가 발생한 소켓이 서버 소켓이다.)
				{
					adr_sz = sizeof(clnt_adr);
					clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_adr, &adr_sz);

					// df_set 형 변수 reads에 클라이언트와 연결된 소켓의 파일 디스크립터 정보를 등록함에 주목하자.
					FD_SET(clnt_sock, &reads);
					if (fd_max < clnt_sock)
						fd_max = clnt_sock;
					printf("connected client: %d \n", clnt_sock);
				}
				else // read message! (상태 변화가 발생한 소켓이 서버 소켓이 아니다. 즉, 수신할 데이터가 있다.)
				{
					str_len = read(i, buf, BUF_SIZE);
					if (str_len == 0) // close request! (수신한 데이터가 연결 종료 EOF 데이터 이다.)
					{
						FD_CLR(i, &reads);
						close(i);
						printf("closed client: %d \n", i);
					}
					else // 수신한 데이터가 문자열 데이터 이다.
					{
						write(i, buf, str_len); // echo!
					}
				}
			}
		}
	}
	close(serv_sock);
	return 0;
}

void error_handling(char *buf)
{
	fputs(buf, stderr);
	fputc('\n', stderr);
	exit(1);
}