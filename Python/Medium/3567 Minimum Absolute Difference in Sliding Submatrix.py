class Solution:
    def minAbsDiff(self, grid: List[List[int]], k: int) -> List[List[int]]:
        m, n = len(grid), len(grid[0])
        res = [[0] * (n - k + 1) for _ in range(m - k + 1)]
        
        for i in range(m - k + 1):
            for j in range(n - k + 1):
                # Extract the k x k submatrix
                sub = []
                for r in range(i, i + k):
                    sub.extend(grid[r][j : j + k])
                
                # Sort the flattened submatrix
                sub.sort()
                
                # Find the minimum absolute difference between distinct elements
                min_diff = float('inf')
                found = False
                for l in range(len(sub) - 1):
                    diff = sub[l + 1] - sub[l]
                    if diff > 0:
                        min_diff = min(min_diff, diff)
                        found = True
                
                res[i][j] = min_diff if found else 0
                
        return res
