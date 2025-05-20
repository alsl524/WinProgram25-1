#pragma comment(lib, "opengl32.lib")
#include <GLFW/glfw3.h>
#include <math.h>
#include <time.h>

#define M_PI 3.1415926535f
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

// ⭕ 원 또는 타원 그리기 함수
// cx, cy: 중심 좌표, r: 반지름, segments: 분할수
// 색상 (r_col, g_col, b_col), is_ellipse: 타원 여부, scale_y: Y 스케일
void draw_circle(float cx, float cy, float r, int segments, float r_col, float g_col, float b_col, int is_ellipse, float scale_y) {
    glColor3f(r_col, g_col, b_col);
    glBegin(GL_POLYGON);
    for (int i = 0; i < segments; i++) {
        float theta = 2.0f * M_PI * i / segments;
        float x = r * cosf(theta);
        float y = r * sinf(theta) * (is_ellipse ? scale_y : 1.0f);
        glVertex2f(cx + x, cy + y);
    }
    glEnd();
}

// 🕓 시계 바늘 그리기 함수
// cx, cy: 중심좌표, length: 길이, angle_deg: 각도(도), 색상(r,g,b), thickness: 굵기
void draw_hand(float cx, float cy, float length, float angle_deg, float r_col, float g_col, float b_col, float thickness) {
    float angle_rad = (angle_deg - 90) * M_PI / 180.0f; // OpenGL 기준에서 12시 정렬
    float x = cx + cosf(angle_rad) * length;
    float y = cy + sinf(angle_rad) * length;

    glLineWidth(thickness);
    glColor3f(r_col, g_col, b_col);
    glBegin(GL_LINES);
    glVertex2f(cx, cy);
    glVertex2f(x, y);
    glEnd();
}

// 📏 눈금 그리기 함수
// count: 총 눈금 개수, length: 길이, thickness: 굵기
void draw_ticks(float cx, float cy, float radius, int count, float length, float thickness, float r_col, float g_col, float b_col) {
    for (int i = 0; i < count; i++) {
        float angle = 2.0f * M_PI * i / count;
        float x1 = cx + cosf(angle) * (radius - length);
        float y1 = cy + sinf(angle) * (radius - length);
        float x2 = cx + cosf(angle) * radius;
        float y2 = cy + sinf(angle) * radius;

        glLineWidth(thickness);
        glColor3f(r_col, g_col, b_col);
        glBegin(GL_LINES);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        glEnd();
    }
}

int main() {
    if (!glfwInit()) return -1;  // GLFW 초기화 실패 시 종료

    // 🖥️ 창 생성
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "GLFW Clock", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glOrtho(-1, 1, -1, 1, -1, 1);  // OpenGL 좌표계를 -1 ~ 1로 설정 (중앙 중심)

    while (!glfwWindowShouldClose(window)) {
        glClearColor(1, 1, 1, 1); // 배경 흰색
        glClear(GL_COLOR_BUFFER_BIT); // 화면 지우기

        // 🕒 현재 시각 가져오기
        time_t now = time(NULL);
        struct tm* t = localtime(&now);

        float seconds = t->tm_sec;
        float minutes = t->tm_min + seconds / 60.0f;
        float hours = t->tm_hour % 12 + minutes / 60.0f;

        // 중심 좌표 설정
        float main_cx = 0.0f, main_cy = 0.0f;     // 회색 시계 중앙
        float sub_cx = 0.3f, sub_cy = 0.0f;       // 검은 초침 시계 (오른쪽에 위치)

        // 🕗 회색 시계 본체
        draw_circle(main_cx, main_cy, 0.8f, 100, 0.9f, 0.9f, 0.9f, 0, 1.0f); // 큰 회색 원
        draw_ticks(main_cx, main_cy, 0.8f, 60, 0.02f, 1.0f, 0, 0, 0);       // 기본 눈금 (60개)
        draw_ticks(main_cx, main_cy, 0.8f, 12, 0.04f, 3.0f, 0, 0, 0);       // 5의 배수 눈금 (굵음)

        // ⏰ 시침과 분침 (실제 시간 기준)
        draw_hand(main_cx, main_cy, 0.5f, -hours * 30, 0, 0, 0, 6.0f);      // 시침 (1시간 = 30도)
        draw_hand(main_cx, main_cy, 0.65f, -minutes * 6, 0, 0, 0, 4.0f);    // 분침 (1분 = 6도)

        // 🔴 검은색 초침 시계
        draw_circle(sub_cx, sub_cy, 0.25f, 100, 0.0f, 0.0f, 0.0f, 0, 1.0f);   // 검은 원
        draw_ticks(sub_cx, sub_cy, 0.25f, 60, 0.015f, 1.0f, 1, 1, 1);        // 초침 눈금 (흰색)
        draw_ticks(sub_cx, sub_cy, 0.25f, 12, 0.03f, 3.0f, 1, 1, 1);         // 5초마다 굵은 눈금

        draw_hand(sub_cx, sub_cy, 0.2f, -seconds * 6, 1, 0, 0, 2.0f);        // 초침 (빨간색)

        glfwSwapBuffers(window); // 버퍼 스왑
        glfwPollEvents();        // 이벤트 처리
    }

    // 종료 처리
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
