#include <stdio.h>
#include <unistd.h>

int gval = 10;
int main(int argc, char *argv[])
{
	pid_t pid;
	int lval = 20;
	gval++, lval += 5;

	// 자식 프로세스를 생성하고 있다.
	pid = fork();
	// 따라서, 부모 프로세스의 pid 에는 자식 프로세스의 pid 가 저장되며,
	// 자식 프로세스의 pid 에는 0이 저장된다.
	// 즉, 부모프로세스의 실제 pid 는 0 이지만, 변수에 담긴건 자식 프로세스의 pid 이며
	// 자식 프로세스의 실제 pid 는 0 이 아니지만, 변수에 담긴건 부모 프로세스의 pid 이다.

	if (pid == 0)
	{
		gval += 2, lval += 2;
	}
	else
	{
		gval -= 2, lval = 2;
	}

	if (pid == 0)
	{
		printf("Child Proc: [%d, %d] \n", gval, lval);
	}
	else
	{
		printf("Parent Proc: [%d, %d] \n", gval, lval);
	}

	return 0;
}