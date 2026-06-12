/*
There is an undirected tree with n nodes labeled from 1 to n, rooted at node 1. The tree is represented by a 2D integer array edges of length n - 1, where edges[i] = [ui, vi] indicates that there is an edge between nodes ui and vi.

Initially, all edges have a weight of 0. You must assign each edge a weight of either 1 or 2.

The cost of a path between any two nodes u and v is the total weight of all edges in the path connecting them.

You are given a 2D integer array queries. For each queries[i] = [ui, vi], determine the number of ways to assign weights to edges in the path such that the cost of the path between ui and vi is odd.

Return an array answer, where answer[i] is the number of valid assignments for queries[i].

Since the answer may be large, apply modulo 109 + 7 to each answer[i].

Note: For each query, disregard all edges not in the path between node ui and vi.

 

Example 1:



Input: edges = [[1,2]], queries = [[1,1],[1,2]]

Output: [0,1]

Explanation:

Query [1,1]: The path from Node 1 to itself consists of no edges, so the cost is 0. Thus, the number of valid assignments is 0.
Query [1,2]: The path from Node 1 to Node 2 consists of one edge (1 → 2). Assigning weight 1 makes the cost odd, while 2 makes it even. Thus, the number of valid assignments is 1.
Example 2:



Input: edges = [[1,2],[1,3],[3,4],[3,5]], queries = [[1,4],[3,4],[2,5]]

Output: [2,1,4]

Explanation:

Query [1,4]: The path from Node 1 to Node 4 consists of two edges (1 → 3 and 3 → 4). Assigning weights (1,2) or (2,1) results in an odd cost. Thus, the number of valid assignments is 2.
Query [3,4]: The path from Node 3 to Node 4 consists of one edge (3 → 4). Assigning weight 1 makes the cost odd, while 2 makes it even. Thus, the number of valid assignments is 1.
Query [2,5]: The path from Node 2 to Node 5 consists of three edges (2 → 1, 1 → 3, and 3 → 5). Assigning (1,2,2), (2,1,2), (2,2,1), or (1,1,1) makes the cost odd. Thus, the number of valid assignments is 4.
 

Constraints:

2 <= n <= 105
edges.length == n - 1
edges[i] == [ui, vi]
1 <= queries.length <= 105
queries[i] == [ui, vi]
1 <= ui, vi <= n
edges represents a valid tree.
*/

#include <stdlib.h>
#include <stdbool.h>

#define LOG 18
#define MOD 1000000007

typedef struct Edge {
    int to;
    struct Edge* next;
} Edge;

int getLCA(int u, int v, int** up, int* depth) {
    if (depth[u] < depth[v]) {
        int temp = u; u = v; v = temp;
    }
    int diff = depth[u] - depth[v];
    for (int i = 0; i < LOG; i++) {
        if ((diff >> i) & 1) u = up[u][i];
    }
    if (u == v) return u;
    
    for (int i = LOG - 1; i >= 0; i--) {
        if (up[u][i] != up[v][i]) {
            u = up[u][i];
            v = up[v][i];
        }
    }
    return up[u][0];
}

long long modPow(long long base, int exp) {
    long long res = 1;
    base %= MOD;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % MOD;
        base = (base * base) % MOD;
        exp /= 2;
    }
    return res;
}

int* assignEdgeWeights(int** edges, int edgesSize, int* edgesColSize, int** queries, int queriesSize, int* queriesColSize, int* returnSize) {
    int n = edgesSize + 1;
    
    Edge** head = (Edge**)calloc(n + 1, sizeof(Edge*));
    Edge* pool = (Edge*)malloc(2 * edgesSize * sizeof(Edge));
    int poolIdx = 0;
    
    for (int i = 0; i < edgesSize; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        
        pool[poolIdx].to = v;
        pool[poolIdx].next = head[u];
        head[u] = &pool[poolIdx++];
        
        pool[poolIdx].to = u;
        pool[poolIdx].next = head[v];
        head[v] = &pool[poolIdx++];
    }
    
    int** up = (int**)malloc((n + 1) * sizeof(int*));
    for (int i = 0; i <= n; i++) up[i] = (int*)calloc(LOG, sizeof(int));
    int* depth = (int*)calloc(n + 1, sizeof(int));
    
    // BFS implementation
    int* q = (int*)malloc((n + 1) * sizeof(int));
    int head_q = 0, tail_q = 0;
    bool* visited = (bool*)calloc(n + 1, sizeof(bool));
    
    q[tail_q++] = 1;
    visited[1] = true;
    up[1][0] = 1;
    
    while (head_q < tail_q) {
        int u = q[head_q++];
        for (Edge* e = head[u]; e != NULL; e = e->next) {
            int v = e->to;
            if (!visited[v]) {
                visited[v] = true;
                depth[v] = depth[u] + 1;
                up[v][0] = u;
                q[tail_q++] = v;
            }
        }
    }
    
    for (int j = 1; j < LOG; j++) {
        for (int i = 1; i <= n; i++) {
            up[i][j] = up[up[i][j-1]][j-1];
        }
    }
    
    int* ans = (int*)malloc(queriesSize * sizeof(int));
    *returnSize = queriesSize;
    
    for (int i = 0; i < queriesSize; i++) {
        int u = queries[i][0];
        int v = queries[i][1];
        int lca = getLCA(u, v, up, depth);
        int dist = depth[u] + depth[v] - 2 * depth[lca];
        
        if (dist == 0) {
            ans[i] = 0;
        } else {
            ans[i] = modPow(2, dist - 1);
        }
    }
    
    // Memory cleanup
    for (int i = 0; i <= n; i++) free(up[i]);
    free(up);
    free(depth);
    free(head);
    free(pool);
    free(q);
    free(visited);
    
    return ans;
}
