class Solution:
    def constructProductMatrix(self, grid: List[List[int]]) -> List[List[int]]:
        n, m = len(grid), len(grid[0])
        p = [[0] * m for _ in range(n)]
        mod = 12345
        
        # Prefix Product
        running_prod = 1
        for i in range(n):
            for j in range(m):
                p[i][j] = running_prod
                running_prod = (running_prod * (grid[i][j] % mod)) % mod
                
        # Suffix Product
        running_prod = 1
        for i in range(n - 1, -1, -1):
            for j in range(m - 1, -1, -1):
                p[i][j] = (p[i][j] * running_prod) % mod
                running_prod = (running_prod * (grid[i][j] % mod)) % mod
                
        return p
