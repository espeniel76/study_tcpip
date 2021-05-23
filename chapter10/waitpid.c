#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	int status;
	pid_t pid = fork();

	if (pid == 0)
	{
		// 자식 프로세스의 종료를 늦추기 위해서 sleep 함수를 호출하고 있다.
		sleep(15);
		return 24;
	}
	else
	{
		// while 문 내에서 waitpid 함수를 호출하고 있다.
		// 세 번째 인자로 WNOHANG을 전달 하였으니, 종료된 자식 프로세스가 없으면 0을 반환한다.
		while (!waitpid(-1, &status, WNOHANG))
		{
			sleep(1);
			puts("sleep 1 sec");
		}

		printf("%d \n", status);

		if (WIFEXITED(status))
		{
			printf("Child send %d \n", WEXITSTATUS(status));
		}
	}

	return 0;
}