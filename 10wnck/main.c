#pragma comment(lib, "Opengl32.lib")
#include <GLFW/glfw3.h>
#include <math.h>  // sin, cos

#define PI 3.14159265

void draw_triangle() {
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f); glVertex2f(-0.5f, -0.5f); // 빨강
    glColor3f(0.0f, 1.0f, 0.0f); glVertex2f(0.5f, -0.5f);  // 초록
    glColor3f(0.0f, 0.0f, 1.0f); glVertex2f(0.0f, 0.5f);   // 파랑
    glEnd();
}

void draw_rectangle() {
    glBegin(GL_QUADS);  // 사각형 (4점)
    glColor3f(1.0f, 1.0f, 0.0f);  // 노랑
    glVertex2f(-0.8f, 0.7f);
    glVertex2f(-0.3f, 0.7f);
    glVertex2f(-0.3f, 0.2f);
    glVertex2f(-0.8f, 0.2f);
    glEnd();
}

void draw_circle(float cx, float cy, float r, int segments) {
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0.5f, 1.0f, 1.0f);  // 밝은 하늘색
    glVertex2f(cx, cy);  // 중심
    for (int i = 0; i <= segments; i++) {
        float angle = 2.0f * PI * i / segments;
        float x = r * cosf(angle);
        float y = r * sinf(angle);
        glVertex2f(cx + x, cy + y);
    }
    glEnd();
}

int main() {
    if (!glfwInit()) return -1;

    GLFWwindow* window = glfwCreateWindow(500, 500, "GLFW: 도형들", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        draw_triangle();
        draw_rectangle();
        draw_circle(0.5f, 0.5f, 0.3f, 100);  // 원 (중심x, 중심y, 반지름, 세분화)

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
