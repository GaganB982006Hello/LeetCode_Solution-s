class Solution {
    public int minDeletionSize(String[] strs) {
        int n = strs.length;
        int m = strs[0].length();

        // dp[j] = length of longest valid subsequence of columns ending at j
        int[] dp = new int[m];
        Arrays.fill(dp, 1);

        int best = 1;

        for (int j = 0; j < m; j++) {
            for (int i = 0; i < j; i++) {
                if (canFollow(strs, i, j)) {
                    dp[j] = Math.max(dp[j], dp[i] + 1);
                }
            }
            best = Math.max(best, dp[j]);
        }

        return m - best;
    }

    // Check if column j can come after column i for all rows
    private boolean canFollow(String[] strs, int i, int j) {
        for (String s : strs) {
            if (s.charAt(i) > s.charAt(j)) {
                return false;
            }
        }
        return true;
    }
}