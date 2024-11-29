#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100

int comparisonCount = 0;  // �� Ƚ��
int moveCount = 0;        // �̵� Ƚ��
int totalComparisons = 0; // �� �� Ƚ��
int totalMoveCount = 0;   // �� �̵� Ƚ��

// ���� �迭 ���� �Լ�
void generateRandomArray(int array[]) {
    for (int i = 0; i < SIZE; i++) {
        array[i] = rand() % 1000; // 0~999 ������ ���� ��
    }
}

// �迭 ��� �Լ�
void printArray(int array[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

// ���� �Լ� (����Ʈ�� �ٽ�)
int partition(int array[], int low, int high) {
    int pivot = array[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        comparisonCount++;
        if (array[j] <= pivot) {
            i++;
            moveCount += 2; // ���� �۾� (2�� �̵� �߻�)
            int temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
    }

    // �ǹ��� �ùٸ� ��ġ�� �̵�
    moveCount += 2; // ���� �۾� (2�� �̵� �߻�)
    int temp = array[i + 1];
    array[i + 1] = array[high];
    array[high] = temp;

    return i + 1;
}

// �� ���� �Լ�
void quickSort(int array[], int low, int high, int* rounds, int isFirst) {
    if (low < high) {
        int pi = partition(array, low, high);

        // ù ��° ���࿡���� ���� ���� ���
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

// �� ���� ���� �Լ�
void doQuickSort(int array[], int low, int high, int isFirst) {
    int rounds = 0; // ���� ī��Ʈ �ʱ�ȭ
    quickSort(array, low, high, &rounds, isFirst);
    if (isFirst) {
        printf("\n");
    }
}

int main(int argc, char* argv[]) {
    srand(time(NULL));
    int array[SIZE];

    printf("Quick Sort Run\n"); // ��� �޽��� (�� ���� ���)

    for (int i = 0; i < 20; i++) {
        generateRandomArray(array);
        comparisonCount = 0;
        moveCount = 0;

        if (i == 0) {
            // ù ��° ���࿡���� ���� ������ ���
            doQuickSort(array, 0, SIZE - 1, 1);
            printf("Result\n");
            printArray(array, SIZE);
        }
        else {
            // ������ ���࿡���� ��� ���� ���ĸ� ����
            doQuickSort(array, 0, SIZE - 1, 0);
        }

        totalComparisons += comparisonCount;
        totalMoveCount += moveCount;
    }

    // ��� ���
    printf("\nAverage Comparisons: %.2f\n", totalComparisons / 20.0);
    printf("Average Moves: %.2f\n", totalMoveCount / 20.0);
    return 0;
}
