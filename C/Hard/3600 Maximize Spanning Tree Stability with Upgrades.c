#include <stdlib.h>

typedef struct {
    int u, v, s, m;
} Edge;

int compareEdges(const void *a, const void *b) {
    Edge *ea = (Edge *)a;
    Edge *eb = (Edge *)b;
    if (ea->s < eb->s) return 1;
    if (ea->s > eb->s) return -1;
    return 0;
}

int find(int *parent, int i) {
    if (parent[i] == i) return i;
    return parent[i] = find(parent, parent[i]);
}

int union_set(int *parent, int *rank, int i, int j) {
    int root_i = find(parent, i);
    int root_j = find(parent, j);
    if (root_i != root_j) {
        if (rank[root_i] < rank[root_j]) {
            parent[root_i] = root_j;
        } else if (rank[root_i] > rank[root_j]) {
            parent[root_j] = root_i;
        } else {
            parent[root_j] = root_i;
            rank[root_i]++;
        }
        return 1;
    }
    return 0;
}

int maxStability(int n, int** edges, int edgesSize, int* edgesColSize, int k) {
    int *parent = (int *)malloc(n * sizeof(int));
    int *rank = (int *)calloc(n, sizeof(int));
    for (int i = 0; i < n; i++) parent[i] = i;

    Edge *edgeArr = (Edge *)malloc(edgesSize * sizeof(Edge));
    for (int i = 0; i < edgesSize; i++) {
        edgeArr[i].u = edges[i][0];
        edgeArr[i].v = edges[i][1];
        edgeArr[i].s = edges[i][2];
        edgeArr[i].m = edges[i][3];
    }

    int cnt = 0;
    // Set baseline infinity high above max potential upgraded edge 
    // max constraints edge strength is 10^5, max doubled is 2 * 10^5.
    int min_strength = 2000000000; 

    // Pass 1
    for (int i = 0; i < edgesSize; i++) {
        if (edgeArr[i].m == 0) continue;
        if (!union_set(parent, rank, edgeArr[i].u, edgeArr[i].v)) {
            free(parent); free(rank); free(edgeArr);
            return -1;
        }
        cnt++;
        if (edgeArr[i].s < min_strength) min_strength = edgeArr[i].s;
    }

    // Pass 2
    qsort(edgeArr, edgesSize, sizeof(Edge), compareEdges);

    for (int i = 0; i < edgesSize; i++) {
        if (edgeArr[i].m == 1) continue;
        if (!union_set(parent, rank, edgeArr[i].u, edgeArr[i].v)) continue;
        cnt++;
        
        if (cnt == (n - 1) - k) {
            if (edgeArr[i].s < min_strength) min_strength = edgeArr[i].s;
        } else if (cnt == n - 1) {
            if (2 * edgeArr[i].s < min_strength) min_strength = 2 * edgeArr[i].s;
        }
    }

    free(parent); free(rank); free(edgeArr);
    return (cnt == n - 1) ? min_strength : -1;
}
