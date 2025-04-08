#include <conio.h>  // kbhit(), getch() ���
#include <stdio.h>
#include <windows.h> // Sleep() ���

#define WIDTH 40
#define HEIGHT 20

void gotoxy(int x, int y) {
    COORD pos = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void drawBackground() {
    system("cls");  // ���� ȭ�� �����
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            printf("\033[44m ");  // �Ķ��� ��� ���
        }
        printf("\033[0m\n");  // �� ������ ���� �ʱ�ȭ �� ����
    }
}

void drawPlayer(int x, int y) {
    gotoxy(x, y);
    printf("\033[33mP\033[0m"); // ����� P ǥ��
}

void erasePlayer(int x, int y) {
    gotoxy(x, y);
    printf("\033[44m \033[0m"); // ���� �����ϸ� �����
}

int main() {

    int x = WIDTH / 2, y = HEIGHT / 2; // P�� �ʱ� ��ġ
    char ch;

    drawBackground();
    drawPlayer(x, y);

    while (1) {
        if (_kbhit()) {
            ch = _getch();

            erasePlayer(x, y); // ���� ��ġ�� �������� �����ϸ鼭 �����

            if (ch == 'w' && y > 0) y--; // ���� �̵�
            if (ch == 's' && y < HEIGHT - 1) y++; // �Ʒ��� �̵�
            if (ch == 'a' && x > 0) x--; // ���� �̵�
            if (ch == 'd' && x < WIDTH - 1) x++; // ������ �̵�
            if (ch == 'q') break; // ���� ����

            drawPlayer(x, y);
        }
    }

    printf("\033[0m"); // ���� �ʱ�ȭ
    system("cls");
    printf("���� ����\n");


    return 0;

}