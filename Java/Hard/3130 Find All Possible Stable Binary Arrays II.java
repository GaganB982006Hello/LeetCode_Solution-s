class Solution {
    public int numberOfStableArrays(int zero, int one, int limit) {
        int mod = 1_000_000_007;
        
        // dp[i][j][k] = number of stable arrays with i zeros, j ones, ending in k
        long[][][] dp = new long[zero + 1][one + 1][2];
        
        // Base case: arrays containing only zeros
        for (int i = 1; i <= Math.min(zero, limit); i++) {
            dp[i][0][0] = 1;
        }
        
        // Base case: arrays containing only ones
        for (int j = 1; j <= Math.min(one, limit); j++) {
            dp[0][j][1] = 1;
        }
        
        for (int i = 1; i <= zero; i++) {
            for (int j = 1; j <= one; j++) {
                
                // Calculate ways to append a 0
                dp[i][j][0] = (dp[i - 1][j][0] + dp[i - 1][j][1]) % mod;
                if (i - limit - 1 >= 0) {
                    // Subtract invalid configurations ending in limit + 1 zeros
                    dp[i][j][0] = (dp[i][j][0] - dp[i - limit - 1][j][1] + mod) % mod;
                }
                
                // Calculate ways to append a 1
                dp[i][j][1] = (dp[i][j - 1][0] + dp[i][j - 1][1]) % mod;
                if (j - limit - 1 >= 0) {
                    // Subtract invalid configurations ending in limit + 1 ones
                    dp[i][j][1] = (dp[i][j][1] - dp[i][j - limit - 1][0] + mod) % mod;
                }
            }
        }
        
        // The answer is the sum of valid arrays ending in 0 and 1
        return (int) ((dp[zero][one][0] + dp[zero][one][1]) % mod);
    }
}
