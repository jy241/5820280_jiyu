#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 100

void generateRandomNumbers(int array[]) {
    for (int i = 0; i < ARRAY_SIZE; i++) {
        array[i] = rand() % 1000; // 0-999 ������ ���� ���� ����
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
            (*moveCount)++; // temp�� �� �ֱ�

            int j;
            for (j = i; j >= gap && array[j - gap] > temp; j -= gap) {
                (*comparisonCount)++; // �� Ƚ�� ����
                array[j] = array[j - gap];
                (*moveCount)++; // �迭 �̵�
            }
            (*comparisonCount)++; // ������ ��
            array[j] = temp;
            (*moveCount)++; // �迭 �̵�
        }
        gap /= divisor;

        // �� �ܰ��� �迭 ���
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
        (*moveCount)++; // key�� �� �ֱ�
        int j = i - 1;

        while (j >= 0 && array[j] > key) {
            (*comparisonCount)++; // �� Ƚ�� ����
            array[j + 1] = array[j];
            (*moveCount)++; // �迭 �̵�
            j--;
        }
        (*comparisonCount)++; // ������ ��
        array[j + 1] = key;
        (*moveCount)++; // �迭 �̵�
    }

    printf("\nSorted array after Insertion Sort:\n");
    printArray(array);
}

int main() {
    srand(time(NULL)); // ���� �õ� �ʱ�ȭ
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

    // �迭�� �ٽ� �����Ͽ� ���� ������ ���� �ʱ�ȭ
    int arrayForInsertion[ARRAY_SIZE];
    generateRandomNumbers(arrayForInsertion);

    // Insertion Sort
    printf("Insertion Sort:\n");
    doInsertionSort(arrayForInsertion, &comparisonCount, &moveCount);
    printf("Insertion Sort - Comparisons: %d, Moves: %d\n", comparisonCount, moveCount);

    return 0;
}
