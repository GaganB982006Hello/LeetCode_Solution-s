class Solution {
    public int countSubmatrices(int[][] grid, int k) {
        int m = grid.length;
        int n = grid[0].length;
        int count = 0;
        int[][] prefixSum = new int[m][n];

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                int current = grid[i][j];
                if (i > 0) current += prefixSum[i - 1][j];
                if (j > 0) current += prefixSum[i][j - 1];
                if (i > 0 && j > 0) current -= prefixSum[i - 1][j - 1];
                
                if (current <= k) {
                    prefixSum[i][j] = current;
                    count++;
                } else {
                    // Optimization: if a row's prefix sum exceeds k, 
                    // elements further right in this row will also exceed k.
                    prefixSum[i][j] = k + 1; 
                }
            }
        }
        return count;
    }
}
