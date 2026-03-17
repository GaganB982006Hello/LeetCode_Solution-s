class Solution {
    public int largestSubmatrix(int[][] matrix) {
        int m = matrix.length;
        int n = matrix[0].length;
        int maxArea = 0;

        // Step 1: Calculate heights of consecutive 1s for each column
        for (int i = 1; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] == 1) {
                    matrix[i][j] += matrix[i - 1][j];
                }
            }
        }

        // Step 2: For each row, sort heights and calculate potential area
        for (int i = 0; i < m; i++) {
            int[] currRow = matrix[i].clone();
            Arrays.sort(currRow);
            
            for (int j = 0; j < n; j++) {
                // Width is (n - j), height is currRow[j]
                maxArea = Math.max(maxArea, currRow[j] * (n - j));
            }
        }

        return maxArea;
    }
}
