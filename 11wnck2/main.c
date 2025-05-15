#pragma comment(lib, "opengl32.lib")
#include <GLFW/glfw3.h>
#include <math.h>

#define M_PI 3.1415926535f
#define WINDOW_WIDTH 494
#define WINDOW_HEIGHT 438

// ��/Ÿ�� �׸��� �Լ�
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

// �ܰ��� ��
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

// �� �׸��� �Լ�
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
    glOrtho(-1, 1, -1, 1, -1, 1); // -1~1 ��ǥ�� ����

    while (!glfwWindowShouldClose(window)) {
        glClearColor(1, 1, 1, 1); // ��� ���
        glClear(GL_COLOR_BUFFER_BIT);

        // [�� �� ��ġ ����] => �߽� (cx, cy), ������
        float faceX = 0.0f;  // �¿�
        float faceY = 0.0f;  // ���Ʒ�
        float faceRadius = 0.9f;
        draw_circle(faceX, faceY, faceRadius, 100, 0.0f, 0.5f, 1.0f, 0, 1.0f);
        draw_outline_circle(faceX, faceY, faceRadius, 100, 0, 0, 0, 0, 1.0f);

        // [�� �ֺ� ��� �� ��ġ] => �߽� x, y ����
        draw_circle(-0.15f, -0.2f, 0.2f, 100, 1, 1, 1, 0, 1.0f);  // ����
        draw_circle(0.15f, -0.2f, 0.2f, 100, 1, 1, 1, 0, 1.0f);  // ������

        // [�� ��ġ ����] => �߾ӿ��� ��¦ �Ʒ�
        draw_circle(0.0f, -0.01f, 0.13f, 100, 0, 0, 0, 1, 0.8f);

        // [�� ��ġ] => ����(x=-0.6), ������(x=0.6)
        draw_circle(-0.6f, 0.3f, 0.07f, 60, 0, 0, 0, 0, 1);  // ����
        draw_circle(0.6f, 0.3f, 0.07f, 60, 0, 0, 0, 0, 1);  // ������

        // [���� ��ġ �� ���� ����]
        // ���� ���� 3�� (���� x1,y1 / �� x2,y2)
        draw_line(-0.25f, -0.10f, -0.5f, -0.05f, 3.0f);  // ����
        draw_line(-0.25f, -0.16f, -0.5f, -0.16f, 3.0f);  // �߰�
        draw_line(-0.25f, -0.22f, -0.5f, -0.28f, 3.0f);  // �Ʒ�

        // ������ ���� 3��
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
