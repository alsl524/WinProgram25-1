#include <stdio.h>
#include <windows.h>
#include <string.h>

#define MAX_WINDOWS 3

typedef struct {
    int x, y;
    int width, height;
    int color;
    char title[100];
    int visible;
} ConsoleWindow;

ConsoleWindow windows[MAX_WINDOWS];
int zOrder[MAX_WINDOWS] = { 0, 1, 2 };
int cursorX = 5, cursorY = 5;

void move_cursor(int row, int col) {
    printf("\033[%d;%dH", row, col);
}

void clear_screen() {
    printf("\033[2J");
}

void drawBG(int width, int height) {
    int left = 2, right = 2;
    int top = 1, bottom = 2;
    int fill_width = width - left - right;

    for (int row = top + 1; row < height - bottom; row++) {
        move_cursor(row, left + 1);
        for (int col = 0; col < fill_width; col++) {
            printf("\033[44m \033[0m");
        }
    }

    move_cursor(height - bottom, left + 1);
    for (int col = 0; col < fill_width; col++) {
        printf("\033[47m \033[0m");
    }
}

void drawWindow(ConsoleWindow* win) {
    if (!win->visible) return;

    printf("\033[%dm", 40 + win->color); // Set background
    for (int row = 0; row < win->height; row++) {
        move_cursor(win->y + row, win->x);
        for (int col = 0; col < win->width; col++) {
            if (row == 0 || row == win->height - 1)
                printf("-");
            else if (col == 0 || col == win->width - 1)
                printf("|");
            else
                printf(" ");
        }
    }

    move_cursor(win->y + 1, win->x + 2);
    printf("%s", win->title);

    move_cursor(win->y + 1, win->x + win->width - 4);
    printf("\033[41;37mX\033[0m");

    printf("\033[0m");
}

void drawCursor() {
    move_cursor(cursorY, cursorX);
    printf("<");
}

void drawAll(int w, int h) {
    clear_screen();
    drawBG(w, h);
    for (int i = 0; i < MAX_WINDOWS; i++) {
        drawWindow(&windows[zOrder[i]]);
    }
    drawCursor();
}

void bringToFront(int idx) {
    int pos = -1;
    for (int i = 0; i < MAX_WINDOWS; i++) {
        if (zOrder[i] == idx) {
            pos = i;
            break;
        }
    }
    if (pos == -1) return;

    for (int i = pos; i < MAX_WINDOWS - 1; i++) {
        zOrder[i] = zOrder[i + 1];
    }
    zOrder[MAX_WINDOWS - 1] = idx;
}

int main() {
    const int screenWidth = 80, screenHeight = 25;
    HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
    SetConsoleMode(hIn, ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);

    windows[0] = (ConsoleWindow){ 10, 4, 30, 8, 4, "나의 멋진 윈도우1", 1 };
    windows[1] = (ConsoleWindow){ 15, 6, 30, 8, 6, "나의 멋진 윈도우2", 1 };
    windows[2] = (ConsoleWindow){ 20, 8, 30, 8, 1, "나의 멋진 윈도우3", 1 };

    drawAll(screenWidth, screenHeight);

    INPUT_RECORD input;
    DWORD events;
    while (1) {
        if (PeekConsoleInput(hIn, &input, 1, &events) && events > 0) {
            ReadConsoleInput(hIn, &input, 1, &events);

            if (input.EventType == MOUSE_EVENT) {
                MOUSE_EVENT_RECORD m = input.Event.MouseEvent;
                int mx = m.dwMousePosition.X + 1;
                int my = m.dwMousePosition.Y + 1;

                cursorX = mx;
                cursorY = my;

                if (cursorX < 3) cursorX = 3;
                if (cursorX > screenWidth - 2) cursorX = screenWidth - 2;
                if (cursorY < 2) cursorY = 2;
                if (cursorY > screenHeight - 2) cursorY = screenHeight - 2;

                // 클릭
                if ((m.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED) && m.dwEventFlags == 0) {
                    for (int i = MAX_WINDOWS - 1; i >= 0; i--) {
                        int idx = zOrder[i];
                        ConsoleWindow* w = &windows[idx];
                        if (!w->visible) continue;

                        if (cursorY == w->y + 1 && cursorX == w->x + w->width - 4) {
                            w->visible = 0;
                            drawAll(screenWidth, screenHeight);
                            break;
                        }

                        if (cursorX >= w->x && cursorX <= w->x + w->width &&
                            cursorY >= w->y && cursorY <= w->y + w->height) {
                            bringToFront(idx);
                            drawAll(screenWidth, screenHeight);
                            break;
                        }
                    }
                }
                drawAll(screenWidth, screenHeight);
            }
        }
        Sleep(10);
    }

    return 0;
}
