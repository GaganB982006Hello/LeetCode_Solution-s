class Solution:
    def maxProductPath(self, grid: List[List[int]]) -> int:
        m, n = len(grid), len(grid[0])
        # dp_max[i][j] and dp_min[i][j] store the max/min product to reach (i, j)
        dp_max = [[0.0] * n for _ in range(m)]
        dp_min = [[0.0] * n for _ in range(m)]
        
        dp_max[0][0] = dp_min[0][0] = grid[0][0]
        
        # Initialize first row
        for j in range(1, n):
            dp_max[0][j] = dp_min[0][j] = dp_max[0][j-1] * grid[0][j]
            
        # Initialize first column
        for i in range(1, m):
            dp_max[i][0] = dp_min[i][0] = dp_max[i-1][0] * grid[i][0]
            
        for i in range(1, m):
            for j in range(1, n):
                choices = (
                    dp_max[i-1][j] * grid[i][j],
                    dp_min[i-1][j] * grid[i][j],
                    dp_max[i][j-1] * grid[i][j],
                    dp_min[i][j-1] * grid[i][j]
                )
                dp_max[i][j] = max(choices)
                dp_min[i][j] = min(choices)
        
        res = int(dp_max[m-1][n-1])
        return res % (10**9 + 7) if res >= 0 else -1
