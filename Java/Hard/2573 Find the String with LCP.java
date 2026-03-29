class Solution {
    public String findTheString(int[][] lcp) {
        int n = lcp.length;
        int[] s = new int[n];
        int charValue = 1;

        for (int i = 0; i < n; i++) {
            if (s[i] > 0) continue;
            if (charValue > 26) return "";
            for (int j = i; j < n; j++) {
                if (lcp[i][j] > 0) {
                    s[j] = charValue;
                }
            }
            charValue++;
        }

        for (int i = n - 1; i >= 0; i--) {
            for (int j = n - 1; j >= 0; j--) {
                int expected = (s[i] == s[j]) ? 
                               (i == n - 1 || j == n - 1 ? 1 : 1 + lcp[i + 1][j + 1]) : 0;
                if (lcp[i][j] != expected) return "";
            }
        }

        StringBuilder sb = new StringBuilder();
        for (int v : s) sb.append((char) ('a' + v - 1));
        return sb.toString();
    }
}
