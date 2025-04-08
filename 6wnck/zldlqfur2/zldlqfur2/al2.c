#include <conio.h>  
#include <stdio.h>
#include <windows.h> 

#define WIDTH 40
#define HEIGHT 20

void gotoxy(int x, int y) {
    COORD pos = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// ���� ������ �Ķ������� ����
void drawGameArea() {
    system("cls");  // ���� ȭ�� �����
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            printf("\033[44m ");  // �Ķ��� ��� ���
        }
        printf("\033[0m\n");  // �� ������ ���� �ʱ�ȭ �� ����
    }
}

// �÷��̾ ���
void drawPlayer(int x, int y) {
    gotoxy(x, y);
    printf("\033[33mP\033[0m"); // ����� P ǥ��
}

// �÷��̾ ����鼭 ��� ����
void erasePlayer(int x, int y) {
    gotoxy(x, y);
    printf("\033[44m \033[0m"); // ���� �������� ����
}

int main() {
    int x = WIDTH / 2, y = HEIGHT / 2; // P�� �ʱ� ��ġ
    int dx = 0, dy = 0; // �̵� ���� ����

    drawGameArea();
    drawPlayer(x, y);

    while (1) {
        // ����Ű ���� üũ (���� ���� ����)
        if (GetAsyncKeyState('W') & 0x8000) dy = -1;
        if (GetAsyncKeyState('S') & 0x8000) dy = 1;
        if (GetAsyncKeyState('A') & 0x8000) dx = -1;
        if (GetAsyncKeyState('D') & 0x8000) dx = 1;

        // Ű�� ���� ����
        if (!(GetAsyncKeyState('W') & 0x8000) && dy == -1) dy = 0;
        if (!(GetAsyncKeyState('S') & 0x8000) && dy == 1) dy = 0;
        if (!(GetAsyncKeyState('A') & 0x8000) && dx == -1) dx = 0;
        if (!(GetAsyncKeyState('D') & 0x8000) && dx == 1) dx = 0;

        // ���� ���� (Q Ű)
        if (GetAsyncKeyState('Q') & 0x8000) break;

        // �̵��� ������ ȭ�� ������Ʈ
        if (dx != 0 || dy != 0) {
            erasePlayer(x, y); // ���� ��ġ�� ����鼭 ��� ����
            x += dx;
            y += dy;

            // ȭ�� ��� üũ
            if (x < 0) x = 0;
            if (x >= WIDTH) x = WIDTH - 1;
            if (y < 0) y = 0;
            if (y >= HEIGHT) y = HEIGHT - 1;

            drawPlayer(x, y);
        }

        Sleep(50); // �̵� �ӵ� ����
    }

    printf("\033[0m"); // ���� �ʱ�ȭ
    system("cls");
    printf("���� ����\n");

    return 0;
}
