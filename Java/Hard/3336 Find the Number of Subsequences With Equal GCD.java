/*
You are given an integer array nums.

Your task is to find the number of pairs of non-empty subsequences (seq1, seq2) of nums that satisfy the following conditions:

The subsequences seq1 and seq2 are disjoint, meaning no index of nums is common between them.
The GCD of the elements of seq1 is equal to the GCD of the elements of seq2.
Return the total number of such pairs.

Since the answer may be very large, return it modulo 109 + 7.

 

Example 1:

Input: nums = [1,2,3,4]

Output: 10

Explanation:

The subsequence pairs which have the GCD of their elements equal to 1 are:

([1, 2, 3, 4], [1, 2, 3, 4])
([1, 2, 3, 4], [1, 2, 3, 4])
([1, 2, 3, 4], [1, 2, 3, 4])
([1, 2, 3, 4], [1, 2, 3, 4])
([1, 2, 3, 4], [1, 2, 3, 4])
([1, 2, 3, 4], [1, 2, 3, 4])
([1, 2, 3, 4], [1, 2, 3, 4])
([1, 2, 3, 4], [1, 2, 3, 4])
([1, 2, 3, 4], [1, 2, 3, 4])
([1, 2, 3, 4], [1, 2, 3, 4])
Example 2:

Input: nums = [10,20,30]

Output: 2

Explanation:

The subsequence pairs which have the GCD of their elements equal to 10 are:

([10, 20, 30], [10, 20, 30])
([10, 20, 30], [10, 20, 30])
Example 3:

Input: nums = [1,1,1,1]

Output: 50

 

Constraints:

1 <= nums.length <= 200
1 <= nums[i] <= 200
  */

import java.util.Arrays;

class Solution {
    private int[][][] memo;
    private int MOD = 1000000007;
    private int[] nums;

    public int subsequencePairCount(int[] nums) {
        this.nums = nums;
        int n = nums.length;
        
        // nums[i] <= 200, so the max GCD is 200. We allocate up to 201 (0 to 200)
        memo = new int[n][201][201];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j <= 200; j++) {
                Arrays.fill(memo[i][j], -1);
            }
        }
        
        return dp(0, 0, 0);
    }

    private int dp(int i, int g1, int g2) {
        if (i == nums.length) {
            return (g1 == g2 && g1 > 0) ? 1 : 0;
        }
        
        if (memo[i][g1][g2] != -1) {
            return memo[i][g1][g2];
        }
        
        long res = dp(i + 1, g1, g2); // Skip element
        res = (res + dp(i + 1, gcd(g1, nums[i]), g2)) % MOD; // Add to seq1
        res = (res + dp(i + 1, g1, gcd(g2, nums[i]))) % MOD; // Add to seq2
        
        return memo[i][g1][g2] = (int) res;
    }

    // Helper method to compute GCD (Euclidean algorithm)
    // Note: gcd(0, x) will return x, which elegantly handles empty sequences
    private int gcd(int a, int b) {
        if (a == 0) return b;
        return gcd(b % a, a);
    }
}
