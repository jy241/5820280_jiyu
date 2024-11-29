#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100

int comparisonCount = 0;  // 비교 횟수
int moveCount = 0;        // 이동 횟수
int totalComparisons = 0; // 총 비교 횟수
int totalMoveCount = 0;   // 총 이동 횟수

// 랜덤 배열 생성 함수
void generateRandomArray(int array[]) {
    for (int i = 0; i < SIZE; i++) {
        array[i] = rand() % 1000; // 0~999 사이의 랜덤 값
    }
}

// 배열 출력 함수
void printArray(int array[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

// 분할 함수 (퀵소트의 핵심)
int partition(int array[], int low, int high) {
    int pivot = array[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        comparisonCount++;
        if (array[j] <= pivot) {
            i++;
            moveCount += 2; // 스왑 작업 (2번 이동 발생)
            int temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
    }

    // 피벗을 올바른 위치로 이동
    moveCount += 2; // 스왑 작업 (2번 이동 발생)
    int temp = array[i + 1];
    array[i + 1] = array[high];
    array[high] = temp;

    return i + 1;
}

// 퀵 정렬 함수
void quickSort(int array[], int low, int high, int* rounds, int isFirst) {
    if (low < high) {
        int pi = partition(array, low, high);

        // 첫 번째 실행에서만 정렬 과정 출력
        if (isFirst && (*rounds) % 10 == 0) {
            for (int i = 40; i < 60; i++) {
                printf("%d ", array[i]);
            }
            printf("\n\n");
        }
        (*rounds)++;

        quickSort(array, low, pi - 1, rounds, isFirst);
        quickSort(array, pi + 1, high, rounds, isFirst);
    }
}

// 퀵 정렬 실행 함수
void doQuickSort(int array[], int low, int high, int isFirst) {
    int rounds = 0; // 라운드 카운트 초기화
    quickSort(array, low, high, &rounds, isFirst);
    if (isFirst) {
        printf("\n");
    }
}

int main(int argc, char* argv[]) {
    srand(time(NULL));
    int array[SIZE];

    printf("Quick Sort Run\n"); // 출력 메시지 (한 번만 출력)

    for (int i = 0; i < 20; i++) {
        generateRandomArray(array);
        comparisonCount = 0;
        moveCount = 0;

        if (i == 0) {
            // 첫 번째 실행에서만 정렬 과정을 출력
            doQuickSort(array, 0, SIZE - 1, 1);
            printf("Result\n");
            printArray(array, SIZE);
        }
        else {
            // 나머지 실행에서는 출력 없이 정렬만 수행
            doQuickSort(array, 0, SIZE - 1, 0);
        }

        totalComparisons += comparisonCount;
        totalMoveCount += moveCount;
    }

    // 평균 출력
    printf("\nAverage Comparisons: %.2f\n", totalComparisons / 20.0);
    printf("Average Moves: %.2f\n", totalMoveCount / 20.0);
    return 0;
}
