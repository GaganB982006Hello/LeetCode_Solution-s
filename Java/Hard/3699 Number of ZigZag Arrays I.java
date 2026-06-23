/*
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
*/

class Solution {
    public int zigZagArrays(int n, int l, int r) {
        int m = r - l + 1;
        int MOD = 1000000007;
        
        int[] dp0 = new int[m + 2];
        int[] dp1 = new int[m + 2];
        
        for (int i = 1; i <= m; i++) {
            dp0[i] = 1;
            dp1[i] = 1;
        }
        
        for (int step = 2; step <= n; step++) {
            int[] new_dp0 = new int[m + 2];
            int[] new_dp1 = new int[m + 2];
            
            int[] pref = new int[m + 2];
            for (int x = 1; x <= m; x++) {
                pref[x] = (pref[x - 1] + dp1[x]) % MOD;
            }
            
            int[] suff = new int[m + 2];
            for (int x = m; x >= 1; x--) {
                suff[x] = (suff[x + 1] + dp0[x]) % MOD;
            }
            
            for (int y = 1; y <= m; y++) {
                new_dp0[y] = pref[y - 1];
                new_dp1[y] = suff[y + 1];
            }
            
            dp0 = new_dp0;
            dp1 = new_dp1;
        }
        
        long ans = 0;
        for (int x = 1; x <= m; x++) {
            ans = (ans + dp0[x]) % MOD;
            ans = (ans + dp1[x]) % MOD;
        }
        
        return (int) ans;
    }
}
