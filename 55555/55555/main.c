#include <stdio.h>
#include <windows.h>

#define MIN_WIDTH 2   // 최소 가로 크기
#define MIN_HEIGHT 4  // 최소 세로 크기

void gotoxy(int x, int y)
{
    COORD Cur;
    Cur.X = x;
    Cur.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}

// 콘솔 창 테두리 그리기 함수
void drawWindow(int width, int height)
{
    gotoxy(0, 0); printf("+");  // 좌상단
    gotoxy(width - 1, 0); printf("+");  // 우상단
    gotoxy(0, height - 1); printf("+");  // 좌하단
    gotoxy(width - 1, height - 1); printf("+");  // 우하단

    // 상단, 하단 테두리
    for (int i = 1; i < width - 1; i++)
    {
        gotoxy(i, 0);
        printf("-");
        gotoxy(i, height - 1);
        printf("-");
    }

    // 좌측, 우측 테두리
    for (int i = 1; i < height - 1; i++)
    {
        gotoxy(0, i);
        printf("|");
        gotoxy(width - 1, i);
        printf("|");
    }

    // 창 내부 상단 추가 선
    gotoxy(1, 1);
    for (int i = 1; i < width - 1; i++) {
        printf("=");
    }
}

int main()
{
    int width, height;

    printf("가로 크기 입력 (최소 %d): ", MIN_WIDTH);
    scanf_s("%d", &width);
    printf("세로 크기 입력 (최소 %d): ", MIN_HEIGHT);
    scanf_s("%d", &height);


    if (width < MIN_WIDTH) width = MIN_WIDTH;
    if (height < MIN_HEIGHT) height = MIN_HEIGHT;

    system("cls");
    drawWindow(width, height);

    gotoxy(0, height);
    return 0;
}
