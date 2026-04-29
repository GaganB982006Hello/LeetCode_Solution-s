'''
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
'''

from typing import List

class Solution:
    def maximumScore(self, grid: List[List[int]]) -> int:
        n = len(grid)
        # Precompute prefix sums for O(1) column range sums
        pref = [[0] * (n + 1) for _ in range(n)]
        for j in range(n):
            for i in range(n):
                pref[j][i + 1] = pref[j][i] + grid[i][j]

        def get_score(col, a, b):
            if a > b:
                return 0
            return pref[col][b + 1] - pref[col][a]

        # dp[p][c] = max score given h_{j-1} = p and h_j = c
        dp = [[-float('inf')] * (n + 1) for _ in range(n + 1)]
        for c in range(n + 1):
            dp[0][c] = 0

        for j in range(1, n + 1):
            next_dp = [[-float('inf')] * (n + 1) for _ in range(n + 1)]
            
            for p in range(n + 1):
                # Precompute prefix max for pp <= c
                pref_max = [-float('inf')] * (n + 1)
                pref_max[0] = dp[0][p]
                for pp in range(1, n + 1):
                    pref_max[pp] = max(pref_max[pp - 1], dp[pp][p])

                # Precompute suffix max for pp > c
                suff_max = [-float('inf')] * (n + 2)
                for pp in range(n, -1, -1):
                    val = dp[pp][p]
                    if val != -float('inf'):
                        val += get_score(j - 1, p, pp - 1)
                    suff_max[pp] = max(suff_max[pp + 1], val)

                # Compute next_dp[p][c]
                for c in range(n + 1):
                    opt1 = -float('inf')
                    if pref_max[c] != -float('inf'):
                        opt1 = pref_max[c] + get_score(j - 1, p, c - 1)
                    opt2 = suff_max[c + 1]
                    
                    next_dp[p][c] = max(opt1, opt2)
            
            dp = next_dp

        # Result is the max score evaluated where the dummy final column's height is 0
        ans = 0
        for p in range(n + 1):
            ans = max(ans, dp[p][0])
            
        return ans
