int** reverseSubmatrix(int** grid, int gridSize, int* gridColSize, int x, int y, int k, int* returnSize, int** returnColumnSizes) {
    int top = x;
    int bottom = x + k - 1;
    
    while (top < bottom) {
        for (int j = y; j < y + k; j++) {
            int temp = grid[top][j];
            grid[top][j] = grid[bottom][j];
            grid[bottom][j] = temp;
        }
        top++;
        bottom--;
    }
    
    *returnSize = gridSize;
    *returnColumnSizes = gridColSize;
    return grid;
}
