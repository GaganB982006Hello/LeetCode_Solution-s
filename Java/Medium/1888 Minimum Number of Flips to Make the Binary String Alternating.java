class Solution {
    public int minFlips(String s) {
        int n = s.length();
        String ss = s + s; // allow all rotations

        // build target alternating patterns for length 2n
        StringBuilder a = new StringBuilder();
        StringBuilder b = new StringBuilder();
        for (int i = 0; i < 2 * n; i++) {
            if ((i & 1) == 0) { // even index
                a.append('0');  // "0101..."
                b.append('1');  // "1010..."
            } else {
                a.append('1');
                b.append('0');
            }
        }

        int res = Integer.MAX_VALUE;
        int diffA = 0, diffB = 0;
        int left = 0;

        for (int right = 0; right < 2 * n; right++) {
            if (ss.charAt(right) != a.charAt(right)) diffA++;
            if (ss.charAt(right) != b.charAt(right)) diffB++;

            // maintain window size <= n (rotation length)
            if (right - left + 1 > n) {
                if (ss.charAt(left) != a.charAt(left)) diffA--;
                if (ss.charAt(left) != b.charAt(left)) diffB--;
                left++;
            }

            // when window size == n, it represents a valid rotation
            if (right - left + 1 == n) {
                res = Math.min(res, Math.min(diffA, diffB));
            }
        }

        return res;
    }
}
