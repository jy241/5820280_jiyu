 #include <stdio.h>
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

    // Print heap state after initial insertion
    for (int i = 0; i < *size; i++) {
        printf("%d ", heap[i]);
    }
    printf("\n");

    // Rearrange the heap to maintain the Max Heap property
    int moveCount = 0; // 노드 이동 횟수
    while (currentIndex > 0) {
        int parentIndex = (currentIndex - 1) / 2;
        if (heap[currentIndex] > heap[parentIndex]) {
            // Swap the current node with its parent
            swap(&heap[currentIndex], &heap[parentIndex]);
            moveCount++; // 이동된 횟수 증가

            // Print the heap after swapping
            for (int i = 0; i < *size; i++) {
                printf("%d ", heap[i]);
            }
            printf("\n");

            currentIndex = parentIndex;
        }
        else {
            break;
        }
    }

    // 노드가 이동된 횟수 출력
    printf("노드가 이동된 횟수: %d\n", moveCount);
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

// 새로운 TreeNode 생성 함수
typedef struct TreeNode {
    int value;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// TreeNode를 동적으로 생성하는 함수
TreeNode* createNode(int value) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    if (newNode == NULL) {
        fprintf(stderr, "메모리 할당 오류\n");
        exit(1);  // 메모리 할당 실패 시 프로그램 종료
    }
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Max Heap Tree에 노드를 삽입하는 함수
void InsertMaxHeapTree(TreeNode** root, int value) {
    if (*root == NULL) {
        *root = createNode(value);
    }
    else {
        // Max Heap Tree의 규칙에 따라 삽입
        if (value > (*root)->value) {
            int temp = (*root)->value;
            (*root)->value = value;
            value = temp;
        }
        if ((*root)->left == NULL) {
            InsertMaxHeapTree(&(*root)->left, value);
        }
        else if ((*root)->right == NULL) {
            InsertMaxHeapTree(&(*root)->right, value);
        }
        else {
            if (rand() % 2 == 0) {
                InsertMaxHeapTree(&(*root)->left, value);
            }
            else {
                InsertMaxHeapTree(&(*root)->right, value);
            }
        }
    }
}

// 트리를 배열로 변환하여 힙을 생성하는 함수
void generateMaxHeapTree(TreeNode** root, int inputData[], int size) {
    *root = NULL;  // Initialize root
    for (int i = 0; i < size; i++) {
        InsertMaxHeapTree(root, inputData[i]);
    }
}

// 힙을 채우기 위한 재귀 함수
void fillHeap(TreeNode* node, int heap[], int* size) {
    if (node == NULL) return;
    heap[(*size)++] = node->value;  // 먼저 현재 노드 값을 배열에 저장
    fillHeap(node->left, heap, size);  // 왼쪽 자식 순회
    fillHeap(node->right, heap, size); // 오른쪽 자식 순회
}

// 사용자 인터페이스를 실행하는 함수
void runUserInterface(TreeNode* root) {
    int heap[100];  // 최대 100개의 노드를 저장할 수 있는 배열
    int size = 0;

    // 힙으로 변환
    fillHeap(root, heap, &size);

    char command;
    // 메뉴와 항목 출력
    printf("ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ\n");
    printf("| i\t: 노드 추가\t|\n");
    printf("| d\t: 루트 삭제\t|\n");
    printf("| p\t: 레벨별 출력\t|\n");
    printf("| c\t: 종료\t\t|\n");
    printf("ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ\n");

    while (1) {
        printf("메뉴 입력: ");
        scanf_s(" %c", &command);

        switch (command) {
        case 'i':
            printf("추가할 값 입력: ");
            int value;
            scanf_s("%d", &value);
            insertAndPrintMaxHeap(heap, &size, value);  // 삽입 후 과정을 출력
            break;
        case 'd':
            deleteRootAndPrintMaxHeap(heap, &size);  // 루트 노드 삭제 후 과정을 출력
            break;
        case 'p':
            printLevelOrder(heap, size);  // 레벨별 트리 출력
            break;
        case 'c':
            printf("프로그램을 종료합니다.\n");
            return;
        default:
            printf("잘못된 명령어입니다.\n");
        }
    }
}

// 메인 함수
int main() {
    int inputData[] = { 90, 89, 70, 36, 75, 63, 65, 21, 18, 15 };
    int size = sizeof(inputData) / sizeof(inputData[0]);

    // 트리 생성, *root에 트리를 생성해 반환
    TreeNode* root;
    generateMaxHeapTree(&root, inputData, size);

    // 사용자 인터페이스 실행
    runUserInterface(root);

    // 동적 메모리 해제
    free(root);  // 메모리 해제
    return 0;
}
