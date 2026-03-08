class Solution {
    public int minOperations(int[] nums, int k) {
        long sum = 0;
        for (int x : nums) {
            sum += x;
        }
        return (int)(sum % k);
    }
}
