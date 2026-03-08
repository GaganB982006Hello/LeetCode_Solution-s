class Solution {
    public int countPartitions(int[] nums, int k) {
        final int MOD = 1_000_000_007;
        int n = nums.length;

        long[] dp = new long[n + 1];      // dp[i]: ways to partition nums[0..i-1]
        long[] pref = new long[n + 1];    // pref[i] = dp[0] + ... + dp[i]

        dp[0] = 1;
        pref[0] = 1;

        java.util.Deque<Integer> maxD = new java.util.ArrayDeque<>();
        java.util.Deque<Integer> minD = new java.util.ArrayDeque<>();

        int left = 0;

        for (int right = 0; right < n; right++) {
            int val = nums[right];

            // maintain max deque (decreasing)
            while (!maxD.isEmpty() && nums[maxD.peekLast()] <= val) {
                maxD.pollLast();
            }
            maxD.offerLast(right);

            // maintain min deque (increasing)
            while (!minD.isEmpty() && nums[minD.peekLast()] >= val) {
                minD.pollLast();
            }
            minD.offerLast(right);

            // shrink window until condition holds
            while (!maxD.isEmpty() && !minD.isEmpty()
                    && nums[maxD.peekFirst()] - nums[minD.peekFirst()] > k) {
                if (maxD.peekFirst() == left) maxD.pollFirst();
                if (minD.peekFirst() == left) minD.pollFirst();
                left++;
            }

            // now all segments ending at 'right' and starting in [left, right] are valid
            int r = right + 1;   // dp index for prefix ending at 'right'
            int l = left;        // dp index for first valid start

            long ways = (pref[r - 1] - (l > 0 ? pref[l - 1] : 0) + MOD) % MOD;

            dp[r] = ways;
            pref[r] = (pref[r - 1] + dp[r]) % MOD;
        }

        return (int) dp[n];
    }
}