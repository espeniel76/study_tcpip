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
		write(fds[1], str_child, sizeof(str_child));
		sleep(2);
		read(fds[0], buf, BUF_SIZE);
		printf("Child proc output: %s \n", buf);
	}
	else // parent process
	{
		read(fds[0], buf, BUF_SIZE);
		printf("Parent proc output: %s \n", buf);
		write(fds[1], str_parent, sizeof(str_parent));
		sleep(3);
	}
	return 0;
}
