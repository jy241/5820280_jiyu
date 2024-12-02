#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000  // 배열 크기 정의

int compareCount = 0;  // 비교 횟수를 저장할 전역 변수

// 임의의 숫자로 배열을 초기화하는 함수
void generateRandomArray(int* array) {
    for (int i = 0; i < SIZE; i++) {
        array[i] = rand() % 1000;  // 0부터 999 사이의 임의 숫자 생성
    }
}

// 순차 탐색 함수
int linearSearch(int* array, int target) {
    int count = 0;
    for (int i = 0; i < SIZE; i++) {
        count++;
        if (array[i] == target) {
            return count;  // 찾으면 비교 횟수 반환
        }
    }
    return count;  // 찾지 못하면 비교 횟수 반환
}

// 평균 순차 탐색 비교 횟수를 계산하는 함수
double getAverageLinearSearchCompareCount(int* array) {
    double totalCount = 0;
    for (int i = 0; i < 100; i++) {
        int target = array[rand() % SIZE];  // 랜덤 타겟 선택
        totalCount += linearSearch(array, target);  // 순차 탐색 수행
    }
    return totalCount / 100;  // 평균 비교 횟수 반환
}

// 퀵 정렬 함수
void quickSort(int* array, int low, int high) {
    if (low < high) {
        int pivot = array[high];  // 피벗 선택
        int i = (low - 1);
        for (int j = low; j < high; j++) {
            compareCount++;  // 비교 횟수 증가
            if (array[j] < pivot) {
                i++;
                // 스왑
                int temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
        }
        // 피벗과 스왑
        int temp = array[i + 1];
        array[i + 1] = array[high];
        array[high] = temp;
        // 분할 정복
        quickSort(array, low, i);
        quickSort(array, i + 2, high);
    }
}

// 퀵 정렬을 호출하고 비교 횟수를 초기화하는 함수
void getQuickSortCompareCount(int* array) {
    compareCount = 0;  // 비교 횟수 초기화
    quickSort(array, 0, SIZE - 1);  // 퀵 정렬 수행
}

// 이진 탐색 함수
int binarySearch(int* array, int low, int high, int target) {
    int count = 0;
    while (low <= high) {
        count++;
        int mid = low + (high - low) / 2;  // 중간 인덱스 계산
        if (array[mid] == target) {
            return count;  // 찾으면 비교 횟수 반환
        }
        if (array[mid] < target) {
            low = mid + 1;  // 오른쪽 탐색
        }
        else {
            high = mid - 1;  // 왼쪽 탐색
        }
    }
    return count;  // 찾지 못하면 비교 횟수 반환
}

// 평균 이진 탐색 비교 횟수를 계산하는 함수
double getAverageBinarySearchCompareCount(int* array) {
    double totalCount = 0;
    for (int i = 0; i < 100; i++) {
        int target = array[rand() % SIZE];  // 랜덤 타겟 선택
        totalCount += binarySearch(array, 0, SIZE - 1, target);  // 이진 탐색 수행
    }
    return totalCount / 100;  // 평균 비교 횟수 반환
}

// 배열의 처음 20개와 마지막 20개 요소를 출력하는 함수
void printArray(int* array) {
    printf("Array Sorting Result:\n");
    for (int i = 0; i < 20; i++)
        printf("%3d ", array[i]);  // 처음 20개 요소 출력
    printf("\n");
    for (int i = SIZE - 20; i < SIZE; i++)
        printf("%3d ", array[i]);  // 마지막 20개 요소 출력
    printf("\n");
}

// 메인 함수
int main(int argc, char* argv[]) {
    srand(time(NULL));  // 랜덤 시드 초기화

    // 3회 반복하여 실험 수행
    for (int run = 0; run < 3; run++) {
        int array[SIZE];  // 배열 선언
        generateRandomArray(array);  // 배열 초기화

        // 평균값을 반환받기 위한 조치
        printf("Run %d:\n", run + 1);
        printf("Average Linear Search Compare Count: %.2f\n",
            getAverageLinearSearchCompareCount(array));

        // 배열을 정렬하고 비교 횟수 출력
        getQuickSortCompareCount(array);
        printf("Quick Sort Compare Count: %d\n", compareCount);

        // 정렬된 배열에 대해 이진 탐색 평균 비교 횟수 출력
        printf("Average Binary Search Compare Count: %.2f\n\n",
            getAverageBinarySearchCompareCount(array));

        printArray(array);  // 배열 출력
    }

    return 0;  // 프로그램 종료
}
