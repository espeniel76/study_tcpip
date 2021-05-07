#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void timeout(int sig) {
	if (sig == SIGALRM) {
		puts("Time out!");
	}
	alarm(2);
}

void keycontrol(int sig) {
	if (sig == SIGINT) {
		puts("CTRL+C pressed");
	}
}

int main(int argc, char *argv[]) {
	int i;

	/**
	 * alarm  함수 호출을 통해서 등록된 시간이 지나면, timeout 함수호출
	 */
	signal(SIGALRM, timeout);

	/**
	 * CTRL+C가 입력되면, keycontrol 함수를 호출해 달라.
	 */
	signal(SIGINT, keycontrol);

	alarm(2);

	for (i = 0; i < 3; i++) {
		/**
		 * puts 는 또 뭘까?
		 * printf 랑 뭐가 다를까?
		 */
		puts("wait...");

		/**
		 * 시그널핸들링이 발생하면, sleep 로 잠든 프로세스도 깨어난다.
		 */
		sleep(100);
	}
	return 0;+
}
