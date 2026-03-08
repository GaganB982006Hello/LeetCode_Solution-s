import java.util.ArrayList;
import java.util.List;

class Solution {
    public List<Boolean> prefixesDivBy5(int[] nums) {
        List<Boolean> result = new ArrayList<>();
        int rem = 0;  // remainder modulo 5

        for (int bit : nums) {
            // shift left (multiply by 2), add current bit, and keep only remainder mod 5
            rem = ((rem << 1) | bit) % 5;
            result.add(rem == 0);
        }

        return result;
    }
}
