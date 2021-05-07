#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
	int status;

	pid_t pid = fork();

	if (pid == 0) {
		puts("Hi, I am a child process\n");
	} else {
		printf("Child Process ID: %d \n", pid);
		sleep(1);
	}

	if (pid == 0)
		puts("End child process\n");
	else
		puts("End parent process\n");

	return 0;
}
