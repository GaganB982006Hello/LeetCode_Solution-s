class Solution {
    public String findDifferentBinaryString(String[] nums) {
        int n = nums.length;
        StringBuilder sb = new StringBuilder();

        // Build a string that differs from nums[i] at position i
        for (int i = 0; i < n; i++) {
            char c = nums[i].charAt(i);
            sb.append(c == '0' ? '1' : '0');
        }

        return sb.toString();
    }
}
