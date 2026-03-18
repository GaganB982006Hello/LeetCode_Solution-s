int countSubmatrices(int** grid, int gridSize, int* gridColSize, int k) {
    int m = gridSize;
    int n = gridColSize[0];
    int count = 0;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (i > 0) grid[i][j] += grid[i - 1][j];
            if (j > 0) grid[i][j] += grid[i][j - 1];
            if (i > 0 && j > 0) grid[i][j] -= grid[i - 1][j - 1];

            if (grid[i][j] <= k) {
                count++;
            } else {
                // Set to a large value so subsequent calculations 
                // for lower rows remain above k.
                grid[i][j] = k + 1; 
                break;
            }
        }
    }
    return count;
}
