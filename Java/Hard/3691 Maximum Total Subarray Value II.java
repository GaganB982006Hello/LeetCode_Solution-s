/*
You are given an integer array nums of length n and an integer k.

You must select exactly k distinct non-empty subarrays nums[l..r] of nums. Subarrays may overlap, but the exact same subarray (same l and r) cannot be chosen more than once.

The value of a subarray nums[l..r] is defined as: max(nums[l..r]) - min(nums[l..r]).

The total value is the sum of the values of all chosen subarrays.

Return the maximum possible total value you can achieve.

 

Example 1:

Input: nums = [1,3,2], k = 2

Output: 4

Explanation:

One optimal approach is:

Choose nums[0..1] = [1, 3]. The maximum is 3 and the minimum is 1, giving a value of 3 - 1 = 2.
Choose nums[0..2] = [1, 3, 2]. The maximum is still 3 and the minimum is still 1, so the value is also 3 - 1 = 2.
Adding these gives 2 + 2 = 4.

Example 2:

Input: nums = [4,2,5,1], k = 3

Output: 12

Explanation:

One optimal approach is:

Choose nums[0..3] = [4, 2, 5, 1]. The maximum is 5 and the minimum is 1, giving a value of 5 - 1 = 4.
Choose nums[1..3] = [2, 5, 1]. The maximum is 5 and the minimum is 1, so the value is also 4.
Choose nums[2..3] = [5, 1]. The maximum is 5 and the minimum is 1, so the value is again 4.
Adding these gives 4 + 4 + 4 = 12.

 

Constraints:

1 <= n == nums.length <= 5 * 10​​​​​​​4
0 <= nums[i] <= 109
1 <= k <= min(105, n * (n + 1) / 2)
*/

import java.util.PriorityQueue;

class Solution {
    public long maxTotalValue(int[] nums, int k) {
        int n = nums.length;
        int log = 32 - Integer.numberOfLeadingZeros(n);
        int[][] maxSt = new int[n][log];
        int[][] minSt = new int[n][log];

        // Initialize sparse tables
        for (int i = 0; i < n; i++) {
            maxSt[i][0] = nums[i];
            minSt[i][0] = nums[i];
        }

        // Build sparse tables
        for (int j = 1; j < log; j++) {
            for (int i = 0; i + (1 << j) <= n; i++) {
                maxSt[i][j] = Math.max(maxSt[i][j - 1], maxSt[i + (1 << (j - 1))][j - 1]);
                minSt[i][j] = Math.min(minSt[i][j - 1], minSt[i + (1 << (j - 1))][j - 1]);
            }
        }

        // Max Heap storing {value, left_index, right_index}
        PriorityQueue<int[]> pq = new PriorityQueue<>((a, b) -> Integer.compare(b[0], a[0]));

        // Push the maximal valid subarrays starting from each index
        for (int i = 0; i < n; i++) {
            pq.offer(new int[]{getVal(i, n - 1, maxSt, minSt), i, n - 1});
        }

        long total = 0;
        
        // Greedily pick the top k combinations
        for (int i = 0; i < k; i++) {
            if (pq.isEmpty()) break;
            int[] top = pq.poll();
            total += top[0];
            int l = top[1];
            int r = top[2];
            
            // If the subarray can be shrunk from the right, calculate its new value and push
            if (r > l) {
                pq.offer(new int[]{getVal(l, r - 1, maxSt, minSt), l, r - 1});
            }
        }
        return total;
    }

    private int getVal(int l, int r, int[][] maxSt, int[][] minSt) {
        int len = r - l + 1;
        int j = 31 - Integer.numberOfLeadingZeros(len); // equivalent to floor(log2(len))
        int max = Math.max(maxSt[l][j], maxSt[r - (1 << j) + 1][j]);
        int min = Math.min(minSt[l][j], minSt[r - (1 << j) + 1][j]);
        return max - min;
    }
}
