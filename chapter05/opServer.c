#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024
#define OPSZ 4
void error_handling(char *message);
int calculate(int opnum, int opnds[], char oprator);

int main(int argc, char *argv[])
{
	int serv_sock, clnt_sock;
	char opinfo[BUF_SIZE];
	int result, opnd_cnt, i;
	int recv_cnt, recv_len;
	struct sockaddr_in serv_adr, clnt_adr;
	socklen_t clnt_adr_sz;

	serv_sock = socket(PF_INET, SOCK_STREAM, 0);
	if (serv_sock == -1)
		error_handling("socket() error");

	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family = AF_INET;
	serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_adr.sin_port = htons(7325);

	if (bind(serv_sock, (struct sockaddr *)&serv_adr, sizeof(serv_adr)) == -1)
		error_handling("bind() error");
	if (listen(serv_sock, 5) == -1)
		error_handling("listen() error");
	clnt_adr_sz = sizeof(clnt_adr);

	opnd_cnt = 0;
	clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_adr, &clnt_adr_sz);
	printf("client connect !\n");

	// 피 연산자의 개수 정보를 수신한다.
	// byte 의 제일 첫 자리에 해당 숫자를 할당 했으므로...
	read(clnt_sock, &opnd_cnt, 1);
	recv_len = 0;

	// 피 연산자의 숫자(4byte) * 개수 + 연산방식(1byte)가 전체 길이 이므로
	// 왜 이렇게 했느냐? buffer 만큼 하면 대부분의 버퍼 쓰레기 값들이 있으므로, 할당된 정확한 수를 판별하기 위해서....
	while ((opnd_cnt * OPSZ + 1) > recv_len)
	{
		recv_cnt = read(clnt_sock, &opinfo[recv_len], BUF_SIZE - 1);
		printf("recv_cnt: %d\n", recv_cnt);
		recv_len += recv_cnt;
	}
	result = calculate(opnd_cnt, (int *)opinfo, opinfo[recv_len - 1]);
	write(clnt_sock, (char *)&result, sizeof(result));
	close(clnt_sock);

	return 0;
}

/**
 * @brief 
 * 
 * @param opnum	중복 횟수
 * @param opnds	연산숫자 배열
 * @param op	연산방식 (+/-/*)
 * @return int 
 */
int calculate(int opnum, int opnds[], char op)
{
	int result = opnds[0], i;

	switch (op)
	{
	case '+':
		for (i = 1; i < opnum; i++)
			result += opnds[i];
		break;
	case '-':
		for (i = 1; i < opnum; i++)
			result -= opnds[i];
		break;
	case '*':
		for (i = 1; i < opnum; i++)
			result *= opnds[i];
		break;
	}
	return result;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}