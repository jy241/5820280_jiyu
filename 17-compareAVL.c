#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
    int key;
    struct Node* left, * right;
    int height; // AVL 트리에서 사용하는 높이 정보
} Node;

int compareCount = 0; // 비교 횟수 누적
int searchCount = 0;  // 탐색 호출 횟수

// 노드 생성
Node* createNode(int key) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->left = node->right = NULL;
    node->height = 1;
    return node;
}

// 트리 높이 가져오기
int getHeight(Node* node) {
    return node ? node->height : 0;
}

// AVL 트리를 위한 균형 계수 계산
int getBalance(Node* node) {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

// 오른쪽 회전
Node* rotateRight(Node* y) {
    Node* x = y->left;
    Node* T = x->right;

    x->right = y;
    y->left = T;

    y->height = 1 + (getHeight(y->left) > getHeight(y->right) ? getHeight(y->left) : getHeight(y->right));
    x->height = 1 + (getHeight(x->left) > getHeight(x->right) ? getHeight(x->left) : getHeight(x->right));

    return x;
}

// 왼쪽 회전
Node* rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T = y->left;

    y->left = x;
    x->right = T;

    x->height = 1 + (getHeight(x->left) > getHeight(x->right) ? getHeight(x->left) : getHeight(x->right));
    y->height = 1 + (getHeight(y->left) > getHeight(y->right) ? getHeight(y->left) : getHeight(y->right));

    return y;
}

// AVL 트리에 삽입
Node* avlInsert(Node* node, int key) {
    if (!node) return createNode(key);

    compareCount++;
    if (key < node->key)
        node->left = avlInsert(node->left, key);
    else if (key > node->key)
        node->right = avlInsert(node->right, key);
    else
        return node;

    node->height = 1 + (getHeight(node->left) > getHeight(node->right) ? getHeight(node->left) : getHeight(node->right));

    int balance = getBalance(node);

    if (balance > 1 && key < node->left->key) return rotateRight(node);
    if (balance < -1 && key > node->right->key) return rotateLeft(node);
    if (balance > 1 && key > node->left->key) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    if (balance < -1 && key < node->right->key) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

// 이진 탐색 트리에 삽입
Node* bstInsert(Node* node, int key) {
    if (!node) return createNode(key);

    compareCount++;
    if (key < node->key)
        node->left = bstInsert(node->left, key);
    else if (key > node->key)
        node->right = bstInsert(node->right, key);

    return node;
}

// 트리에서 최소값 노드 찾기
Node* findMin(Node* node) {
    while (node->left) node = node->left;
    return node;
}

// AVL 트리에서 삭제
Node* avlDelete(Node* root, int key) {
    if (!root) return root;

    compareCount++;
    if (key < root->key)
        root->left = avlDelete(root->left, key);
    else if (key > root->key)
        root->right = avlDelete(root->right, key);
    else {
        if (!root->left || !root->right) {
            Node* temp = root->left ? root->left : root->right;
            free(root);
            return temp;
        }
        else {
            Node* temp = findMin(root->right);
            root->key = temp->key;
            root->right = avlDelete(root->right, temp->key);
        }
    }

    root->height = 1 + (getHeight(root->left) > getHeight(root->right) ? getHeight(root->left) : getHeight(root->right));

    int balance = getBalance(root);
    if (balance > 1 && getBalance(root->left) >= 0) return rotateRight(root);
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }
    if (balance < -1 && getBalance(root->right) <= 0) return rotateLeft(root);
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

// BST에서 삭제
Node* bstDelete(Node* root, int key) {
    if (!root) return root;

    compareCount++;
    if (key < root->key)
        root->left = bstDelete(root->left, key);
    else if (key > root->key)
        root->right = bstDelete(root->right, key);
    else {
        if (!root->left || !root->right) {
            Node* temp = root->left ? root->left : root->right;
            free(root);
            return temp;
        }
        else {
            Node* temp = findMin(root->right);
            root->key = temp->key;
            root->right = bstDelete(root->right, temp->key);
        }
    }

    return root;
}

// 트리에서 탐색
void searchTree(Node* root, int key) {
    if (!root) return;

    compareCount++;
    if (key == root->key) return;
    else if (key < root->key)
        searchTree(root->left, key);
    else
        searchTree(root->right, key);
}

// 트리 해제
void freeTree(Node* root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

// AVL 실험 수행
void doAVLBatch(Node* root) {
    for (int i = 0; i < 2000; i++) {
        int A = rand() % 3;
        int B = rand() % 1000;
        if (A == 0) {
            root = avlInsert(root, B);
        }
        else if (A == 1) {
            root = avlDelete(root, B);
        }
        else if (A == 2) {
            searchTree(root, B);
            searchCount++;
        }
    }
}

// BST 실험 수행
void doBinaryBatch(Node* root) {
    for (int i = 0; i < 2000; i++) {
        int A = rand() % 3;
        int B = rand() % 1000;
        if (A == 0) {
            root = bstInsert(root, B);
        }
        else if (A == 1) {
            root = bstDelete(root, B);
        }
        else if (A == 2) {
            searchTree(root, B);
            searchCount++;
        }
    }
}

int main(int argc, char* argv[]) {
    srand(time(NULL));

    for (int run = 0; run < 3; run++) {
        Node* root = NULL;
        compareCount = searchCount = 0;
        float allCount = 0.0;

        // AVL 실험
        doAVLBatch(root);
        allCount = (float)compareCount / searchCount;
        printf("average AVL compare count: %.2f\n", allCount);

        // AVL 트리 메모리 해제
        freeTree(root);
        root = NULL;

        compareCount = searchCount = 0;

        // BST 실험
        doBinaryBatch(root);
        allCount = (float)compareCount / searchCount;
        printf("average Bin compare count: %.2f\n", allCount);

        freeTree(root);
        printf("\n");
    }

    return 0;
}
