#include <stdio.h>
#include <arpa/inet.h>

/**
 * @brief inet_addr 함수
 * 문자스트링 주소로 부터 실제, 네트워크 주소를 뽑아낸다.
 * INADDR_NONE 상수로 판별 한다.
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char *argv[])
{
	char *addr1 = "127.212.124.78";

	// 1 Byte 가 표시할 수 있는 최대 크기의 정수를 넘었다.
	char *addr2 = "127.212.124.256";

	unsigned long conv_addr = inet_addr(addr1);
	if (conv_addr == INADDR_NONE)
	{
		printf("Error occured! \n");
	}
	else
	{
		printf("Network ordered integer addr: %#lx \n", conv_addr);
	}

	conv_addr = inet_addr(addr2);
	if (conv_addr == INADDR_NONE)
	{
		printf("Error occureded \n");
	}
	else
	{
		printf("Network ordered integer addr: %#lx \n\n", conv_addr);
	}

	return 0;
}