class Solution:
    def maximumAmount(self, coins: List[List[int]]) -> int:
        m, n = len(coins), len(coins[0])
        # dp[i][j][k] -> max coins at (i, j) with k neutralizations used
        # We use k = 0, 1, 2
        dp = [[[float('-inf')] * 3 for _ in range(n)] for _ in range(m)]
        
        # Base case: Starting point
        dp[0][0][0] = coins[0][0]
        if coins[0][0] < 0:
            dp[0][0][1] = 0 # Use first neutralization
            
        for i in range(m):
            for j in range(n):
                for k in range(3):
                    if dp[i][j][k] == float('-inf'):
                        continue
                    
                    # Possible moves: Right and Down
                    for di, dj in [(0, 1), (1, 0)]:
                        ni, nj = i + di, j + dj
                        
                        if ni < m and nj < n:
                            # Option 1: Don't neutralize the next cell
                            dp[ni][nj][k] = max(dp[ni][nj][k], dp[i][j][k] + coins[ni][nj])
                            
                            # Option 2: Neutralize the next cell if it's a robber
                            if k + 1 < 3 and coins[ni][nj] < 0:
                                dp[ni][nj][k+1] = max(dp[ni][nj][k+1], dp[i][j][k])
                                
        return max(dp[m-1][n-1])
