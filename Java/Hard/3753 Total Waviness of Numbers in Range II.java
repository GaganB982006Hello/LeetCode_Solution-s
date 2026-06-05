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

class Solution {
    private long[][][][][] memoCount;
    private long[][][][][] memoSum;
    private String s;

    public long totalWaviness(long num1, long num2) {
        return solve(Long.toString(num2)) - solve(Long.toString(num1 - 1));
    }

    private long solve(String str) {
        if (str.equals("-1")) return 0;
        this.s = str;
        int n = str.length();
        
        // State: [idx][tight][isLeadingZero][prev1 + 1][prev2 + 1]
        memoCount = new long[n][2][2][11][11];
        memoSum = new long[n][2][2][11][11];
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < 2; j++) {
                for (int k = 0; k < 2; k++) {
                    for (int l = 0; l < 11; l++) {
                        for (int m = 0; m < 11; m++) {
                            memoCount[i][j][k][l][m] = -1;
                            memoSum[i][j][k][l][m] = -1;
                        }
                    }
                }
            }
        }
        return dp(0, 1, 1, -1, -1)[1];
    }

    private long[] dp(int idx, int tight, int isLz, int prev1, int prev2) {
        if (idx == s.length()) {
            return new long[]{1, 0}; // 1 valid number formed, 0 base waviness
        }
        
        int p1 = prev1 + 1;
        int p2 = prev2 + 1;

        if (memoCount[idx][tight][isLz][p1][p2] != -1) {
            return new long[]{memoCount[idx][tight][isLz][p1][p2], memoSum[idx][tight][isLz][p1][p2]};
        }

        int limit = tight == 1 ? s.charAt(idx) - '0' : 9;
        long totCount = 0;
        long totSum = 0;

        for (int d = 0; d <= limit; d++) {
            int nxtTight = (tight == 1 && d == limit) ? 1 : 0;
            
            if (isLz == 1) {
                if (d == 0) {
                    long[] res = dp(idx + 1, nxtTight, 1, -1, -1);
                    totCount += res[0];
                    totSum += res[1];
                } else {
                    long[] res = dp(idx + 1, nxtTight, 0, d, -1);
                    totCount += res[0];
                    totSum += res[1];
                }
            } else {
                int isWave = 0;
                if (prev1 != -1 && prev2 != -1) {
                    if ((prev1 > prev2 && prev1 > d) || (prev1 < prev2 && prev1 < d)) {
                        isWave = 1; // It's a peak or a valley
                    }
                }
                long[] res = dp(idx + 1, nxtTight, 0, d, prev1);
                totCount += res[0];
                totSum += res[1] + res[0] * isWave;
            }
        }

        memoCount[idx][tight][isLz][p1][p2] = totCount;
        memoSum[idx][tight][isLz][p1][p2] = totSum;
        return new long[]{totCount, totSum};
    }
}
