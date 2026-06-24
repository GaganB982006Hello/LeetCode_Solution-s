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

#include <stdlib.h>

#define MOD 1000000007

// Helper function to multiply two flat 1D arrays simulating 2D matrices
void multiply(long long *A, long long *B, long long *res, int size) {
    long long *temp = calloc(size * size, sizeof(long long));
    
    for (int i = 0; i < size; ++i) {
        for (int k = 0; k < size; ++k) {
            if (A[i * size + k] != 0) {
                for (int j = 0; j < size; ++j) {
                    temp[i * size + j] = (temp[i * size + j] + A[i * size + k] * B[k * size + j]) % MOD;
                }
            }
        }
    }
    
    // Copy results back to the target matrix
    for (int i = 0; i < size * size; ++i) {
        res[i] = temp[i];
    }
    
    free(temp);
}

int zigZagArrays(int n, int l, int r) {
    int m = r - l + 1;
    if (n == 1) return m;
    
    int size = 2 * m;
    
    // Allocate memory for matrices
    long long *T = calloc(size * size, sizeof(long long));
    long long *res = calloc(size * size, sizeof(long long));
    long long *base = calloc(size * size, sizeof(long long));
    
    // Build Transition Matrix
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            if (i > j) T[(i + m) * size + j] = 1; // Down -> Up
            if (i < j) T[i * size + (j + m)] = 1; // Up -> Down
        }
    }
    
    // Setup Identity Matrix
    for (int i = 0; i < size; i++) {
        res[i * size + i] = 1;
    }
    
    // Setup Base matrix
    for (int i = 0; i < size * size; i++) {
        base[i] = T[i];
    }
    
    int p = n - 1;
    
    // Fast Matrix Exponentiation
    while (p > 0) {
        if (p % 2 == 1) {
            multiply(res, base, res, size);
        }
        multiply(base, base, base, size);
        p /= 2;
    }
    
    // Sum all paths
    long long total = 0;
    for (int i = 0; i < size * size; i++) {
        total = (total + res[i]) % MOD;
    }
    
    // Free allocated memory to prevent leaks
    free(T);
    free(res);
    free(base);
    
    return (int)total;
}
