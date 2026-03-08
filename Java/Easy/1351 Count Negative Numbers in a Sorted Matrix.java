class Solution {
    public int countNegatives(int[][] grid) {
        int m = grid.length;
        int n = grid[0].length;

        int row = m - 1;  // start from bottom-left
        int col = 0;
        int count = 0;

        while (row >= 0 && col < n) {
            if (grid[row][col] < 0) {
                // all elements from col to n-1 in this row are negative
                count += (n - col);
                row--;          // move up
            } else {
                col++;          // move right
            }
        }

        return count;
    }
}