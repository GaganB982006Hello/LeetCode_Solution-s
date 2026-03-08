class Solution {
    public long maxProfit(int[] prices, int[] strategy, int k) {
        int n = prices.length;
        long[] s = new long[n + 1]; // prefix of original profit
        long[] t = new long[n + 1]; // prefix of prices

        for (int i = 0; i < n; i++) {
            s[i + 1] = s[i] + (long) prices[i] * strategy[i];
            t[i + 1] = t[i] + (long) prices[i];
        }

        long original = s[n];
        long bestDelta = 0L; // no modification is allowed (can be zero)

        for (int i = k - 1; i < n; i++) {
            int r = i;           // window right end
            int l = i - k + 1;   // window left end
            int mid = l + k / 2; // second half starts at mid

            // original profit on [l, r] is s[r+1] - s[l]
            long originalWindow = s[r + 1] - s[l];

            // new profit: first half [l, mid-1] -> 0, second half [mid, r] -> 1
            // sum of prices on [mid, r] is t[r+1] - t[mid]
            long newWindow = t[r + 1] - t[mid];

            long delta = newWindow - originalWindow;
            if (delta > bestDelta) {
                bestDelta = delta;
            }
        }

        return original + bestDelta;
    }
}