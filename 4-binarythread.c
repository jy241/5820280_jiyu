#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int value;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

typedef struct ThreadNode {
    int value;
    struct ThreadNode* left;
    struct ThreadNode* right;
    int is_threaded_left;
    int is_threaded_right;
} ThreadNode;

// ���� Ž�� Ʈ���� ����
TreeNode* insertBST(TreeNode* root, int value) {
    if (root == NULL) {
        TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
        node->value = value;
        node->left = NULL;
        node->right = NULL;
        return node;
    }
    if (value < root->value) {
        root->left = insertBST(root->left, value);
    }
    else {
        root->right = insertBST(root->right, value);
    }
    return root;
}

// ���� Ž�� Ʈ�� ����
TreeNode* GenerateBinaryTree(int inputData[], int size) {
    TreeNode* root = NULL;
    for (int i = 0; i < size; i++) {
        root = insertBST(root, inputData[i]);
    }
    return root;
}

// ���� Ž�� Ʈ�� ���� ��ȸ
void BinaryTreeOrder(TreeNode* root) {
    if (root == NULL) return;
    BinaryTreeOrder(root->left);
    printf("%d ", root->value);
    BinaryTreeOrder(root->right);
}

// ������ ���� Ʈ���� ����
ThreadNode* insertThreaded(ThreadNode* root, int value, ThreadNode** prev) {
    if (root == NULL) {
        ThreadNode* node = (ThreadNode*)malloc(sizeof(ThreadNode));
        node->value = value;
        node->left = NULL;
        node->right = NULL;
        node->is_threaded_left = 0;
        node->is_threaded_right = 0;

        if (*prev != NULL && (*prev)->is_threaded_right) {
            (*prev)->right = node;
        }

        *prev = node;
        return node;
    }
    if (value < root->value) {
        if (root->left == NULL || root->is_threaded_left) {
            root->left = insertThreaded(root->left, value, prev);
        }
        else {
            root->left = insertThreaded(root->left, value, prev);
        }
    }
    else {
        if (root->right == NULL || root->is_threaded_right) {
            root->right = insertThreaded(root->right, value, prev);
        }
        else {
            root->right = insertThreaded(root->right, value, prev);
        }
    }
    return root;
}

// ������ ���� Ʈ�� ����
ThreadNode* GenerateThreadTree(int inputData[], int size) {
    ThreadNode* root = NULL;
    ThreadNode* prev = NULL;
    for (int i = 0; i < size; i++) {
        root = insertThreaded(root, inputData[i], &prev);
    }
    return root;
}

// ������ ���� Ʈ�� ���� ��ȸ
void ThreadTreeInOrder(ThreadNode* root) {
    if (root == NULL) return;
    ThreadTreeInOrder(root->left);
    printf("%d ", root->value);
    ThreadTreeInOrder(root->right);
}

int main() {
    int inputData[] = { 4, 1, 9, 13, 15, 3, 6, 14, 7, 10, 12, 2, 5, 8, 11 };
    int size = sizeof(inputData) / sizeof(inputData[0]);

    // ���� Ž�� Ʈ�� ����
    TreeNode* root = GenerateBinaryTree(inputData, size);
    printf("Binary tree inorder: ");
    BinaryTreeOrder(root);
    printf("\n");

    // ������ ���� Ʈ�� ����
    ThreadNode* troot = GenerateThreadTree(inputData, size);
    printf("Thread tree inorder: ");
    ThreadTreeInOrder(troot);
    printf("\n");

    // �޸� ����
    free(root);
    free(troot);

    return 0;
}
