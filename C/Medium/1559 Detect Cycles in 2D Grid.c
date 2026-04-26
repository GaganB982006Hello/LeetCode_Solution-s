/*
Given a 2D array of characters grid of size m x n, you need to find if there exists any cycle consisting of the same value in grid.

A cycle is a path of length 4 or more in the grid that starts and ends at the same cell. From a given cell, you can move to one of the cells adjacent to it - in one of the four directions (up, down, left, or right), if it has the same value of the current cell.

Also, you cannot move to the cell that you visited in your last move. For example, the cycle (1, 1) -> (1, 2) -> (1, 1) is invalid because from (1, 2) we visited (1, 1) which was the last visited cell.

Return true if any cycle of the same value exists in grid, otherwise, return false.

 

Example 1:



Input: grid = [["a","a","a","a"],["a","b","b","a"],["a","b","b","a"],["a","a","a","a"]]
Output: true
Explanation: There are two valid cycles shown in different colors in the image below:

Example 2:



Input: grid = [["c","c","c","a"],["c","d","c","c"],["c","c","e","c"],["f","c","c","c"]]
Output: true
Explanation: There is only one valid cycle highlighted in the image below:

*/

#include <stdbool.h>

bool dfs(char** grid, int m, int n, int** visited, int r, int c, int pr, int pc, char val) {
    visited[r][c] = 1;
    int dr[] = {0, 0, 1, -1};
    int dc[] = {1, -1, 0, 0};

    for (int i = 0; i < 4; i++) {
        int nr = r + dr[i];
        int nc = c + dc[i];

        if (nr >= 0 && nr < m && nc >= 0 && nc < n && grid[nr][nc] == val) {
            if (visited[nr][nc]) {
                if (nr != pr || nc != pc) return true;
            } else {
                if (dfs(grid, m, n, visited, nr, nc, r, c, val)) return true;
            }
        }
    }
    return false;
}

bool containsCycle(char** grid, int gridSize, int* gridColSize) {
    int m = gridSize;
    int n = gridColSize[0];
    
    int** visited = (int**)malloc(m * sizeof(int*));
    for (int i = 0; i < m; i++) {
        visited[i] = (int*)calloc(n, sizeof(int));
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (!visited[i][j]) {
                if (dfs(grid, m, n, visited, i, j, -1, -1, grid[i][j])) {
                    // Free memory before returning
                    for (int k = 0; k < m; k++) free(visited[k]);
                    free(visited);
                    return true;
                }
            }
        }
    }

    for (int i = 0; i < m; i++) free(visited[i]);
    free(visited);
    return false;
}
