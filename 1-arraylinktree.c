#include <stdio.h>
#include <stdlib.h>

// TreeNode ����ü (���Ḯ��Ʈ ��� Ʈ��)
typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// �迭 ��� Ʈ�� ���� �Լ�
void GenerateArrayTree(int* tree) {
    // Ʈ�� �迭�� �� �Է�
    int list[] = { 1, 2, 9, 3, 5, 10, 13, 4, 6, 7, 8, 11, 12, 14, 15 };

    for (int i = 0; i < 15; i++) {
        tree[i] = list[i];
    }
    printf("arrayƮ�� ������� ���: ");
    for (int i = 0; i < 15; i++) {
        printf("%d ", tree[i]);
    }
    printf("\n");
    printf("\n");

}

// ������ȸ (Pre-order)
void ArrayPreOrder(int* tree, int index, int size) {
    if (index >= size) return;
    printf("%d ", tree[index]);
    ArrayPreOrder(tree, 2 * index + 1, size);  // ���� �ڽ�
    ArrayPreOrder(tree, 2 * index + 2, size);  // ������ �ڽ�
}

// ������ȸ (In-order)
void ArrayInOrder(int* tree, int index, int size) {
    if (index >= size) return;
    ArrayInOrder(tree, 2 * index + 1, size);  // ���� �ڽ�
    printf("%d ", tree[index]);
    ArrayInOrder(tree, 2 * index + 2, size);  // ������ �ڽ�
}

// ������ȸ (Post-order)
void ArrayPostOrder(int* tree, int index, int size) {
    if (index >= size) return;
    ArrayPostOrder(tree, 2 * index + 1, size);  // ���� �ڽ�
    ArrayPostOrder(tree, 2 * index + 2, size);  // ������ �ڽ�
    printf("%d ", tree[index]);
}

// �迭 ��� Ʈ�� ��ȸ �Լ�
void ArrayOrders(int* tree) {
    int size = 15; // Ʈ�� ũ��
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

// ���ο� TreeNode ���� �Լ� (���Ḯ��Ʈ ���)
TreeNode* CreateNode(int data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// ���Ḯ��Ʈ ��� Ʈ�� ���� �Լ�
TreeNode* GenerateLinkTree() {
    // Ʈ�� ���� (���������� �°� Ʈ�� ����)
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

// ���Ḯ��Ʈ ��� ������ȸ (Pre-order)
void LinkPreOrder(TreeNode* root) {
    if (root == NULL) return;
    printf("%d ", root->data);
    LinkPreOrder(root->left);
    LinkPreOrder(root->right);
}

// ���Ḯ��Ʈ ��� ������ȸ (In-order)
void LinkInOrder(TreeNode* root) {
    if (root == NULL) return;
    LinkInOrder(root->left);
    printf("%d ", root->data);
    LinkInOrder(root->right);
}

// ���Ḯ��Ʈ ��� ������ȸ (Post-order)
void LinkPostOrder(TreeNode* root) {
    if (root == NULL) return;
    LinkPostOrder(root->left);
    LinkPostOrder(root->right);
    printf("%d ", root->data);
}

// ���Ḯ��Ʈ ��� Ʈ�� ��ȸ �Լ�
void LinkOrders(TreeNode* root) {
    printf("������ȸ(Link): ");
    LinkPreOrder(root);
    printf("\n");

    printf("������ȸ(Link): ");
    LinkInOrder(root);
    printf("\n");

    printf("Post-Order(Link) : ");
    LinkPostOrder(root);
    printf("\n");
}

int main() {
    int arr[15];

    // �迭 ��� Ʈ�� ����
    GenerateArrayTree(arr);
    // �迭 ��� Ʈ�� ��ȸ
    ArrayOrders(arr);

    // ���Ḯ��Ʈ ��� Ʈ�� ���� �� ��ȸ
    TreeNode* root = GenerateLinkTree();
    LinkOrders(root);

    return 0;
}
