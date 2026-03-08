import java.util.HashMap;
import java.util.Map;

class Solution {
    public int[] twoSum(int[] nums, int target) {
        // Map from number value -> its index
        Map<Integer, Integer> map = new HashMap<>();

        // One pass
        for (int i = 0; i < nums.length; i++) {
            int complement = target - nums[i];

            // If we have already seen the complement, we found the answer
            if (map.containsKey(complement)) {
                return new int[] { map.get(complement), i };
            }

            // Otherwise store current number and its index
            map.put(nums[i], i);
        }

        // According to the problem, there is exactly one solution,
        // so this line should never be reached.
        throw new IllegalArgumentException("No two sum solution");
    }
}
