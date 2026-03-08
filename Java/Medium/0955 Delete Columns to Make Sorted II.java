class Solution {
    public int minDeletionSize(String[] strs) {
        int n = strs.length;
        int m = strs[0].length();

        // fixed[i] == true means strs[i] < strs[i+1] is already determined
        boolean[] fixed = new boolean[n - 1];
        int deletions = 0;

        for (int col = 0; col < m; col++) {
            boolean needDelete = false;

            // Check if this column breaks lexicographic order
            for (int row = 0; row < n - 1; row++) {
                if (!fixed[row] && strs[row].charAt(col) > strs[row + 1].charAt(col)) {
                    needDelete = true;
                    break;
                }
            }

            if (needDelete) {
                deletions++;
                continue; // skip marking fixed for this column
            }

            // Column is kept, update which pairs become strictly increasing here
            for (int row = 0; row < n - 1; row++) {
                if (!fixed[row] && strs[row].charAt(col) < strs[row + 1].charAt(col)) {
                    fixed[row] = true;
                }
            }
        }

        return deletions;
    }
}