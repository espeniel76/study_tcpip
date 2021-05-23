/**
 * @file wait.c
 * @author espeniel (espeniel@naver.com)
 * @brief 
 * @version 0.1
 * @date 2021-05-23
 * 
 * @copyright Copyright (c) 2021
 * wait 함수 호출로 자식이 부모를 기다리지 않고, 프로세스가 완전히 종료됨
 * WIFEXITED: 자식 프로세스의 정상 종료한 여부 boolean
 * WEXITSTATUS 자식 프로세스의 전달 값을 반환한다.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	int status;
	pid_t pid = fork();

	if (pid == 0)
	{
		// 9행에서 생성된 자식 프로세스는 return 문을 통해 종료
		return 3;
	}
	else
	{
		printf("Child PID: %d \n", pid);
		pid = fork();
		if (pid == 0)
		{
			// 19행에서 생성된 자식 프로세스는 exit 문을 통해 종료
			exit(7);
		}
		else
		{
			printf("Child PID: %d \n", pid);

			// wait 함수를 호출
			// 이로 인해서 종료된 프로세스 관련 정보는 status 에 담기게 되고, 해당 정보의 프로세스는 완전히 소멸된다.
			wait(&status);

			// 매크로 함수 WIFEXITED를 통해서 자식 프로세스의 정상종료 여부를 확인하고 있다.
			// 그리고 정상종료인 경우에 한해서 WEXITSTATUS 함수를 호출하여 자식 프로세스가 전달한 값을 출력하고 있다.
			if (WIFEXITED(status))
			{
				printf("Child send one: %d \n", WEXITSTATUS(status));
			}

			// 앞서 생성한 자식 프로세스가 두 개이므로 또 한번의 wait 함수호출과 매크로 함수의 호출을 진행하고 있다.
			wait(&status);
			if (WIFEXITED(status))
			{
				printf("Child send to: %d \n", WEXITSTATUS(status));
			}

			// 부모 프로세스의 종료를 멈추기 위해서 삽인한 코드이다. 이 순간에 여러분은 자식 프로세스의 상태를 확인하면 된다.
			sleep(30);
		}
	}

	return 0;
}