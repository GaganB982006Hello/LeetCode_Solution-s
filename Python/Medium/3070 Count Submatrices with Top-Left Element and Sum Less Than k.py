class Solution:
    def countSubmatrices(self, grid: List[List[int]], k: int) -> int:
        m, n = len(grid), len(grid[0])
        count = 0
        
        for r in range(m):
            for c in range(n):
                if r > 0:
                    grid[r][c] += grid[r-1][c]
                if c > 0:
                    grid[r][c] += grid[r][c-1]
                if r > 0 and c > 0:
                    grid[r][c] -= grid[r-1][c-1]
                
                if grid[r][c] <= k:
                    count += 1
                else:
                    # Once a sum exceeds k, further elements in 
                    # this row will definitely exceed k.
                    break 
                    
        return count
