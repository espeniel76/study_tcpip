#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
void error_handling(char *message);

int main(int argc, char *argv[])
{
	char *addr = "127.232.124.79";

	/**
	 * @brief 변환된 IP주소 정보는 구조체 sockaddr_in의 멤버인
	 * in_addr형 변수에 담겨야 의미있게 사용할 수 있다.
	 * 그래서 inet_aton 함수는 두 번째 인자로 in_addr형 변수의 주소 값을 요구하고 있다.
	 * 이로써 변환된 IP주소 정보를 직접 저장하는 일을 덜 수 있게 되었다.
	 * 
	 */
	struct sockaddr_in addr_inet;

	if (!inet_aton(addr, &addr_inet.sin_addr))
	{
		error_handling("Conversion error");
	}
	else
	{
		printf("Network ordered integer addr: %#x \n", addr_inet.sin_addr.s_addr);
	}

	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}