#include <stdio.h>

// 5. 점수를 입력받아 50 이상이면 1, 아니면 0 반환
int PassOrFail(int score) {
    if (score >= 50) return 1;
    else return 0;
}

int main() {
    int myExpectedScore = 75;  // ← 본인이 예상하는 점수로 수정해도 됨

    // 6. PassOrFail 결과에 따라 메시지 출력
    if (PassOrFail(myExpectedScore)) {
        printf("재시험 없습니다!\n");
    }
    else {
        printf("우리는 망했다…  재시험이다…\n");
    }

    return 0;
}
