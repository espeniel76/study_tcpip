#include <stdio.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
	/**
	 * @brief 각각 2바이트, 4바이트 데이터를 변수에 저장하고 있다.
	 * 물론 예제를 실행하는 시스템의 CPU에 따라서 저장되는 바이트 순서는 달라진다.
	 */
	unsigned short host_port = 0x1234;
	unsigned short net_port;
	unsigned long host_addr = 0x12345678;
	unsigned long net_addr;

	/**
	 * @brief 변수host_port 와 host_addr에 저장된 데이터를 네트워크 바이트 순서로 변환하고있다.
	 * 만약에 위 예제가 리틀 엔디안 기준으로 정렬하는 CPU상에서 실행된다면, 바이트 순서가 바뀐 값이 반환되어 변수에 저장된다.
	 */
	net_port = htons(host_port);
	net_addr = htonl(host_addr);

	printf("Host ordered port: %#x \n", host_port);
	printf("Network ordered port: %#x \n", net_port);
	printf("Host ordered address: %#lx \n", host_addr);
	printf("Network ordered address: %#lx \n", net_addr);
	return 0;
}