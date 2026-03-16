from typing import List

class Solution:
    def getBiggestThree(self, grid: List[List[int]]) -> List[int]:
        m, n = len(grid), len(grid[0])
        unique_sums = set()
        
        for i in range(m):
            for j in range(n):
                # sz represents the size/length of the rhombus edge
                sz = 0
                
                # Treat (i, j) as the LEFT corner. 
                # Check bounds: Bottom corner (i + sz), Top corner (i - sz), Right corner (j + 2*sz)
                while i + sz < m and i - sz >= 0 and j + 2 * sz < n:
                    if sz == 0:
                        unique_sums.add(grid[i][j])
                    else:
                        x, y = i, j
                        current_sum = 0
                        
                        # Go UP-RIGHT
                        for _ in range(sz):
                            x -= 1
                            y += 1
                            current_sum += grid[x][y]
                            
                        # Go DOWN-RIGHT
                        for _ in range(sz):
                            x += 1
                            y += 1
                            current_sum += grid[x][y]
                            
                        # Go DOWN-LEFT
                        for _ in range(sz):
                            x += 1
                            y -= 1
                            current_sum += grid[x][y]
                            
                        # Go UP-LEFT
                        for _ in range(sz):
                            x -= 1
                            y -= 1
                            current_sum += grid[x][y]
                            
                        unique_sums.add(current_sum)
                    
                    sz += 1
                    
        # Sort in descending order and return the top 3 distinct sums
        return sorted(list(unique_sums), reverse=True)[:3]
