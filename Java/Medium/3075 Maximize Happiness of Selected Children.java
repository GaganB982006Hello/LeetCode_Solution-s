import java.util.Arrays;

class Solution {
    public long maximumHappinessSum(int[] happiness, int k) {
        // Sort in descending order
        Arrays.sort(happiness);
        int n = happiness.length;

        long ans = 0;
        long taken = 0; // number of children already selected

        // traverse from largest to smallest
        for (int i = n - 1; i >= 0 && k > 0; i--) {
            long val = happiness[i] - taken;
            if (val <= 0) {
                break; // further values will be even smaller
            }
            ans += val;
            taken++;
            k--;
        }

        return ans;
    }
}