class Solution:
    def numberOfSubmatrices(self, grid: List[List[str]]) -> int:
        C = len(grid[0])
        diff = [0] * C
        has_x = [False] * C
        ans = 0
        
        for row in grid:
            row_diff = 0
            row_has_x = False
            
            for c, val in enumerate(row):
                if val == 'X':
                    row_diff += 1
                    row_has_x = True
                elif val == 'Y':
                    row_diff -= 1
                
                diff[c] += row_diff
                if row_has_x:
                    has_x[c] = True
                
                if diff[c] == 0 and has_x[c]:
                    ans += 1
                    
        return ans
