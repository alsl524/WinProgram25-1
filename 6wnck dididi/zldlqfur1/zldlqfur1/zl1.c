#include <conio.h>  // kbhit(), getch() 사용
#include <stdio.h>
#include <windows.h> // Sleep() 사용

#define WIDTH 40
#define HEIGHT 20

void gotoxy(int x, int y) {
    COORD pos = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void drawBackground() {
    system("cls");  // 기존 화면 지우기
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            printf("\033[44m ");  // 파란색 배경 출력
        }
        printf("\033[0m\n");  // 줄 끝에서 배경색 초기화 후 개행
    }
}

void drawPlayer(int x, int y) {
    gotoxy(x, y);
    printf("\033[33mP\033[0m"); // 노란색 P 표시
}

void erasePlayer(int x, int y) {
    gotoxy(x, y);
    printf("\033[44m \033[0m"); // 배경색 유지하며 지우기
}

int main() {

    int x = WIDTH / 2, y = HEIGHT / 2; // P의 초기 위치
    char ch;

    drawBackground();
    drawPlayer(x, y);

    while (1) {
        if (_kbhit()) {
            ch = _getch();

            erasePlayer(x, y); // 기존 위치를 배경색으로 유지하면서 지우기

            if (ch == 'w' && y > 0) y--; // 위로 이동
            if (ch == 's' && y < HEIGHT - 1) y++; // 아래로 이동
            if (ch == 'a' && x > 0) x--; // 왼쪽 이동
            if (ch == 'd' && x < WIDTH - 1) x++; // 오른쪽 이동
            if (ch == 'q') break; // 게임 종료

            drawPlayer(x, y);
        }
    }

    printf("\033[0m"); // 색상 초기화
    system("cls");
    printf("게임 종료\n");


    return 0;

}