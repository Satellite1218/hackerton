#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>

// �� ���� �߿��� ū ���� ��ȯ�ϴ� �Լ�
int f(int a, int b) {
    return a > b ? a : b;
}

// �־��� ���ڿ��� ������ ���� ���� ū ������ ã�� �Լ�
int findbead(int* box, int numbox, int select) {
    int maxsum = 0; // �ִ� ���� ���� �����ϴ� ����

    // ������ �� �ִ� ������ ������ 0���� Ŭ ���� ���
    if (select > 0) {
        // ó�� M���� ���ڸ� ������ ����� ���� ���� �ʱⰪ���� ����
        for (int i = 0; i < select; i++) {
            maxsum += box[i];
        }

        int current = maxsum; // ���� ���� ���� �����ϴ� ����

        // M���� ���ڸ� ������ ���¿��� �� ĭ�� �̵��ϸ� ���� ���� ����
        for (int i = select; i < numbox; i++) {
            current = current - box[i - select] + box[i];
            maxsum = f(maxsum, current);
        }
    }

    return maxsum;
}

int main() {
    int numbox, select;
    scanf("%d %d", &numbox, &select);

    int* box = (int*)malloc(sizeof(int) * numbox);
    for (int i = 0; i < numbox; i++) {
        scanf("%d", &box[i]);
    }

    int maxsum = findbead(box, numbox, select);
    printf("%d\n", maxsum);

    free(box);

    return 0;
}