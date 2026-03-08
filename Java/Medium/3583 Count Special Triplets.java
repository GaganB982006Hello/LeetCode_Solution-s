import java.util.HashMap;
import java.util.Map;

class Solution {
    public int specialTriplets(int[] nums) {   // <- method name must be specialTriplets
        final long MOD = 1_000_000_007L;
        int n = nums.length;

        Map<Integer, Long> right = new HashMap<>();
        for (int x : nums) {
            right.put(x, right.getOrDefault(x, 0L) + 1);
        }

        Map<Integer, Long> left = new HashMap<>();
        long ans = 0L;

        for (int j = 0; j < n; j++) {
            int mid = nums[j];
            right.put(mid, right.get(mid) - 1);
            if (right.get(mid) == 0) {
                right.remove(mid);
            }

            long target = 2L * mid;
            long leftCount = left.getOrDefault((int) target, 0L);
            long rightCount = right.getOrDefault((int) target, 0L);

            ans = (ans + (leftCount * rightCount) % MOD) % MOD;

            left.put(mid, left.getOrDefault(mid, 0L) + 1);
        }

        return (int) ans;
    }
}