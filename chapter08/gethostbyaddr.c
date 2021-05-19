#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>

void error_handling(char *message);

int main(int argc, char *argv[])
{
	int i;
	struct hostent *host;
	struct sockaddr_in addr;

	memset(&addr, 0, sizeof(addr));
	addr.sin_addr.s_addr = inet_addr(argv[1]);
	host = gethostbyaddr((char *)&addr.sin_addr, 4, AF_INET);

	printf("Official name: %s \n", host->h_name);

	for (i = 0; host->h_aliases[i]; i++)
	{
		printf("Aliases %d: %s \n", i + 1, host->h_aliases[i]);
	}

	printf("Addres type: %s \n", (host->h_addrtype == AF_INET) ? "AF_INET" : "AF_INET6");

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

// ./gethostbyaddr 216.58.220.196
// Official name: hkg12s16-in-f4.1e100.net
// Addres type: AF_INET
// IP addr 1: 216.58.220.196