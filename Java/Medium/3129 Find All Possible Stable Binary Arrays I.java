class Solution {
    public int numberOfStableArrays(int zero, int one, int limit) {
        int MOD = 1000000007;
        
        // dp[i][j][0] -> Ways to arrange i zeros and j ones, ending in 0
        // dp[i][j][1] -> Ways to arrange i zeros and j ones, ending in 1
        long[][][] dp = new long[zero + 1][one + 1][2];

        // Base cases: purely 0s or purely 1s up to the limit
        for (int i = 1; i <= Math.min(zero, limit); i++) {
            dp[i][0][0] = 1;
        }
        for (int j = 1; j <= Math.min(one, limit); j++) {
            dp[0][j][1] = 1;
        }

        // Fill the DP table
        for (int i = 1; i <= zero; i++) {
            for (int j = 1; j <= one; j++) {
                
                // Calculate ways to end with 0
                dp[i][j][0] = (dp[i - 1][j][0] + dp[i - 1][j][1]) % MOD;
                // Subtract invalid states that exceed the limit for 0s
                if (i > limit) {
                    dp[i][j][0] = (dp[i][j][0] - dp[i - limit - 1][j][1] + MOD) % MOD;
                }

                // Calculate ways to end with 1
                dp[i][j][1] = (dp[i][j - 1][0] + dp[i][j - 1][1]) % MOD;
                // Subtract invalid states that exceed the limit for 1s
                if (j > limit) {
                    dp[i][j][1] = (dp[i][j][1] - dp[i][j - limit - 1][0] + MOD) % MOD;
                }
            }
        }

        // The answer is the sum of valid arrays ending in 0 and ending in 1
        return (int) ((dp[zero][one][0] + dp[zero][one][1]) % MOD);
    }
}
