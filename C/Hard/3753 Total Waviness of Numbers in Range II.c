/*
You are given two integers num1 and num2 representing an inclusive range [num1, num2].

The waviness of a number is defined as the total count of its peaks and valleys:

A digit is a peak if it is strictly greater than both of its immediate neighbors.
A digit is a valley if it is strictly less than both of its immediate neighbors.
The first and last digits of a number cannot be peaks or valleys.
Any number with fewer than 3 digits has a waviness of 0.
Return the total sum of waviness for all numbers in the range [num1, num2].
 

Example 1:

Input: num1 = 120, num2 = 130

Output: 3

Explanation:

In the range [120, 130]:

120: middle digit 2 is a peak, waviness = 1.
121: middle digit 2 is a peak, waviness = 1.
130: middle digit 3 is a peak, waviness = 1.
All other numbers in the range have a waviness of 0.
Thus, total waviness is 1 + 1 + 1 = 3.

Example 2:

Input: num1 = 198, num2 = 202

Output: 3

Explanation:

In the range [198, 202]:

198: middle digit 9 is a peak, waviness = 1.
201: middle digit 0 is a valley, waviness = 1.
202: middle digit 0 is a valley, waviness = 1.
All other numbers in the range have a waviness of 0.
Thus, total waviness is 1 + 1 + 1 = 3.

Example 3:

Input: num1 = 4848, num2 = 4848

Output: 2

Explanation:

Number 4848: the second digit 8 is a peak, and the third digit 4 is a valley, giving a waviness of 2.

 

Constraints:

1 <= num1 <= num2 <= 1015​​​​​​​
  */

#include <stdio.h>
#include <string.h>

long long memoCount[20][2][2][11][11];
long long memoSum[20][2][2][11][11];
char s[20];
int n;

typedef struct {
    long long count;
    long long sum;
} Result;

Result dp(int idx, int tight, int isLz, int prev1, int prev2) {
    if (idx == n) {
        Result r = {1, 0};
        return r;
    }
    
    int p1 = prev1 + 1;
    int p2 = prev2 + 1;

    if (memoCount[idx][tight][isLz][p1][p2] != -1) {
        Result r = {memoCount[idx][tight][isLz][p1][p2], memoSum[idx][tight][isLz][p1][p2]};
        return r;
    }

    int limit = tight ? s[idx] - '0' : 9;
    long long totCount = 0;
    long long totSum = 0;

    for (int d = 0; d <= limit; d++) {
        int nxtTight = (tight && d == limit) ? 1 : 0;
        
        if (isLz) {
            if (d == 0) {
                Result res = dp(idx + 1, nxtTight, 1, -1, -1);
                totCount += res.count;
                totSum += res.sum;
            } else {
                Result res = dp(idx + 1, nxtTight, 0, d, -1);
                totCount += res.count;
                totSum += res.sum;
            }
        } else {
            int isWave = 0;
            if (prev1 != -1 && prev2 != -1) {
                if ((prev1 > prev2 && prev1 > d) || (prev1 < prev2 && prev1 < d)) {
                    isWave = 1;
                }
            }
            Result res = dp(idx + 1, nxtTight, 0, d, prev1);
            totCount += res.count;
            totSum += res.sum + res.count * isWave;
        }
    }

    memoCount[idx][tight][isLz][p1][p2] = totCount;
    memoSum[idx][tight][isLz][p1][p2] = totSum;
    Result r = {totCount, totSum};
    return r;
}

long long solve(long long num) {
    if (num < 0) return 0;
    sprintf(s, "%lld", num);
    n = strlen(s);
    memset(memoCount, -1, sizeof(memoCount));
    memset(memoSum, -1, sizeof(memoSum));
    return dp(0, 1, 1, -1, -1).sum;
}

long long totalWaviness(long long num1, long long num2) {
    return solve(num2) - solve(num1 - 1);
}
