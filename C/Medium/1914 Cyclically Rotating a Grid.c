/*
You are given an m x n integer matrix grid​​​, where m and n are both even integers, and an integer k.

The matrix is composed of several layers, which is shown in the below image, where each color is its own layer:



A cyclic rotation of the matrix is done by cyclically rotating each layer in the matrix. To cyclically rotate a layer once, each element in the layer will take the place of the adjacent element in the counter-clockwise direction. An example rotation is shown below:


Return the matrix after applying k cyclic rotations to it.

 

Example 1:


Input: grid = [[40,10],[30,20]], k = 1
Output: [[10,20],[40,30]]
Explanation: The figures above represent the grid at every state.
Example 2:


Input: grid = [[1,2,3,4],[5,6,7,8],[9,10,11,12],[13,14,15,16]], k = 2
Output: [[3,4,8,12],[2,11,10,16],[1,7,6,15],[5,9,13,14]]
Explanation: The figures above represent the grid at every state.
 

Constraints:

m == grid.length
n == grid[i].length
2 <= m, n <= 50
Both m and n are even integers.
1 <= grid[i][j] <= 5000
1 <= k <= 109
  */
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 */
int** rotateGrid(int** grid, int gridSize, int* gridColSize, int k, int* returnSize, int** returnColumnSizes) {
    int m = gridSize;
    int n = gridColSize[0];
    int num_layers = (m < n ? m : n) / 2;

    for (int l = 0; l < num_layers; l++) {
        int height = m - 2 * l;
        int width = n - 2 * l;
        int total = 2 * (height + width) - 4;
        int* layerArr = (int*)malloc(total * sizeof(int));
        int idx = 0;

        // Extract
        for (int j = l; j < n - 1 - l; j++) layerArr[idx++] = grid[l][j];
        for (int i = l; i < m - 1 - l; i++) layerArr[idx++] = grid[i][n - 1 - l];
        for (int j = n - 1 - l; j > l; j--) layerArr[idx++] = grid[m - 1 - l][j];
        for (int i = m - 1 - l; i > l; i--) layerArr[idx++] = grid[i][l];

        int netK = k % total;
        idx = 0;
        // Put back with offset
        for (int j = l; j < n - 1 - l; j++) grid[l][j] = layerArr[(idx++ + netK) % total];
        for (int i = l; i < m - 1 - l; i++) grid[i][n - 1 - l] = layerArr[(idx++ + netK) % total];
        for (int j = n - 1 - l; j > l; j--) grid[m - 1 - l][j] = layerArr[(idx++ + netK) % total];
        for (int i = m - 1 - l; i > l; i--) grid[i][l] = layerArr[(idx++ + netK) % total];
        
        free(layerArr);
    }

    *returnSize = m;
    *returnColumnSizes = gridColSize;
    return grid;
}
