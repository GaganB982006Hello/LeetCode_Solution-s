/*
You are given a 2D integer grid of size m x n and an integer x. In one operation, you can add x to or subtract x from any element in the grid.

A uni-value grid is a grid where all the elements of it are equal.

Return the minimum number of operations to make the grid uni-value. If it is not possible, return -1.

 

Example 1:


Input: grid = [[2,4],[6,8]], x = 2
Output: 4
Explanation: We can make every element equal to 4 by doing the following: 
- Add x to 2 once.
- Subtract x from 6 once.
- Subtract x from 8 twice.
A total of 4 operations were used.
Example 2:


Input: grid = [[1,5],[2,3]], x = 1
Output: 5
Explanation: We can make every element equal to 3.
Example 3:


Input: grid = [[1,2],[3,4]], x = 2
Output: -1
Explanation: It is impossible to make every element equal.
 

Constraints:

m == grid.length
n == grid[i].length
1 <= m, n <= 105
1 <= m * n <= 105
1 <= x, grid[i][j] <= 104
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Comparison function for qsort
int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int minOperations(int** grid, int gridSize, int* gridColSize, int x) {
    int m = gridSize;
    int n = gridColSize[0];
    int totalElements = m * n;
    
    // Allocate memory for a 1D array to store all elements
    int* nums = (int*)malloc(totalElements * sizeof(int));
    int index = 0;
    
    // Flatten the grid and check if a solution is possible
    int targetRemainder = grid[0][0] % x;
    
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] % x != targetRemainder) {
                free(nums);
                return -1; // Impossible to make them equal
            }
            nums[index++] = grid[i][j];
        }
    }
    
    // Sort the array to find the median
    qsort(nums, totalElements, sizeof(int), compare);
    
    // The median is the best value to minimize absolute differences
    int median = nums[totalElements / 2];
    int operations = 0;
    
    for (int i = 0; i < totalElements; i++) {
        operations += abs(nums[i] - median) / x;
    }
    
    free(nums);
    return operations;
}
