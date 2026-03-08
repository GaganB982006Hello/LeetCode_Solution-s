class Solution {
    public long maximumProfit(int[] prices, int k) {  // <- name must be maximumProfit
        int n = prices.length;
        if (n == 0 || k == 0) return 0L;

        // f[i][t][s]:
        // i = day (0..n-1)
        // t = how many transactions have been COMPLETED so far (0..k)
        // s = 0: no position
        //     1: holding a long (bought, not yet sold)
        //     2: holding a short (sold, not yet bought back)
        long[][][] f = new long[n][k + 1][3];

        // Day 0 initialization
        for (int t = 0; t <= k; t++) {
            f[0][t][0] = 0;
            f[0][t][1] = -prices[0]; // open long
            f[0][t][2] = prices[0];  // open short
        }

        for (int i = 1; i < n; i++) {
            long price = prices[i];
            for (int t = 0; t <= k; t++) {
                // State 0: no position, after t completed transactions
                long stayFlat = f[i - 1][t][0];
                long closeLong = Long.MIN_VALUE;
                long closeShort = Long.MIN_VALUE;
                if (t > 0) {
                    // finish the t-th transaction today
                    closeLong = f[i - 1][t - 1][1] + price;  // sell long
                    closeShort = f[i - 1][t - 1][2] - price; // buy back short
                }
                f[i][t][0] = Math.max(stayFlat, Math.max(closeLong, closeShort));

                // State 1: holding a long, t transactions already completed
                long keepLong = f[i - 1][t][1];
                long openLong = f[i - 1][t][0] - price; // buy today
                f[i][t][1] = Math.max(keepLong, openLong);

                // State 2: holding a short, t transactions already completed
                long keepShort = f[i - 1][t][2];
                long openShort = f[i - 1][t][0] + price; // short sell today
                f[i][t][2] = Math.max(keepShort, openShort);
            }
        }

        long ans = 0;
        for (int t = 0; t <= k; t++) {
            ans = Math.max(ans, f[n - 1][t][0]);
        }
        return ans;
    }
}