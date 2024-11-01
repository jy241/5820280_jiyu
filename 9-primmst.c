#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VERTICES 100
#define INF INT_MAX

typedef struct {
    int adj[MAX_VERTICES][MAX_VERTICES];
    int num_vertices;
} GraphType;

void graph_init(GraphType* g) {
    g->num_vertices = 0;
    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = 0; j < MAX_VERTICES; j++) {
            g->adj[i][j] = (i == j) ? 0 : INF;
        }
    }
}

void insert_edge(GraphType* g, int start, int end, int weight) {
    g->adj[start][end] = weight;
    g->adj[end][start] = weight; // ���� �׷����̹Ƿ� ���ʿ� �߰�
    if (start > g->num_vertices) g->num_vertices = start;
    if (end > g->num_vertices) g->num_vertices = end;
}

void FindPrimMST(GraphType* g) {
    int selected[MAX_VERTICES] = { 0 };
    int num_edges = 0;

    selected[1] = 1; // ù ��° ����(1�� ����)�� ����
    printf("���� 1 �߰�\n");

    while (num_edges < g->num_vertices - 1) {
        int min_weight = INF;
        int u = -1, v = -1;

        for (int i = 1; i <= g->num_vertices; i++) {
            if (selected[i]) {
                for (int j = 1; j <= g->num_vertices; j++) {
                    if (!selected[j] && g->adj[i][j] < min_weight) {
                        min_weight = g->adj[i][j];
                        u = i;
                        v = j;
                    }
                }
            }
        }

        if (v != -1) {
            selected[v] = 1; // ���� v�� ����
            num_edges++;

            printf("���� %d �߰�\n", v); // �߰��� ���� ���
        }
    }
}

void GenerateGraph(GraphType* g) {
    // �׷��� ������ �����Ͽ� ���ϴ� ������ ������ �߰��ǵ��� ����
    insert_edge(g, 1, 2, 3); // 1 - 2
    insert_edge(g, 2, 5, 1); // 2 - 5
    insert_edge(g, 5, 4, 4); // 5 - 4
    insert_edge(g, 4, 3, 2); // 4 - 3
    insert_edge(g, 3, 8, 5); // 3 - 8
    insert_edge(g, 8, 7, 6); // 8 - 7
    insert_edge(g, 7, 6, 12); // 7 - 6
    insert_edge(g, 6, 10, 11); // 6 - 10
    insert_edge(g, 10, 9, 10); // 10 - 9

    // ���� �� ������Ʈ
    g->num_vertices = 10;
}

int main(void) {
    GraphType* g;
    g = (GraphType*)malloc(sizeof(GraphType));
    graph_init(g);

    //�׷����� �����ϴ� �Լ�
    GenerateGraph(g);

    FindPrimMST(g); // Prim�� �̿��� MST�� ã��
    
    free(g);
    return 0;
}
