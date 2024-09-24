#include <stdio.h>
#include <stdlib.h>

// 트리 노드 구조체 정의
typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// 노드 생성 함수
TreeNode* CreateNode(int data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// 노드를 트리에 배치하는 함수
void PlaceNode(TreeNode* node, int direction, int data) {
    TreeNode* newNode = CreateNode(data);
    if (direction == 0) {
        node->left = newNode;  // 왼쪽에 노드 배치
    }
    else {
        node->right = newNode;  // 오른쪽에 노드 배치
    }
}

// 트리를 생성하는 함수
void GenerateLinkTree(TreeNode* root) {
    // 루트 1의 자식: 2, 9
    PlaceNode(root, 0, 2);
    PlaceNode(root, 1, 9);

    // 2의 자식: 3, 5
    PlaceNode(root->left, 0, 3);
    PlaceNode(root->left, 1, 5);

    // 3의 자식: 4, 6
    PlaceNode(root->left->left, 0, 4);
    PlaceNode(root->left->left, 1, 6);

    // 5의 자식: 7, 8
    PlaceNode(root->left->right, 0, 7);
    PlaceNode(root->left->right, 1, 8);

    // 9의 자식: 10, 13
    PlaceNode(root->right, 0, 10);
    PlaceNode(root->right, 1, 13);

    // 10의 자식: 11, 12
    PlaceNode(root->right->left, 0, 11);
    PlaceNode(root->right->left, 1, 12);

    // 13의 자식: 14, 15
    PlaceNode(root->right->right, 0, 14);
    PlaceNode(root->right->right, 1, 15);
}

// 스택 구조체 정의
typedef struct Stack {
    TreeNode* node;
    struct Stack* next;
} Stack;

// 스택에 노드 삽입
void Push(Stack** stack, TreeNode* node) {
    Stack* newStackNode = (Stack*)malloc(sizeof(Stack));
    newStackNode->node = node;
    newStackNode->next = *stack;
    *stack = newStackNode;
}

// 스택에서 노드 추출
TreeNode* Pop(Stack** stack) {
    if (*stack == NULL) return NULL;
    Stack* temp = *stack;
    TreeNode* poppedNode = temp->node;
    *stack = temp->next;
    free(temp);
    return poppedNode;
}

// 트리의 노드 합을 반복적으로 계산하는 함수
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

// 트리의 노드 개수를 반복적으로 계산하는 함수
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

// 트리의 높이를 반복적으로 계산하는 함수
int GetHeightOfTreeIter(TreeNode* root) {
    if (root == NULL) return 0;

    Stack* stack = NULL;
    Push(&stack, root);

    int maxDepth = 0;
    Stack* depthStack = NULL;
    Push(&depthStack, (TreeNode*)(intptr_t)1);  // 깊이 1에서 시작

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

// 리프 노드 수를 반복적으로 계산하는 함수
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
    // 트리의 루트 노드를 생성
    TreeNode* root = CreateNode(1);

    // 트리 생성
    GenerateLinkTree(root);

    // 트리 데이터 출력
    printf("Sum of nodes: %d\n", GetSumOfNodesIter(root));
    printf("Number of nodes: %d\n", GetNumberOfNodesIter(root));
    printf("Height of Tree: %d\n", GetHeightOfTreeIter(root));
    printf("Number of leaf nodes: %d\n", GetNumberOfLeafNodesIter(root));

    return 0;
}
