#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
/*
int main()
{
		puts("*********************");
		puts("* �̼����� ����ϱ� *");
		puts("*********************\n");

	char ch;
	puts("1.���ӽ���\n2.��������\n");
	puts("�Է�\n");
	ch = getch();
	if (ch == '1') {
		puts("������ �����߽��ϴ�.\n");
	}
	else if (ch == '2') {
		puts("������ �����մϴ�.\n");
	}
	else
		puts("�߸��� �Է��Դϴ�.\n");

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
