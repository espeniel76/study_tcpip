#include <stdio.h>

#define BUF_SIZE 1024
#define RLT_SIZE 4
#define OPSZ 4

int calculate(int opnum, int opnds[], char oprator);

int main(int argc, char *argv[]) {

	char opmsg[BUF_SIZE];
	int opnd_cnt;
	int i;
	int now_opsz = 0;

	// 스트림에 문자열을 쓴다.
	fputs("Operand count:", stdout);

	// 숫자 하나를 입력 받는다.
	scanf("%d", &opnd_cnt);

	// 문자배열 첫번째 인자로 할당한다.
	opmsg[0] = (char) opnd_cnt;

	// 입력받은 숫자만큼 배열을 돌면서
	for (i = 0; i < opnd_cnt; i++) {
		printf("Operand %d: ", i + 1);

		now_opsz = i * OPSZ + 1;

		// char 형(1byte) 배열에 int 형(4byte)배열을 할당하라
		scanf("%d", (int*) &opmsg[now_opsz]);
	}

	// 파일에서부터 글자를 하나하나 읽는다.
	fgetc(stdin);

	// 스트림에 문자열을 쓴다.
	fputs("Operator: ", stdout);

	// 마지막 byte에 연산자를 작성한다.
	now_opsz = opnd_cnt * OPSZ + 1;
	opmsg[now_opsz] = '+';
	// scanf("%c", &opmsg[now_opsz]);

	int result = calculate(opnd_cnt, (int*) opmsg, opmsg[now_opsz]);
	printf("Result: %d\n", result);

	return 0;
}

int calculate(int opnum, int opnds[], char op) {

	printf("opnum: %d, op: %c\n", opnum, op);
	int result = opnds[0], i;
	printf("result: %d\n", result);

	switch (op) {
	case '+':
		for (i = 1; i < opnum; i++)
			result += opnds[i];
		break;
	case '-':
		for (i = 1; i < opnum; i++)
			result -= opnds[i];
		break;
	case '*':
		for (i = 1; i < opnum; i++)
			result *= opnds[i];
		break;
	}
	return result;
}
