class Solution {
    public int[][] constructProductMatrix(int[][] grid) {
        int n = grid.length;
        int m = grid[0].length;
        int[][] p = new int[n][m];
        long runningProduct = 1;
        int mod = 12345;

        // Prefix Product
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                p[i][j] = (int) runningProduct;
                runningProduct = (runningProduct * (grid[i][j] % mod)) % mod;
            }
        }

        // Suffix Product
        runningProduct = 1;
        for (int i = n - 1; i >= 0; i--) {
            for (int j = m - 1; j >= 0; j--) {
                p[i][j] = (int) ((p[i][j] * runningProduct) % mod);
                runningProduct = (runningProduct * (grid[i][j] % mod)) % mod;
            }
        }

        return p;
    }
}
