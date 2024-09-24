#include <stdio.h>
#include <stdlib.h>

// Ʈ�� ��� ����ü ����
typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// ��� ���� �Լ�
TreeNode* CreateNode(int data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// ��带 Ʈ���� ��ġ�ϴ� �Լ�
void PlaceNode(TreeNode* node, int direction, int data) {
    TreeNode* newNode = CreateNode(data);
    if (direction == 0) {
        node->left = newNode;  // ���ʿ� ��� ��ġ
    }
    else {
        node->right = newNode;  // �����ʿ� ��� ��ġ
    }
}

// Ʈ���� �����ϴ� �Լ�
void GenerateLinkTree(TreeNode* root) {
    // ��Ʈ 1�� �ڽ�: 2, 9
    PlaceNode(root, 0, 2);
    PlaceNode(root, 1, 9);

    // 2�� �ڽ�: 3, 5
    PlaceNode(root->left, 0, 3);
    PlaceNode(root->left, 1, 5);

    // 3�� �ڽ�: 4, 6
    PlaceNode(root->left->left, 0, 4);
    PlaceNode(root->left->left, 1, 6);

    // 5�� �ڽ�: 7, 8
    PlaceNode(root->left->right, 0, 7);
    PlaceNode(root->left->right, 1, 8);

    // 9�� �ڽ�: 10, 13
    PlaceNode(root->right, 0, 10);
    PlaceNode(root->right, 1, 13);

    // 10�� �ڽ�: 11, 12
    PlaceNode(root->right->left, 0, 11);
    PlaceNode(root->right->left, 1, 12);

    // 13�� �ڽ�: 14, 15
    PlaceNode(root->right->right, 0, 14);
    PlaceNode(root->right->right, 1, 15);
}

// ���� ����ü ����
typedef struct Stack {
    TreeNode* node;
    struct Stack* next;
} Stack;

// ���ÿ� ��� ����
void Push(Stack** stack, TreeNode* node) {
    Stack* newStackNode = (Stack*)malloc(sizeof(Stack));
    newStackNode->node = node;
    newStackNode->next = *stack;
    *stack = newStackNode;
}

// ���ÿ��� ��� ����
TreeNode* Pop(Stack** stack) {
    if (*stack == NULL) return NULL;
    Stack* temp = *stack;
    TreeNode* poppedNode = temp->node;
    *stack = temp->next;
    free(temp);
    return poppedNode;
}

// Ʈ���� ��� ���� �ݺ������� ����ϴ� �Լ�
int GetSumOfNodesIter(TreeNode* root) {
    if (root == NULL) return 0;

    int sum = 0;
    Stack* stack = NULL;
    Push(&stack, root);

    while (stack != NULL) {
        TreeNode* currentNode = Pop(&stack);
        sum += currentNode->data;

        if (currentNode->right) Push(&stack, currentNode->right);
        if (currentNode->left) Push(&stack, currentNode->left);
    }

    return sum;
}

// Ʈ���� ��� ������ �ݺ������� ����ϴ� �Լ�
int GetNumberOfNodesIter(TreeNode* root) {
    if (root == NULL) return 0;

    int count = 0;
    Stack* stack = NULL;
    Push(&stack, root);

    while (stack != NULL) {
        TreeNode* currentNode = Pop(&stack);
        count++;

        if (currentNode->right) Push(&stack, currentNode->right);
        if (currentNode->left) Push(&stack, currentNode->left);
    }

    return count;
}

// Ʈ���� ���̸� �ݺ������� ����ϴ� �Լ�
int GetHeightOfTreeIter(TreeNode* root) {
    if (root == NULL) return 0;

    Stack* stack = NULL;
    Push(&stack, root);

    int maxDepth = 0;
    Stack* depthStack = NULL;
    Push(&depthStack, (TreeNode*)(intptr_t)1);  // ���� 1���� ����

    while (stack != NULL) {
        TreeNode* currentNode = Pop(&stack);
        int currentDepth = (int)(intptr_t)Pop(&depthStack);

        if (currentNode->left == NULL && currentNode->right == NULL) {
            if (currentDepth > maxDepth) {
                maxDepth = currentDepth;
            }
        }
        if (currentNode->right) {
            Push(&stack, currentNode->right);
            Push(&depthStack, (TreeNode*)(intptr_t)(currentDepth + 1));
        }
        if (currentNode->left) {
            Push(&stack, currentNode->left);
            Push(&depthStack, (TreeNode*)(intptr_t)(currentDepth + 1));
        }
    }

    return maxDepth;
}

// ���� ��� ���� �ݺ������� ����ϴ� �Լ�
int GetNumberOfLeafNodesIter(TreeNode* root) {
    if (root == NULL) return 0;

    int leafCount = 0;
    Stack* stack = NULL;
    Push(&stack, root);

    while (stack != NULL) {
        TreeNode* currentNode = Pop(&stack);

        if (currentNode->left == NULL && currentNode->right == NULL) {
            leafCount++;
        }
        else {
            if (currentNode->right) Push(&stack, currentNode->right);
            if (currentNode->left) Push(&stack, currentNode->left);
        }
    }

    return leafCount;
}

int main() {
    // Ʈ���� ��Ʈ ��带 ����
    TreeNode* root = CreateNode(1);

    // Ʈ�� ����
    GenerateLinkTree(root);

    // Ʈ�� ������ ���
    printf("Sum of nodes: %d\n", GetSumOfNodesIter(root));
    printf("Number of nodes: %d\n", GetNumberOfNodesIter(root));
    printf("Height of Tree: %d\n", GetHeightOfTreeIter(root));
    printf("Number of leaf nodes: %d\n", GetNumberOfLeafNodesIter(root));

    return 0;
}
