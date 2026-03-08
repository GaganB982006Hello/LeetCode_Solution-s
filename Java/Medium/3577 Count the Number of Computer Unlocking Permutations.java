class Solution {
    private static final int MOD = 1_000_000_007;

    public int countPermutations(int[] complexity) {
        int n = complexity.length;

        // Check feasibility: complexity[0] must be strictly smaller
        // than every other complexity[i] for i >= 1.
        int root = complexity[0];
        for (int i = 1; i < n; i++) {
            if (complexity[i] <= root) {
                return 0;
            }
        }

        // Compute (n - 1)! % MOD
        long fact = 1;
        for (int i = 2; i <= n - 1; i++) {
            fact = (fact * i) % MOD;
        }

        return (int) fact;
    }
}