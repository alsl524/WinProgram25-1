#include <windows.h>
#include <stdio.h>

// 마우스 상태 정의
typedef enum {
    IDLE,      // 아무것도 안 함
    CLICKED,   // 클릭했지만 드래그는 아님
    DRAGGING,  // 드래그 중
    RELEASED   // 클릭을 떼었음
} MouseState;

int main() {
    char letter = 'O';  // 이동할 문자
    POINT mousePos;     // 마우스 좌표
    int letterX = 10, letterY = 5;  // 알파벳 'O'의 초기 위치
    MouseState mouseState = IDLE;  // 초기 상태
    int isDragging = 0;  // 현재 'O'를 드래그 중인지 여부

    // 콘솔 화면 초기화
    system("cls");

    while (1) {
        // 현재 마우스 좌표 가져오기
        GetCursorPos(&mousePos);
        ScreenToClient(GetConsoleWindow(), &mousePos); // 콘솔 좌표로 변환

        // 마우스 클릭 상태 확인
        if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {  // 왼쪽 버튼 눌림
            if (mouseState == IDLE) {
                // 'O' 위에서 클릭했는지 확인 (9,19는 글자 크기 보정)
                int clickX = mousePos.x / 9;
                int clickY = mousePos.y / 19;

                if (clickX == letterX && clickY == letterY) {
                    mouseState = CLICKED;  // 'O' 위에서 클릭했을 때만
                    isDragging = 1;
                }
            }
            else if (mouseState == CLICKED && isDragging) {
                mouseState = DRAGGING; // 클릭 후 드래그 시작
            }

            if (mouseState == DRAGGING) {  // 드래그 중일 때만 이동
                letterX = mousePos.x / 9;
                letterY = mousePos.y / 19;
            }
        }
        else { // 마우스를 떼었을 때
            if (mouseState == DRAGGING) {
                mouseState = RELEASED; // 드래그 후 떼었음
            }
            else {
                mouseState = IDLE;
            }
            isDragging = 0;
        }

        // 화면 갱신
        system("cls");
        printf("알파벳 '%c'을 드래그하세요.\n", letter);
        printf("현재 마우스 상태: ");
        switch (mouseState) {
        case IDLE:      printf("IDLE\n"); break;
        case CLICKED:   printf("CLICKED\n"); break;
        case DRAGGING:  printf("DRAGGING\n"); break;
        case RELEASED:  printf("RELEASED\n"); break;
        }
        printf("현재 알파벳 위치: (%d, %d)\n", letterX, letterY);

        // 알파벳 출력
        COORD pos = { letterX, letterY };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
        printf("%c", letter);

        // ESC 키를 누르면 종료
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
            printf("\n프로그램 종료\n");
            break;
        }

        Sleep(50);  // CPU 사용 최적화
    }

    return 0;
}
