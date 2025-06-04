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

void drawShape(
    ShapeType shape,
    float x, float y,
    float scale,
    float angleDeg,
    float pivotX, float pivotY,
    float r, float g, float b,
    int keyCondition,         // 키 코드 (예: GLFW_KEY_W 또는 -1)
    bool negateKey,           // true면 "키가 눌리지 않았을 때" 출력
    GLFWwindow* window
) {
    // 🔑 키 조건 처리
    if (keyCondition != -1) {
        int keyState = glfwGetKey(window, keyCondition);
        if ((!negateKey && keyState != GLFW_PRESS) || (negateKey && keyState == GLFW_PRESS))
            return;  // 조건 불만족이면 그리지 않음
    }

    glPushMatrix(); // 현재 변환 행렬 저장 (stack에 저장)

    // 🎯 1단계: 도형의 기준 위치로 이동
    glTranslatef(x, y, 0);

    // 🎯 2단계: 회전 기준점을 중심으로 이동 (회전 중심 이동)
    glTranslatef(pivotX, pivotY, 0);

    // 🎯 3단계: 지정된 각도만큼 회전 (Z축 기준 회전)
    glRotatef(angleDeg, 0, 0, 1);

    // 🎯 4단계: 회전 기준점을 다시 원래대로 되돌림 (이동 보정)
    glTranslatef(-pivotX, -pivotY, 0);

    // 🎯 5단계: 도형의 크기 비율 조절
    glScalef(scale, scale, 1);

    // 도형 색 설정
    glColor3f(r, g, b);

    // 도형 유형에 따라 분기하여 각각의 도형을 그리기
    switch (shape) {
    case SHAPE_CIRCLE:
        // ⭕ 원 그리기 (삼각형 팬)
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(0, 0);  // 중심점
        for (int i = 0; i <= 50; i++) {
            float a = 2 * PI * i / 50;   // 360도 = 2π
            glVertex2f(cosf(a), sinf(a));
        }
        glEnd();
        break;

    case SHAPE_LINE:
        // ─ 선 그리기 (좌우로 -1 ~ 1)
        glBegin(GL_LINES);
        glVertex2f(-1, 0);
        glVertex2f(1, 0);
        glEnd();
        break;

    case SHAPE_POINT:
        // · 점 그리기
        glPointSize(8.0f);              // 점 크기 설정
        glBegin(GL_POINTS);
        glVertex2f(0, 0);
        glEnd();
        break;

    case SHAPE_RECT:
        // ◼ 사각형 (정사각형 기준)
        glBegin(GL_QUADS);
        glVertex2f(-0.5f, 0.5f);  // 좌상단
        glVertex2f(0.5f, 0.5f);   // 우상단
        glVertex2f(0.5f, -0.5f);  // 우하단
        glVertex2f(-0.5f, -0.5f); // 좌하단
        glEnd();
        break;

    case SHAPE_SEMI_CIRCLE:
        // 🌓 반원 그리기 (삼각형 팬 사용)
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(0, 0);  // 중심점
        for (int i = 0; i <= 25; i++) {
            float a = PI * i / 25;      // 반원은 0~π (180도)
            glVertex2f(cosf(a), sinf(a));
        }
        glEnd();
        break;

    case SHAPE_STAR:
        // ⭐ 별 그리기: 중심에서 5개의 꼭짓점 그리기 (10개 점)
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(0, 0);  // 중심

        for (int i = 0; i <= 10; i++) {
            float angle = i * (PI / 5); // 36도 간격
            float radius = (i % 2 == 0) ? 1.0f : 0.5f;  // 짝수: 바깥 / 홀수: 안쪽
            glVertex2f(cosf(angle) * radius, sinf(angle) * radius);
        }
        glEnd();
        break;

    case SHAPE_RECT2:
        // ▭ 직사각형 그리기 (가로:1.0, 세로:0.5)
        glBegin(GL_QUADS);
        glVertex2f(-0.5f, 0.25f);  // 좌상단
        glVertex2f(0.5f, 0.25f);   // 우상단
        glVertex2f(0.5f, -0.25f);  // 우하단
        glVertex2f(-0.5f, -0.25f); // 좌하단
        glEnd();
        break;

        // 기존 switch문 마지막에 이어붙이세요
    case SHAPE_TRIANGLE:
        glBegin(GL_TRIANGLES);
        glVertex2f(0.0f, 1.0f);   // 상단
        glVertex2f(-1.0f, -1.0f); // 좌하단
        glVertex2f(1.0f, -1.0f);  // 우하단
        glEnd();
        break;

    case SHAPE_HEXAGON:
        glBegin(GL_POLYGON);
        for (int i = 0; i < 6; i++) {
            float angle = 2 * PI * i / 6;
            glVertex2f(cosf(angle), sinf(angle));
        }
        glEnd();
        break;

    case SHAPE_ARROW:
        glBegin(GL_TRIANGLES); // 머리
        glVertex2f(0.0f, 1.0f);
        glVertex2f(-0.5f, 0.0f);
        glVertex2f(0.5f, 0.0f);
        glEnd();

        glBegin(GL_QUADS); // 몸통
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
        glVertex2f(0, -0.5f);  // 하단
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
            float angle = 2 * PI * i / 8.0f;  // 360도를 8등분
            glVertex2f(cosf(angle), sinf(angle));
        }
        glEnd();
        break;

    }

    glPopMatrix();  // 이전 좌표 변환 상태로 복구
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

    // 메인 루프
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0, 0, 0, 1);         // 배경색 
        glClear(GL_COLOR_BUFFER_BIT);    // 색 버퍼 초기화 → 이전 도형 모두 삭제
        // 시간 기반 회전 각도
        float time = glfwGetTime();
        float earthSpinAngle = time * -50;   // 자전 (시계)
        
        float scale = 0.2f;
        // 키 입력으로 크기 조절
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
            scale += 0.5f;
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
            scale -= 0.01f;
            if (scale < 0.05f) scale = 0.05f; // 최소 크기 제한
        }
   
        drawShape(
            SHAPE_STAR,        // 도형: 원
            0.0f, 0.0f,          // 위치: 도형의 기본 위치 (회전 중심에서의 상대 위치)
            scale,                // 크기 배율
            earthSpinAngle,                   // 회전 각도 (시간에 따라 변하는 값)
            0.0f, 0.0f,          // 회전 기준점 (pivot): (0, 0) → 창의 중심
            1.0f, 1.0f, 0.0f,    // 색상: 노란색
            -1,                  // 키 -1면 조건 없음 (항상 출력) GLFW_KEY_W
            false,               // true(진실), false(거짓)  negateKey: false → 키가 안 눌려도 그림 
            window               // 윈도우 포인터
        );

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
        // 종료 처리
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

