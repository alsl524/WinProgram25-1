#include <stdio.h>
#include <windows.h>

#define MIN_WIDTH 2   // �ּ� ���� ũ��
#define MIN_HEIGHT 4  // �ּ� ���� ũ��

void gotoxy(int x, int y)
{
    COORD Cur;
    Cur.X = x;
    Cur.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}

// �ܼ� â �׵θ� �׸��� �Լ�
void drawWindow(int width, int height)
{
    gotoxy(0, 0); printf("+");  // �»��
    gotoxy(width - 1, 0); printf("+");  // ����
    gotoxy(0, height - 1); printf("+");  // ���ϴ�
    gotoxy(width - 1, height - 1); printf("+");  // ���ϴ�

    // ���, �ϴ� �׵θ�
    for (int i = 1; i < width - 1; i++)
    {
        gotoxy(i, 0);
        printf("-");
        gotoxy(i, height - 1);
        printf("-");
    }

    // ����, ���� �׵θ�
    for (int i = 1; i < height - 1; i++)
    {
        gotoxy(0, i);
        printf("|");
        gotoxy(width - 1, i);
        printf("|");
    }

    // â ���� ��� �߰� ��
    gotoxy(1, 1);
    for (int i = 1; i < width - 1; i++) {
        printf("=");
    }
}

int main()
{
    int width, height;

    printf("���� ũ�� �Է� (�ּ� %d): ", MIN_WIDTH);
    scanf_s("%d", &width);
    printf("���� ũ�� �Է� (�ּ� %d): ", MIN_HEIGHT);
    scanf_s("%d", &height);


    if (width < MIN_WIDTH) width = MIN_WIDTH;
    if (height < MIN_HEIGHT) height = MIN_HEIGHT;

    system("cls");
    drawWindow(width, height);

    gotoxy(0, height);
    return 0;
}
