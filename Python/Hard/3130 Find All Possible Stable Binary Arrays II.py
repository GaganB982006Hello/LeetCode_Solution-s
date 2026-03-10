class Solution:
    def numberOfStableArrays(self, zero: int, one: int, limit: int) -> int:
        MOD = 10**9 + 7
        
        # dp[i][j][0] = number of stable arrays with i zeros, j ones, ending in 0
        # dp[i][j][1] = number of stable arrays with i zeros, j ones, ending in 1
        dp = [[[0, 0] for _ in range(one + 1)] for _ in range(zero + 1)]
        
        # Base case: arrays containing only zeros
        for i in range(1, min(zero, limit) + 1):
            dp[i][0][0] = 1
            
        # Base case: arrays containing only ones
        for j in range(1, min(one, limit) + 1):
            dp[0][j][1] = 1
            
        for i in range(1, zero + 1):
            for j in range(1, one + 1):
                
                # Calculate ways to append a 0
                dp[i][j][0] = (dp[i - 1][j][0] + dp[i - 1][j][1]) % MOD
                if i - limit - 1 >= 0:
                    # Subtract invalid configurations ending in limit + 1 zeros
                    dp[i][j][0] = (dp[i][j][0] - dp[i - limit - 1][j][1]) % MOD
                
                # Calculate ways to append a 1
                dp[i][j][1] = (dp[i][j - 1][0] + dp[i][j - 1][1]) % MOD
                if j - limit - 1 >= 0:
                    # Subtract invalid configurations ending in limit + 1 ones
                    dp[i][j][1] = (dp[i][j][1] - dp[i][j - limit - 1][0]) % MOD
                    
        # The answer is the sum of valid arrays ending in 0 and 1
        return (dp[zero][one][0] + dp[zero][one][1]) % MOD
