#include <stdio.h>
#include <unistd.h>
#define BUF_SIZE 30

int main(int argc, char *argv)
{
	int fds[2];
	char buf[BUF_SIZE];
	char str_child[] = "Who are you?";
	char str_parent[] = "Thank you for your message";
	pid_t pid;

	// pipe line 생성 (2개)
	pipe(fds);

	// 프로세스 생성
	pid = fork();

	// child process
	if (pid == 0)
	{
		// fds 입구를 통해 문자열을 넣는다.
		write(fds[1], str_child, sizeof(str_child));
		
		// 2초 딜레이 준다.
		// sleep(2);

		// fds 출구를 통해 문자열을 받는다.
		read(fds[0], buf, BUF_SIZE);
		printf("Child proc output: %s \n", buf);
	}
	else // parent process
	{
		// fds 출구를 통해 문자를 받는다.
		read(fds[0], buf, BUF_SIZE);
		printf("Parent proc output: %s \n", buf);
		
		// fds 입구를 통해 문자를 넣는다.
		write(fds[1], str_parent, sizeof(str_parent));
		sleep(3);
	}
	return 0;
}
