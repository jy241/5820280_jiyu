#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VERTICES 10

// ���� ����Ʈ�� ��� ����ü
typedef struct Edge {
    int destination;
    int weight;
    struct Edge* next;
} Edge;

// �׷��� ����ü
typedef struct Graph {
    Edge* adjacencyList[MAX_VERTICES];
} Graph;

// �ּ� �� ��� ����ü
typedef struct MinHeapNode {
    int vertex;
    int distance;
} MinHeapNode;

// �ּ� �� ����ü
typedef struct MinHeap {
    MinHeapNode* array;
    int size;
    int capacity;
} MinHeap;

// �Լ� ������Ÿ��
Graph* createGraph();
void insertEdge(Graph* g, int src, int dest, int weight);
MinHeap* createMinHeap(int capacity);
void insertMinHeap(MinHeap* minHeap, int vertex, int distance);
MinHeapNode extractMin(MinHeap* minHeap);
int isEmpty(MinHeap* minHeap);
void dijkstra(Graph* g, int startVertex);
void printDistances(int distances[], int size, int found[], int path[][MAX_VERTICES], int startVertex);
void printPath(int path[], int vertex);

// ���� �Լ�
int main() {
    Graph* g = createGraph();

    // �׷����� ���� ����
    insertEdge(g, 1, 2, 3);
    insertEdge(g, 2, 5, 1);
    insertEdge(g, 5, 4, 4);
    insertEdge(g, 4, 3, 2);
    insertEdge(g, 3, 8, 5);
    insertEdge(g, 8, 7, 6);
    insertEdge(g, 7, 6, 12);
    insertEdge(g, 6, 10, 11);
    insertEdge(g, 10, 9, 10);

    // ���ͽ�Ʈ�� �˰��� ����
    dijkstra(g, 1);

    return 0;
}

// �׷��� ����
Graph* createGraph() {
    Graph* g = (Graph*)malloc(sizeof(Graph));
    for (int i = 0; i < MAX_VERTICES; i++) {
        g->adjacencyList[i] = NULL;
    }
    return g;
}

// ���� ����
void insertEdge(Graph* g, int src, int dest, int weight) {
    Edge* newEdge = (Edge*)malloc(sizeof(Edge));
    newEdge->destination = dest;
    newEdge->weight = weight;
    newEdge->next = g->adjacencyList[src];
    g->adjacencyList[src] = newEdge;
}

// �ּ� �� ����
MinHeap* createMinHeap(int capacity) {
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
    minHeap->capacity = capacity;
    minHeap->size = 0;
    minHeap->array = (MinHeapNode*)malloc(capacity * sizeof(MinHeapNode));
    return minHeap;
}

// �ּ� ���� ��� ����
void insertMinHeap(MinHeap* minHeap, int vertex, int distance) {
    minHeap->size++;
    int i = minHeap->size - 1;
    minHeap->array[i].vertex = vertex;
    minHeap->array[i].distance = distance;

    // �θ� ���� ���Ͽ� ��ġ ����
    while (i && minHeap->array[i].distance < minHeap->array[(i - 1) / 2].distance) {
        MinHeapNode temp = minHeap->array[i];
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        minHeap->array[(i - 1) / 2] = temp;
        i = (i - 1) / 2;
    }
}

// �ּ� ������ �ּ� ��� ����
MinHeapNode extractMin(MinHeap* minHeap) {
    if (isEmpty(minHeap)) {
        return (MinHeapNode) { -1, INT_MAX }; // �� ��� �ִ� �Ÿ� ��ȯ
    }
    MinHeapNode root = minHeap->array[0];
    MinHeapNode lastNode = minHeap->array[minHeap->size - 1];
    minHeap->size--;
    if (minHeap->size > 0) {
        minHeap->array[0] = lastNode;
        // �ּ� �� �Ӽ� ����
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

// �ּ� ���� ������� Ȯ��
int isEmpty(MinHeap* minHeap) {
    return minHeap->size == 0;
}

// ���ͽ�Ʈ�� �˰��� ����
void dijkstra(Graph* g, int startVertex) {
    int distances[MAX_VERTICES];
    int found[MAX_VERTICES] = { 0 }; // �߰� ����
    int path[MAX_VERTICES][MAX_VERTICES]; // ��� ����
    for (int i = 0; i < MAX_VERTICES; i++) {
        distances[i] = INT_MAX; // �ʱ�ȭ
        for (int j = 0; j < MAX_VERTICES; j++) {
            path[i][j] = 0; // �ʱ�ȭ
        }
    }
    distances[startVertex] = 0;

    MinHeap* minHeap = createMinHeap(MAX_VERTICES);
    insertMinHeap(minHeap, startVertex, distances[startVertex]);

    while (!isEmpty(minHeap)) {
        MinHeapNode minNode = extractMin(minHeap);
        int currentVertex = minNode.vertex;
        found[currentVertex] = 1; // ���� ���� �߰� ǥ��

        // ��� ���
        for (int i = 0; i < MAX_VERTICES; i++) {
            path[currentVertex][i] = path[i][currentVertex]; // ���� ��� ����
        }
        path[currentVertex][currentVertex] = 1; // ���� ���� ��� �߰�

        // ���� ���� Ž��
        Edge* edge = g->adjacencyList[currentVertex];
        while (edge != NULL) {
            int destination = edge->destination;
            int weight = edge->weight;

            // �ּ� �Ÿ� ������Ʈ
            if (distances[currentVertex] + weight < distances[destination]) {
                distances[destination] = distances[currentVertex] + weight;
                insertMinHeap(minHeap, destination, distances[destination]);
            }
            edge = edge->next;
        }

        // ���� ���� ���
        printDistances(distances, MAX_VERTICES, found, path, startVertex);
    }

    // ���� ��� ���
    printf("Final Order: ");
    for (int i = 1; i < MAX_VERTICES; i++) {
        if (found[i]) {
            printf("%d ", i);
        }
    }
    printf("\n");
}

// �ִ� �Ÿ� ���
void printDistances(int distances[], int size, int found[], int path[][MAX_VERTICES], int startVertex) {
    printf("Distance: ");
    for (int i = 1; i < size; i++) {
        if (distances[i] == INT_MAX) {
            printf(" * "); // ���Ѵ��� ���
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

// ��� ���
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
