#include <stdio.h>

#define MOD 1000000007

long long maxVal(long long a, long long b) { return a > b ? a : b; }
long long minVal(long long a, long long b) { return a < b ? a : b; }

int maxProductPath(int** grid, int gridSizerow, int* gridSizecol) {
    int m = gridSizerow;
    int n = gridSizecol[0];
    
    // dp_max and dp_min tables to store the maximum and minimum products to reach (i, j)
    long long dp_max[m][n];
    long long dp_min[m][n];
    
    dp_max[0][0] = dp_min[0][0] = grid[0][0];
    
    // Initialize the first row
    for (int j = 1; j < n; j++) {
        dp_max[0][j] = dp_min[0][j] = dp_max[0][j - 1] * grid[0][j];
    }
    
    // Initialize the first column
    for (int i = 1; i < m; i++) {
        dp_max[i][0] = dp_min[i][0] = dp_max[i - 1][0] * grid[i][0];
    }
    
    // Fill the DP tables
    for (int i = 1; i < m; i++) {
        for (int j = 1; j < n; j++) {
            long long cur = grid[i][j];
            // Potential products from top or left
            long long a = dp_max[i - 1][j] * cur;
            long long b = dp_min[i - 1][j] * cur;
            long long c = dp_max[i][j - 1] * cur;
            long long d = dp_min[i][j - 1] * cur;
            
            dp_max[i][j] = maxVal(maxVal(a, b), maxVal(c, d));
            dp_min[i][j] = minVal(minVal(a, b), minVal(c, d));
        }
    }
    
    long long result = dp_max[m - 1][n - 1];
    
    // If the maximum product is negative, return -1 as per problem statement
    return (result < 0) ? -1 : (int)(result % MOD);
}
