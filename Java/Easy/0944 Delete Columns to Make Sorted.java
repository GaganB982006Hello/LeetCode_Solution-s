class Solution {
    public int minDeletionSize(String[] strs) {
        int n = strs.length;
        int m = strs[0].length();
        int deletions = 0;

        // Iterate over each column
        for (int col = 0; col < m; col++) {
            // Check if this column is sorted (non-decreasing) down the rows
            for (int row = 1; row < n; row++) {
                if (strs[row].charAt(col) < strs[row - 1].charAt(col)) {
                    deletions++;
                    break; // No need to check further in this column
                }
            }
        }

        return deletions;
    }
}