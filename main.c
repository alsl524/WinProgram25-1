#pragma comment(lib, "opengl32.lib")
#include <GLFW/glfw3.h>
#include <time.h>
#include <stdio.h>
#include "stb_easy_font.h"

#define WINDOW_WIDTH 460
#define WINDOW_HEIGHT 122

void draw_text(float x, float y, const char* text, float r, float g, float b, float scale) {
    char buffer[9999];
    int num_quads = stb_easy_font_print(0, 0, (char*)text, NULL, buffer, sizeof(buffer));

    glPushMatrix();
    glTranslatef(x, y, 0);     // 위치 보정
    glScalef(scale, scale, 1); // 크기 조정

    glColor3f(r, g, b);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, 16, buffer);
    glDrawArrays(GL_QUADS, 0, num_quads * 4);
    glDisableClientState(GL_VERTEX_ARRAY);

    glPopMatrix();
}

int main() {
    if (!glfwInit()) return -1;

    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Digital Clock (C)", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, -1, 1);  // 좌상단 기준 좌표
    glMatrixMode(GL_MODELVIEW);

    while (!glfwWindowShouldClose(window)) {
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);  // 흰 배경
        glClear(GL_COLOR_BUFFER_BIT);
        glLoadIdentity();

        // 현재 시간 문자열 생성
        time_t now = time(NULL);
        struct tm* t = localtime(&now);
        char timeStr[16];
        sprintf_s(timeStr, sizeof(timeStr), "%02d:%02d:%02d", t->tm_hour, t->tm_min, t->tm_sec);

        // 확대 비율 지정
        float scale = 7.0f;

        // 텍스트 출력 (중앙 배치 보정)
        draw_text(100, 40, timeStr, 0.1f, 0.1f, 0.1f, scale);  // 어두운 회색

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
