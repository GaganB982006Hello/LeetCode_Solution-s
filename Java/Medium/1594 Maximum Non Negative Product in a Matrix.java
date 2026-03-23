class Solution {
    public int maxProductPath(int[][] grid) {
        int m = grid.length, n = grid[0].length;
        long[][] maxDP = new long[m][n];
        long[][] minDP = new long[m][n];
        
        maxDP[0][0] = minDP[0][0] = grid[0][0];
        
        for (int i = 1; i < m; i++) {
            maxDP[i][0] = minDP[i][0] = maxDP[i-1][0] * grid[i][0];
        }
        for (int j = 1; j < n; j++) {
            maxDP[0][j] = minDP[0][j] = maxDP[0][j-1] * grid[0][j];
        }
        
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                long a = maxDP[i-1][j] * grid[i][j];
                long b = minDP[i-1][j] * grid[i][j];
                long c = maxDP[i][j-1] * grid[i][j];
                long d = minDP[i][j-1] * grid[i][j];
                maxDP[i][j] = Math.max(Math.max(a, b), Math.max(c, d));
                minDP[i][j] = Math.min(Math.min(a, b), Math.min(c, d));
            }
        }
        
        long res = maxDP[m-1][n-1];
        return res < 0 ? -1 : (int) (res % 1000000007);
    }
}
