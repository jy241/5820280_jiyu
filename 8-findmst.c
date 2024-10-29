#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 20
#define MAX_EDGES 20 // MAX_EDGES를 20으로 유지
#define INF 1000

typedef struct {
    int start, end, weight;
} Edge;

typedef struct {
    int n; // number of vertices
    int m; // number of edges
    Edge edges[MAX_EDGES];
} GraphType;

// 그래프 초기화 함수
void graph_init(GraphType* g) {
    g->n = 10; // 총 10개의 정점
    g->m = 18; // 총 18개의 간선
}

// 그래프 생성 함수
void GenerateGraph(GraphType* g) {
    g->edges[0] = (Edge){ 2, 5, 1 };
    g->edges[1] = (Edge){ 3, 4, 2 };
    g->edges[2] = (Edge){ 1, 2, 3 };
    g->edges[3] = (Edge){ 2, 4, 4 };
    g->edges[4] = (Edge){ 3, 8, 5 };
    g->edges[5] = (Edge){ 3, 7, 6 };
    g->edges[6] = (Edge){ 2, 6, 7 };
    g->edges[7] = (Edge){ 9, 10, 10 };
    g->edges[8] = (Edge){ 8, 10, 15 };
    // 추가 간선 (가중치가 더 높은 간선들)
    g->edges[9] = (Edge){ 1, 6, 11 };
    g->edges[10] = (Edge){ 1, 7, 12 };
    g->edges[11] = (Edge){ 2, 3, 7 };
    g->edges[12] = (Edge){ 2, 7, 8 };
    g->edges[13] = (Edge){ 3, 7, 6 };
    g->edges[14] = (Edge){ 4, 8, 14 };
    g->edges[15] = (Edge){ 4, 10, 16 };
    g->edges[16] = (Edge){ 5, 6, 9 };
    g->edges[17] = (Edge){ 5, 10, 17 };
}

// Union-Find를 위한 함수
int parent[MAX_VERTICES];
void set_init(int n) {
    for (int i = 0; i < n; i++) parent[i] = -1;
}

int set_find(int curr) {
    if (parent[curr] == -1) return curr;
    return parent[curr] = set_find(parent[curr]);
}

void set_union(int a, int b) {
    int root1 = set_find(a);
    int root2 = set_find(b);
    if (root1 != root2) parent[root1] = root2;
}

// Quick Sort 기반 Kruskal 알고리즘
int compare(const void* a, const void* b) {
    return ((Edge*)a)->weight - ((Edge*)b)->weight;
}

void QuickKruskal(GraphType* g) {
    set_init(g->n);
    qsort(g->edges, g->m, sizeof(Edge), compare);

    printf("Quick Based Kruskal\n");
    int edge_count = 0;
    int last_weight = -1; // 마지막으로 선택된 간선의 weight
    for (int i = 0; i < g->m; i++) {
        int u = g->edges[i].start;
        int v = g->edges[i].end;
        int w = g->edges[i].weight;

        if (set_find(u) != set_find(v)) {
            if (w != last_weight) { // 중복된 weight 체크
                set_union(u, v);
                printf("Edge (%d, %d) select %d\n", u, v, w);
                edge_count++;
                last_weight = w; // 마지막 weight 업데이트
                if (edge_count == g->n - 1) break;
            }
        }
    }
}

// Min-Heap을 사용한 Kruskal 알고리즘
typedef struct {
    Edge heap[MAX_EDGES];
    int size;
} MinHeap;

void initMinHeap(MinHeap* h) {
    h->size = 0;
}

void insertMinHeap(MinHeap* h, Edge e) {
    int i = ++(h->size);
    while (i != 1 && e.weight < h->heap[i / 2].weight) {
        h->heap[i] = h->heap[i / 2];
        i /= 2;
    }
    h->heap[i] = e;
}

Edge deleteMinHeap(MinHeap* h) {
    int parent = 1, child = 2;
    Edge item = h->heap[1], temp = h->heap[h->size--];

    while (child <= h->size) {
        if (child < h->size && h->heap[child].weight > h->heap[child + 1].weight) child++;
        if (temp.weight <= h->heap[child].weight) break;
        h->heap[parent] = h->heap[child];
        parent = child;
        child *= 2;
    }
    h->heap[parent] = temp;
    return item;
}

void MinHeapKruskal(GraphType* g) {
    MinHeap h;
    initMinHeap(&h);
    for (int i = 0; i < g->m; i++) {
        insertMinHeap(&h, g->edges[i]);
    }

    set_init(g->n);
    printf("MinHeap Based Kruskal\n");
    int edge_count = 0;
    int last_weight = -1; // 마지막으로 선택된 간선의 weight
    while (edge_count < g->n - 1) {
        Edge e = deleteMinHeap(&h);
        int u = e.start;
        int v = e.end;

        if (set_find(u) != set_find(v)) {
            if (e.weight != last_weight) { // 중복된 weight 체크
                set_union(u, v);
                printf("Edge (%d, %d) select %d\n", u, v, e.weight);
                edge_count++;
                last_weight = e.weight; // 마지막 weight 업데이트
            }
        }
    }
}

// 메인 함수
int main(void) {
    GraphType* g;
    g = (GraphType*)malloc(sizeof(GraphType));
    graph_init(g);
    GenerateGraph(g);

    QuickKruskal(g); // Quick Sort 기반 Kruskal
    MinHeapKruskal(g); // Min-Heap 기반 Kruskal

    free(g);
    return 0;
}
