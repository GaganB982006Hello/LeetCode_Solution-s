/*
You are given an m x n grid. Each cell of grid represents a street. The street of grid[i][j] can be:

1 which means a street connecting the left cell and the right cell.
2 which means a street connecting the upper cell and the lower cell.
3 which means a street connecting the left cell and the lower cell.
4 which means a street connecting the right cell and the lower cell.
5 which means a street connecting the left cell and the upper cell.
6 which means a street connecting the right cell and the upper cell.

You will initially start at the street of the upper-left cell (0, 0). A valid path in the grid is a path that starts from the upper left cell (0, 0) and ends at the bottom-right cell (m - 1, n - 1). The path should only follow the streets.

Notice that you are not allowed to change any street.

Return true if there is a valid path in the grid or false otherwise.

 

Example 1:


Input: grid = [[2,4,3],[6,5,2]]
Output: true
Explanation: As shown you can start at cell (0, 0) and visit all the cells of the grid to reach (m - 1, n - 1).
Example 2:


Input: grid = [[1,2,1],[1,2,1]]
Output: false
Explanation: As shown you the street at cell (0, 0) is not connected with any street of any other cell and you will get stuck at cell (0, 0)
Example 3:

Input: grid = [[1,1,2]]
Output: false
Explanation: You will get stuck at cell (0, 1) and you cannot reach cell (0, 2).
 

Constraints:

m == grid.length
n == grid[i].length
1 <= m, n <= 300
1 <= grid[i][j] <= 6
*/

#include <stdbool.h>
#include <stdlib.h>

bool hasValidPath(int** grid, int gridSize, int* gridColSize) {
    int m = gridSize, n = gridColSize[0];
    bool visited[m][n];
    for (int i = 0; i < m; i++) 
        for (int j = 0; j < n; j++) visited[i][j] = false;

    // Directions: 0:Up, 1:Down, 2:Left, 3:Right
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};
    bool connections[7][4] = {
        {0,0,0,0},
        {0,0,1,1}, {1,1,0,0}, {0,1,1,0},
        {0,1,0,1}, {1,0,1,0}, {1,0,0,1}
    };

    int* queueR = (int*)malloc(m * n * sizeof(int));
    int* queueC = (int*)malloc(m * n * sizeof(int));
    int head = 0, tail = 0;

    queueR[tail] = 0;
    queueC[tail++] = 0;
    visited[0][0] = true;

    while (head < tail) {
        int r = queueR[head];
        int c = queueC[head++];
        if (r == m - 1 && c == n - 1) {
            free(queueR); free(queueC);
            return true;
        }

        for (int i = 0; i < 4; i++) {
            int nr = r + dr[i], nc = c + dc[i];
            if (nr >= 0 && nr < m && nc >= 0 && nc < n && !visited[nr][nc]) {
                int opp = i ^ 1;
                if (connections[grid[r][c]][i] && connections[grid[nr][nc]][opp]) {
                    visited[nr][nc] = true;
                    queueR[tail] = nr;
                    queueC[tail++] = nc;
                }
            }
        }
    }

    free(queueR); free(queueC);
    return false;
}
