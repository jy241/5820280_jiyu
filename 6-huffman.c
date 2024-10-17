/* #include <stdio.h>
#include <stdlib.h>

#define MAX_ELEMENT 200

// 노드 구조체
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

// 히프 생성 및 초기화 함수
HeapType* create() {
    return (HeapType*)malloc(sizeof(HeapType));
}

void init(HeapType* h) {
    h->heap_size = 0;
}

// 히프 상태를 출력하는 함수
void print_heap(HeapType* h) {
    for (int i = 1; i <= h->heap_size; i++) {
        printf("%d ", h->heap[i].key);
    }
    printf("\n");
}

// 최소 히프에 요소를 삽입하는 함수
void insert_min_heap(HeapType* h, element item) {
    int i = ++(h->heap_size);
    while (i != 1 && item.key < h->heap[i / 2].key) {
        h->heap[i] = h->heap[i / 2];
        i /= 2;
    }
    h->heap[i] = item;
    print_heap(h);  // 히프 상태 출력
}

// 최소 히프에서 요소를 삭제하는 함수
element delete_min_heap(HeapType* h) {
    int parent, child;
    element item, temp;

    item = h->heap[1];  // 루트 삭제
    temp = h->heap[(h->heap_size)--];  // 마지막 요소를 가져옴
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

// 이진 트리 생성 함수
TreeNode* make_tree(TreeNode* left, TreeNode* right) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    if (node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);  // 메모리 할당 실패 시 프로그램 종료
    }
    node->left = left;
    node->right = right;
    return node;
}

// 이진 트리 제거 함수
void destroy_tree(TreeNode* root) {
    if (root == NULL) return;
    destroy_tree(root->left);
    destroy_tree(root->right);
    free(root);
}

// 단말 노드 확인 함수
int is_leaf(TreeNode* root) {
    return !(root->left) && !(root->right);
}

// 허프만 코드를 출력하는 함수 (코드 반대로 출력)
void print_codes(TreeNode* root, int arr[], int top) {
    if (root->left) {
        arr[top] = 1;  // 왼쪽 자식에 1 할당
        print_codes(root->left, arr, top + 1);
    }
    if (root->right) {
        arr[top] = 0;  // 오른쪽 자식에 0 할당
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

// 허프만 트리를 만드는 함수
TreeNode* buildHuffmanTree(char characters[], int frequencies[], int size) {
    HeapType* heap = create();
    init(heap);
    element e, e1, e2;
    TreeNode* node, * x;

    // 각 문자와 빈도수로 최소 히프 초기화
    for (int i = 0; i < size; i++) {
        node = make_tree(NULL, NULL);
        node->ch = characters[i];
        node->weight = frequencies[i];
        e.ptree = node;
        e.key = node->weight;
        insert_min_heap(heap, e);  // 히프에 삽입
    }

    // 두 개의 최소값을 반복적으로 제거하고 새로운 노드를 만들어 히프에 삽입
    for (int i = 1; i < size; i++) {  // 반복 횟수 수정 (size-1번)
        e1 = delete_min_heap(heap);
        e2 = delete_min_heap(heap);
        x = make_tree(e1.ptree, e2.ptree);
        x->weight = e1.key + e2.key;
        e.ptree = x;
        e.key = x->weight;
        printf("///%d + %d -> %d\n", e1.key, e2.key, e.key);
        insert_min_heap(heap, e);  // 새로 합친 노드를 히프에 삽입
    }

    e = delete_min_heap(heap);
    TreeNode* root = e.ptree;  // 히프에서 최종 트리 루트 추출
    free(heap);
    return root;
}

// 허프만 코드 생성 함수
void GenerateHuffmanCodes(char characters[], int frequencies[], int size) {
    TreeNode* root = buildHuffmanTree(characters, frequencies, size);
    int* arr = (int*)malloc(size * sizeof(int));  // 동적 배열 할당
    int top = 0;
    printf("Huffman Codes:\n");
    print_codes(root, arr, top);
    destroy_tree(root);
    free(arr);  // 동적 배열 해제
}

int main() {
    char characters[] = { 'a', 'e', 'i', 'o', 'u', 's', 't' };
    int frequencies[] = { 10, 15, 12, 3, 4, 13, 1 };
    int size = sizeof(characters) / sizeof(characters[0]);
    GenerateHuffmanCodes(characters, frequencies, size);
    return 0;
} */