#include <stdio.h>
#include <stdlib.h>

// 두 정수를 교환하는 함수
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 힙을 재정렬하는 함수
void resortHeap(int inputData[], int n, int i) {
    int largest = i; // 루트
    int left = 2 * i + 1; // 왼쪽 자식
    int right = 2 * i + 2; // 오른쪽 자식

    // 왼쪽 자식이 루트보다 크면 largest를 업데이트
    if (left < n && inputData[left] > inputData[largest]) {
        largest = left;
    }

    // 오른쪽 자식이 현재 largest보다 크면 업데이트
    if (right < n && inputData[right] > inputData[largest]) {
        largest = right;
    }

    // largest가 루트가 아니면 교환하고 재귀적으로 힙을 재정렬
    if (largest != i) {
        swap(&inputData[i], &inputData[largest]);
        resortHeap(inputData, n, largest);
    }
}

// 힙을 구축하는 함수
void BuildMaxHeap(int inputData[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        resortHeap(inputData, n, i);
    }
}

// 배열 상태 출력 함수
void printArray(int inputData[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", inputData[i]);
    }
    printf("\n");
}

// 배열에 요소를 삽입하고 힙 상태를 출력하는 함수
void insertAndHeapify(int inputData[], int* size, int value) {
    // 배열 크기 증가
    inputData[*size] = value; // 새로운 요소 추가
    (*size)++;

    // 힙을 재구성
    BuildMaxHeap(inputData, *size);

    // 현재 힙 상태 출력
    printArray(inputData, *size);
}

// 새로운 요소들을 배열에 추가하며 힙 상태를 출력하는 함수
void insertElementsAndPrintHeap(int inputData[], int newElements[], int newSize, int* size) {
    for (int i = 0; i < newSize; i++) {
        insertAndHeapify(inputData, size, newElements[i]);

    }
}

// 힙 정렬 및 상태 출력 함수
void BuildMaxHeapAndSort(int inputData[], int n) {
    BuildMaxHeap(inputData, n);


    for (int i = n - 1; i > 0; i--) {
        swap(&inputData[0], &inputData[i]);
        resortHeap(inputData, i, 0);
        printArray(inputData, i); // 현재 정렬 상태 출력
    }
}

// 메인 함수
int main() {
    int inputData[100]; // 배열 크기 100으로 설정
    int size = 0;

    // 초기 데이터 추가
    int initialData[] = { 34, 12, 76, 59, 32, 55, 88, 26, 16, 79, 35, 85, 29, 78, 41, 56, 86 };
    int initialSize = sizeof(initialData) / sizeof(initialData[0]);

    // 초기 데이터 삽입
    insertElementsAndPrintHeap(inputData, initialData, initialSize, &size);

    // 힙 정렬 실행
    BuildMaxHeapAndSort(inputData, size);

    // 정렬된 결과 출력
    printf("\nSorted Array:\n");
    printArray(inputData, size); // 최종 정렬된 배열 출력

    return 0;
}
