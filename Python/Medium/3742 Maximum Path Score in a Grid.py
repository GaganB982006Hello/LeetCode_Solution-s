'''
You are given an m x n grid where each cell contains one of the values 0, 1, or 2. You are also given an integer k.

You start from the top-left corner (0, 0) and want to reach the bottom-right corner (m - 1, n - 1) by moving only right or down.

Each cell contributes a specific score and incurs an associated cost, according to their cell values:

0: adds 0 to your score and costs 0.
1: adds 1 to your score and costs 1.
2: adds 2 to your score and costs 1. ​​​​​​​
Return the maximum score achievable without exceeding a total cost of k, or -1 if no valid path exists.

Note: If you reach the last cell but the total cost exceeds k, the path is invalid.

 

Example 1:

Input: grid = [[0, 1],[2, 0]], k = 1

Output: 2

Explanation:​​​​​​​

The optimal path is:

Cell	grid[i][j]	Score	Total
Score	Cost	Total
Cost
(0, 0)	0	0	0	0	0
(1, 0)	2	2	2	1	1
(1, 1)	0	0	2	0	1
Thus, the maximum possible score is 2.

Example 2:

Input: grid = [[0, 1],[1, 2]], k = 1

Output: -1

Explanation:

There is no path that reaches cell (1, 1)​​​​​​​ without exceeding cost k. Thus, the answer is -1.

 

Constraints:

1 <= m, n <= 200
0 <= k <= 103​​​​​​​
​​​​​​​grid[0][0] == 0
0 <= grid[i][j] <= 2
'''

class Solution:
    def maxPathScore(self, grid: list[list[int]], k: int) -> int:
        m, n = len(grid), len(grid[0])
        # dp[j][cost] = max score at column j with specific cost
        dp = [[-1] * (k + 1) for _ in range(n)]
        
        # Base case: start cell (0, 0)
        start_val = grid[0][0]
        start_cost = 1 if start_val > 0 else 0
        if start_cost <= k:
            dp[0][start_cost] = start_val
            
        for i in range(m):
            next_dp = [[-1] * (k + 1) for _ in range(n)]
            for j in range(n):
                val = grid[i][j]
                cost_inc = 1 if val > 0 else 0
                
                for c in range(k + 1):
                    # Initial cell (0,0) is handled by the base case
                    if i == 0 and j == 0:
                        if c == start_cost:
                            next_dp[j][c] = start_val
                        continue
                        
                    # Find max score from top or left
                    prev_max = -1
                    if i > 0:
                        prev_max = max(prev_max, dp[j][c])
                    if j > 0:
                        prev_max = max(prev_max, next_dp[j-1][c])
                    
                    # Update next state if we reached this cost
                    if prev_max != -1 and c + cost_inc <= k:
                        next_dp[j][c + cost_inc] = max(next_dp[j][c + cost_inc], prev_max + val)
            dp = next_dp
            
        ans = max(dp[n-1])
        return ans if ans != -1 else -1
