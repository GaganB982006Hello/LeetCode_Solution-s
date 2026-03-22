class Solution {
    public boolean findRotation(int[][] mat, int[][] target) {
        int n = mat.length;
        
        // Assume all 4 possible rotations could be valid initially
        boolean deg0 = true;
        boolean deg90 = true;
        boolean deg180 = true;
        boolean deg270 = true;
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                // Check 0 degrees (no rotation)
                if (mat[i][j] != target[i][j]) {
                    deg0 = false;
                }
                // Check 90 degrees clockwise
                if (mat[i][j] != target[j][n - 1 - i]) {
                    deg90 = false;
                }
                // Check 180 degrees
                if (mat[i][j] != target[n - 1 - i][n - 1 - j]) {
                    deg180 = false;
                }
                // Check 270 degrees clockwise
                if (mat[i][j] != target[n - 1 - j][i]) {
                    deg270 = false;
                }
            }
        }
        
        // If any of the rotations remain true, then it's a valid match
        return deg0 || deg90 || deg180 || deg270;
    }
}
