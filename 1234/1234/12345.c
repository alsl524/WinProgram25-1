#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
/*
int main()
{
		puts("*********************");
		puts("* 이성재의 비밀일기 *");
		puts("*********************\n");

	char ch;
	puts("1.게임시작\n2.게임종료\n");
	puts("입력\n");
	ch = getch();
	if (ch == '1') {
		puts("게임을 시작했습니다.\n");
	}
	else if (ch == '2') {
		puts("게임을 종료합니다.\n");
	}
	else
		puts("잘못된 입력입니다.\n");

	return 0;
}

*/
#define WIDTH 21

int main() {
	int x = WIDTH / 2;
	char ch;

	while (1) {
		system("cls");

		for (int i = 0; i < WIDTH; i++) {
			if (i == x)
				printf("0");
			else
				printf("_");
		}
		printf("\n");

		ch = _getch();

		if (ch == 'a') x = (x > 0) ? x - 1 : x;
		if (ch == 'd') x = (x < WIDTH - 1) ? x + 1 : x;
	}

	return 0;
}
