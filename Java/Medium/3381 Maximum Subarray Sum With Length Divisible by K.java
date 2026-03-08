class Solution {
    public long maxSubarraySum(int[] nums, int k) {
        int n = nums.length;
        long prefixSum = 0;

        // minPrefix[r] = minimum prefix sum seen so far at indices i where i % k == r
        long[] minPrefix = new long[k];
        // Initialize with +infinity
        for (int i = 0; i < k; i++) {
            minPrefix[i] = Long.MAX_VALUE;
        }

        long maxSum = Long.MIN_VALUE;

        // We treat prefix index -1 as 0 with remainder 0 (no elements taken)
        minPrefix[0] = 0L;

        for (int i = 0; i < n; i++) {
            prefixSum += nums[i];

            int r = (i + 1) % k; // prefix index is i+1, so use (i+1) % k

            // First, use the best previous prefix with same remainder
            long candidate = prefixSum - minPrefix[r];
            if (minPrefix[r] != Long.MAX_VALUE) {
                maxSum = Math.max(maxSum, candidate);
            }

            // Then update the minimum prefix for this remainder
            if (prefixSum < minPrefix[r]) {
                minPrefix[r] = prefixSum;
            }
        }

        // There will always be at least one valid subarray, so maxSum is set
        return maxSum;
    }
}
