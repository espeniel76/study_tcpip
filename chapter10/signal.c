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

/**
 * @brief Ctrl+C 시그널 핸들러
 * 
 * @param sig 
 */
void keycontrol(int sig)
{
	if (sig == SIGINT)
	{
		puts("CTRL+C pressed");
	}
}

int main(int argc, char *argv[])
{
	int i;

	// 시그널 핸들러 등록
	signal(SIGALRM, timeout);
	signal(SIGINT, keycontrol);

	// 2초 간격으로 SIGALRM 을 반복 발생 시킨다.
	alarm(2);

	// 100초마다 블로킹을 걸지만, signal 함수로 인해 프로세스가 sleep 에서 깨어 난다.
	for (i = 0; i < 3; i++)
	{
		puts("wait...");
		sleep(100);
	}

	return 0;
}