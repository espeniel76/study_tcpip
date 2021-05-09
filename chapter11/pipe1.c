#include <stdio.h>
#include <unistd.h>
#define BUF_SIZE 30

int main(int argc, char *argv[]) {
	int fds[2];
	char str[] = "Who are you?";
	char buf[BUF_SIZE];
	pid_t pid;

	// 이놈은 뭐지?
	// fds 배열에 파이프 생성
	// 두개의 file 디스크립터가 생성됨
	pipe(fds);

	// 자식 프로세스 생성
	pid = fork();

	if (pid == 0) {
		write(fds[1], str, sizeof(str));
	} else {
		int i;
		read(fds[0], buf, BUF_SIZE);
		puts(buf);
	}
	return 0;
}
