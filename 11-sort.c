#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100

void initializeRandom() {
    srand(time(NULL)); // 랜덤 시드 초기화
}

void generateRandomData(int data[]) {
    for (int i = 0; i < SIZE; i++) {
        data[i] = rand() % 1000; // 0-999 사이의 랜덤 데이터 생성
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
        tempData[i] = data[i]; // 원본 데이터를 복사
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

        // 10, 30, 50, 70, 90, 99단계 출력
        if (i == 9 || i == 29 || i == 49 || i == 69 || i == 89 || i == SIZE - 2) {
            printf("Step %d: ", i + 1);
            printArray(tempData, SIZE);
        }
    }
}

void doInsertionSort(int data[]) {
    int totalComparisons, trials = 20; // 삽입 정렬 시도 횟수
    int totalComparisonsSum = 0;
    int finalSortedData[SIZE]; // 최종 결과를 저장할 배열

    for (int t = 0; t < trials; t++) {
        int tempData[SIZE];
        for (int i = 0; i < SIZE; i++) {
            tempData[i] = data[i]; // 원본 데이터를 복사
        }

        totalComparisons = 0; // 비교 횟수 초기화

        for (int i = 1; i < SIZE; i++) {
            int key = tempData[i];
            int j = i - 1;

            while (j >= 0 && tempData[j] > key) {
                tempData[j + 1] = tempData[j];
                j--;
                totalComparisons++;
            }
            tempData[j + 1] = key;

            // 비교횟수 증가
            if (j >= 0) {
                totalComparisons++;
            }
        }

        totalComparisonsSum += totalComparisons; // 총 비교 횟수 합산

        // 최종 결과를 마지막 시도에서 저장
        if (t == trials - 1) {
            for (int i = 0; i < SIZE; i++) {
                finalSortedData[i] = tempData[i];
            }
        }
    }

    printf("\nInsertion Sort Compare Average: %.0f\n", (float)totalComparisonsSum / trials);
    printf("Insertion Sort Result:\n");
    printArray(finalSortedData, SIZE); // 최종 정렬 결과 출력
}

void doBubbleSort(int data[]) {
    int totalComparisons, trials = 20; // 버블 정렬 시도 횟수
    int totalComparisonsSum = 0;
    int finalSortedData[SIZE]; // 최종 결과를 저장할 배열

    for (int t = 0; t < trials; t++) {
        int tempData[SIZE];
        for (int i = 0; i < SIZE; i++) {
            tempData[i] = data[i]; // 원본 데이터를 복사
        }

        totalComparisons = 0; // 비교 횟수 초기화

        for (int i = 0; i < SIZE - 1; i++) {
            for (int j = 0; j < SIZE - i - 1; j++) {
                if (tempData[j] > tempData[j + 1]) {
                    // Swap
                    int temp = tempData[j];
                    tempData[j] = tempData[j + 1];
                    tempData[j + 1] = temp;
                }
                totalComparisons++; // 비교 횟수 증가
            }
        }

        totalComparisonsSum += totalComparisons; // 총 비교 횟수 합산

        // 최종 결과를 마지막 시도에서 저장
        if (t == trials - 1) {
            for (int i = 0; i < SIZE; i++) {
                finalSortedData[i] = tempData[i];
            }
        }
    }

    printf("\nBubble Sort Compare Average: %.0f\n", (float)totalComparisonsSum / trials);
    printf("Bubble Sort Result:\n");
    printArray(finalSortedData, SIZE); // 최종 정렬 결과 출력
}

int main() {
    initializeRandom(); // 랜덤 시드 초기화
    int randomData[SIZE];

    generateRandomData(randomData);
    doSelectionSort(randomData);
    doInsertionSort(randomData);
    doBubbleSort(randomData);

    return 0;
}
