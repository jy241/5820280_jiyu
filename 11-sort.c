#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100

void initializeRandom() {
    srand(time(NULL)); // ���� �õ� �ʱ�ȭ
}

void generateRandomData(int data[]) {
    for (int i = 0; i < SIZE; i++) {
        data[i] = rand() % 1000; // 0-999 ������ ���� ������ ����
    }
}

void printArray(int data[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", data[i]);
    }
    printf("\n");
}

void doSelectionSort(int data[]) {
    int tempData[SIZE];
    for (int i = 0; i < SIZE; i++) {
        tempData[i] = data[i]; // ���� �����͸� ����
    }

    printf("Selection Sort:\n");
    for (int i = 0; i < SIZE - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < SIZE; j++) {
            if (tempData[j] < tempData[minIndex]) {
                minIndex = j;
            }
        }
        // Swap
        int temp = tempData[i];
        tempData[i] = tempData[minIndex];
        tempData[minIndex] = temp;

        // 10, 30, 50, 70, 90, 99�ܰ� ���
        if (i == 9 || i == 29 || i == 49 || i == 69 || i == 89 || i == SIZE - 2) {
            printf("Step %d: ", i + 1);
            printArray(tempData, SIZE);
        }
    }
}

void doInsertionSort(int data[]) {
    int totalComparisons, trials = 20; // ���� ���� �õ� Ƚ��
    int totalComparisonsSum = 0;
    int finalSortedData[SIZE]; // ���� ����� ������ �迭

    for (int t = 0; t < trials; t++) {
        int tempData[SIZE];
        for (int i = 0; i < SIZE; i++) {
            tempData[i] = data[i]; // ���� �����͸� ����
        }

        totalComparisons = 0; // �� Ƚ�� �ʱ�ȭ

        for (int i = 1; i < SIZE; i++) {
            int key = tempData[i];
            int j = i - 1;

            while (j >= 0 && tempData[j] > key) {
                tempData[j + 1] = tempData[j];
                j--;
                totalComparisons++;
            }
            tempData[j + 1] = key;

            // ��Ƚ�� ����
            if (j >= 0) {
                totalComparisons++;
            }
        }

        totalComparisonsSum += totalComparisons; // �� �� Ƚ�� �ջ�

        // ���� ����� ������ �õ����� ����
        if (t == trials - 1) {
            for (int i = 0; i < SIZE; i++) {
                finalSortedData[i] = tempData[i];
            }
        }
    }

    printf("\nInsertion Sort Compare Average: %.0f\n", (float)totalComparisonsSum / trials);
    printf("Insertion Sort Result:\n");
    printArray(finalSortedData, SIZE); // ���� ���� ��� ���
}

void doBubbleSort(int data[]) {
    int totalComparisons, trials = 20; // ���� ���� �õ� Ƚ��
    int totalComparisonsSum = 0;
    int finalSortedData[SIZE]; // ���� ����� ������ �迭

    for (int t = 0; t < trials; t++) {
        int tempData[SIZE];
        for (int i = 0; i < SIZE; i++) {
            tempData[i] = data[i]; // ���� �����͸� ����
        }

        totalComparisons = 0; // �� Ƚ�� �ʱ�ȭ

        for (int i = 0; i < SIZE - 1; i++) {
            for (int j = 0; j < SIZE - i - 1; j++) {
                if (tempData[j] > tempData[j + 1]) {
                    // Swap
                    int temp = tempData[j];
                    tempData[j] = tempData[j + 1];
                    tempData[j + 1] = temp;
                }
                totalComparisons++; // �� Ƚ�� ����
            }
        }

        totalComparisonsSum += totalComparisons; // �� �� Ƚ�� �ջ�

        // ���� ����� ������ �õ����� ����
        if (t == trials - 1) {
            for (int i = 0; i < SIZE; i++) {
                finalSortedData[i] = tempData[i];
            }
        }
    }

    printf("\nBubble Sort Compare Average: %.0f\n", (float)totalComparisonsSum / trials);
    printf("Bubble Sort Result:\n");
    printArray(finalSortedData, SIZE); // ���� ���� ��� ���
}

int main() {
    initializeRandom(); // ���� �õ� �ʱ�ȭ
    int randomData[SIZE];

    generateRandomData(randomData);
    doSelectionSort(randomData);
    doInsertionSort(randomData);
    doBubbleSort(randomData);

    return 0;
}
