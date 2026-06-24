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
[5, 4, 5]
Example 2:

Input: n = 3, l = 1, r = 3

Output: 10

Explanation:

​​​​​​​There are 10 valid ZigZag arrays of length n = 3 using values in the range [1, 3]:

[1, 2, 1], [1, 3, 1], [1, 3, 2]
[2, 1, 2], [2, 1, 3], [2, 3, 1], [2, 3, 2]
[3, 1, 2], [3, 1, 3], [3, 2, 3]
All arrays meet the ZigZag conditions.

 

Constraints:

3 <= n <= 109
1 <= l < r <= 75​​​​​​​
*/

class Solution {
    public int zigZagArrays(int n, int l, int r) {
        int m = r - l + 1;
        if (n == 1) return m;
        
        int MOD = 1000000007;
        int size = 2 * m;
        
        // Build Transition Matrix
        long[][] T = new long[size][size];
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < m; j++) {
                if (i > j) T[i + m][j] = 1; // Down -> Up
                if (i < j) T[i][j + m] = 1; // Up -> Down
            }
        }
        
        // Identity Matrix
        long[][] res = new long[size][size];
        for (int i = 0; i < size; i++) {
            res[i][i] = 1;
        }
        
        int p = n - 1;
        long[][] base = T;
        
        // Fast Matrix Exponentiation
        while (p > 0) {
            if (p % 2 == 1) res = multiply(res, base, size, MOD);
            base = multiply(base, base, size, MOD);
            p /= 2;
        }
        
        // Sum all paths
        long total = 0;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                total = (total + res[i][j]) % MOD;
            }
        }
        
        return (int) total;
    }
    
    private long[][] multiply(long[][] A, long[][] B, int size, int MOD) {
        long[][] C = new long[size][size];
        for (int i = 0; i < size; i++) {
            for (int k = 0; k < size; k++) {
                if (A[i][k] != 0) {
                    for (int j = 0; j < size; j++) {
                        C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % MOD;
                    }
                }
            }
        }
        return C;
    }
}
