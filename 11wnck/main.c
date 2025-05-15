#pragma comment(lib, "Opengl32.lib")
#include <GLFW/glfw3.h>
#include <math.h>   // sin, cos
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void draw_rotating_triangle(float angle) {
    float radius = 0.5f;

    // 회전 중심
    float cx = 0.0f;
    float cy = 0.0f;

    // 꼭짓점 각도 (초기 위치)
    float angles[3] = { 0.0f, 2.0f * M_PI / 3.0f, 4.0f * M_PI / 3.0f };

    glBegin(GL_TRIANGLES);
    for (int i = 0; i < 3; i++) {
        float a = angles[i] + angle;  // 회전된 각도
        float x = cx + radius * cosf(a);
        float y = cy + radius * sinf(a);

        // 색상 지정 (RGB)
        if (i == 0) glColor3f(1.0f, 0.0f, 0.0f);
        if (i == 1) glColor3f(0.0f, 1.0f, 0.0f);
        if (i == 2) glColor3f(0.0f, 0.0f, 1.0f);

        glVertex2f(x, y);
    }
    glEnd();
}

int main() {
    if (!glfwInit()) return -1;

    GLFWwindow* window = glfwCreateWindow(500, 500, "GLFW: Rotating Triangle", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    float angle = 0.0f;

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        draw_rotating_triangle(angle);
        angle += 0.01f;  // 회전 속도 (라디안)

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
