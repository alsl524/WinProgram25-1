#pragma comment(lib, "opengl32.lib")
#include <GLFW/glfw3.h>
#include <math.h>

#define M_PI 3.1415926535f
#define WINDOW_WIDTH 494
#define WINDOW_HEIGHT 438

// 원/타원 그리기 함수
void draw_circle(float cx, float cy, float r, int segments, float r_col, float g_col, float b_col, int is_ellipse, float scale_y) {
    glColor3f(r_col, g_col, b_col);
    glBegin(GL_POLYGON);
    for (int i = 0; i < segments; i++) {
        float theta = 2.0f * M_PI * (float)i / segments;
        float x = r * cosf(theta);
        float y = r * sinf(theta) * (is_ellipse ? scale_y : 1.0f);
        glVertex2f(cx + x, cy + y);
    }
    glEnd();
}

// 외곽선 원
void draw_outline_circle(float cx, float cy, float r, int segments, float r_col, float g_col, float b_col, int is_ellipse, float scale_y) {
    glColor3f(r_col, g_col, b_col);
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < segments; i++) {
        float theta = 2.0f * M_PI * (float)i / segments;
        float x = r * cosf(theta);
        float y = r * sinf(theta) * (is_ellipse ? scale_y : 1.0f);
        glVertex2f(cx + x, cy + y);
    }
    glEnd();
}

// 선 그리기 함수
void draw_line(float x1, float y1, float x2, float y2, float thickness) {
    glLineWidth(thickness);
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
}

int main() {
    if (!glfwInit()) return -1;

    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Cat Face Movable", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glOrtho(-1, 1, -1, 1, -1, 1); // -1~1 좌표계 설정

    while (!glfwWindowShouldClose(window)) {
        glClearColor(1, 1, 1, 1); // 배경 흰색
        glClear(GL_COLOR_BUFFER_BIT);

        // [얼굴 원 위치 조정] => 중심 (cx, cy), 반지름
        float faceX = 0.0f;  // 좌우
        float faceY = 0.0f;  // 위아래
        float faceRadius = 0.9f;
        draw_circle(faceX, faceY, faceRadius, 100, 0.0f, 0.5f, 1.0f, 0, 1.0f);
        draw_outline_circle(faceX, faceY, faceRadius, 100, 0, 0, 0, 0, 1.0f);

        // [입 주변 흰색 원 위치] => 중심 x, y 조정
        draw_circle(-0.15f, -0.2f, 0.2f, 100, 1, 1, 1, 0, 1.0f);  // 왼쪽
        draw_circle(0.15f, -0.2f, 0.2f, 100, 1, 1, 1, 0, 1.0f);  // 오른쪽

        // [코 위치 조정] => 중앙에서 살짝 아래
        draw_circle(0.0f, -0.01f, 0.13f, 100, 0, 0, 0, 1, 0.8f);

        // [눈 위치] => 왼쪽(x=-0.6), 오른쪽(x=0.6)
        draw_circle(-0.6f, 0.3f, 0.07f, 60, 0, 0, 0, 0, 1);  // 왼쪽
        draw_circle(0.6f, 0.3f, 0.07f, 60, 0, 0, 0, 0, 1);  // 오른쪽

        // [수염 위치 및 길이 조정]
        // 왼쪽 수염 3개 (시작 x1,y1 / 끝 x2,y2)
        draw_line(-0.25f, -0.10f, -0.5f, -0.05f, 3.0f);  // 위쪽
        draw_line(-0.25f, -0.16f, -0.5f, -0.16f, 3.0f);  // 중간
        draw_line(-0.25f, -0.22f, -0.5f, -0.28f, 3.0f);  // 아래

        // 오른쪽 수염 3개
        draw_line(0.25f, -0.10f, 0.5f, -0.05f, 3.0f);
        draw_line(0.25f, -0.16f, 0.5f, -0.16f, 3.0f);
        draw_line(0.25f, -0.22f, 0.5f, -0.28f, 3.0f);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
