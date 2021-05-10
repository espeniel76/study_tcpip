#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/select.h>

#define BUF_SIZE 30

int main(int argc, char *argv[]) {
	fd_set reads, temps;
	int result, str_len;
	char buf[BUF_SIZE];
	struct timeval timeout;

	
	FD_ZERO(&reads);	// fd_set 형 변수를 초기화하고
	FD_SET(0, &reads);	// 파일 디스크립터 0의 위치를 1로 설정해 주고 있다.

	/*
	 timeout.tv_sec=5;
	 timeout.tv_usec=5000;
	 */

	while (1) {
		temps = reads;	// temp 에 저장해 두어, 원본을 복사 해 둔다.
		timeout.tv_sec = 5;
		timeout.tv_usec = 0;
		result = select(1, &temps, 0, 0, &timeout);
		if (result == -1) {
			puts("select() error!");
			break;
		} else if (result == 0) {
			puts("Time-out!");
		} else {
			if (FD_ISSET(0, &temps)) {
				str_len = read(0, buf, BUF_SIZE);
				buf[str_len] = 0;
				printf("message from console: %s", buf);
			}
		}
	}
	return 0;
}
