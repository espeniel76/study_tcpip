#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	// 자식 생성
	// 자식은 부모의 아이디 0를 가진다.
	// 부모는 자식의 아이디를 가진다.
	// 즉, 자식은 0, 부모는 0이 아닌 값이다.
	pid_t pid = fork();
	int status;

	if (pid == 0)
	{
		puts("Hi, I am a child process.");
		return 3;
		//sleep(30);
	}
	else
	{
		printf("Hi, I am a parent process. Child Process ID: %d \n", pid);
		sleep(30);
	}

	if (pid == 0)
	{
		puts("End child process");
	}
	else
	{
		puts("End parent process");
	}

	return 0;
}