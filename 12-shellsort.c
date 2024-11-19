#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 100

void generateRandomNumbers(int array[]) {
    for (int i = 0; i < ARRAY_SIZE; i++) {
        array[i] = rand() % 1000; // 0-999 사이의 랜덤 숫자 생성
    }
}

void printArray(int array[]) {
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

void doShellSort(int array[], int divisor, int* comparisonCount, int* moveCount) {
    int gap = ARRAY_SIZE / divisor;
    int temp;

    printf("\nSorting with gap = %d:\n", gap);
    printArray(array);

    *comparisonCount = 0;
    *moveCount = 0;

    while (gap > 0) {
        for (int i = gap; i < ARRAY_SIZE; i++) {
            temp = array[i];
            (*moveCount)++; // temp에 값 넣기

            int j;
            for (j = i; j >= gap && array[j - gap] > temp; j -= gap) {
                (*comparisonCount)++; // 비교 횟수 증가
                array[j] = array[j - gap];
                (*moveCount)++; // 배열 이동
            }
            (*comparisonCount)++; // 마지막 비교
            array[j] = temp;
            (*moveCount)++; // 배열 이동
        }
        gap /= divisor;

        // 각 단계의 배열 출력
        if (gap > 0) {
            printf("\nSorting with gap = %d:\n", gap);
            printArray(array);
        }
    }

    printf("\nSorted shellArray (gap = %d):\n", divisor);
    printArray(array);
}

void doInsertionSort(int array[], int* comparisonCount, int* moveCount) {
    *comparisonCount = 0;
    *moveCount = 0;

    for (int i = 1; i < ARRAY_SIZE; i++) {
        int key = array[i];
        (*moveCount)++; // key에 값 넣기
        int j = i - 1;

        while (j >= 0 && array[j] > key) {
            (*comparisonCount)++; // 비교 횟수 증가
            array[j + 1] = array[j];
            (*moveCount)++; // 배열 이동
            j--;
        }
        (*comparisonCount)++; // 마지막 비교
        array[j + 1] = key;
        (*moveCount)++; // 배열 이동
    }

    printf("\nSorted array after Insertion Sort:\n");
    printArray(array);
}

int main() {
    srand(time(NULL)); // 랜덤 시드 초기화
    int array[ARRAY_SIZE];
    int comparisonCount, moveCount;

    // Shell Sort (n/2)
    generateRandomNumbers(array);
    printf("Shell Sort (n/2):\n");
    doShellSort(array, 2, &comparisonCount, &moveCount);
    printf("\nShell Sort (n/2) - Comparisons: %d, Moves: %d\n\n", comparisonCount, moveCount);

    // Shell Sort (n/3)
    generateRandomNumbers(array);
    printf("Shell Sort (n/3):\n");
    doShellSort(array, 3, &comparisonCount, &moveCount);
    printf("\nShell Sort (n/3) - Comparisons: %d, Moves: %d\n\n", comparisonCount, moveCount);

    // 배열을 다시 생성하여 삽입 정렬을 위해 초기화
    int arrayForInsertion[ARRAY_SIZE];
    generateRandomNumbers(arrayForInsertion);

    // Insertion Sort
    printf("Insertion Sort:\n");
    doInsertionSort(arrayForInsertion, &comparisonCount, &moveCount);
    printf("Insertion Sort - Comparisons: %d, Moves: %d\n", comparisonCount, moveCount);

    return 0;
}
