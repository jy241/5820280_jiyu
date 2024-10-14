/* #include <stdio.h>
#include <stdlib.h>

// Tree Node structure
typedef struct TreeNode {
    int value;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// Function to create a new tree node
TreeNode* createNode(int value) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to insert a value into the Max Heap Tree
TreeNode* insertMaxHeapTree(TreeNode* root, int value) {
    if (root == NULL) {
        return createNode(value);
    }

    // Perform level-order insertion
    TreeNode* queue[100]; // Queue for level-order traversal
    int front = 0, rear = 0;

    queue[rear++] = root;

    while (front < rear) {
        TreeNode* current = queue[front++];

        // Check left child
        if (current->left == NULL) {
            current->left = createNode(value);
            return root;
        }
        else {
            queue[rear++] = current->left;
        }

        // Check right child
        if (current->right == NULL) {
            current->right = createNode(value);
            return root;
        }
        else {
            queue[rear++] = current->right;
        }
    }

    return root;
}

// Function to generate a Max Heap Tree from an array
TreeNode* generateMaxHeapTree(int inputData[], int size) {
    TreeNode* root = NULL;
    for (int i = 0; i < size; i++) {
        root = insertMaxHeapTree(root, inputData[i]);
    }
    return root;
}

// Function to print the heap (tree) in level order
void printLevelOrder(TreeNode* root) {
    if (root == NULL) {
        return;
    }

    printf("Ʈ�� ������ ���\n");
    TreeNode* queue[100]; // Simple queue for level order traversal
    int front = 0, rear = 0;

    queue[rear++] = root;
    int level = 0, count = 1;

    while (front < rear) {
        int currentLevelCount = rear - front;
        printf("\n[%d] ", level + 1);
        for (int i = 0; i < currentLevelCount; i++) {
            TreeNode* node = queue[front++];
            printf("%d ", node->value);
            if (node->left != NULL) {
                queue[rear++] = node->left;
            }
            if (node->right != NULL) {
                queue[rear++] = node->right;
            }
        }
        level++;
    }
    printf("\n");
}

// User interface to interact with the Max Heap Tree
void runUserInterface(TreeNode* root) {
    char command;

    // Menu output
    printf("�ѤѤѤѤѤѤѤѤѤѤѤ�\n");
    printf("| i\t: ��� �߰�\t|\n");
    printf("| d\t: ��Ʈ ����\t|\n");
    printf("| p\t: ������ ���\t|\n");
    printf("| c\t: ����\t\t|\n");
    printf("�ѤѤѤѤѤѤѤѤѤѤѤ�\n");

    while (1) {
        printf("�޴� �Է�: ");
        scanf_s(" %c", &command);

        switch (command) {
        case 'i': {
            printf("�߰��� �� �Է�: ");
            int value;
            scanf_s("%d", &value);
            root = insertMaxHeapTree(root, value); // Insert value and maintain Max Heap property
            break;
        }
        case 'p':
            printLevelOrder(root); // Print the tree in level order
            break;
        case 'c':
            printf("���α׷��� �����մϴ�.\n");
            return;
        default:
            printf("�߸��� ��ɾ��Դϴ�.\n");
        }
    }
}

// Free the binary tree nodes
void freeTree(TreeNode* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

// Main function
int main() {
    int inputData[] = { 90, 89, 70, 36, 75, 63, 65, 21, 18, 15 }; // Order does not matter
    int size = sizeof(inputData) / sizeof(inputData[0]);

    // Generate the Max Heap Tree from the input data
    TreeNode* root = generateMaxHeapTree(inputData, size);

    // Run the user interface
    runUserInterface(root);

    // Free the allocated memory
    freeTree(root);

    return 0;
}
*/