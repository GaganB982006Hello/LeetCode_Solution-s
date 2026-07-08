/*
You are given a string s of length m consisting of digits. You are also given a 2D integer array queries, where queries[i] = [li, ri].

For each queries[i], extract the substring s[li..ri]. Then, perform the following:

Form a new integer x by concatenating all the non-zero digits from the substring in their original order. If there are no non-zero digits, x = 0.
Let sum be the sum of digits in x. The answer is x * sum.
Return an array of integers answer where answer[i] is the answer to the ith query.

Since the answers may be very large, return them modulo 109 + 7.

 

Example 1:

Input: s = "10203004", queries = [[0,7],[1,3],[4,6]]

Output: [12340, 4, 9]

Explanation:

s[0..7] = "10203004"
x = 1234
sum = 1 + 2 + 3 + 4 = 10
Therefore, answer is 1234 * 10 = 12340.
s[1..3] = "020"
x = 2
sum = 2
Therefore, the answer is 2 * 2 = 4.
s[4..6] = "300"
x = 3
sum = 3
Therefore, the answer is 3 * 3 = 9.
Example 2:

Input: s = "1000", queries = [[0,3],[1,1]]

Output: [1, 0]

Explanation:

s[0..3] = "1000"
x = 1
sum = 1
Therefore, the answer is 1 * 1 = 1.
s[1..1] = "0"
x = 0
sum = 0
Therefore, the answer is 0 * 0 = 0.
Example 3:

Input: s = "9876543210", queries = [[0,9]]

Output: [444444137]

Explanation:

s[0..9] = "9876543210"
x = 987654321
sum = 9 + 8 + 7 + 6 + 5 + 4 + 3 + 2 + 1 = 45
Therefore, the answer is 987654321 * 45 = 44444444445.
We return 44444444445 modulo (109 + 7) = 444444137.
 

Constraints:

1 <= m == s.length <= 105
s consists of digits only.
1 <= queries.length <= 105
queries[i] = [li, ri]
0 <= li <= ri < m
*/

class Solution {
    public int[] sumAndMultiply(String s, int[][] queries) {
        int MOD = 1000000007;
        int n = s.length();
        
        int[] orig_idx = new int[n];
        int[] v = new int[n];
        int k = 0;
        
        // Extract non-zero digits
        for (int i = 0; i < n; i++) {
            char c = s.charAt(i);
            if (c != '0') {
                orig_idx[k] = i;
                v[k] = c - '0';
                k++;
            }
        }
        
        long[] S = new long[k + 1];
        long[] P = new long[k + 1];
        long[] P10 = new long[k + 1];
        P10[0] = 1;
        
        for (int i = 0; i < k; i++) {
            S[i+1] = S[i] + v[i];
            P[i+1] = (P[i] * 10 + v[i]) % MOD;
            P10[i+1] = (P10[i] * 10) % MOD;
        }
        
        int[] ans = new int[queries.length];
        for (int q = 0; q < queries.length; q++) {
            int l = queries[q][0];
            int r = queries[q][1];
            
            int left_c = lowerBound(orig_idx, k, l);
            int right_c = upperBound(orig_idx, k, r) - 1;
            
            if (left_c > right_c) {
                ans[q] = 0;
            } else {
                int L = right_c - left_c + 1;
                long sum_val = S[right_c + 1] - S[left_c];
                
                long x = (P[right_c + 1] - (P[left_c] * P10[L]) % MOD) % MOD;
                if (x < 0) x += MOD;
                
                ans[q] = (int) ((x * sum_val) % MOD);
            }
        }
        return ans;
    }
    
    private int lowerBound(int[] arr, int len, int target) {
        int low = 0, high = len - 1, res = len;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (arr[mid] >= target) {
                res = mid;
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        return res;
    }
    
    private int upperBound(int[] arr, int len, int target) {
        int low = 0, high = len - 1, res = len;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (arr[mid] > target) {
                res = mid;
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        return res;
    }
}
