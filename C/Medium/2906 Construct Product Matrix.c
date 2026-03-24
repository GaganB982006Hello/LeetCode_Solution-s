#include <stdlib.h>

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** constructProductMatrix(int** grid, int gridSize, int* gridColSize, int* returnSize, int** returnColumnSizes) {
    int n = gridSize;
    int m = gridColSize[0];
    int mod = 12345;
    
    // 1. Memory Allocation for the result matrix
    int** p = (int**)malloc(n * sizeof(int*));
    *returnColumnSizes = (int*)malloc(n * sizeof(int));
    *returnSize = n;
    
    for (int i = 0; i < n; i++) {
        p[i] = (int*)malloc(m * sizeof(int));
        (*returnColumnSizes)[i] = m;
    }

    long runningProduct = 1;

    // 2. Prefix Product Pass
    // We store the product of all elements seen so far (before grid[i][j])
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            p[i][j] = (int)runningProduct;
            // Update running product with current element, modulo 12345
            runningProduct = (runningProduct * (grid[i][j] % mod)) % mod;
        }
    }

    // 3. Suffix Product Pass
    // We traverse backwards and multiply the prefix product by the suffix product
    runningProduct = 1;
    for (int i = n - 1; i >= 0; i--) {
        for (int j = m - 1; j >= 0; j--) {
            p[i][j] = (int)((p[i][j] * runningProduct) % mod);
            // Update running product for the next element in reverse
            runningProduct = (runningProduct * (grid[i][j] % mod)) % mod;
        }
    }

    return p;
}
