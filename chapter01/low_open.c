#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

void error_handling(char *message);

int main(void) {
	char buffer[] = "Let's go!\n";

	// c open 함수
	int fileDescriptor = open("data.txt", O_CREAT | O_WRONLY | O_TRUNC);
	if (fileDescriptor == -1) {
		error_handling("open() error!");
	}

	printf("file descriptor: %d \n", fileDescriptor);

	if (write(fileDescriptor, buffer, sizeof(buffer)) == -1) {
		error_handling("write() error!");
	}

	close(fileDescriptor);
	return 0;
}

/**
 * fputs, printf 차이: printf 는 인자를 받아서 출력 할 수 있다.
 * printf 가 기능이 좀 더 많으므로, 좀 더 무겁다.
 * fputs 를 자주 쓰면 복잡한 코드에서 오류가 잘 난다고 한다.
 * ? 그럼 fputs 를 쓸 필요가 없는거 아닌가?
 * fputc
 */
void error_handling(char *message) {
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
