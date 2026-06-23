'''
You are given three integers n, l, and r.

A ZigZag array of length n is defined as follows:

Each element lies in the range [l, r].
No two adjacent elements are equal.
No three consecutive elements form a strictly increasing or strictly decreasing sequence.
Return the total number of valid ZigZag arrays.

Since the answer may be large, return it modulo 109 + 7.

A sequence is said to be strictly increasing if each element is strictly greater than its previous one (if exists).

A sequence is said to be strictly decreasing if each element is strictly smaller than its previous one (if exists).

 

Example 1:

Input: n = 3, l = 4, r = 5

Output: 2

Explanation:

There are only 2 valid ZigZag arrays of length n = 3 using values in the range [4, 5]:

[4, 5, 4]
[5, 4, 5]​​​​​​​
Example 2:

Input: n = 3, l = 1, r = 3

Output: 10

Explanation:

There are 10 valid ZigZag arrays of length n = 3 using values in the range [1, 3]:

[1, 2, 1], [1, 3, 1], [1, 3, 2]
[2, 1, 2], [2, 1, 3], [2, 3, 1], [2, 3, 2]
[3, 1, 2], [3, 1, 3], [3, 2, 3]
All arrays meet the ZigZag conditions.

 

Constraints:

3 <= n <= 2000
1 <= l < r <= 2000
'''

class Solution:
    def zigZagArrays(self, n: int, l: int, r: int) -> int:
        m = r - l + 1
        MOD = 10**9 + 7
        
        # dp0[x] tracks sequences ending at x that require the next step to be DOWN
        # dp1[x] tracks sequences ending at x that require the next step to be UP
        dp0 = [1] * (m + 2)
        dp1 = [1] * (m + 2)
        
        # Boundary elements to handle 1-based indexing easily
        dp0[0] = dp0[m + 1] = 0
        dp1[0] = dp1[m + 1] = 0
        
        for _ in range(2, n + 1):
            new_dp0 = [0] * (m + 2)
            new_dp1 = [0] * (m + 2)
            
            # Prefix sums of dp1
            pref = [0] * (m + 2)
            for x in range(1, m + 1):
                pref[x] = (pref[x - 1] + dp1[x]) % MOD
                
            # Suffix sums of dp0
            suff = [0] * (m + 2)
            for x in range(m, 0, -1):
                suff[x] = (suff[x + 1] + dp0[x]) % MOD
                
            for y in range(1, m + 1):
                new_dp0[y] = pref[y - 1]      # Sum of dp1[x] for x < y
                new_dp1[y] = suff[y + 1]      # Sum of dp0[x] for x > y
                
            dp0 = new_dp0
            dp1 = new_dp1
            
        ans = 0
        for x in range(1, m + 1):
            ans = (ans + dp0[x] + dp1[x]) % MOD
            
        return ans
