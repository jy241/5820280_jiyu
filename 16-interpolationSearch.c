#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 10000

// 함수 선언: 난수 배열 생성 함수
void generateRandomArray(int* array);
// 함수 선언: 퀵 정렬 함수
void QuickSort(int* array, int low, int high);
// 함수 선언: 배열의 구간을 나누는 함수 (퀵정렬에 사용)
int Partition(int* array, int low, int high);
// 함수 선언: 배열 출력 함수
void printArray(int* array);
// 함수 선언: 이진 탐색을 위한 평균 비교 횟수 구하는 함수
float getAverageBinarySearchCompareCount(int* array);
// 함수 선언: 보간 탐색을 위한 평균 비교 횟수 구하는 함수
float getAverageInterpolationSearchCompareCount(int* array);
// 함수 선언: 이진 탐색
int BinarySearch(int* array, int target);
// 함수 선언: 보간 탐색
int InterpolationSearch(int* array, int target);

int main(int argc, char* argv[]) {
    // 3번 반복하여 출력
    for (int i = 0; i < 3; i++) {
        // 각 반복마다 다른 시드값을 사용하여 난수 생성
        srand(time(NULL) + i);
        int array[SIZE];

        // 배열 생성 및 퀵정렬 실행
        generateRandomArray(array);
        QuickSort(array, 0, SIZE - 1);

        // 배열 출력
        printArray(array);

        // 이진 탐색과 보간 탐색 평균 비교 횟수 출력
        printf("Average Compare Count of Binary Search: %.2f\n",
            getAverageBinarySearchCompareCount(array));
        printf("Average Compare Count of Interpolation Search: %.2f\n",
            getAverageInterpolationSearchCompareCount(array));
        printf("\n");
    }
    return 0;
}

// 배열에 0부터 SIZE-1 사이의 난수를 저장하는 함수
void generateRandomArray(int* array) {
    for (int i = 0; i < SIZE; i++) {
        array[i] = rand() % SIZE;  // SIZE 범위 내에서 난수 생성
    }
}

// 퀵 정렬 함수 (배열을 정렬)
void QuickSort(int* array, int low, int high) {
    if (low < high) {
        // 배열을 파티션으로 나누고, 분할된 배열에 대해 재귀적으로 퀵 정렬 실행
        int pivotIndex = Partition(array, low, high);
        QuickSort(array, low, pivotIndex - 1);
        QuickSort(array, pivotIndex + 1, high);
    }
}

// 배열을 나누는 파티션 함수 (퀵정렬의 중요한 부분)
int Partition(int* array, int low, int high) {
    int pivot = array[high];  // 마지막 요소를 피벗으로 설정
    int i = low - 1;  // 피벗보다 작은 값을 놓을 위치

    // low부터 high-1까지의 값을 순차적으로 확인하며 피벗보다 작은 값은 앞쪽으로 보내기
    for (int j = low; j < high; j++) {
        if (array[j] <= pivot) {
            i++;
            // 값 스왑
            int temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
    }

    // 피벗을 정렬된 위치에 놓기 위해 스왑
    int temp = array[i + 1];
    array[i + 1] = array[high];
    array[high] = temp;
    return i + 1;  // 피벗의 최종 위치 반환
}

// 배열의 처음 20개와 끝 20개의 값을 출력하는 함수
void printArray(int* array) {
    printf("Array Sorting Result:\n");
    for (int i = 0; i < 20; i++) {
        printf("%4d ", array[i]);  // 처음 20개 값 출력
    }
    printf("\n");
    for (int i = SIZE - 20; i < SIZE; i++) {
        printf("%4d ", array[i]);  // 끝 20개 값 출력
    }
    printf("\n\n");
}

// 이진 탐색을 1000번 수행하고 평균 비교 횟수를 구하는 함수
float getAverageBinarySearchCompareCount(int* array) {
    int totalComparisons = 0;  // 비교 횟수의 합
    for (int i = 0; i < 1000; i++) {
        int target = array[rand() % SIZE];  // 배열에서 랜덤한 값을 target으로 선택
        totalComparisons += BinarySearch(array, target);  // 이진 탐색 수행
    }
    return totalComparisons / 1000.0;  // 평균 비교 횟수 반환
}

// 이진 탐색 함수
int BinarySearch(int* array, int target) {
    int left = 0, right = SIZE - 1, comparisons = 0;  // 초기화
    while (left <= right) {
        comparisons++;  // 비교 횟수 증가
        int mid = (left + right) / 2;
        if (array[mid] == target) {
            return comparisons;  // 값 찾으면 비교 횟수 반환
        }
        else if (array[mid] < target) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return comparisons;  // 찾지 못하면 비교 횟수 반환
}

// 보간 탐색을 1000번 수행하고 평균 비교 횟수를 구하는 함수
float getAverageInterpolationSearchCompareCount(int* array) {
    int totalComparisons = 0;  // 비교 횟수의 합
    for (int i = 0; i < 1000; i++) {
        int target = array[rand() % SIZE];  // 배열에서 랜덤한 값을 target으로 선택
        totalComparisons += InterpolationSearch(array, target);  // 보간 탐색 수행
    }
    return totalComparisons / 1000.0;  // 평균 비교 횟수 반환
}

// 보간 탐색 함수
int InterpolationSearch(int* array, int target) {
    int low = 0, high = SIZE - 1, comparisons = 0;  // 초기화
    while (low <= high && target >= array[low] && target <= array[high]) {
        comparisons++;  // 비교 횟수 증가
        if (low == high) {
            if (array[low] == target) return comparisons;  // 값 찾으면 비교 횟수 반환
            break;
        }
        // 보간법을 사용하여 새로운 검색 위치 계산
        int pos = low + ((double)(high - low) / (array[high] - array[low]) * (target - array[low]));
        if (array[pos] == target) {
            return comparisons;  // 값 찾으면 비교 횟수 반환
        }
        else if (array[pos] < target) {
            low = pos + 1;
        }
        else {
            high = pos - 1;
        }
    }
    return comparisons;  // 찾지 못하면 비교 횟수 반환
}
