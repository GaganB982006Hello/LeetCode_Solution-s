/*
You are given a 2D matrix grid of size n x n. Initially, all cells of the grid are colored white. In one operation, you can select any cell of indices (i, j), and color black all the cells of the jth column starting from the top row down to the ith row.

The grid score is the sum of all grid[i][j] such that cell (i, j) is white and it has a horizontally adjacent black cell.

Return the maximum score that can be achieved after some number of operations.

 

Example 1:

Input: grid = [[0,0,0,0,0],[0,0,3,0,0],[0,1,0,0,0],[5,0,0,3,0],[0,0,0,0,2]]

Output: 11

Explanation:


In the first operation, we color all cells in column 1 down to row 3, and in the second operation, we color all cells in column 4 down to the last row. The score of the resulting grid is grid[3][0] + grid[1][2] + grid[3][3] which is equal to 11.

Example 2:

Input: grid = [[10,9,0,0,15],[7,1,0,8,0],[5,20,0,11,0],[0,0,0,1,2],[8,12,1,10,3]]

Output: 94

Explanation:


We perform operations on 1, 2, and 3 down to rows 1, 4, and 0, respectively. The score of the resulting grid is grid[0][0] + grid[1][0] + grid[2][1] + grid[4][1] + grid[1][3] + grid[2][3] + grid[3][3] + grid[4][3] + grid[0][4] which is equal to 94.

 

Constraints:

1 <= n == grid.length <= 100
n == grid[i].length
0 <= grid[i][j] <= 109
*/

#include <stdlib.h>

long long maximumScore(int** grid, int gridSize, int* gridColSize) {
    int n = gridSize;
    long long pref[105][105] = {0};
    
    for (int j = 0; j < n; j++) {
        for (int i = 0; i < n; i++) {
            pref[j][i + 1] = pref[j][i] + grid[i][j];
        }
    }
    
    long long dp[105][105];
    long long next_dp[105][105];
    long long INF = 10000000000000000LL;
    
    for (int p = 0; p <= n; p++) {
        for (int c = 0; c <= n; c++) {
            dp[p][c] = -INF;
        }
    }
    for (int c = 0; c <= n; c++) {
        dp[0][c] = 0;
    }
    
    for (int j = 1; j <= n; j++) {
        for (int p = 0; p <= n; p++) {
            for (int c = 0; c <= n; c++) {
                next_dp[p][c] = -INF;
            }
        }
        
        for (int p = 0; p <= n; p++) {
            long long pref_max[105];
            pref_max[0] = dp[0][p];
            for (int pp = 1; pp <= n; pp++) {
                pref_max[pp] = pref_max[pp - 1] > dp[pp][p] ? pref_max[pp - 1] : dp[pp][p];
            }
            
            long long suff_max[105];
            suff_max[n + 1] = -INF;
            for (int pp = n; pp >= 0; pp--) {
                long long val = dp[pp][p];
                if (val != -INF) {
                    int b = pp - 1;
                    long long s = (p > b) ? 0 : pref[j - 1][b + 1] - pref[j - 1][p];
                    val += s;
                }
                suff_max[pp] = suff_max[pp + 1] > val ? suff_max[pp + 1] : val;
            }
            
            for (int c = 0; c <= n; c++) {
                long long opt1 = -INF;
                if (pref_max[c] != -INF) {
                    int b = c - 1;
                    long long s = (p > b) ? 0 : pref[j - 1][b + 1] - pref[j - 1][p];
                    opt1 = pref_max[c] + s;
                }
                long long opt2 = suff_max[c + 1];
                next_dp[p][c] = opt1 > opt2 ? opt1 : opt2;
            }
        }
        
        for (int p = 0; p <= n; p++) {
            for (int c = 0; c <= n; c++) {
                dp[p][c] = next_dp[p][c];
            }
        }
    }
    
    long long ans = 0;
    for (int p = 0; p <= n; p++) {
        if (dp[p][0] > ans) {
            ans = dp[p][0];
        }
    }
    
    return ans;
}
