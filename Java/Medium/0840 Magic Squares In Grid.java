class Solution {
    public int numMagicSquaresInside(int[][] grid) {
        int rows = grid.length;
        int cols = grid[0].length;
        if (rows < 3 || cols < 3) return 0;

        int count = 0;
        for (int r = 0; r <= rows - 3; r++) {
            for (int c = 0; c <= cols - 3; c++) {
                if (isMagic(grid, r, c)) {
                    count++;
                }
            }
        }
        return count;
    }

    private boolean isMagic(int[][] g, int r, int c) {
        // Center must be 5 in any 3x3 magic square using 1..9
        if (g[r + 1][c + 1] != 5) return false;

        // Check that all numbers are in [1,9] and distinct
        boolean[] seen = new boolean[10]; // indices 1..9
        for (int i = r; i < r + 3; i++) {
            for (int j = c; j < c + 3; j++) {
                int val = g[i][j];
                if (val < 1 || val > 9 || seen[val]) return false;
                seen[val] = true;
            }
        }

        // Each row, column, diagonal must sum to 15
        int s1 = g[r][c] + g[r][c+1] + g[r][c+2];
        int s2 = g[r+1][c] + g[r+1][c+1] + g[r+1][c+2];
        int s3 = g[r+2][c] + g[r+2][c+1] + g[r+2][c+2];
        if (s1 != 15 || s2 != 15 || s3 != 15) return false;

        int c1 = g[r][c] + g[r+1][c] + g[r+2][c];
        int c2 = g[r][c+1] + g[r+1][c+1] + g[r+2][c+1];
        int c3 = g[r][c+2] + g[r+1][c+2] + g[r+2][c+2];
        if (c1 != 15 || c2 != 15 || c3 != 15) return false;

        int d1 = g[r][c] + g[r+1][c+1] + g[r+2][c+2];
        int d2 = g[r][c+2] + g[r+1][c+1] + g[r+2][c];
        if (d1 != 15 || d2 != 15) return false;

        return true;
    }
}