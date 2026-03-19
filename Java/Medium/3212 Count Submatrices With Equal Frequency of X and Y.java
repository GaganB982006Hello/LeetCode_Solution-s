class Solution {
    public int numberOfSubmatrices(char[][] grid) {
        int C = grid[0].length;
        int[] diff = new int[C];
        boolean[] hasX = new boolean[C];
        int count = 0;
        
        // Iterate directly over rows to cache the 1D array reference
        for (char[] row : grid) {
            int rowDiff = 0;
            boolean rowHasX = false;
            
            for (int j = 0; j < C; j++) {
                char val = row[j];
                
                if (val == 'X') {
                    rowDiff++;
                    rowHasX = true;
                } else if (val == 'Y') {
                    rowDiff--;
                }
                
                // Update vertical prefix state
                diff[j] += rowDiff;
                
                // Once a column sees an 'X', it remains true
                if (rowHasX) {
                    hasX[j] = true;
                }
                
                // Check validity
                if (diff[j] == 0 && hasX[j]) {
                    count++;
                }
            }
        }
        return count;
    }
}
