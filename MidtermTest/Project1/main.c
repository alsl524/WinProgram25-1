#include <stdio.h>

// 5. ������ �Է¹޾� 50 �̻��̸� 1, �ƴϸ� 0 ��ȯ
int PassOrFail(int score) {
    if (score >= 50) return 1;
    else return 0;
}

int main() {
    int myExpectedScore = 75;  // �� ������ �����ϴ� ������ �����ص� ��

    // 6. PassOrFail ����� ���� �޽��� ���
    if (PassOrFail(myExpectedScore)) {
        printf("����� �����ϴ�!\n");
    }
    else {
        printf("�츮�� ���ߴ١�  ������̴١�\n");
    }

    return 0;
}
