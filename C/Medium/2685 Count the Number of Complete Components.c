/*
You are given an integer n. There is an undirected graph with n vertices, numbered from 0 to n - 1. You are given a 2D integer array edges where edges[i] = [ai, bi] denotes that there exists an undirected edge connecting vertices ai and bi.

Return the number of complete connected components of the graph.

A connected component is a subgraph of a graph in which there exists a path between any two vertices, and no vertex of the subgraph shares an edge with a vertex outside of the subgraph.

A connected component is said to be complete if there exists an edge between every pair of its vertices.

 

Example 1:



Input: n = 6, edges = [[0,1],[0,2],[1,2],[3,4]]
Output: 3
Explanation: From the picture above, one can see that all of the components of this graph are complete.
Example 2:



Input: n = 6, edges = [[0,1],[0,2],[1,2],[3,4],[3,5]]
Output: 1
Explanation: The component containing vertices 0, 1, and 2 is complete since there is an edge between every pair of two vertices. On the other hand, the component containing vertices 3, 4, and 5 is not complete since there is no edge between vertices 4 and 5. Thus, the number of complete components in this graph is 1.
 

Constraints:

1 <= n <= 50
0 <= edges.length <= n * (n - 1) / 2
edges[i].length == 2
0 <= ai, bi <= n - 1
ai != bi
There are no repeated edges.
  */

int countCompleteComponents(int n, int** edges, int edgesSize, int* edgesColSize) {
    int adj[50][50] = {0};
    int degree[50] = {0};

    // Build the adjacency matrix and track degrees
    for (int i = 0; i < edgesSize; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        adj[u][degree[u]++] = v;
        adj[v][degree[v]++] = u;
    }

    int visited[50] = {0};
    int completeComponents = 0;

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            int vCount = 0;
            int eCount = 0;

            // Simple queue for BFS
            int q[50];
            int head = 0, tail = 0;

            q[tail++] = i;
            visited[i] = 1;

            while (head < tail) {
                int curr = q[head++];
                vCount++;
                eCount += degree[curr];

                for (int j = 0; j < degree[curr]; j++) {
                    int neighbor = adj[curr][j];
                    if (!visited[neighbor]) {
                        visited[neighbor] = 1;
                        q[tail++] = neighbor;
                    }
                }
            }

            // Check if the component is complete
            if (eCount == vCount * (vCount - 1)) {
                completeComponents++;
            }
        }
    }
    return completeComponents;
}
