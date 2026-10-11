#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
	int u, v, w;
	int id;
} Edge;

void kruskalMST(int **cost, int V) {
	int maxEdges = V * (V - 1) / 2;
	Edge *edges = (Edge *)malloc(maxEdges * sizeof(Edge));
	int edgeCount = 0;

	for (int i = 0; i < V; i++) {
		for (int j = i + 1; j < V; j++) {
			if (cost[i][j] != 9999) {
				edges[edgeCount].u = i;
				edges[edgeCount].v = j;
				edges[edgeCount].w = cost[i][j];
				edges[edgeCount].id = edgeCount;
				edgeCount++;
			}
		}
	}

	for (int i = 0; i < edgeCount - 1; i++) {
		for (int j = 0; j < edgeCount - i - 1; j++) {
			if (edges[j].w > edges[j + 1].w || (edges[j].w == edges[j + 1].w && edges[j].id > edges[j + 1].id)) {
				Edge temp = edges[j];
				edges[j] = edges[j + 1];
				edges[j + 1] = temp;
			}
		}
	}

	int *parent = (int *)malloc(V * sizeof(int));
	for (int i = 0; i < V; i++) {
		parent[i] = i;
	}

	int mst_edges = 0;
	int min_cost = 0;

	for (int i = 0; i < edgeCount; i++) {
		int u = edges[i].u;
		int v = edges[i].v;

		int root_u = u;
		while (parent[root_u] != root_u) {
			root_u = parent[root_u];
		}

		int root_v = v;
		while (parent[root_v] != root_v) {
			root_v = parent[root_v];
		}

		if (root_u != root_v) {
			printf("Edge %d:(%d, %d) cost:%d\n", mst_edges, u, v, edges[i].w);
			min_cost += edges[i].w;
			parent[root_u] = root_v;
			mst_edges++;

			if (mst_edges == V - 1) {
				break;
			}
		}
	}

	printf("Minimum cost= %d\n", min_cost);

	free(edges);
	free(parent);
}

int main() {
    int V;
    printf("No of vertices: ");
    scanf("%d", &V);

    int **cost = (int **)malloc(V * sizeof(int *));
    for (int i = 0; i < V; i++)
        cost[i] = (int *)malloc(V * sizeof(int));

    printf("Adjacency matrix:\n");
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            scanf("%d", &cost[i][j]);

    kruskalMST(cost, V);

    for (int i = 0; i < V; i++)
        free(cost[i]);
    free(cost);

    return 0;
}