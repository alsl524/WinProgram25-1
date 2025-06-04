#pragma comment(lib, "opengl32.lib")       // OpenGL 1.1 라이브러리를 링커에 자동 연결
#include <GLFW/glfw3.h>                    // GLFW: 창 생성, 입력 이벤트 처리용 라이브러리
#include <math.h>                          // 삼각함수 sinf(), cosf() 사용을 위한 헤더
#include <stdbool.h>                       // bool, true, false 타입 사용을 위한 헤더

// 상수 정의
#define PI 3.1415926535f                   // 원주율 (파이)
#define WINDOW_WIDTH 800                  // 창 너비
#define WINDOW_HEIGHT 600                 // 창 높이

// 🌐 도형 종류를 정의하는 열거형 (ShapeType)
// 이 열거형을 통해 어떤 도형을 그릴지 지정
typedef enum {
    SHAPE_CIRCLE,         // ⭕ 원
    SHAPE_SEMI_CIRCLE,    // 🌓 반원
    SHAPE_POINT,          // · 점
    SHAPE_LINE,           // ─ 선
    SHAPE_RECT,           // ◼ 정사각형
    SHAPE_RECT2,          // ▭ 직사각형
    SHAPE_TRIANGLE,       // 🔺 정삼각형
    SHAPE_STAR,           // ⭐ 별 (5각)
    SHAPE_HEXAGON,        // ⬡ 육각형
    SHAPE_ARROW,          // ➤ 화살표
    SHAPE_CROSS,          // ✚ 십자
    SHAPE_HEART,          // ❤️ 하트
    SHAPE_OCTAGON         // 🛑 팔각형           
} ShapeType;


/*
🎯 범용 도형 그리기 함수

shape       : 도형 종류 (SHAPE_CIRCLE 등)
x, y        : 위치 좌표
scale       : 크기 배율 (0.5면 절반 크기)
angleDeg    : 회전 각도 (도 단위)
pivotX/Y    : 회전 중심 (x, y 기준이 아님)
r/g/b       : 색상 (0~1 사이 RGB 값)
keyCondition: 특정 키가 눌렸을 때만 그리기 (GLFW_KEY_SPACE 등, -1은 무조건 그리기)
window      : 현재 GLFW 윈도우 객체 포인터
*/
void drawRotatingShape(
    ShapeType shape,
    float orbitAngleDeg,
    float orbitRadius,
    float spinAngleDeg,
    float scale,
    float r, float g, float b,
    float orbitCenterX, float orbitCenterY,
    GLFWwindow* window,
    int keyCondition,         // ← 추가
    bool negateKey            // ← 추가
) {

    // 🔑 키 조건 처리
    if (keyCondition != -1) {
        int keyState = glfwGetKey(window, keyCondition);
        if ((!negateKey && keyState != GLFW_PRESS) || (negateKey && keyState == GLFW_PRESS))
            return;  // 조건을 만족하지 않으면 출력하지 않음
    }

    glPushMatrix();

    // [1] 공전 중심으로 이동
    glTranslatef(orbitCenterX, orbitCenterY, 0);

    // [2] 공전 회전 + 공전 반지름 거리만큼 이동
    glRotatef(orbitAngleDeg, 0, 0, 1);
    glTranslatef(orbitRadius, 0, 0);

    // [3] 자전 (자기 중심 회전) + 크기 적용
    glRotatef(spinAngleDeg, 0, 0, 1);
    glScalef(scale, scale, 1);

    // [4] 색상 설정
    glColor3f(r, g, b);

    // [5] 도형 그리기
    switch (shape) {
    case SHAPE_CIRCLE:
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(0, 0);
        for (int i = 0; i <= 50; i++) {
            float a = 2 * PI * i / 50;
            glVertex2f(cosf(a), sinf(a));
        }
        glEnd();
        break;

    case SHAPE_SEMI_CIRCLE:
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(0, 0);
        for (int i = 0; i <= 25; i++) {
            float a = PI * i / 25;
            glVertex2f(cosf(a), sinf(a));
        }
        glEnd();
        break;

    case SHAPE_POINT:
        glPointSize(8.0f);
        glBegin(GL_POINTS);
        glVertex2f(0, 0);
        glEnd();
        break;

    case SHAPE_LINE:
        glBegin(GL_LINES);
        glVertex2f(-1, 0);
        glVertex2f(1, 0);
        glEnd();
        break;

    case SHAPE_RECT:
        glBegin(GL_QUADS);
        glVertex2f(-0.5f, 0.5f);
        glVertex2f(0.5f, 0.5f);
        glVertex2f(0.5f, -0.5f);
        glVertex2f(-0.5f, -0.5f);
        glEnd();
        break;

    case SHAPE_RECT2:
        glBegin(GL_QUADS);
        glVertex2f(-0.5f, 0.25f);
        glVertex2f(0.5f, 0.25f);
        glVertex2f(0.5f, -0.25f);
        glVertex2f(-0.5f, -0.25f);
        glEnd();
        break;

    case SHAPE_TRIANGLE:
        glBegin(GL_TRIANGLES);
        glVertex2f(0.0f, 1.0f);
        glVertex2f(-1.0f, -1.0f);
        glVertex2f(1.0f, -1.0f);
        glEnd();
        break;

    case SHAPE_HEXAGON:
        glBegin(GL_POLYGON);
        for (int i = 0; i < 6; i++) {
            float a = 2 * PI * i / 6;
            glVertex2f(cosf(a), sinf(a));
        }
        glEnd();
        break;

    case SHAPE_STAR:
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(0, 0);
        for (int i = 0; i <= 10; i++) {
            float a = i * (PI / 5);
            float radius = (i % 2 == 0) ? 1.0f : 0.5f;
            glVertex2f(cosf(a) * radius, sinf(a) * radius);
        }
        glEnd();
        break;

    case SHAPE_ARROW:
        glBegin(GL_TRIANGLES);
        glVertex2f(0.0f, 1.0f);
        glVertex2f(-0.5f, 0.0f);
        glVertex2f(0.5f, 0.0f);
        glEnd();

        glBegin(GL_QUADS);
        glVertex2f(-0.2f, 0.0f);
        glVertex2f(0.2f, 0.0f);
        glVertex2f(0.2f, -1.0f);
        glVertex2f(-0.2f, -1.0f);
        glEnd();
        break;

    case SHAPE_CROSS:
        glBegin(GL_QUADS);
        glVertex2f(-0.2f, 0.5f);
        glVertex2f(0.2f, 0.5f);
        glVertex2f(0.2f, -0.5f);
        glVertex2f(-0.2f, -0.5f);
        glEnd();

        glBegin(GL_QUADS);
        glVertex2f(-0.5f, 0.2f);
        glVertex2f(0.5f, 0.2f);
        glVertex2f(0.5f, -0.2f);
        glVertex2f(-0.5f, -0.2f);
        glEnd();
        break;

    case SHAPE_HEART:
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(0, -0.5f);
        for (int i = 0; i <= 100; i++) {
            float t = i / 100.0f * 2 * PI;
            float x = 0.16f * sinf(t) * sinf(t) * sinf(t);
            float y = 0.13f * cosf(t) - 0.05f * cosf(2 * t) - 0.02f * cosf(3 * t) - 0.01f * cosf(4 * t);
            glVertex2f(x * 6.0f, y * 6.0f);
        }
        glEnd();
        break;

    case SHAPE_OCTAGON:
        glBegin(GL_POLYGON);
        for (int i = 0; i < 8; i++) {
            float a = 2 * PI * i / 8;
            glVertex2f(cosf(a), sinf(a));
        }
        glEnd();
        break;
    }

    glPopMatrix();
}
int main() {
    // GLFW 초기화
    if (!glfwInit()) return -1;

    // 윈도우 생성
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Rotate Semi-Circle", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    // OpenGL 컨텍스트 바인딩
    glfwMakeContextCurrent(window);

    // 2D 좌표계 설정
    glOrtho(-1, 1, -1, 1, -1, 1);
    float time = 0;
    float speed = 0.5f;   // 속도 (한 프레임당 증가량)
    // 메인 루프
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0, 0, 0, 1);         // 배경색
        glClear(GL_COLOR_BUFFER_BIT);    // 색 버퍼 초기화 → 이전 도형 모두 삭제

        // 시간 기반 회전 각도
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) time += speed;
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) time -= speed;

        float earthOrbitAngle = time * 20;    // 공전 (반시계)
        float earthSpinAngle = time * -50;   // 자전 (시계)
        
        drawRotatingShape(
            SHAPE_CIRCLE,
            0,
            0.0f,              // 태양으로부터의 거리
            0,
            0.2f,              // 크기
            1.0f, 1.0f, 0.0f,        // 색
            0.0f, 0.0f,        // 태양 중심
            window,
            -1, false          // 키 입력 true(진실), false(거짓)
        );
        drawRotatingShape(
            SHAPE_CIRCLE,
            earthOrbitAngle,
            0.6f,              // 태양으로부터의 거리
            earthSpinAngle,
            0.1f,              // 크기
            0, 0.3f, 1,        // 파란색
            0.0f, 0.0f,        // 태양 중심
            window,
            -1, false          // 키 입력 true(진실), false(거짓)
        );

        float moonOrbitAngle = time * 30;     // 공전
        float moonSpinAngle = time * -90;    // 자전

        // 먼저 지구 위치 계산 (공전 중심 좌표로 사용)
        float earthX = cosf(earthOrbitAngle * PI / 180.0f) * 0.6f;
        float earthY = sinf(earthOrbitAngle * PI / 180.0f) * 0.6f;

        drawRotatingShape(
            SHAPE_CIRCLE,
            moonOrbitAngle,
            0.2f,             // 지구로부터의 거리
            moonSpinAngle,
            0.05f,            // 크기
            0.7f, 0.7f, 0.7f, // 회색
            earthX, earthY,   // 공전 중심을 지구 위치로 지정
            window,
            GLFW_KEY_W, true  // W키를 누를 때만 달을 그림 true(진실), false(거짓)
        );

        drawRotatingShape(
            SHAPE_STAR,
            moonOrbitAngle,
            0.2f,             // 지구로부터의 거리
            moonSpinAngle,
            0.05f,            // 크기
            0.7f, 0.7f, 0.7f, // 회색
            earthX, earthY,   // 공전 중심을 지구 위치로 지정
            window,
            GLFW_KEY_W, false  // W키를 누를 때만 달을 그림 true(진실), false(거짓)
        );

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    // 종료 처리
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
