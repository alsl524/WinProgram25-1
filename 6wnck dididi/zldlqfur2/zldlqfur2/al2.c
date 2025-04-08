#include <conio.h>  
#include <stdio.h>
#include <windows.h> 

#define WIDTH 40
#define HEIGHT 20

void gotoxy(int x, int y) {
    COORD pos = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// 게임 영역을 파란색으로 설정
void drawGameArea() {
    system("cls");  // 기존 화면 지우기
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            printf("\033[44m ");  // 파란색 배경 출력
        }
        printf("\033[0m\n");  // 줄 끝에서 배경색 초기화 후 개행
    }
}

// 플레이어를 출력
void drawPlayer(int x, int y) {
    gotoxy(x, y);
    printf("\033[33mP\033[0m"); // 노란색 P 표시
}

// 플레이어를 지우면서 배경 유지
void erasePlayer(int x, int y) {
    gotoxy(x, y);
    printf("\033[44m \033[0m"); // 기존 배경색으로 복원
}

int main() {
    int x = WIDTH / 2, y = HEIGHT / 2; // P의 초기 위치
    int dx = 0, dy = 0; // 이동 방향 변수

    drawGameArea();
    drawPlayer(x, y);

    while (1) {
        // 방향키 상태 체크 (누른 상태 유지)
        if (GetAsyncKeyState('W') & 0x8000) dy = -1;
        if (GetAsyncKeyState('S') & 0x8000) dy = 1;
        if (GetAsyncKeyState('A') & 0x8000) dx = -1;
        if (GetAsyncKeyState('D') & 0x8000) dx = 1;

        // 키를 떼면 멈춤
        if (!(GetAsyncKeyState('W') & 0x8000) && dy == -1) dy = 0;
        if (!(GetAsyncKeyState('S') & 0x8000) && dy == 1) dy = 0;
        if (!(GetAsyncKeyState('A') & 0x8000) && dx == -1) dx = 0;
        if (!(GetAsyncKeyState('D') & 0x8000) && dx == 1) dx = 0;

        // 종료 조건 (Q 키)
        if (GetAsyncKeyState('Q') & 0x8000) break;

        // 이동이 있으면 화면 업데이트
        if (dx != 0 || dy != 0) {
            erasePlayer(x, y); // 기존 위치를 지우면서 배경 유지
            x += dx;
            y += dy;

            // 화면 경계 체크
            if (x < 0) x = 0;
            if (x >= WIDTH) x = WIDTH - 1;
            if (y < 0) y = 0;
            if (y >= HEIGHT) y = HEIGHT - 1;

            drawPlayer(x, y);
        }

        Sleep(50); // 이동 속도 조절
    }

    printf("\033[0m"); // 색상 초기화
    system("cls");
    printf("게임 종료\n");

    return 0;
}
