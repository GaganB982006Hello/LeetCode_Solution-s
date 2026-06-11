/*
There is an undirected tree with n nodes labeled from 1 to n, rooted at node 1. The tree is represented by a 2D integer array edges of length n - 1, where edges[i] = [ui, vi] indicates that there is an edge between nodes ui and vi.

Initially, all edges have a weight of 0. You must assign each edge a weight of either 1 or 2.

The cost of a path between any two nodes u and v is the total weight of all edges in the path connecting them.

Select any one node x at the maximum depth. Return the number of ways to assign edge weights in the path from node 1 to x such that its total cost is odd.

Since the answer may be large, return it modulo 109 + 7.

Note: Ignore all edges not in the path from node 1 to x.

 

Example 1:



Input: edges = [[1,2]]

Output: 1

Explanation:

The path from Node 1 to Node 2 consists of one edge (1 → 2).
Assigning weight 1 makes the cost odd, while 2 makes it even. Thus, the number of valid assignments is 1.
Example 2:



Input: edges = [[1,2],[1,3],[3,4],[3,5]]

Output: 2

Explanation:

The maximum depth is 2, with nodes 4 and 5 at the same depth. Either node can be selected for processing.
For example, the path from Node 1 to Node 4 consists of two edges (1 → 3 and 3 → 4).
Assigning weights (1,2) or (2,1) results in an odd cost. Thus, the number of valid assignments is 2.
 

Constraints:

2 <= n <= 105
edges.length == n - 1
edges[i] == [ui, vi]
1 <= ui, vi <= n
edges represents a valid tree.
  */

#include <stdlib.h>

// Fast modular exponentiation
long long power(long long base, long long exp, long long mod) {
    long long res = 1;
    base %= mod;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return res;
}

int assignEdgeWeights(int** edges, int edgesSize, int* edgesColSize) {
    // Calculate n (a tree has n - 1 edges)
    int n = edgesSize + 1;
    
    // Implementing an adjacency list using offset arrays (CSR format)
    int* head = (int*)calloc(n + 1, sizeof(int));
    for (int i = 0; i <= n; i++) head[i] = -1;
    
    int* next = (int*)malloc((2 * edgesSize) * sizeof(int));
    int* to = (int*)malloc((2 * edgesSize) * sizeof(int));
    
    for (int i = 0; i < edgesSize; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        
        // Edge u -> v
        to[2 * i] = v;
        next[2 * i] = head[u];
        head[u] = 2 * i;
        
        // Edge v -> u
        to[2 * i + 1] = u;
        next[2 * i + 1] = head[v];
        head[v] = 2 * i + 1;
    }
    
    // BFS configuration
    int* q = (int*)malloc(n * sizeof(int));
    int* depth = (int*)malloc((n + 1) * sizeof(int));
    for (int i = 0; i <= n; i++) depth[i] = -1;
    
    int front = 0, rear = 0;
    q[rear++] = 1;
    depth[1] = 0;
    int max_d = 0;
    
    // Execute BFS to find maximum depth
    while (front < rear) {
        int u = q[front++];
        if (depth[u] > max_d) {
            max_d = depth[u];
        }
        
        for (int e = head[u]; e != -1; e = next[e]) {
            int v = to[e];
            if (depth[v] == -1) {
                depth[v] = depth[u] + 1;
                q[rear++] = v;
            }
        }
    }
    
    // Free allocated memory
    free(head);
    free(next);
    free(to);
    free(q);
    free(depth);
    
    return (int)power(2, max_d - 1, 1000000007);
}
