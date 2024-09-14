#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

typedef struct Stack {
    TreeNode* data;
    struct Stack* next;
} Stack;

// 스택 push 함수
void push(Stack** top, TreeNode* node) {
    Stack* newNode = (Stack*)malloc(sizeof(Stack));
    newNode->data = node;
    newNode->next = *top;
    *top = newNode;
    printf("push(%d) ", node->data);
}

// 스택 pop 함수
TreeNode* pop(Stack** top) {
    if (*top == NULL) return NULL;
    Stack* temp = *top;
    TreeNode* node = temp->data;
    *top = temp->next;
    printf("pop(%d) ", node->data);
    free(temp);
    return node;
}

// 전위 순회 (PreOrder) 비재귀적 구현
void LinkPreOrder(TreeNode* root) {
    if (root == NULL) return;

    Stack* stack = NULL;
    push(&stack, root);

    printf("\nLinkedPreOrder: ");
    while (stack != NULL) {
        TreeNode* node = pop(&stack);
        if (node->right) push(&stack, node->right);
        if (node->left) push(&stack, node->left);
    }
    printf("\n");
}

// 중위 순회 (InOrder) 비재귀적 구현
void LinkInOrder(TreeNode* root) {
    if (root == NULL) return;

    Stack* stack = NULL;
    TreeNode* current = root;

    printf("\nLinkedInOrder: ");
    while (current != NULL || stack != NULL) {
        while (current != NULL) {
            push(&stack, current);
            current = current->left;
        }

        current = pop(&stack);
        current = current->right;
    }
    printf("\n");
}

// 후위 순회 (PostOrder) 비재귀적 구현
void LinkPostOrder(TreeNode* root) {
    if (root == NULL) return;

    Stack* stack = NULL;
    TreeNode* lastVisited = NULL;

    printf("\nLinkedPostOrder: ");
    do {
        while (root != NULL) {
            push(&stack, root);
            root = root->left;
        }

        TreeNode* peekNode = stack != NULL ? stack->data : NULL;
        if (peekNode && peekNode->right != NULL && lastVisited != peekNode->right) {
            root = peekNode->right;
        }
        else {
            root = pop(&stack);
            lastVisited = root;
            root = NULL;
        }
    } while (stack != NULL);

    printf("\n");
}

// 노드 생성 함수
TreeNode* createNode(int data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// 트리 생성 함수
void GenerateLinkTree(TreeNode** root) {
    *root = createNode(1);
    (*root)->left = createNode(2);
    (*root)->right = createNode(9);

    (*root)->left->left = createNode(3);
    (*root)->left->right = createNode(5);

    (*root)->right->left = createNode(10);
    (*root)->right->right = createNode(13);

    (*root)->left->left->left = createNode(4);
    (*root)->left->left->right = createNode(6);

    (*root)->right->left->left = createNode(7);
    (*root)->right->left->right = createNode(8);

    (*root)->right->right->right = createNode(15);

    (*root)->left->left->left->left = createNode(11);
    (*root)->left->left->left->right = createNode(12);

    (*root)->right->left->right->left = createNode(14);
}

// 트리 순회 함수
void LinkOrders(TreeNode* root) {
    LinkPreOrder(root);
    LinkInOrder(root);
    LinkPostOrder(root);
}

int main() {
    TreeNode* root = NULL;

    // 트리 생성
    GenerateLinkTree(&root);

    // 트리 순회
    LinkOrders(root);

    return 0;
}
