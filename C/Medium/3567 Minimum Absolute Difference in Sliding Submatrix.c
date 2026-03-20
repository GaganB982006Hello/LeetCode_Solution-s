#include <stdlib.h>
#include <limits.h>

// Comparison function for qsort
int cmp(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int** minAbsDiff(int** grid, int gridSize, int* gridColSize, int k, int* returnSize, int** returnColumnSizes) {
    int m = gridSize;
    int n = gridColSize[0];
    int outRows = m - k + 1;
    int outCols = n - k + 1;
    
    // Set the number of rows being returned
    *returnSize = outRows;
    
    // Allocate memory for the array of column sizes and the 2D result array
    *returnColumnSizes = (int*)malloc(outRows * sizeof(int));
    int** ans = (int**)malloc(outRows * sizeof(int*));
    
    // Reusable buffer to hold the elements of the current k x k submatrix
    int* elements = (int*)malloc(k * k * sizeof(int));
    
    for (int i = 0; i < outRows; i++) {
        (*returnColumnSizes)[i] = outCols;
        ans[i] = (int*)malloc(outCols * sizeof(int));
        
        for (int j = 0; j < outCols; j++) {
            // Extract the k x k submatrix
            int idx = 0;
            for (int r = i; r < i + k; r++) {
                for (int c = j; c < j + k; c++) {
                    elements[idx++] = grid[r][c];
                }
            }
            
            // Sort the flattened submatrix elements
            qsort(elements, k * k, sizeof(int), cmp);
            
            // Find the minimum absolute difference between distinct elements
            int min_diff = INT_MAX;
            int found_distinct = 0;
            for (int l = 0; l < k * k - 1; l++) {
                int diff = elements[l + 1] - elements[l];
                if (diff > 0) {
                    if (diff < min_diff) {
                        min_diff = diff;
                    }
                    found_distinct = 1;
                }
            }
            
            ans[i][j] = found_distinct ? min_diff : 0;
        }
    }
    
    free(elements); // Free the temporary buffer
    return ans;
}
