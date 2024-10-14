/* #include <stdio.h>
#include <stdlib.h>

// Helper function to swap two integer values
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Max Heap insertion logic
void insertAndPrintMaxHeap(int heap[], int* size, int value) {
    // Insert the new value at the end of the heap
    heap[*size] = value;
    int currentIndex = *size;
    (*size)++;

    // Rearrange the heap to maintain the Max Heap property
    int moveCount = 0; // 노드 이동 횟수
    while (currentIndex > 0) {
        int parentIndex = (currentIndex - 1) / 2;
        if (heap[currentIndex] > heap[parentIndex]) {
            // Swap the current node with its parent
            swap(&heap[currentIndex], &heap[parentIndex]);
            moveCount++; // 이동된 횟수 증가

            // Print the heap after swapping
            printf("노드가 이동한 후: ");
            for (int i = 0; i < *size; i++) {
                printf("%d ", heap[i]);
            }
            printf("\n");

            currentIndex = parentIndex;

          
        }
        else {
            break;
        }
        printf("노드가 이동된 횟수: %d\n", moveCount);
    }

 
}

// Max Heap deletion logic for root node with printing intermediate steps
void deleteRootAndPrintMaxHeap(int heap[], int* size) {
    if (*size <= 0) {
        printf("삭제할 노드가 없습니다.\n");
        return;
    }

    int moveCount = 0;  // 노드 이동 횟수

    // Print the value of the node being deleted (root node)
    printf("삭제된 값: %d\n", heap[0]);

    // Replace the root node with the last element
    heap[0] = heap[*size - 1];
    (*size)--;

    int currentIndex = 0;

    // Rearrange the heap to maintain the Max Heap property (down-heapify)
    while (1) {
        int leftChild = 2 * currentIndex + 1;
        int rightChild = 2 * currentIndex + 2;
        int largest = currentIndex;

        if (leftChild < *size && heap[leftChild] > heap[largest]) {
            largest = leftChild;
        }
        if (rightChild < *size && heap[rightChild] > heap[largest]) {
            largest = rightChild;
        }

        if (largest != currentIndex) {
            // Swap the current node with the largest child
            swap(&heap[currentIndex], &heap[largest]);
            moveCount++;  // 노드가 이동한 횟수 증가

            // Print the heap after swapping
            printf("노드가 이동한 후: ");
            for (int i = 0; i < *size; i++) {
                printf("%d ", heap[i]);
            }
            printf("\n");

            currentIndex = largest;
        }
        else {
            break;
        }
    }

    // 이동된 횟수 출력
    printf("노드가 이동된 횟수: %d\n", moveCount);
}

// Level-order traversal to print the heap as a binary tree (breadth-first search)
void printLevelOrder(int heap[], int size) {
    printf("트리 레벨별 출력\n");
    int level = 0;
    int count = 1;
    for (int i = 0; i < size; i++) {
        if (i == count - 1) {
            printf("\n[%d] ", level + 1);
            level++;
            count *= 2;
        }
        printf("%d ", heap[i]);
    }
    printf("\n");
}

void runUserInterface(int heap[], int* size) {
    char command;

    // 메뉴와 항목 출력
    printf("ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ\n");
    printf("| i\t: 노드 추가\t|\n");
    printf("| d\t: 루트 삭제\t|\n");
    printf("| p\t: 레벨별 출력\t|\n");
    printf("| c\t: 종료\t\t|\n");
    printf("ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ\n");

    while (1) {
        printf("메뉴 입력: ");
        scanf_s(" %c", &command);

        switch (command) {
        case 'i':
            printf("추가할 값 입력: ");
            int value;
            scanf_s("%d", &value);
            insertAndPrintMaxHeap(heap, size, value);  // 삽입 후 과정을 출력
            break;
        case 'd':
            deleteRootAndPrintMaxHeap(heap, size);  // 루트 노드 삭제 후 과정을 출력
            break;
        case 'p':
            printLevelOrder(heap, *size);  // 레벨별 트리 출력
            break;
        case 'c':
            printf("프로그램을 종료합니다.\n");
            return;
        default:
            printf("잘못된 명령어입니다.\n");
        }
    }
}

int main() {
    int heap[100];  // 배열로 힙을 관리
    int size = 0;   // 현재 힙에 있는 노드의 개수

    // 초기 힙 데이터
    int inputData[] = { 90, 89, 70, 36, 75, 63, 65, 21, 18, 15 };
    int initialSize = sizeof(inputData) / sizeof(inputData[0]);

    // 기존 데이터를 힙에 삽입 (초기에는 노드 이동 횟수 출력 안함)
    for (int i = 0; i < initialSize; i++) {
        insertAndPrintMaxHeap(heap, &size, inputData[i]);
    }

    // 사용자 인터페이스 실행
    runUserInterface(heap, &size);

    return 0;
}
*/