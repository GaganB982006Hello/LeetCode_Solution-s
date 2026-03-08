class Solution {
    public int countPartitions(int[] nums) {
        int total = 0;
        for (int x : nums) {
            total += x;
        }

        // If total sum is even, all n-1 partitions work; otherwise none.
        if (total % 2 == 0) {
            return nums.length - 1;
        } else {
            return 0;
        }
    }
}