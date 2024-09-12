#include <stdio.h>
#include <stdlib.h>

// TreeNode 구조체 (연결리스트 기반 트리)
typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// 배열 기반 트리 생성 함수
void GenerateArrayTree(int* tree) {
    // 트리 배열에 값 입력
    int list[] = { 1, 2, 9, 3, 5, 10, 13, 4, 6, 7, 8, 11, 12, 14, 15 };

    for (int i = 0; i < 15; i++) {
        tree[i] = list[i];
    }
    printf("array트리 순서대로 출력: ");
    for (int i = 0; i < 15; i++) {
        printf("%d ", tree[i]);
    }
    printf("\n");
    printf("\n");

}

// 전위순회 (Pre-order)
void ArrayPreOrder(int* tree, int index, int size) {
    if (index >= size) return;
    printf("%d ", tree[index]);
    ArrayPreOrder(tree, 2 * index + 1, size);  // 왼쪽 자식
    ArrayPreOrder(tree, 2 * index + 2, size);  // 오른쪽 자식
}

// 중위순회 (In-order)
void ArrayInOrder(int* tree, int index, int size) {
    if (index >= size) return;
    ArrayInOrder(tree, 2 * index + 1, size);  // 왼쪽 자식
    printf("%d ", tree[index]);
    ArrayInOrder(tree, 2 * index + 2, size);  // 오른쪽 자식
}

// 후위순회 (Post-order)
void ArrayPostOrder(int* tree, int index, int size) {
    if (index >= size) return;
    ArrayPostOrder(tree, 2 * index + 1, size);  // 왼쪽 자식
    ArrayPostOrder(tree, 2 * index + 2, size);  // 오른쪽 자식
    printf("%d ", tree[index]);
}

// 배열 기반 트리 순회 함수
void ArrayOrders(int* tree) {
    int size = 15; // 트리 크기
    printf("Pre-order(Array): ");
    ArrayPreOrder(tree, 0, size);
    printf("\n");

    printf("In-order(Array): ");
    ArrayInOrder(tree, 0, size);
    printf("\n");

    printf("Post-order(Array): ");
    ArrayPostOrder(tree, 0, size);
    printf("\n");
    printf("\n");

}

// 새로운 TreeNode 생성 함수 (연결리스트 기반)
TreeNode* CreateNode(int data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// 연결리스트 기반 트리 생성 함수
TreeNode* GenerateLinkTree() {
    // 트리 생성 (전위순서에 맞게 트리 구성)
    TreeNode* root = CreateNode(1);
    root->left = CreateNode(2);
    root->right = CreateNode(9);

    root->left->left = CreateNode(3);
    root->left->right = CreateNode(5);

    root->right->left = CreateNode(10);
    root->right->right = CreateNode(13);

    root->left->left->left = CreateNode(4);
    root->left->left->right = CreateNode(6);

    root->left->right->left = CreateNode(7);
    root->left->right->right = CreateNode(8);

    root->right->left->left = CreateNode(11);
    root->right->left->right = CreateNode(12);

    root->right->right->left = CreateNode(14);
    root->right->right->right = CreateNode(15);

    return root;
}

// 연결리스트 기반 전위순회 (Pre-order)
void LinkPreOrder(TreeNode* root) {
    if (root == NULL) return;
    printf("%d ", root->data);
    LinkPreOrder(root->left);
    LinkPreOrder(root->right);
}

// 연결리스트 기반 중위순회 (In-order)
void LinkInOrder(TreeNode* root) {
    if (root == NULL) return;
    LinkInOrder(root->left);
    printf("%d ", root->data);
    LinkInOrder(root->right);
}

// 연결리스트 기반 후위순회 (Post-order)
void LinkPostOrder(TreeNode* root) {
    if (root == NULL) return;
    LinkPostOrder(root->left);
    LinkPostOrder(root->right);
    printf("%d ", root->data);
}

// 연결리스트 기반 트리 순회 함수
void LinkOrders(TreeNode* root) {
    printf("전위순회(Link): ");
    LinkPreOrder(root);
    printf("\n");

    printf("중위순회(Link): ");
    LinkInOrder(root);
    printf("\n");

    printf("Post-Order(Link) : ");
    LinkPostOrder(root);
    printf("\n");
}

int main() {
    int arr[15];

    // 배열 기반 트리 생성
    GenerateArrayTree(arr);
    // 배열 기반 트리 순회
    ArrayOrders(arr);

    // 연결리스트 기반 트리 생성 및 순회
    TreeNode* root = GenerateLinkTree();
    LinkOrders(root);

    return 0;
}
