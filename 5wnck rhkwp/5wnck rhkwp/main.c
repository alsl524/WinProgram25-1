#include <stdio.h>
#include <windows.h>

#define MIN_WIDTH 2   // �ּ� ���� ũ��
#define MIN_HEIGHT 4  // �ּ� ���� ũ��

// ������ �Ӽ��� ����ü�� ����
typedef struct {
    int width;
    int height;
    int x;
    int y;
    char color[8];  // ���� �ڵ�
} Window;

void gotoxy(int x, int y) {
    COORD Cur;
    Cur.X = x;
    Cur.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}

// �ܼ� ����� �ʷϻ����� ä���
void fillBackground() {
    system("cls");
    printf("\033[H\033[42m"); // (0,0)���� �̵� �� �ʷϻ� ��� ����

    for (int i = 0; i < 40; i++) {
        for (int j = 0; j < 200; j++) {
            printf(" ");
        }
        printf("\n");
    }

    printf("\033[0m\033[H"); // ���� ���� �� (0,0)���� �̵�
}


// �ܼ� â �׵θ� �׸��� �Լ�
void drawWindow(Window win) {
    printf("%s", win.color); // ���� ����

    gotoxy(win.x, win.y); printf("+");  // �»��
    gotoxy(win.x + win.width - 1, win.y); printf("+");  // ����
    gotoxy(win.x, win.y + win.height - 1); printf("+");  // ���ϴ�
    gotoxy(win.x + win.width - 1, win.y + win.height - 1); printf("+");  // ���ϴ�

    // ���, �ϴ� �׵θ�
    for (int i = 1; i < win.width - 1; i++) {
        gotoxy(win.x + i, win.y);
        printf("-");
        gotoxy(win.x + i, win.y + win.height - 1);
        printf("-");
    }

    // ����, ���� �׵θ�
    for (int i = 1; i < win.height - 1; i++) {
        gotoxy(win.x, win.y + i);
        printf("|");
        gotoxy(win.x + win.width - 1, win.y + i);
        printf("|");
    }

    // ���� ��� �߰� ��
    gotoxy(win.x + 1, win.y + 1);
    for (int i = 1; i < win.width - 1; i++) {
        printf("=");
    }

    printf("\033[0m"); // ���� ����
}

int main() {
    fillBackground(); // �ܼ� ����� �ʷϻ����� ä��

    // ù ��° ������
    Window win1 = { 20, 7, 10, 3, "\033[41m" }; // ������ ���
    drawWindow(win1);

    // �� ��° ������
    Window win2 = { 20, 7, 15, 5, "\033[44m" }; // �Ķ��� ���
    drawWindow(win2);

    gotoxy(0, 30); // Ŀ�� �Ʒ��� �̵�
    getchar(); // ����� �Է��� ��ٸ� (�޽��� ���� �Է� ���)

    return 0;
}
