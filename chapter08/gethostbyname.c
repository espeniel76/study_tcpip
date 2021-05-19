#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>

void error_handling(char *message);

int main(int argc, char *argv[])
{
	int i;
	struct hostent *host;

	// main 함수를 통해 전달된 인자로 gethostbyname 함수를 호출하고 있다.
	host = gethostbyname(argv[1]);
	if (!host)
	{
		error_handling("gethost... error");
	}

	// 공식 도메인 이름을 출력하고 있다.
	printf("Official name: %s \n", host->h_name);

	// 공식 도메인 이름 이외의 도메인 이름을 출력하고 있다.
	for (i = 0; host->h_aliases[i]; i++)
	{
		printf("Aliases %d: %s \n", i + 1, host->h_aliases[i]);
	}

	// IPv4 or IPv6 여부를 판단하고 있다.
	printf("Addres type: %s \n", (host->h_addrtype == AF_INET) ? "AF_INET" : "AF_INET6");

	// IP 주소 정보를 출력하고 있다.
	// 그런데 이해할 수 없는 형변환을 진행하고 있다.
	// 이와 관련해서는 다음에서 진행 하겠다.
	for (i = 0; host->h_addr_list[i]; i++)
	{
		printf("IP addr %d: %s \n", i + 1, inet_ntoa(*(struct in_addr *)host->h_addr_list[i]));
	}
	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}

// ./gethostbyname www.naver.com
// Official name: www.naver.com.nheos.com
// Aliases 1: www.naver.com
// Addres type: AF_INET
// IP addr 1: 125.209.222.141
// IP addr 2: 125.209.222.142