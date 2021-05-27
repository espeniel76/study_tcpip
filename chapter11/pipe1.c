#include <stdio.h>
#include <unistd.h>
#define BUF_SIZE 30

int main(int argc, char *argv[])
{
	int fds[2];
	char str[] = "Who are you?";
	char buf[BUF_SIZE];
	pid_t pid;

	// 이놈은 뭐지?
	// fds 배열에 파이프 생성
	// 두개의 pipe file 디스크립터가 생성됨
	pipe(fds);
	// fds[0] 파이프의 출구다.
	// fds[1] 파이프의 입구다.

	// 자식 프로세스 생성
	pid = fork();

	if (pid == 0)
	{
		// 자식 프로세스가 fds 파이프를 통해 문자를 집어넣고 있다.
		write(fds[1], str, sizeof(str));
	}
	else
	{
		// 부모 프로세스가 fds 파이프를 통해 문자열을 받고있다.
		read(fds[0], buf, BUF_SIZE);
		puts(buf);
	}
	return 0;
}
