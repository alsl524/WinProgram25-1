#include <windows.h>
#include <stdio.h>

// ���콺 ���� ����
typedef enum {
    IDLE,      // �ƹ��͵� �� ��
    CLICKED,   // Ŭ�������� �巡�״� �ƴ�
    DRAGGING,  // �巡�� ��
    RELEASED   // Ŭ���� ������
} MouseState;

int main() {
    char letter = 'O';  // �̵��� ����
    POINT mousePos;     // ���콺 ��ǥ
    int letterX = 10, letterY = 5;  // ���ĺ� 'O'�� �ʱ� ��ġ
    MouseState mouseState = IDLE;  // �ʱ� ����
    int isDragging = 0;  // ���� 'O'�� �巡�� ������ ����

    // �ܼ� ȭ�� �ʱ�ȭ
    system("cls");

    while (1) {
        // ���� ���콺 ��ǥ ��������
        GetCursorPos(&mousePos);
        ScreenToClient(GetConsoleWindow(), &mousePos); // �ܼ� ��ǥ�� ��ȯ

        // ���콺 Ŭ�� ���� Ȯ��
        if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {  // ���� ��ư ����
            if (mouseState == IDLE) {
                // 'O' ������ Ŭ���ߴ��� Ȯ�� (9,19�� ���� ũ�� ����)
                int clickX = mousePos.x / 9;
                int clickY = mousePos.y / 19;

                if (clickX == letterX && clickY == letterY) {
                    mouseState = CLICKED;  // 'O' ������ Ŭ������ ����
                    isDragging = 1;
                }
            }
            else if (mouseState == CLICKED && isDragging) {
                mouseState = DRAGGING; // Ŭ�� �� �巡�� ����
            }

            if (mouseState == DRAGGING) {  // �巡�� ���� ���� �̵�
                letterX = mousePos.x / 9;
                letterY = mousePos.y / 19;
            }
        }
        else { // ���콺�� ������ ��
            if (mouseState == DRAGGING) {
                mouseState = RELEASED; // �巡�� �� ������
            }
            else {
                mouseState = IDLE;
            }
            isDragging = 0;
        }

        // ȭ�� ����
        system("cls");
        printf("���ĺ� '%c'�� �巡���ϼ���.\n", letter);
        printf("���� ���콺 ����: ");
        switch (mouseState) {
        case IDLE:      printf("IDLE\n"); break;
        case CLICKED:   printf("CLICKED\n"); break;
        case DRAGGING:  printf("DRAGGING\n"); break;
        case RELEASED:  printf("RELEASED\n"); break;
        }
        printf("���� ���ĺ� ��ġ: (%d, %d)\n", letterX, letterY);

        // ���ĺ� ���
        COORD pos = { letterX, letterY };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
        printf("%c", letter);

        // ESC Ű�� ������ ����
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
            printf("\n���α׷� ����\n");
            break;
        }

        Sleep(50);  // CPU ��� ����ȭ
    }

    return 0;
}
