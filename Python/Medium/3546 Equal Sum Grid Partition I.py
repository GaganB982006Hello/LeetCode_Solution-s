class Solution:
    def canPartitionGrid(self, grid: List[List[int]]) -> bool:
        m, n = len(grid), len(grid[0])
        total_sum = sum(sum(row) for row in grid)
        
        if total_sum % 2 != 0:
            return False
        
        target = total_sum // 2
        
        # Check Horizontal Cuts
        current_row_sum = 0
        for i in range(m - 1):
            current_row_sum += sum(grid[i])
            if current_row_sum == target:
                return True
                
        # Check Vertical Cuts
        current_col_sum = 0
        for j in range(n - 1):
            for i in range(m):
                current_col_sum += grid[i][j]
            if current_col_sum == target:
                return True
                
        return False
