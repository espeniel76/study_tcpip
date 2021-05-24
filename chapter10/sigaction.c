#include <stdio.h>
#include <unistd.h>
#include <signal.h>

/**
 * @brief 타임아웃 시그널 핸들러
 * 
 * @param sig 
 */
void timeout(int sig)
{
	if (sig == SIGALRM)
	{
		puts("Time out!");
	}
	// 2초 간격으로 SIGALRM 을 반복 발생 시킨다.
	alarm(2);
}

int main(int argc, char *argv[])
{
	int i;

	struct sigaction act;

	// sa_handler 에 함수 포인터 값 할당
	act.sa_handler = timeout;

	// sa_mask 의 모든 비트를 0으로 초기화
	sigemptyset(&act.sa_mask);

	// 0으로 초기화
	act.sa_flags = 0;

	// 핸들러 실행 예약?
	sigaction(SIGALRM, &act, 0);

	alarm(2);
	for (i = 0; i < 3; i++)
	{
		puts("wait...");
		sleep(100);
	}

	return 0;
}