#define _CRT_SECURE_NO_WARNINGS    // sprintf 보안 경고로 인한 컴파일 에러 방지
#include <stdio.h>     // sprintf 함수가 선언된 헤더 파일

#define BUF_SIZE 1024

int main()
{
	int oper_cnt;
	char opmsg[BUF_SIZE];
	fputs("Operand count:", stdout);
	scanf("%d", &oper_cnt);
	opmsg[0] = (char)oper_cnt;

	printf("%c", opmsg[0]);

    return 0;
}