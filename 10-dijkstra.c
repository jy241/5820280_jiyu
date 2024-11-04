#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VERTICES 10

// 연결 리스트의 노드 구조체
typedef struct Edge {
    int destination;
    int weight;
    struct Edge* next;
} Edge;

// 그래프 구조체
typedef struct Graph {
    Edge* adjacencyList[MAX_VERTICES];
} Graph;

// 최소 힙 노드 구조체
typedef struct MinHeapNode {
    int vertex;
    int distance;
} MinHeapNode;

// 최소 힙 구조체
typedef struct MinHeap {
    MinHeapNode* array;
    int size;
    int capacity;
} MinHeap;

// 함수 프로토타입
Graph* createGraph();
void insertEdge(Graph* g, int src, int dest, int weight);
MinHeap* createMinHeap(int capacity);
void insertMinHeap(MinHeap* minHeap, int vertex, int distance);
MinHeapNode extractMin(MinHeap* minHeap);
int isEmpty(MinHeap* minHeap);
void dijkstra(Graph* g, int startVertex);
void printDistances(int distances[], int size, int found[], int path[][MAX_VERTICES], int startVertex);
void printPath(int path[], int vertex);

// 메인 함수
int main() {
    Graph* g = createGraph();

    // 그래프에 엣지 삽입
    insertEdge(g, 1, 2, 3);
    insertEdge(g, 2, 5, 1);
    insertEdge(g, 5, 4, 4);
    insertEdge(g, 4, 3, 2);
    insertEdge(g, 3, 8, 5);
    insertEdge(g, 8, 7, 6);
    insertEdge(g, 7, 6, 12);
    insertEdge(g, 6, 10, 11);
    insertEdge(g, 10, 9, 10);

    // 다익스트라 알고리즘 실행
    dijkstra(g, 1);

    return 0;
}

// 그래프 생성
Graph* createGraph() {
    Graph* g = (Graph*)malloc(sizeof(Graph));
    for (int i = 0; i < MAX_VERTICES; i++) {
        g->adjacencyList[i] = NULL;
    }
    return g;
}

// 엣지 삽입
void insertEdge(Graph* g, int src, int dest, int weight) {
    Edge* newEdge = (Edge*)malloc(sizeof(Edge));
    newEdge->destination = dest;
    newEdge->weight = weight;
    newEdge->next = g->adjacencyList[src];
    g->adjacencyList[src] = newEdge;
}

// 최소 힙 생성
MinHeap* createMinHeap(int capacity) {
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
    minHeap->capacity = capacity;
    minHeap->size = 0;
    minHeap->array = (MinHeapNode*)malloc(capacity * sizeof(MinHeapNode));
    return minHeap;
}

// 최소 힙에 노드 삽입
void insertMinHeap(MinHeap* minHeap, int vertex, int distance) {
    minHeap->size++;
    int i = minHeap->size - 1;
    minHeap->array[i].vertex = vertex;
    minHeap->array[i].distance = distance;

    // 부모 노드와 비교하여 위치 조정
    while (i && minHeap->array[i].distance < minHeap->array[(i - 1) / 2].distance) {
        MinHeapNode temp = minHeap->array[i];
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        minHeap->array[(i - 1) / 2] = temp;
        i = (i - 1) / 2;
    }
}

// 최소 힙에서 최소 노드 추출
MinHeapNode extractMin(MinHeap* minHeap) {
    if (isEmpty(minHeap)) {
        return (MinHeapNode) { -1, INT_MAX }; // 빈 경우 최대 거리 반환
    }
    MinHeapNode root = minHeap->array[0];
    MinHeapNode lastNode = minHeap->array[minHeap->size - 1];
    minHeap->size--;
    if (minHeap->size > 0) {
        minHeap->array[0] = lastNode;
        // 최소 힙 속성 유지
        int i = 0;
        while (i < minHeap->size / 2) {
            int leftChild = 2 * i + 1;
            int rightChild = 2 * i + 2;
            int smallest = i;

            if (leftChild < minHeap->size && minHeap->array[leftChild].distance < minHeap->array[smallest].distance) {
                smallest = leftChild;
            }
            if (rightChild < minHeap->size && minHeap->array[rightChild].distance < minHeap->array[smallest].distance) {
                smallest = rightChild;
            }
            if (smallest == i) break;

            MinHeapNode temp = minHeap->array[i];
            minHeap->array[i] = minHeap->array[smallest];
            minHeap->array[smallest] = temp;
            i = smallest;
        }
    }
    return root;
}

// 최소 힙이 비었는지 확인
int isEmpty(MinHeap* minHeap) {
    return minHeap->size == 0;
}

// 다익스트라 알고리즘 구현
void dijkstra(Graph* g, int startVertex) {
    int distances[MAX_VERTICES];
    int found[MAX_VERTICES] = { 0 }; // 발견 여부
    int path[MAX_VERTICES][MAX_VERTICES]; // 경로 저장
    for (int i = 0; i < MAX_VERTICES; i++) {
        distances[i] = INT_MAX; // 초기화
        for (int j = 0; j < MAX_VERTICES; j++) {
            path[i][j] = 0; // 초기화
        }
    }
    distances[startVertex] = 0;

    MinHeap* minHeap = createMinHeap(MAX_VERTICES);
    insertMinHeap(minHeap, startVertex, distances[startVertex]);

    while (!isEmpty(minHeap)) {
        MinHeapNode minNode = extractMin(minHeap);
        int currentVertex = minNode.vertex;
        found[currentVertex] = 1; // 현재 정점 발견 표시

        // 경로 기록
        for (int i = 0; i < MAX_VERTICES; i++) {
            path[currentVertex][i] = path[i][currentVertex]; // 이전 경로 복사
        }
        path[currentVertex][currentVertex] = 1; // 현재 정점 경로 추가

        // 인접 정점 탐색
        Edge* edge = g->adjacencyList[currentVertex];
        while (edge != NULL) {
            int destination = edge->destination;
            int weight = edge->weight;

            // 최소 거리 업데이트
            if (distances[currentVertex] + weight < distances[destination]) {
                distances[destination] = distances[currentVertex] + weight;
                insertMinHeap(minHeap, destination, distances[destination]);
            }
            edge = edge->next;
        }

        // 현재 상태 출력
        printDistances(distances, MAX_VERTICES, found, path, startVertex);
    }

    // 최종 경로 출력
    printf("Final Order: ");
    for (int i = 1; i < MAX_VERTICES; i++) {
        if (found[i]) {
            printf("%d ", i);
        }
    }
    printf("\n");
}

// 최단 거리 출력
void printDistances(int distances[], int size, int found[], int path[][MAX_VERTICES], int startVertex) {
    printf("Distance: ");
    for (int i = 1; i < size; i++) {
        if (distances[i] == INT_MAX) {
            printf(" * "); // 무한대인 경우
        }
        else {
            printf("%d ", distances[i]);
        }
    }
    printf("\n");

    printf("Found: ");
    for (int i = 1; i < size; i++) {
        printf("%d ", found[i]);
    }
    printf("\n");

    printf("Path: ");
    for (int i = 1; i < size; i++) {
        if (found[i]) {
            printPath(path[i], i);
        }
    }
    printf("\n");
}

// 경로 출력
void printPath(int path[], int vertex) {
    int prev = -1;
    printf("Path to %d: ", vertex);
    for (int i = 1; i < MAX_VERTICES; i++) {
        if (path[i] == 1) {
            if (prev != -1) {
                printf(" -> ");
            }
            printf("%d", i);
            prev = i;
        }
    }
    printf("\n");
}
