#include <stdio.h>
#include <windows.h>

#define MIN_WIDTH 2   // 최소 가로 크기
#define MIN_HEIGHT 4  // 최소 세로 크기

// 윈도우 속성을 구조체로 관리
typedef struct {
    int width;
    int height;
    int x;
    int y;
    char color[8];  // 색상 코드
} Window;

void gotoxy(int x, int y) {
    COORD Cur;
    Cur.X = x;
    Cur.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}

// 콘솔 배경을 초록색으로 채우기
void fillBackground() {
    system("cls");
    printf("\033[H\033[42m"); // (0,0)으로 이동 후 초록색 배경 설정

    for (int i = 0; i < 40; i++) {
        for (int j = 0; j < 200; j++) {
            printf(" ");
        }
        printf("\n");
    }

    printf("\033[0m\033[H"); // 색상 리셋 후 (0,0)으로 이동
}


// 콘솔 창 테두리 그리기 함수
void drawWindow(Window win) {
    printf("%s", win.color); // 색상 설정

    gotoxy(win.x, win.y); printf("+");  // 좌상단
    gotoxy(win.x + win.width - 1, win.y); printf("+");  // 우상단
    gotoxy(win.x, win.y + win.height - 1); printf("+");  // 좌하단
    gotoxy(win.x + win.width - 1, win.y + win.height - 1); printf("+");  // 우하단

    // 상단, 하단 테두리
    for (int i = 1; i < win.width - 1; i++) {
        gotoxy(win.x + i, win.y);
        printf("-");
        gotoxy(win.x + i, win.y + win.height - 1);
        printf("-");
    }

    // 좌측, 우측 테두리
    for (int i = 1; i < win.height - 1; i++) {
        gotoxy(win.x, win.y + i);
        printf("|");
        gotoxy(win.x + win.width - 1, win.y + i);
        printf("|");
    }

    // 내부 상단 추가 선
    gotoxy(win.x + 1, win.y + 1);
    for (int i = 1; i < win.width - 1; i++) {
        printf("=");
    }

    printf("\033[0m"); // 색상 리셋
}

int main() {
    fillBackground(); // 콘솔 배경을 초록색으로 채움

    // 첫 번째 윈도우
    Window win1 = { 20, 7, 10, 3, "\033[41m" }; // 빨간색 배경
    drawWindow(win1);

    // 두 번째 윈도우
    Window win2 = { 20, 7, 15, 5, "\033[44m" }; // 파란색 배경
    drawWindow(win2);

    gotoxy(0, 30); // 커서 아래로 이동
    getchar(); // 사용자 입력을 기다림 (메시지 없이 입력 대기)

    return 0;
}
