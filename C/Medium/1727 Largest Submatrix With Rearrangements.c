#include <stdlib.h>
#include <math.h>

// Comparison function for qsort
int compare(const void *a, const void *b) {
    return (*(int*)b - *(int*)a); // Descending order
}

int largestSubmatrix(int** matrix, int matrixSize, int* matrixColSize) {
    int m = matrixSize;
    int n = matrixColSize[0];
    int maxArea = 0;

    // Step 1: Calculate consecutive heights
    for (int i = 1; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] == 1) {
                matrix[i][j] += matrix[i - 1][j];
            }
        }
    }

    // Step 2: Sort heights in each row and calculate area
    for (int i = 0; i < m; i++) {
        // We need a temporary row to sort so we don't break the height accumulation
        int* tempRow = (int*)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) tempRow[j] = matrix[i][j];
        
        qsort(tempRow, n, sizeof(int), compare);

        for (int j = 0; j < n; j++) {
            int area = tempRow[j] * (j + 1);
            if (area > maxArea) maxArea = area;
        }
        free(tempRow);
    }

    return maxArea;
}
