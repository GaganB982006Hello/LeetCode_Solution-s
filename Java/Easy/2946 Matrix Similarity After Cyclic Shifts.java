class Solution {
    public boolean areSimilar(int[][] mat, int k) {
        int m = mat.length;
        int n = mat[0].length;
        k %= n; // Optimization: k shifts is the same as k % n shifts
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                // Check if the element at j matches the element at its shifted position
                if (mat[i][j] != mat[i][(j + k) % n]) {
                    return false;
                }
            }
        }
        return true;
    }
}
