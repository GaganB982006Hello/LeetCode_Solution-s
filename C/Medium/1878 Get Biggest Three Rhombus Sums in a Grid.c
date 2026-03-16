#include <stdlib.h>

// Helper function to maintain the top 3 distinct sums in descending order
void updateTop3(int* top3, int val) {
    // Check if the value is already in the top 3 to ensure distinctness
    if (val == top3[0] || val == top3[1] || val == top3[2]) {
        return;
    }
    
    // Insert the new value in the correct sorted position
    if (val > top3[0]) {
        top3[2] = top3[1];
        top3[1] = top3[0];
        top3[0] = val;
    } else if (val > top3[1]) {
        top3[2] = top3[1];
        top3[1] = val;
    } else if (val > top3[2]) {
        top3[2] = val;
    }
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* getBiggestThree(int** grid, int gridSize, int* gridColSize, int* returnSize) {
    int m = gridSize;
    int n = gridColSize[0];
    
    // Initialize with -1 since grid values are positive
    int top3[3] = {-1, -1, -1};

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            int sz = 0;
            
            // Treat (i, j) as the LEFT corner. 
            // Check bounds: Top (i - sz), Bottom (i + sz), Right (j + 2 * sz)
            while (i - sz >= 0 && i + sz < m && j + 2 * sz < n) {
                int current_sum = 0;
                
                if (sz == 0) {
                    current_sum = grid[i][j];
                } else {
                    int x = i, y = j;
                    
                    // Go UP-RIGHT
                    for (int k = 0; k < sz; k++) {
                        x -= 1; y += 1;
                        current_sum += grid[x][y];
                    }
                    // Go DOWN-RIGHT
                    for (int k = 0; k < sz; k++) {
                        x += 1; y += 1;
                        current_sum += grid[x][y];
                    }
                    // Go DOWN-LEFT
                    for (int k = 0; k < sz; k++) {
                        x += 1; y -= 1;
                        current_sum += grid[x][y];
                    }
                    // Go UP-LEFT
                    for (int k = 0; k < sz; k++) {
                        x -= 1; y -= 1;
                        current_sum += grid[x][y];
                    }
                }
                
                // Try to add the calculated sum to our top 3 array
                updateTop3(top3, current_sum);
                sz++;
            }
        }
    }

    // Count how many valid distinct sums we actually found
    int count = 0;
    for (int i = 0; i < 3; i++) {
        if (top3[i] != -1) count++;
    }

    // Prepare the return array expected by LeetCode
    *returnSize = count;
    int* result = (int*)malloc(count * sizeof(int));
    for (int i = 0; i < count; i++) {
        result[i] = top3[i];
    }

    return result;
}
