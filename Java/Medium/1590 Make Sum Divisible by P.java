import java.util.HashMap;
import java.util.Map;

class Solution {
    public int minSubarray(int[] nums, int p) {
        long total = 0;
        for (int x : nums) {
            total += x;
        }
        int rem = (int)(total % p);

        // Already divisible, remove empty subarray
        if (rem == 0) return 0;

        Map<Integer, Integer> last = new HashMap<>();
        last.put(0, -1); // prefix remainder 0 before starting
        int n = nums.length;
        int ans = n;
        int prefix = 0;

        for (int i = 0; i < n; i++) {
            prefix = (int)((prefix + (long)nums[i]) % p);
            // We need a previous prefix with remainder = (prefix - rem + p) % p
            int target = (prefix - rem + p) % p;
            if (last.containsKey(target)) {
                ans = Math.min(ans, i - last.get(target));
            }
            last.put(prefix, i);
        }

        // Cannot remove entire array
        return ans == n ? -1 : ans;
    }
}
