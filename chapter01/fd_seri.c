#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/socket.h>

int main(void) {

	// 파일 디스크립터 정수 변수 선언
	int fd1, fd2, fd3;

	// 소켓 생성 (SOCK_STREAM)
	// int socket(int domain, int type, int protocol)
	// domain: 생성할 소켓이 통신을 하기 위해 사용할 프로토콜 체계를 설정
	// type: 소켓이 데이터를 전송하는데 있어서, 사용하게 되는 전송 타입을 설정
	//// SOCK_STREAM (TCP)
	//// 1. 에러나 데이터의 손실 없이 무사히 전달
	//// 2. 전송하는 순서대로 데이터가 전달
	//// 3. 전송되는 데이터의 경계가 존재하지 않음
	////  * 신뢰성 있는 순차적인 바이트 기반의 연결 지향 전송 타입
	//// SOCK_DGRAM (UDP)
	//// 1. 전송되는 순서에 상관없이 가장 빠른 전송을 지향
	//// 2. 전송되는 데이터는 손실될 수도 있고, 에러가 발생할 수 있음
	//// 3. 전송되는 데이터의 경계가 존재
	//// 4. 한번에 전송되는 데이터의 크기는 제한
	// protocol: 두 호스트간에 통신을 하는데 있어서 특정 프로토콜을 지정하기 위해 사용
	//// IPROTO_TCP: TCP를 기반으로 하는 소켓을 생성 (연결 지향형 소켓)
	//// IPROTO_UDP: UDP를 기반으로 하는 소켓을 생성 (비연결 지향형 소켓)
	fd1 = socket(PF_INET, SOCK_STREAM, 0);

	// 파일 생성
	fd2 = open("test.dat", O_CREAT | O_WRONLY | O_TRUNC);

	// 소켓 생성 (SOCK_DGRAM)
	fd3 = socket(PF_INET, SOCK_DGRAM, 0);

	printf("file descriptor 1: %d\n", fd1);
	printf("file descriptor 2: %d\n", fd2);
	printf("file descriptor 3: %d\n", fd3);

	close(fd1);
	close(fd2);
	close(fd3);

	return 0;
}
