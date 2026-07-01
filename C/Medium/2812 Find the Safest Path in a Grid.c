/*
You are given a 0-indexed 2D matrix grid of size n x n, where (r, c) represents:

A cell containing a thief if grid[r][c] = 1
An empty cell if grid[r][c] = 0
You are initially positioned at cell (0, 0). In one move, you can move to any adjacent cell in the grid, including cells containing thieves.

The safeness factor of a path on the grid is defined as the minimum manhattan distance from any cell in the path to any thief in the grid.

Return the maximum safeness factor of all paths leading to cell (n - 1, n - 1).

An adjacent cell of cell (r, c), is one of the cells (r, c + 1), (r, c - 1), (r + 1, c) and (r - 1, c) if it exists.

The Manhattan distance between two cells (a, b) and (x, y) is equal to |a - x| + |b - y|, where |val| denotes the absolute value of val.

 

Example 1:


Input: grid = [[1,0,0],[0,0,0],[0,0,1]]
Output: 0
Explanation: All paths from (0, 0) to (n - 1, n - 1) go through the thieves in cells (0, 0) and (n - 1, n - 1).
Example 2:


Input: grid = [[0,0,1],[0,0,0],[0,0,0]]
Output: 2
Explanation: The path depicted in the picture above has a safeness factor of 2 since:
- The closest cell of the path to the thief at cell (0, 2) is cell (0, 0). The distance between them is | 0 - 0 | + | 0 - 2 | = 2.
It can be shown that there are no other paths with a higher safeness factor.
Example 3:


Input: grid = [[0,0,0,1],[0,0,0,0],[0,0,0,0],[1,0,0,0]]
Output: 2
Explanation: The path depicted in the picture above has a safeness factor of 2 since:
- The closest cell of the path to the thief at cell (0, 3) is cell (1, 2). The distance between them is | 0 - 1 | + | 3 - 2 | = 2.
- The closest cell of the path to the thief at cell (3, 0) is cell (3, 2). The distance between them is | 3 - 3 | + | 0 - 2 | = 2.
It can be shown that there are no other paths with a higher safeness factor.
 

Constraints:

1 <= grid.length == n <= 400
grid[i].length == n
grid[i][j] is either 0 or 1.
There is at least one thief in the grid.
*/

#include <stdlib.h>
#include <stdbool.h>

// A simple structure to represent coordinates in our queue
typedef struct {
    int r;
    int c;
} Pair;

int maximumSafenessFactor(int** grid, int gridSize, int* gridColSize) {
    int n = gridSize;
    // If the start or end cell has a thief, safeness is 0
    if (grid[0][0] == 1 || grid[n - 1][n - 1] == 1) {
        return 0;
    }

    // Allocate distance grid and initialize to -1 (unvisited)
    int** dist = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        dist[i] = (int*)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            dist[i][j] = -1; 
        }
    }

    // Allocate a queue large enough for all grid cells
    Pair* q = (Pair*)malloc(n * n * sizeof(Pair));
    int head = 0, tail = 0;

    // Step 1: Multi-source BFS to find distance to the nearest thief
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            if (grid[r][c] == 1) {
                dist[r][c] = 0;
                q[tail].r = r;
                q[tail].c = c;
                tail++;
            }
        }
    }

    int dirs[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

    while (head < tail) {
        Pair curr = q[head++];
        for (int i = 0; i < 4; i++) {
            int nr = curr.r + dirs[i][0];
            int nc = curr.c + dirs[i][1];
            if (nr >= 0 && nr < n && nc >= 0 && nc < n && dist[nr][nc] == -1) {
                dist[nr][nc] = dist[curr.r][curr.c] + 1;
                q[tail].r = nr;
                q[tail].c = nc;
                tail++;
            }
        }
    }

    // Step 2: Binary Search for the maximum valid safeness factor
    // The max possible safe path cannot exceed the safety of the start or end point
    int left = 0;
    int right = dist[0][0] < dist[n - 1][n - 1] ? dist[0][0] : dist[n - 1][n - 1];
    int ans = 0;

    // Pre-allocate a visited array to reuse during binary search
    bool** visited = (bool**)malloc(n * sizeof(bool*));
    for (int i = 0; i < n; i++) {
        visited[i] = (bool*)malloc(n * sizeof(bool));
    }

    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        // Reset the visited array for the current binary search test
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                visited[i][j] = false;
            }
        }

        head = 0;
        tail = 0;
        q[tail].r = 0;
        q[tail].c = 0;
        tail++;
        visited[0][0] = true;
        bool possible = false;

        // Standard BFS checking if a path exists using only cells with dist >= mid
        while (head < tail) {
            Pair curr = q[head++];
            if (curr.r == n - 1 && curr.c == n - 1) {
                possible = true;
                break;
            }
            for (int i = 0; i < 4; i++) {
                int nr = curr.r + dirs[i][0];
                int nc = curr.c + dirs[i][1];
                if (nr >= 0 && nr < n && nc >= 0 && nc < n && !visited[nr][nc] && dist[nr][nc] >= mid) {
                    visited[nr][nc] = true;
                    q[tail].r = nr;
                    q[tail].c = nc;
                    tail++;
                }
            }
        }

        if (possible) {
            ans = mid;         // This safeness factor works, try a higher one
            left = mid + 1;
        } else {
            right = mid - 1;   // It failed, we need a lower safeness factor
        }
    }

    // Step 3: Free allocated memory to prevent memory leaks
    for (int i = 0; i < n; i++) {
        free(dist[i]);
        free(visited[i]);
    }
    free(dist);
    free(visited);
    free(q);

    return ans;
}
