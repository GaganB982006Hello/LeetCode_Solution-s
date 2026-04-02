class Solution {
    public int maximumAmount(int[][] coins) {
        int m = coins.length;
        int n = coins[0].length;
        
        // dp[i][j][k] -> max coins at (i, j) with k neutralizations used
        // k can be 0, 1, or 2.
        int[][][] dp = new int[m][n][3];
        
        // Initialize with a very small value to handle negative coin paths
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < 3; k++) {
                    dp[i][j][k] = Integer.MIN_VALUE;
                }
            }
        }

        // Starting point (0, 0)
        dp[0][0][0] = coins[0][0];
        if (coins[0][0] < 0) {
            dp[0][0][1] = 0; // Use 1 neutralization
        }

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < 3; k++) {
                    if (dp[i][j][k] == Integer.MIN_VALUE) continue;

                    // Move Right
                    if (j + 1 < n) {
                        update(dp, i, j + 1, k, dp[i][j][k], coins[i][j + 1]);
                    }
                    
                    // Move Down
                    if (i + 1 < m) {
                        update(dp, i + 1, j, k, dp[i][j][k], coins[i + 1][j]);
                    }
                }
            }
        }

        // Return the max value from the bottom-right cell among all k options
        return Math.max(dp[m - 1][n - 1][0], Math.max(dp[m - 1][n - 1][1], dp[m - 1][n - 1][2]));
    }

    private void update(int[][][] dp, int r, int c, int k, int currentVal, int nextCoin) {
        // Option 1: Don't neutralize the next cell
        dp[r][c][k] = Math.max(dp[r][c][k], currentVal + nextCoin);
        
        // Option 2: Neutralize the next cell (if it's a robber and we have charges left)
        if (nextCoin < 0 && k + 1 < 3) {
            dp[r][c][k + 1] = Math.max(dp[r][c][k + 1], currentVal);
        }
    }
}
