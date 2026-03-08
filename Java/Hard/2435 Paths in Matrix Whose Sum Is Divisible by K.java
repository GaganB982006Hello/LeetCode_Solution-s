class Solution {
    public int numberOfPaths(int[][] grid, int k) {
        int m = grid.length;
        int n = grid[0].length;
        int mod = 1000000007;

        int[][][] dp = new int[m][n][k];
        dp[0][0][grid[0][0] % k] = 1;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                for (int rem = 0; rem < k; rem++) {
                    if (i > 0) {
                        int prevRem = (rem - grid[i][j] % k + k) % k;
                        dp[i][j][rem] = (dp[i][j][rem] + dp[i-1][j][prevRem]) % mod;
                    }
                    if (j > 0) {
                        int prevRem = (rem - grid[i][j] % k + k) % k;
                        dp[i][j][rem] = (dp[i][j][rem] + dp[i][j-1][prevRem]) % mod;
                    }
                }
            }
        }
        return dp[m-1][n-1][0];
    }
}
