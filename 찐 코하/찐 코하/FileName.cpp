#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>

// 두 정수 중에서 큰 값을 반환하는 함수
int f(int a, int b) {
    return a > b ? a : b;
}

// 주어진 상자에서 구슬의 합이 가장 큰 구간을 찾는 함수
int findbead(int* box, int numbox, int select) {
    int maxsum = 0; // 최대 구슬 합을 저장하는 변수

    // 선택할 수 있는 상자의 개수가 0보다 클 때만 계산
    if (select > 0) {
        // 처음 M개의 상자를 선택한 경우의 구슬 합을 초기값으로 설정
        for (int i = 0; i < select; i++) {
            maxsum += box[i];
        }

        int current = maxsum; // 현재 구슬 합을 저장하는 변수

        // M개의 상자를 선택한 상태에서 한 칸씩 이동하며 구슬 합을 갱신
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