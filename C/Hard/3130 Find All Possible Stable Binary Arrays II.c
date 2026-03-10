#include <stdlib.h>

int numberOfStableArrays(int zero, int one, int limit) {
    int MOD = 1000000007;
    
    // Allocate a flat 1D array on the heap to avoid stack overflow
    // Size required: (zero + 1) * (one + 1) * 2
    long long *dp = (long long *)calloc((zero + 1) * (one + 1) * 2, sizeof(long long));
    if (!dp) return 0; // Memory allocation fallback
    
    // Helper macro to simulate 3D array indexing: dp[i][j][k]
    #define DP(i, j, k) dp[((i) * (one + 1) + (j)) * 2 + (k)]
    
    // Base case: arrays containing only zeros
    int min_zero = (zero < limit) ? zero : limit;
    for (int i = 1; i <= min_zero; i++) {
        DP(i, 0, 0) = 1;
    }
    
    // Base case: arrays containing only ones
    int min_one = (one < limit) ? one : limit;
    for (int j = 1; j <= min_one; j++) {
        DP(0, j, 1) = 1;
    }
    
    for (int i = 1; i <= zero; i++) {
        for (int j = 1; j <= one; j++) {
            
            // Calculate ways to append a 0
            long long val0 = (DP(i - 1, j, 0) + DP(i - 1, j, 1)) % MOD;
            if (i - limit - 1 >= 0) {
                // Add MOD before modulo to prevent negative results in C
                val0 = (val0 - DP(i - limit - 1, j, 1) + MOD) % MOD;
            }
            DP(i, j, 0) = val0;
            
            // Calculate ways to append a 1
            long long val1 = (DP(i, j - 1, 0) + DP(i, j - 1, 1)) % MOD;
            if (j - limit - 1 >= 0) {
                val1 = (val1 - DP(i, j - limit - 1, 0) + MOD) % MOD;
            }
            DP(i, j, 1) = val1;
        }
    }
    
    int result = (DP(zero, one, 0) + DP(zero, one, 1)) % MOD;
    
    // Clean up heap memory
    free(dp);
    #undef DP
    
    return result;
}
