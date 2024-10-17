/* #include <stdio.h>
#include <stdlib.h>

#define MAX_ELEMENT 200

// ��� ����ü
typedef struct TreeNode {
    int weight;
    char ch;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

typedef struct {
    TreeNode* ptree;
    int key;
} element;

typedef struct {
    element heap[MAX_ELEMENT];
    int heap_size;
} HeapType;

// ���� ���� �� �ʱ�ȭ �Լ�
HeapType* create() {
    return (HeapType*)malloc(sizeof(HeapType));
}

void init(HeapType* h) {
    h->heap_size = 0;
}

// ���� ���¸� ����ϴ� �Լ�
void print_heap(HeapType* h) {
    for (int i = 1; i <= h->heap_size; i++) {
        printf("%d ", h->heap[i].key);
    }
    printf("\n");
}

// �ּ� ������ ��Ҹ� �����ϴ� �Լ�
void insert_min_heap(HeapType* h, element item) {
    int i = ++(h->heap_size);
    while (i != 1 && item.key < h->heap[i / 2].key) {
        h->heap[i] = h->heap[i / 2];
        i /= 2;
    }
    h->heap[i] = item;
    print_heap(h);  // ���� ���� ���
}

// �ּ� �������� ��Ҹ� �����ϴ� �Լ�
element delete_min_heap(HeapType* h) {
    int parent, child;
    element item, temp;

    item = h->heap[1];  // ��Ʈ ����
    temp = h->heap[(h->heap_size)--];  // ������ ��Ҹ� ������
    parent = 1;
    child = 2;

    while (child <= h->heap_size) {
        if (child < h->heap_size && h->heap[child].key > h->heap[child + 1].key) {
            child++;
        }
        if (temp.key <= h->heap[child].key) break;
        h->heap[parent] = h->heap[child];
        parent = child;
        child *= 2;
    }
    h->heap[parent] = temp;
    return item;
}

// ���� Ʈ�� ���� �Լ�
TreeNode* make_tree(TreeNode* left, TreeNode* right) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    if (node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);  // �޸� �Ҵ� ���� �� ���α׷� ����
    }
    node->left = left;
    node->right = right;
    return node;
}

// ���� Ʈ�� ���� �Լ�
void destroy_tree(TreeNode* root) {
    if (root == NULL) return;
    destroy_tree(root->left);
    destroy_tree(root->right);
    free(root);
}

// �ܸ� ��� Ȯ�� �Լ�
int is_leaf(TreeNode* root) {
    return !(root->left) && !(root->right);
}

// ������ �ڵ带 ����ϴ� �Լ� (�ڵ� �ݴ�� ���)
void print_codes(TreeNode* root, int arr[], int top) {
    if (root->left) {
        arr[top] = 1;  // ���� �ڽĿ� 1 �Ҵ�
        print_codes(root->left, arr, top + 1);
    }
    if (root->right) {
        arr[top] = 0;  // ������ �ڽĿ� 0 �Ҵ�
        print_codes(root->right, arr, top + 1);
    }
    if (is_leaf(root)) {
        printf("%c: ", root->ch);
        for (int i = 0; i < top; i++) {
            printf("%d", arr[i]);
        }
        printf("\n");
    }
}

// ������ Ʈ���� ����� �Լ�
TreeNode* buildHuffmanTree(char characters[], int frequencies[], int size) {
    HeapType* heap = create();
    init(heap);
    element e, e1, e2;
    TreeNode* node, * x;

    // �� ���ڿ� �󵵼��� �ּ� ���� �ʱ�ȭ
    for (int i = 0; i < size; i++) {
        node = make_tree(NULL, NULL);
        node->ch = characters[i];
        node->weight = frequencies[i];
        e.ptree = node;
        e.key = node->weight;
        insert_min_heap(heap, e);  // ������ ����
    }

    // �� ���� �ּҰ��� �ݺ������� �����ϰ� ���ο� ��带 ����� ������ ����
    for (int i = 1; i < size; i++) {  // �ݺ� Ƚ�� ���� (size-1��)
        e1 = delete_min_heap(heap);
        e2 = delete_min_heap(heap);
        x = make_tree(e1.ptree, e2.ptree);
        x->weight = e1.key + e2.key;
        e.ptree = x;
        e.key = x->weight;
        printf("///%d + %d -> %d\n", e1.key, e2.key, e.key);
        insert_min_heap(heap, e);  // ���� ��ģ ��带 ������ ����
    }

    e = delete_min_heap(heap);
    TreeNode* root = e.ptree;  // �������� ���� Ʈ�� ��Ʈ ����
    free(heap);
    return root;
}

// ������ �ڵ� ���� �Լ�
void GenerateHuffmanCodes(char characters[], int frequencies[], int size) {
    TreeNode* root = buildHuffmanTree(characters, frequencies, size);
    int* arr = (int*)malloc(size * sizeof(int));  // ���� �迭 �Ҵ�
    int top = 0;
    printf("Huffman Codes:\n");
    print_codes(root, arr, top);
    destroy_tree(root);
    free(arr);  // ���� �迭 ����
}

int main() {
    char characters[] = { 'a', 'e', 'i', 'o', 'u', 's', 't' };
    int frequencies[] = { 10, 15, 12, 3, 4, 13, 1 };
    int size = sizeof(characters) / sizeof(characters[0]);
    GenerateHuffmanCodes(characters, frequencies, size);
    return 0;
} */