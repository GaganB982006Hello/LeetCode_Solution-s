#include <stdbool.h>

bool canPartitionGrid(int** grid, int gridSize, int* gridColSize) {
    int m = gridSize;
    int n = gridColSize[0];
    long long totalSum = 0;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            totalSum += grid[i][j];
        }
    }

    if (totalSum % 2 != 0) return false;
    long long target = totalSum / 2;

    // Check Horizontal Cuts
    long long currentHeightSum = 0;
    for (int i = 0; i < m - 1; i++) {
        for (int j = 0; j < n; j++) {
            currentHeightSum += grid[i][j];
        }
        if (currentHeightSum == target) return true;
    }

    // Check Vertical Cuts
    long long currentWidthSum = 0;
    for (int j = 0; j < n - 1; j++) {
        for (int i = 0; i < m; i++) {
            currentWidthSum += grid[i][j];
        }
        if (currentWidthSum == target) return true;
    }

    return false;
}
