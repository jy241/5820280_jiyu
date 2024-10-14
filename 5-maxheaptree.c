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
    int moveCount = 0; // ��� �̵� Ƚ��
    while (currentIndex > 0) {
        int parentIndex = (currentIndex - 1) / 2;
        if (heap[currentIndex] > heap[parentIndex]) {
            // Swap the current node with its parent
            swap(&heap[currentIndex], &heap[parentIndex]);
            moveCount++; // �̵��� Ƚ�� ����

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

    // ��尡 �̵��� Ƚ�� ���
    printf("��尡 �̵��� Ƚ��: %d\n", moveCount);
}

// Max Heap deletion logic for root node with printing intermediate steps
void deleteRootAndPrintMaxHeap(int heap[], int* size) {
    if (*size <= 0) {
        printf("������ ��尡 �����ϴ�.\n");
        return;
    }

    int moveCount = 0;  // ��� �̵� Ƚ��

    // Print the value of the node being deleted (root node)
    printf("������ ��: %d\n", heap[0]);

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
            moveCount++;  // ��尡 �̵��� Ƚ�� ����

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

    // �̵��� Ƚ�� ���
    printf("��尡 �̵��� Ƚ��: %d\n", moveCount);
}

// Level-order traversal to print the heap as a binary tree (breadth-first search)
void printLevelOrder(int heap[], int size) {
    printf("Ʈ�� ������ ���\n");
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

// ���ο� TreeNode ���� �Լ�
typedef struct TreeNode {
    int value;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// TreeNode�� �������� �����ϴ� �Լ�
TreeNode* createNode(int value) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    if (newNode == NULL) {
        fprintf(stderr, "�޸� �Ҵ� ����\n");
        exit(1);  // �޸� �Ҵ� ���� �� ���α׷� ����
    }
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Max Heap Tree�� ��带 �����ϴ� �Լ�
void InsertMaxHeapTree(TreeNode** root, int value) {
    if (*root == NULL) {
        *root = createNode(value);
    }
    else {
        // Max Heap Tree�� ��Ģ�� ���� ����
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

// Ʈ���� �迭�� ��ȯ�Ͽ� ���� �����ϴ� �Լ�
void generateMaxHeapTree(TreeNode** root, int inputData[], int size) {
    *root = NULL;  // Initialize root
    for (int i = 0; i < size; i++) {
        InsertMaxHeapTree(root, inputData[i]);
    }
}

// ���� ä��� ���� ��� �Լ�
void fillHeap(TreeNode* node, int heap[], int* size) {
    if (node == NULL) return;
    heap[(*size)++] = node->value;  // ���� ���� ��� ���� �迭�� ����
    fillHeap(node->left, heap, size);  // ���� �ڽ� ��ȸ
    fillHeap(node->right, heap, size); // ������ �ڽ� ��ȸ
}

// ����� �������̽��� �����ϴ� �Լ�
void runUserInterface(TreeNode* root) {
    int heap[100];  // �ִ� 100���� ��带 ������ �� �ִ� �迭
    int size = 0;

    // ������ ��ȯ
    fillHeap(root, heap, &size);

    char command;
    // �޴��� �׸� ���
    printf("�ѤѤѤѤѤѤѤѤѤѤ�\n");
    printf("| i\t: ��� �߰�\t|\n");
    printf("| d\t: ��Ʈ ����\t|\n");
    printf("| p\t: ������ ���\t|\n");
    printf("| c\t: ����\t\t|\n");
    printf("�ѤѤѤѤѤѤѤѤѤѤ�\n");

    while (1) {
        printf("�޴� �Է�: ");
        scanf_s(" %c", &command);

        switch (command) {
        case 'i':
            printf("�߰��� �� �Է�: ");
            int value;
            scanf_s("%d", &value);
            insertAndPrintMaxHeap(heap, &size, value);  // ���� �� ������ ���
            break;
        case 'd':
            deleteRootAndPrintMaxHeap(heap, &size);  // ��Ʈ ��� ���� �� ������ ���
            break;
        case 'p':
            printLevelOrder(heap, size);  // ������ Ʈ�� ���
            break;
        case 'c':
            printf("���α׷��� �����մϴ�.\n");
            return;
        default:
            printf("�߸��� ��ɾ��Դϴ�.\n");
        }
    }
}

// ���� �Լ�
int main() {
    int inputData[] = { 90, 89, 70, 36, 75, 63, 65, 21, 18, 15 };
    int size = sizeof(inputData) / sizeof(inputData[0]);

    // Ʈ�� ����, *root�� Ʈ���� ������ ��ȯ
    TreeNode* root;
    generateMaxHeapTree(&root, inputData, size);

    // ����� �������̽� ����
    runUserInterface(root);

    // ���� �޸� ����
    free(root);  // �޸� ����
    return 0;
}
